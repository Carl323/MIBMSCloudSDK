/*
This file is part of MIBMSCloudSystem Project.
MIBMSCloud.h/.cpp - The base code of connection and data transmission.
Copyright (c) 2021 SuYichen.
*/
#pragma once

#include "MIBMSCloudApp.h"
#include "Core.h"
#include "send_info.h"
#include <conio.h>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <vector>

#ifdef WINDOWS
#include <winsock2.h> 
#include<ws2tcpip.h>//定义socklen_t
#pragma comment(lib, "WS2_32")  // 链接到WS2_32.lib
#endif

#ifdef LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>//定义socklen_t
#endif



#ifdef SERVER
class server
{
public:
    server();
    ~server();
    Core* ServerCore;
    void init();
    void process();
    void sendata(int TargetClient, int MesType, char ModuleName[20], char sendbuf[1024]);
    void close(bool Forced);
    void sendrebootmessage();
    bool canrebootnow();
private:
    int listener;//监听套接字
    int writing;
    sockaddr_in  serverAddr;//IPV4的地址方式
    std::vector <int> socnum;//存放创建的套接字
};
#endif

#ifdef CLIENT
class client
{
public:
    client();
    ~client()
    Core* ClientCore;
    void init();
    void process();
    void sendata(int MesType,char ModuleName[20],char sendbuf[1024]);

private:
    int user;
    int writing;
    sockaddr_in  serverAddr;//IPV4的地址方式包括服务端地址族、服务端IP地址、服务端端口号
};
#endif

class Handler
{
public:
    Handler();
    ~Handler();
    send_info MessageHandler(char buf[1024]);
    void TaskDistributor(int client,send_info info);
    #ifdef SERVER
    void SetOwner(server* Server);
    #endif
    #ifdef CLIENT
    void SetOwner(client* Client);
    #endif
private:
    #ifdef SERVER
    server* Ser;
    #endif
    #ifdef CLIENT
    client* Cli;
    #endif
};