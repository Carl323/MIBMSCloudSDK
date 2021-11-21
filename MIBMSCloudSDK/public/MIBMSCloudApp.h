/*
This file is part of MIBMSCloudSystem Project.
MIBMSCloudApp.h - MIBMSCloudSDK项目编译配置页
Copyright (c) 2021 SuYichen.
*/
#pragma once
//如果开发的是服务端，请去掉下一行的注释符号
#define SERVER

//如果开发的是客户端(终端)，请去掉下一行的注释符号
//#define CLIENT

//如果平台是WINDOWS,请去掉下一行的注释符号
#define WINDOWS

//如果平台是LINUX,请去掉下一行的注释符号
//#define LINUX

//服务器IP和端口配置
#define SERVER_IP "127.0.0.1"// 默认服务器端IP地址
#define SERVER_PORT 9999// 服务器端口号

//以下内容请勿更改否则会导致Core运行异常
#define GENERATE 0
#define COMMAND 1
#define INFOREPORT 2
#define ERRORREPORT 3
#define WARNINGREPORT 4
#define SDKVersion "1.0.3"
