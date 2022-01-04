/*
This file is part of MIBMSCloudSystem Project.
MIBMSCloud.h/.cpp - The base code of connection and data transmission.
Copyright (c) 2021 SuYichen.
*/
#pragma once

#define SDKVersion "1.1.5"
#include "MIBMSCloudApp.h"
#include "Core.h"
#include "send_info.h"
#include "SClock.h"
#include "ScriptCodeInterface.h"
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
    void APIS_init();
    void process();
    void APIS_process();
    void sendrebootmessage();
    bool canrebootnow();
private:
    SOCKET listener;//客户端服务监听套接字
    SOCKET apilistener;//API服务监听套接字
    sockaddr_in  serverAddr;//IPV4的地址方式
    sockaddr_in  apiserverAddr;
    std::vector <SOCKET> socnum;//存放创建的套接字
    std::vector <SOCKET> socnum_AS;
    char* SERVER_IP;
    int SERVER_PORT;
    int API_SERVER_PORT;
    Control* ControlScript;
    SClock* clock;
};
#endif

#ifdef CLIENT
#define SERVER_PORT 9999
#define SERVER_IP "127.0.0.1"
class client
{
public:
    client();
    ~client();
    Core* ClientCore;
    void init();
    void process();
    int user;


private:
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
    void TaskDistributor(SOCKET client,char info[1024]);
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