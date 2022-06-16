# Tiny-WebServer
用C++实现的高性能WEB服务器，经过webbenchh压力测试可以实现上万的QPS

## 功能
* 利用IO复用技术Epoll与线程池实现多线程的Reactor高并发模型；
* 利用正则与状态机解析HTTP请求报文，实现处理静态资源的请求；
* 利用标准库容器封装char，实现自动增长的缓冲区；
* 基于小根堆实现的定时器，关闭超时的非活动连接；
* 利用单例模式与阻塞队列实现异步的日志系统，记录服务器运行状态；
* 利用RAII机制实现了数据库连接池，减少数据库连接建立与关闭的开销，同时实现了用户注册登录功能。

* 增加logsys,threadpool测试单元(todo: timer, sqlconnpool, httprequest, httpresponse) 

## 环境要求
* Linux
* C++14
* MySql

## 目录树
```
.
├── code           源代码
│   ├── buffer
│   ├── config
│   ├── http
│   ├── log
│   ├── timer
│   ├── pool
│   ├── server
│   └── main.cpp
├── test           单元测试
│   ├── Makefile
│   └── test.cpp
├── resources      静态资源
│   ├── index.html
│   ├── image
│   ├── video
│   ├── js
│   └── css
├── bin            可执行文件
│   └── server
├── log            日志文件
├── webbench-1.5   压力测试
├── build          
│   └── Makefile
├── Makefile
├── LICENSE
└── readme.md
```


## 项目启动
需要先配置好对应的数据库
```bash
// 建立yourdb库
create database yourdb;

// 创建user表
USE yourdb;
CREATE TABLE user(
    username char(50) NULL,
    password char(50) NULL
)ENGINE=InnoDB;

// 添加数据
INSERT INTO user(username, password) VALUES('name', 'password');
```

```bash
make
./bin/server
```

## 单元测试
```bash
cd test
make
./test
```

## 压力测试

```bash
cd webbench-1.5
make
```

```bash
./webbench-1.5/webbench -c 100 -t 10 http://ip:port/
./webbench-1.5/webbench -c 1000 -t 10 http://ip:port/
./webbench-1.5/webbench -c 5000 -t 10 http://ip:port/
./webbench-1.5/webbench -c 10000 -t 10 http://ip:port/
```

* 测试环境: Ubuntu:18.40 cpu:i5-8400 内存:12G 
* QPS 10000+

## TODO
* config配置
* 完善单元测试
* 实现循环缓冲区

## 庖丁解牛

- [C++ Linux轻量级WebServer（一）前言介绍](https://juejin.cn/post/7098659904721780749)
- [C++ Linux轻量级WebServer（二）并发模型](https://juejin.cn/post/7099035785613033509)
- [C++ Linux轻量级WebServer（三）解析请求](https://juejin.cn/post/7106108431395717128)
- [C++ Linux轻量级WebServer（四）超时连接](https://juejin.cn/post/7107831560769896461)
- [C++ Linux轻量级WebServer（五）日志系统](https://juejin.cn/post/7108553758753161230)
- [C++ Linux轻量级WebServer（六）压力测试](https://juejin.cn/post/7109690826422222862)

## 致谢

[@qinguoyi](https://github.com/qinguoyi/TinyWebServer)、[@markparticle](https://github.com/markparticle/WebServer/)

