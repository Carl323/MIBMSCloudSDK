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


#include <conio.h>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <vector>

#ifdef WINDOWS
#include <winsock2.h> 
#include<ws2tcpip.h>//����socklen_t
#pragma comment(lib, "WS2_32")  // ���ӵ�WS2_32.lib
#endif

#ifdef LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>//����socklen_t
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
    SOCKET listener;//�ͻ��˷�������׽���
    SOCKET apilistener;//API��������׽���
    sockaddr_in  serverAddr;//IPV4�ĵ�ַ��ʽ
    sockaddr_in  apiserverAddr;
    std::vector <SOCKET> socnum;//��Ŵ������׽���
    std::vector <SOCKET> socnum_AS;
    char* SERVER_IP;
    int SERVER_PORT;
    int API_SERVER_PORT;

    
};
#endif


class Handler
{
public:
    Handler();
    ~Handler();
    send_info MessageHandler(char buf[1024]);
    void TaskDistributor(SOCKET client,char info[1024]);
    void SetOwner(server* Server);
private:
    server* Ser;
};