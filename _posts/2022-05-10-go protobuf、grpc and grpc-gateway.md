

# protocol buffer介绍  
protobuf是google开源的数据交换格式，它有两个必要组成部分：
- protocol compiler：协议编译器，用来编译 .proto 文件，它是用 C++ 写的，可以直接[ 下载 ](https://github.com/protocolbuffers/protobuf/releases)安装二进制使用，或者基于源码编译，由于是开源的，也可以基于代码进行修改和扩展。[ 代码库 ](https://github.com/protocolbuffers/protobuf)中有更详细的介绍。
- protobuf运行时：protobuf 支持多个语言，可以在下列相应的代码库中找到安装方法。  

| Language                             | Source                                                                         |
| ------------------------------------ | ------------------------------------------------------------------------------ |
| C++ (include C++ runtime and protoc) | [src](https://github.com/protocolbuffers/protobuf/blob/main/src)               |
| Java                                 | [java](https://github.com/protocolbuffers/protobuf/blob/main/java)             |
| Python                               | [python](https://github.com/protocolbuffers/protobuf/blob/main/python)         |
| Objective-C                          | [objectivec](https://github.com/protocolbuffers/protobuf/blob/main/objectivec) |
| C#                                   | [csharp](https://github.com/protocolbuffers/protobuf/blob/main/csharp)         |
| Ruby                                 | [ruby](https://github.com/protocolbuffers/protobuf/blob/main/ruby)             |
| Go                                   | [protocolbuffers/protobuf-go](https://github.com/protocolbuffers/protobuf-go)  |
| PHP                                  | [php](https://github.com/protocolbuffers/protobuf/blob/main/php)               |
| Dart                                 | [dart-lang/protobuf](https://github.com/dart-lang/protobuf)                    |



## 关于go protobuf运行时

go运行时包含两个主要版本，第二个版本提供更简单的API，支持protobuf反射和很多提升，推荐新的代码使用新版本。
- 第一个主要版本由[github.com/golang/protobuf](https://pkg.go.dev/mod/github.com/golang/protobuf)模块实现，具体介绍可查看前面链接中的官方文档。
- 第二个主要版本有[google.golang.org/protobuf](https://pkg.go.dev/mod/google.golang.org/protobuf)模块实现，提供了将prootbuf文件生成Go代码和Go语言序列化消息的运行时实现。它由两部分组成：
  - Code Gennerator：代码生成器 protoc-gen-go 是用来将.proto编译生成Go代码的 protoc 插件，它作为参数传递给 protoc ，具体方法参考[官方文档](https://developers.google.com/protocol-buffers/docs/reference/go-generated)。新版本的模块不支持service类型，需要单独安装grpc-go插件，具体方法参考[官方文档](https://grpc.io/docs/languages/go/quickstart/)。安装命令如下（Make sure that your  $GOBIN  is in your  $PATH ）
  	```
 	 go install google.golang.org/protobuf/cmd/protoc-gen-go@v1.28
 	```
  - Runtime library： protobuf 模块包含一组Go包，这些包构成了protobuf在Go中的运行时实现，提供了一组定义消息的接口和消息序列化的函数（如json，text等）。可以在[官方文档](https://pkg.go.dev/google.golang.org/protobuf#readme-package-index)中找到这些包。



> 很多教程里面使用了第一个版本的protobuf，但是没有做说明，导致读者看到和官方教程有很大出入而一脸懵，所以最好是看官方文档，两个版本一个比较明显的区别是：第一个版本protoc支持grpc的参数是下面这样的，带有 **plugins=grpc** 这个参数,因为第二个版本是直接用go-grpc这个参数，后续讲解都是使用第二个版本：
> ```
> protoc --go_out ./ --go_opt=plugins=grpc
> ```

## go protobuf实例
完整代码查看：[github](https://github.com/lxxxxxxxx/learn-code/tree/main/learn-go-protobuf/example1)
### protobuf文件

```proto
syntax = "proto3";
package person;
option go_package="./person";

enum Sex{
    MAN = 0;
    WOMAN = 1;
}

message Person{
    string name = 1;
    int32 age = 2;
    Sex sex = 3;
}
```
### 编译命令
```bash
protoc -I./pb --go_out=./person --go_opt=paths=source_relative ./pb/person.proto
```

### 使用
```go
package main

import (
	"fmt"

	pb "com.example.test/person"
	"google.golang.org/protobuf/proto"
)

func main() {
	p := pb.Person{
		Name: "jone",
		Age:  18,
		Sex:  pb.Sex_MAN,
	}
	fmt.Println("p : ", p.String())
	fmt.Println("p : ", "name:", p.GetName(), "age:", p.GetAge(), "sex:", p.GetSex())

	// 使用 google.golang.org/protobuf/proto 序列化和反序列化
	bytes, err := proto.Marshal(&p)
	if err != nil {
		panic(err)
	}
	var p2 pb.Person
	err = proto.Unmarshal(bytes, &p2)
	fmt.Println("p2 : ", "name:", p2.GetName(), "age:", p2.GetAge(), "sex:", p2.GetSex())
}

```




## 跨语言能力
protobuf支持在多个语言之间交换数据。其中 C++ /C# /JAVA /Kotlin /Objective-C /PHP /Python /Ruby 由protocol buffer编译器 protoc 直接支持。 Dart /Go 由google提供，以插件方式提供给 protoc 。  

其他语言不直接支持，但是可以使用第三方[github项目](https://github.com/protocolbuffers/protobuf/blob/main/docs/third_party.md)。




# grpc介绍
[官方文档](https://grpc.io/docs/what-is-grpc/introduction/)

RPC即远程过程调用(Remote procedure call)，它的客户端程序可以像在本地一样直接调用一个服务端的方法，这使得创建分布式应用和服务变得很简单。  
grpc是由google开源的一个高性能RPC框架，它使用 protobuf 语言作为IDL（接口定义语言，Interface define
 language）和底层数据交换格式。与许多 RPC 系统一样，gRPC 基于定义服务的思想，指定可以远程调用的方法及其参数和返回类型。在服务端，服务端实现这个接口并运行一个 gRPC 服务器来处理客户端调用。在客户端，客户端有一个存根（在某些语言中仅称为客户端），它提供与服务器相同的方法。

![grpc框架](https://grpc.io/img/landing-2.svg)

gRPC 客户端和服务器可以在各种环境中运行和相互通信，例如，你可以使用 Go、Python 或 Ruby 中的客户端轻松地在 Java 中创建 gRPC 服务器。后续主要介绍Go语言使用grpc。

## Go语言grpc
新版本的protoc不直接支持编译Go语言，需要单独安装插件，具体方法参考[官方文档](https://grpc.io/docs/languages/go/quickstart/)。
### 安装插件
 ```bash
$ go install google.golang.org/protobuf/cmd/protoc-gen-go@v1.28
$ go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@v1.2
```

# 编译命令
 ```bash
$ protoc -I. --go_out=. --go_opt=paths=source_relative \
    --go-grpc_out=. --go-grpc_opt=paths=source_relative \
    helloworld/helloworld.proto
```

### 编译命令参数

| 参数                              | 说明                                                                                                 |
| --------------------------------- | ---------------------------------------------------------------------------------------------------- |
| go_out=path                       | 指定go语言的protobuf编译结果输出路径，即xxx.pb.go的路径，加这个参数将加载protoc-gen-go插件           |
| go_opt=paths=source_relative      | go_out路径为相对路径                                                                                 |
| go-grpc_out=path                  | 指定go语言的protobuf serivce输出路径，即xxx_grpc.pb.go的路径，加这个参数将加载protoc-gen-go-grpc插件 |
| go-grpc_opt=paths=source_relative | go-grpc_out路径为相对路径                                                                            |
| I. 或--proto_path=path            | 指定依赖的.proto搜索路径，与gcc编译器的-I类似，若不指定，则默认为当前目录                            |
| helloworld/helloworld.proto       | 最后加上需要编译的文件名                                                                             |

### 生成的文件
- xxx.pb.go：包含用于填充、序列化和检索请求和响应消息类型的所有协议缓冲区代码。   

- xxx_grpc.pb.go：包含
  - proto文件service下定义的客户端可调用的方法的interface类型（或叫存根stub）。
  - proto文件service下定义的服务器需要实现的接口类型。


## 实例
实例用一个基本的操作演示了grpc的四种消息类型，一元消息，c->s流，s->c流，c<->s双向流，完整代码查看：[github](https://github.com/lxxxxxxxx/learn-code/tree/main/learn-go-grpc/example1)
### protobuf
```proto
syntax = "proto3";

option go_package="./pb";

import "google/protobuf/timestamp.proto";

enum EmployeeStatus{
    NORMAL = 0;
    NO_VACATION = 1;
    RESINGED = 2;
    RETIRED = 3;
}

message Employee{
    int32 id = 1;
    int32 no = 2;
    string name = 3;
    // float salary = 4;

    MonthSalary monthSalary = 5;
    EmployeeStatus status = 6;
    google.protobuf.Timestamp lastModified = 7;

    reserved 4;
    reserved "salary";
}

message MonthSalary{
    float basic = 1;
    float bonus = 2;
}

message GetByNoRequest{
    int32 no = 1;
}

message EmployeeResponse{
    Employee employee = 1;
}

message GetAllRequest{}

message AddPhotoRequest{
    bytes data = 1;
}

message AddPhotoResponse{
    bool isOk = 1;
}

message SaveEmployeeRequest{
    Employee employee = 1;
}

service EmployeeService{
    // 一元消息
    rpc GetByNo(GetByNoRequest) returns (EmployeeResponse);
    // server stream
    // 获取所有员工
    rpc GetAll(GetAllRequest) returns (stream EmployeeResponse);
    // client stream
    // 上传头像信息
    rpc AllPhoto(stream AddPhotoRequest) returns (AddPhotoResponse);
    // 双向stream
    // 上传employee信息
    rpc Save(SaveEmployeeRequest) returns (EmployeeResponse);
    rpc SaveAll(stream SaveEmployeeRequest) returns (stream EmployeeResponse);
}

```



### 编译命令
 ```bash
protoc -I. \
--go_out=../server/pb \
--go_out=../client/pb  \
--go_opt=paths=source_relative \
--go-grpc_out=../server/pb \
--go-grpc_out=../client/pb \
--go-grpc_opt=paths=source_relative \
messages.proto
```

### client
```go
package main

import (
	"context"
	"fmt"
	"io"
	"log"
	"os"
	"time"

	"github.com/lxxxxxxx/grpc-client/pb"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
	"google.golang.org/grpc/metadata"
	"google.golang.org/protobuf/types/known/timestamppb"
)

const port = ":5001"

func main() {
	creds, err := credentials.NewClientTLSFromFile("./keys/server.pem", "127.0.0.1")
	if err != nil {
		log.Fatalln(err.Error())
	}

	options := []grpc.DialOption{grpc.WithTransportCredentials(creds)}
	conn, err := grpc.Dial("localhost"+port, options...)
	if err != nil {
		log.Fatalln(err.Error())
	}
	defer conn.Close()

	// 和server不同的是，grpc会实现client的接口
	// 我们只需要调用这些接口取数据就可以
	client := pb.NewEmployeeServiceClient(conn)
	getByNo(client)
	getAll(client)
	addPhoto(client)
	saveAll(client)
}

func getByNo(client pb.EmployeeServiceClient) {
	res, err := client.GetByNo(context.Background(), &pb.GetByNoRequest{No: 1999})
	if err != nil {
		log.Fatalln(err.Error())
	}
	fmt.Println(res.Employee)
}

func getAll(client pb.EmployeeServiceClient) {
	stream, err := client.GetAll(context.Background(), &pb.GetAllRequest{})

	if err != nil {
		log.Fatalln(err.Error())
	}
	for {
		res, err := stream.Recv()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Fatalln(err.Error())
		}
		fmt.Println(res.Employee)
	}
}

func addPhoto(client pb.EmployeeServiceClient) {
	imgFile, err := os.Open("avatar.jpeg")
	if err != nil {
		log.Fatalln(err.Error())
	}
	defer imgFile.Close()

	md := metadata.New(map[string]string{"no": "1996"})
	context := context.Background()
	context = metadata.NewOutgoingContext(context, md)

	stream, err := client.AllPhoto(context)
	if err != nil {
		log.Fatalln(err.Error())
	}

	for {
		chunk := make([]byte, 32*1024)
		chunkSize, err := imgFile.Read(chunk)
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Fatalln("--- " + err.Error())
		}

		if chunkSize < len(chunk) {
			chunk = chunk[:chunkSize]
		}

		stream.Send(&pb.AddPhotoRequest{Data: chunk})

	}

	res, err := stream.CloseAndRecv()
	if err != nil {
		log.Fatalln("--- 1" + err.Error())
	}

	fmt.Println("add photo isok:", res.IsOk)
}

func saveAll(client pb.EmployeeServiceClient) {
	employees := []pb.Employee{
		{
			Id:   1,
			No:   23,
			Name: "lx",
			MonthSalary: &pb.MonthSalary{
				Basic: 200.0,
				Bonus: 23233.0,
			},
			Status: pb.EmployeeStatus_NORMAL,
			LastModified: &timestamppb.Timestamp{
				Seconds: time.Now().Unix(),
			},
		},
		{
			Id:   2,
			No:   23,
			Name: "wzz",
			MonthSalary: &pb.MonthSalary{
				Basic: 200.0,
				Bonus: 23233.0,
			},
			Status: pb.EmployeeStatus_NORMAL,
			LastModified: &timestamppb.Timestamp{
				Seconds: time.Now().Unix(),
			},
		},
	}

	stream, err := client.SaveAll(context.Background())
	if err != nil {
		log.Fatalln(err.Error())
	}

	finishChannel := make(chan struct{})
	go func() {
		for {
			res, err := stream.Recv()
			if err == io.EOF {
				finishChannel <- struct{}{}
				break
			}
			if err != nil {
				log.Fatalln(err.Error())
			}
			fmt.Println(res.Employee)
		}
	}()

	for _, e := range employees {
		err := stream.Send(&pb.SaveEmployeeRequest{Employee: &e})
		if err != nil {
			log.Fatalln(err.Error())
		}
	}
	stream.CloseSend()
	<-finishChannel
}

```


### server

```go
package main

// https://www.bilibili.com/video/BV1eE411T7GC?p=1

import (
	"context"
	"errors"
	"fmt"
	"io"
	"log"
	"net"
	"time"

	"github.com/lxxxxxxxx/grpc-server/pb"

	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
	"google.golang.org/grpc/metadata"
	"google.golang.org/protobuf/types/known/timestamppb"
)

const port = ":5001"

var employees = []pb.Employee{
	{
		Id:   1,
		No:   1999,
		Name: "Dave",
		MonthSalary: &pb.MonthSalary{
			Basic: 5000,
			Bonus: 1000,
		},
		Status: pb.EmployeeStatus_NORMAL,
		LastModified: &timestamppb.Timestamp{
			Seconds: time.Now().Unix(),
		},
	},
	{
		Id:   2,
		No:   1996,
		Name: "Lili",
		MonthSalary: &pb.MonthSalary{
			Basic: 6000,
			Bonus: 500,
		},
		Status: pb.EmployeeStatus_NORMAL,
		LastModified: &timestamppb.Timestamp{
			Seconds: time.Now().Unix(),
		},
	},
}

func main() {
	listen, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalln(err.Error())
	}
	creds, err := credentials.NewServerTLSFromFile("./keys/server.pem", "./keys/ca.key")
	if err != nil {
		log.Fatalln(err.Error())
	}
	options := []grpc.ServerOption{grpc.Creds(creds)}
	server := grpc.NewServer(options...)
	pb.RegisterEmployeeServiceServer(server, new(employeeService))

	log.Println("grpc server listening " + port)

	server.Serve(listen)

}

type employeeService struct {
	pb.UnimplementedEmployeeServiceServer
}

func (*employeeService) GetByNo(ctx context.Context, req *pb.GetByNoRequest) (*pb.EmployeeResponse, error) {
	for _, e := range employees {
		if e.No == req.No {
			fmt.Println("find employee no:", e.No)
			return &pb.EmployeeResponse{Employee: &e}, nil
		}
	}
	return nil, errors.New("employee not found")
}

func (*employeeService) GetAll(req *pb.GetAllRequest, stream pb.EmployeeService_GetAllServer) error {
	for _, e := range employees {
		stream.Send(&pb.EmployeeResponse{
			Employee: &e,
		})
		time.Sleep(time.Second)
	}
	return nil
}

func (*employeeService) AllPhoto(stream pb.EmployeeService_AllPhotoServer) error {
	md, ok := metadata.FromIncomingContext(stream.Context())
	if ok {
		fmt.Printf("Employee no:%s \n", md["no"][0])
	}

	img := []byte{}
	for {
		data, err := stream.Recv()
		if err == io.EOF {
			fmt.Printf("img size: %d\n", len(img))
			stream.SendAndClose(&pb.AddPhotoResponse{IsOk: true})
			return nil
		}
		if err != nil {
			log.Fatalln(err.Error())
			return err
		}

		fmt.Printf("recv size:%d \n", len(data.Data))
		img = append(img, data.Data...)
		time.Sleep(time.Millisecond * 500)
	}
	return errors.New("add photo failed.")
}

func (*employeeService) Save(ctx context.Context, req *pb.SaveEmployeeRequest) (*pb.EmployeeResponse, error) {
	for _, e := range employees {
		if e.No == req.Employee.No {
			fmt.Println("employee exist,no:", e.No)
			return &pb.EmployeeResponse{
				Employee: req.Employee,
			}, nil
		}
	}
	employees = append(employees, *req.Employee)

	return &pb.EmployeeResponse{
		Employee: req.Employee,
	}, nil
}
func (*employeeService) SaveAll(stream pb.EmployeeService_SaveAllServer) error {
	for {
		empReq, err := stream.Recv()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Fatalln(err.Error())
			return err
		}
		employees = append(employees, *empReq.Employee)
		stream.Send(&pb.EmployeeResponse{Employee: empReq.Employee})
	}

	for _, e := range employees {
		fmt.Println(e)
	}
	return nil
}

```


# grpc-gateway介绍
gRPC-Gateway 是一个[protoc的插件](https://github.com/protocolbuffers/protobuf/releases) (注意：protoc v3.0.0以上版本才支持)。它读取gRPC服务定义并生成反向代理服务器，将 RESTful JSON API 转换为 gRPC。此服务器是根据您的 gRPC 定义中的自定义选项生成的。

详细请参考[官方文档](https://grpc-ecosystem.github.io/grpc-gateway/)。gRPC-Gateway 可以同时提供 gRPC 和 RESTful 风格的API，从下图可以看出，可以直接使用http client通过RESTful API来请求服务，而不用grpc client，当然grpc服务也可以同时提供。

![gRPC-Gateway框架](https://grpc-ecosystem.github.io/grpc-gateway/assets/images/architecture_introduction_diagram.svg)


## 安装插件
使用如下命令安装protoc插件，安装之后将在$GOPATH/bin目录下有 protoc-gen-grpc-gateway 、 protoc-gen-openapiv2 、 protoc-gen-go 、 protoc-gen-go-grpc 四个工具。

其中 protoc-gen-go 用于编译go语言版本的protobuf， protoc-gen-go-grpc 用于编译go语言版本的grpc service，这两个工具在上面介绍proto-buf和grpc的时候已经安装过，是一样的。

protoc-gen-grpc-gateway 、 protoc-gen-openapiv2 两个工具才是真正与grpc-gateway相关的插件。
 ```bash
$ go install \
    github.com/grpc-ecosystem/grpc-gateway/v2/protoc-gen-grpc-gateway \
    github.com/grpc-ecosystem/grpc-gateway/v2/protoc-gen-openapiv2 \
    google.golang.org/protobuf/cmd/protoc-gen-go \
    google.golang.org/grpc/cmd/protoc-gen-go-grpc
```

## 使用实例

完整代码查看：[github](https://github.com/lxxxxxxxx/learn-code/tree/main/learn-go-grpc-gateway/example1)

### 定义protobuf
```proto
syntax="proto3";

package pb;

option go_package="./pb";

import "google/api/annotations.proto";

message StrMsg{
    string msg = 1;
}

service MyService{
    rpc Echo(StrMsg)returns(StrMsg){
        option(google.api.http)={
            get:"/echo"
        };
    }
}
```


### 编译命令
一个比较完整的编译脚本，包括环境安装等。
 ```bash
#!/usr/bin/env bash
set -eu

cd "$(dirname "$0")"

find . \( -type f  -name '*.pb.go' -o -name '*.pb.gw.go' -o -name '*.json' \) -exec rm -f {} +

export GO111MODULE="on"


go get \
    github.com/grpc-ecosystem/grpc-gateway/v2/protoc-gen-grpc-gateway \
    github.com/grpc-ecosystem/grpc-gateway/v2/protoc-gen-openapiv2 \
    google.golang.org/protobuf/cmd/protoc-gen-go \
    google.golang.org/grpc/cmd/protoc-gen-go-grpc


GW_ORIGIN_VERSION=v1.14.4
go get github.com/grpc-ecosystem/grpc-gateway@$GW_ORIGIN_VERSION

GOPATH=$(go env GOPATH)
ARGS="\
--proto_path=. \
--proto_path=$GOPATH/pkg/mod/github.com/grpc-ecosystem/grpc-gateway@$GW_ORIGIN_VERSION \
--proto_path=$GOPATH/pkg/mod/github.com/grpc-ecosystem/grpc-gateway@$GW_ORIGIN_VERSION/third_party/googleapis \
--go_out=. \
--go_opt=paths=source_relative \
--go-grpc_out=. \
--go-grpc_opt=paths=source_relative \
--grpc-gateway_opt=logtostderr=true \
--grpc-gateway_out=. \
--grpc-gateway_opt=paths=source_relative \
--grpc-gateway_opt=repeated_path_param_separator=ssv"

for dir in $(find . -name '*.proto' | xargs -I{} dirname {} | sort | uniq); do
    echo "building $dir/*.proto"
    protoc $ARGS $dir/*.proto
done
```

执行之后目录结构是这样的
```bash
.
├── go.mod
├── go.sum
├── main.go
└── pb
    ├── gen-go.sh
    ├── hello.pb.go
    ├── hello.pb.gw.go
    ├── hello.proto
    └── hello_grpc.pb.go
```


创建http服务

```go
package main

import (
	"context"
	"log"
	"net"
	"net/http"

	"github.com/grpc-ecosystem/grpc-gateway/v2/runtime"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"

	gw "com.example.test/pb"
)

type myServiceImpl struct {
	gw.UnimplementedMyServiceServer
}

func (*myServiceImpl) Echo(ctx context.Context, req *gw.StrMsg) (*gw.StrMsg, error) {
	log.Println("recv msg :" + req.Msg + ",resp : hello " + req.Msg)
	return &gw.StrMsg{Msg: "hello " + req.Msg}, nil
}

func main() {

	// 创建grpc服务
	s := grpc.NewServer()
	gw.RegisterMyServiceServer(s, &myServiceImpl{})
	lis, err := net.Listen("tcp", ":9099")
	if err != nil {
		panic(err)
	}

	log.Println("Serving gRPC on 0.0.0.0:9099...")
	go func() {
		if err := s.Serve(lis); err != nil {
			log.Fatalln("Failed to serve grpc, err:", err.Error())
		}
	}()

    // 创建http服务
	ctx := context.Background()
	ctx, cancel := context.WithCancel(ctx)

	defer cancel()

	mux := runtime.NewServeMux()
	opts := []grpc.DialOption{grpc.WithTransportCredentials(insecure.NewCredentials())}
	err = gw.RegisterMyServiceHandlerFromEndpoint(ctx, mux, "127.0.0.1:9099", opts)
	if err != nil {
		panic(err)
	}

	log.Println("Serving http on 0.0.0.0:8088...")
	http.ListenAndServe(":8088", mux)
}

```