---
layout: post
title: libvirt教程
categories: [libvirt]
description: libvirt教程
keywords: libvirt
---

virsh命令 
| 命令                                               | 说明                         | 备注                     |
| -------------------------------------------------- | ---------------------------- | ------------------------ |
| virsh list                                         | 列出运行中的虚拟机           |
| virsh list --all                                   | 列出所有define的虚拟机       |
| virsh define vm.xml                                | 根据vm.xml描述文件创建虚拟机 |
| virsh start [domain/id]                               | 开机                         |
| virsh shutdown [domain/id]                            | 关机                         |
| virsh reboot [domain/id]
| virsh destroy [domain/id]                             | 断电                         |
| virsh undefine [domain/id]                            | 删除虚拟机                   |
| virsh console [domain/id]| 连接虚拟机console |
| virsh set-user-password [domain/id] [user] [password] | 修改虚拟机root密码           | 需要安装qemu-guest-agent |


如果在openstack平台上创建虚拟机时要传入密码则安装cloud-init即可。

若想要通过virsh命令上修改虚拟机的密码则需要安装qemu-guest-agent

安装以及配置方法

 https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/Virtualization_Deployment_and_Administration_Guide/chap-QEMU_Guest_Agent.html



把镜像上传到openstack云平台（我是N版的Openstack)
```
openstack image create  centos7.3 --disk-format qcow2 --container-format bare --file  moban.qcow2 --property hw_qemu_guest_agent=yes  --public
```
or
```
glance image-create --progress --name 'centos7.3.raw' --container-format=bare --disk-format=raw --min-ram=1024 --property architecture=x86_64 --property os_distro=linux  --property os_version=7.3 --property vol_size=24 --property hw_qemu_guest_agent=yes --file centos7.3.raw
```



注意

务必设置property的hw_qemu_guest_agent=yes,否则libvert启动虚拟机时不会生成qemu-ga配置项导致虚拟机内部的qemu-ga由于找不到对应的虚拟串行字符设备而启动失败提示找不到channel。

创建完虚拟机后若忘记了虚拟机的密码则可以直接修改

```
virsh set-user-password <domain> <user> <password>
```


下面是关于基于agent的几个命令小操作。

1. 关闭/重启虚拟机

# virsh shutdown/reboot domain --mode=agent
virsh shutdown/reboot  默认的方式是使用ACPI--mode=acpi可省略没有安装ACPI 的Linux虚拟机和Windows 虚拟机并不响应virsh shutdown/reboot domain 指令。使用--mode=agent方式QEMU guest agent 可以保证虚拟机完成关机/重启动作。