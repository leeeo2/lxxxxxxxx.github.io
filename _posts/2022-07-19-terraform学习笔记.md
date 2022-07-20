---
layout: post
title: "terraform学习笔记"
subtitle: "erraform"
author: "技术菜鸟"
header-style: text
description: terraform学习笔记
---


参考文档：  
[Terrafomm入门](https://lonegunmanb.github.io/introduction-terraform/)  
[华为云terraform基础教程](https://support.huaweicloud.com/qs-terraform/index.html)

# Terraform简介
Terraform 是有HashiCorp公司开源的一种安全有效地构建、更改和版本控制基础设施的工具(基础架构自动化的编排工具)。它的目标是 "Write, Plan, and create Infrastructure as Code", 基础架构即代码。Terraform通过HasiCorp自研的HCL语言描述资源操作code，不需要在web上点点点，就可以对系列基础设施进行操作（比如：创建删除ECS实例）。相比于使用脚本来进行基础设置操作，Terraform的优势在于多云场景，它制定了一个标准的操作流程（通过sdk提供），实现这个标准的云厂商都可以通过terraform来操作其基础设施，这样客户就可以仅使用terraform一个工具就可以实现多个云厂商基础设施的操作。

> HashiCorp的产品线主要有 Nomad、**Consul**、Valut 以及 Terraform，另外还有 Vagrant 以及 Packer 两个开源工具，2020 年还推出了 Boundary 以及 Waypoint 两个新产品。

terraform由两个部分组成，一个terraform同名的二进制可执行程序，一个由云厂商（Provider）使用terraform-plugin sdk和自家sdk实现的插件，插件也是一个独立可执行程序，通过rpc与主程序同学。

插件可以上传到`https://registry.terraform.io/browse/providers`上，这样用户可以通过名称（如aws、alicloud等）直接下载到插件。


# Terraform 主程序安装
```bash
# ubuntu/debina
sudo apt-get install -y terraform 
# centos
sudo yum -y install terraform
# macos
brew tap hashicorp/tap
brew install hashicorp/tap/terraform
```


# Terraform 语法
terraform通过hcl语言定义基础设施的操作（目前也支持json），以下述为例，在一个空目录中创建一个main.tf文件，用于在ucloud云上创建一个ecs和一个eip，并创建一个ecs和eip的绑定关系。

```go
terraform {   // 定义terraform的版本和provider插件的版本
  required_version = "~>0.13.5"  
  required_providers {
    ucloud = {
      source  = "ucloud/ucloud"
      version = "~>1.22.0"
    }
  }
}

provider "ucloud" {  //定义provider的ak/sk/project/region信息
  public_key  = "JInqRnkSY8eAmxKFRxW9kVANYThg1pcvjD2Aw5f5p"
  private_key = "IlJn6GlmanYI1iDVEtrPyt5R9noAGz41B8q5TML7abqD8e4YjVdylwaKWdY61J5TcA"
  project_id  = "org-tgqbvi"
  region      = "cn-bj2"
}

data "ucloud_security_groups" "default" { //data关键字定义查询：根据插件定义的schema
  type = "recommend_web"
}

data "ucloud_images" "default" {
  availability_zone = "cn-bj2-04"
  name_regex        = "^CentOS 6.5 64"
  image_type        = "base"
}

resource "ucloud_instance" "web" { //resource关键字定义资源创建
  availability_zone = "cn-bj2-04"
  image_id          = data.ucloud_images.default.images[0].id
  instance_type     = "n-basic-2"
  root_password     = "supersecret1234"
  name              = "tf-example-instance"
  tag               = "tf-example"
  boot_disk_type    = "cloud_ssd"

  security_group = data.ucloud_security_groups.default.security_groups[0].id

  delete_disks_with_instance = true

  user_data = <<EOF
#!/bin/bash
yum install -y nginx
service nginx start
EOF
}

resource "ucloud_eip" "web-eip" {
  internet_type = "bgp"
  charge_mode   = "bandwidth"
  charge_type   = "dynamic"
  name          = "web-eip"
}

resource "ucloud_eip_association" "web-eip-association" {
  eip_id      = ucloud_eip.web-eip.id
  resource_id = ucloud_instance.web.id
}

output "eip" {
  value = ucloud_eip.web-eip.public_ip
}

```
这里的资源（resource）是一个抽象概念，不一定是ECS这样的实体才是资源，比如ecs和eip的绑定关系也可以是一个资源，创建这样一个资源后端的操作就是把对应的ecs和eip进行绑定。

# terraform基础操作

- 初始化
```bash
terraform init
```
如下命令进行初始化工作，将会在本地cache中搜索需要的插件，如果搜索不到，会从指定的terraform下载（官方仓库为：registry.terraform.io）

- 查看计划
```
terraform plan
```
将会列出该.tf文件定义内容将会有哪些操作。

- 执行计划
```
terraform apply
```
将执行具体操作，查询或创建，执行之后会在本地当前目录下创建terraform.tfstate文件来记录当前状态，该文件很重要，如果删除将会失去状态。

- 销毁
```
terraform destroy
```
将会销毁创建的资源，terraform.tfstate也会做相应改变。


