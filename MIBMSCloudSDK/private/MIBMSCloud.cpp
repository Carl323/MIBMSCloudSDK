/*
This file is part of MIBMSCloudSystem Project.
MIBMSCloud.h/.cpp - The base code of connection and data transmission.
Copyright (c) 2021 SuYichen.
*/

#include "MIBMSCloud.h"
#include "Core.h"
#include "send_info.h"
#include "stdio.h"
#include "MethodsLibrary.h"


#ifdef CLIENT
client::client()
{
    ClientCore = new Core;
    user = 0;
    writing = 0;
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = SERVER_PORT;
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr.s_addr);//将字符串类型转换uint32_t
}

client::~client()
{
    delete ClientCore;
}

void client::init()
{
    int   Ret;
    WSADATA   wsaData;                        // 用于初始化套接字环境
                                              // 初始化WinSock环境
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSAStartup()   failed   with   error   %d\n", Ret);
        WSACleanup();

    }

    user = socket(AF_INET, SOCK_STREAM, 0);//采用ipv4,TCP传输
    if (user <= 0)
    {
        perror("establish client faild");
        printf("Error at socket(): %ld\n", WSAGetLastError());
        exit(1);
    };
    printf("establish succesfully\n");//创建成功
    //阻塞式的等待服务器连接
    if (connect(user, (const sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect to server faild");
        printf("Error at socket(): %ld\n", WSAGetLastError());
        exit(1);
    }
    printf("connect IP:%s  Port:%d  succesfully\n", SERVER_IP, SERVER_PORT);//创建成功
    sendhandler* SH = ClientCore->SHandler;
    jsonsendler*  JSender = SH->CreatANewSendTask();
    SH->AddNewValue_int(JSender, "MesType", 0);
    SH->AddNewValue_string(JSender, "ModuleName", "Door001");
    SH->SendJson(user, JSender);
}

void client::process()
{
    char recvbuf[1024];
    fd_set fdread, fedwrite;
    FD_ZERO(&fdread);//将fds清零
    FD_ZERO(&fedwrite);//将fds清零
    init();
    

    while (1)
    {
        FD_SET(user, &fdread);
        if (writing == 0) FD_SET(user, &fedwrite);

        struct timeval timeout = { 1,0 };//每个Select等待三秒
        switch (select(0, &fdread, &fedwrite, NULL, &timeout))
        {
        case -1:
        {
            //perror("select");
            printf("Error at socket(): %ld\n", WSAGetLastError());
            /*exit(1);*/
            break;
        }
        case 0:
        {
            //printf("select timeout......");
            break;
        }
        default:
        {
            if (FD_ISSET(user, &fdread))//则有读事件
            {
                int size = recv(user, recvbuf, sizeof(recvbuf) - 1, 0);
                if (size > 0)
                {
                    printf("server:%s\n", recvbuf);
                    memset(recvbuf, '\0', sizeof(recvbuf));
                    Handler* handler = new Handler;
                    handler->SetOwner(this);
                    send_info RecvCon = handler->MessageHandler(recvbuf);
                    handler->TaskDistributor(user, RecvCon);
                    Delay(1);
                }
                else if (size == 0)
                {
                    printf("server is closed\n");
                    exit(1);
                }
            }
            if (FD_ISSET(user, &fedwrite))
            {
                FD_ZERO(&fedwrite);//将fedwrite清零
                writing = 1;//表示正在写作
                //std::thread sendtask(bind(user,(SOCKADDR*)&serverAddr, sizeof(serverAddr)));
                //sendtask.detach();//将子线程和主进程分离且互相不影响
            }

            break;
        }
        }

    }

}
#endif

#ifdef SERVER
server::server()
{
    ServerCore = new Core;
    listener = 0;
    writing=0;
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = SERVER_PORT;
    printf("ServerIP:%s  ", SERVER_IP);
    printf("Port:%d\n",SERVER_PORT);
    inet_pton(AF_INET,SERVER_IP, &serverAddr.sin_addr.s_addr);//将字符串类型转换uint32_t
}
server::~server()
{
    delete ServerCore;
}
//初始化函数，功能创建监听套接字，绑定端口，并进行监听
void server::init()
{
    int   Ret;
    WSADATA   wsaData;                        // 用于初始化套接字环境
    // 初始化WinSock环境
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSAStartup()   failed   with   error   %d\n", Ret);
        WSACleanup();
    }


    listener = socket(AF_INET, SOCK_STREAM, 0);//采用ipv4,TCP传输
    if (listener == -1) { printf("Error at socket(): %ld\n", WSAGetLastError()); perror("listener failed"); exit(1); }
    printf("Listner创建成功\n");

    unsigned long ul = 1;
    if (ioctlsocket(listener, FIONBIO, (unsigned long*)&ul) == -1) { perror("ioctl failed"); exit(1); };
    ///////////////////////////////////////////////////////////////////
    //中间的参数绑定的地址如果是IPV4则是///////////////////
    //struct sockaddr_in {
    //  sa_family_t    sin_family; /* address family: AF_INET */
    //  in_port_t      sin_port;   /* port in network byte order */
    //  struct in_addr sin_addr;   /* internet address */
    //};
    //Internet address.
    //struct in_addr {
    //  uint32_t       s_addr;     /* address in network byte order */
    //}
    /////////////////////////////////////////////////////////////////
    if (bind(listener, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("bind error");
        exit(1);
    }
    if (listen(listener, 6) < 0) { perror("listen failed"); exit(1); };
    socnum.push_back(listener);//将监听套接字加入
}

void server::process()
{

    int mount = 0;
    fd_set fds;
    FD_ZERO(&fds);//将fds清零
    init();
    //下面就是不断的检查
    printf("监听服务启动\n");
    printf("--Powerd By MIBMSCloudSDK V%s--\n",SDKVersion);
    vector<int> SWD;
    while (1)
    {
        cout << "\n processing \n" << endl;
        mount = socnum.size();
        //将fds每次都重新赋值
        for (int i = 0; i < mount; ++i)
        {
            FD_SET(socnum[i], &fds);
        }

        struct timeval timeout = { 1,0 };//每个Select等待三秒
        switch (select(0, &fds, NULL, NULL, &timeout))
        {
        case -1:
        {
            perror("select\n");
            printf("Error at socket(): %ld\n", WSAGetLastError());
            printf("%d\n", mount);
            /*          for (int i = 0; i < mount; ++i)
                        {
                            printf("%d\n", socnum[i]);
                        }*/
            Sleep(1000);
            break;
        }
        case 0:
        {
            //printf("select timeout......");
            break;
        }
        default:
        {
            //将数组中的每一个套接字都和剩余的额套接字进行比较得到当前的任务
            for (int i = 0; i < mount; ++i)
            {
                //如果第一个套接字可读的消息。就要建立连接
                if (i == 0 && FD_ISSET(socnum[i], &fds))
                {
                    struct sockaddr_in client_address;
                    socklen_t client_addrLength = sizeof(struct sockaddr_in);
                    //返回一个用户的套接字
                    int clientfd = accept(listener, (struct sockaddr*)&client_address, &client_addrLength);
                    //添加用户，服务器上显示消息，并通知用户连接成功
                    socnum.push_back(clientfd);
                    char ID[1024];
                    sprintf_s(ID, "客户端ID: % d,", clientfd);
                    char buf[30] = "欢迎使用智能楼宇云服务！\n";
                    strcat_s(ID, buf);
                    send(clientfd, ID, sizeof(ID) - 1, 0);//减去最后一个'/0'
                }
                if (i != 0 && FD_ISSET(socnum[i], &fds))
                {
                    char buf[1024];
                    memset(buf, '\0', sizeof(buf));
                    int size = recv(socnum[i], buf, sizeof(buf) - 1, 0);
                    //检测是否断线
                    if (size == 0 || size == -1)
                    {
                        closesocket(socnum[i]);//先关闭这个套接字
                        cout << "\n模块 "+ ServerCore->FindModule(socnum[i]) +"  已注销" << endl;
                        //ServerCore->ModuleLogout(socnum[i]);//从业务中注销该ModuleClient
                        SWD.push_back(i);
                    }
                    //若是没有掉线
                    else
                    {
                        Handler *handler=new Handler;
                        handler->SetOwner(this);
                        send_info RecvCon=handler->MessageHandler(buf);
                        handler->TaskDistributor(socnum[i],RecvCon);
                        delete(handler);
                    }

                }
            }
            for (int X = 0; X < SWD.size(); X++)
            {
                FD_CLR(socnum[SWD[X]], &fds);//在列表列表中删除
                socnum.erase(socnum.begin() + SWD[X]);//在vector数组中删除
            }
            SWD.clear();
            break;
        }
        }


    }
}
void server::sendrebootmessage()
{

}
bool server::canrebootnow()
{
    return (ServerCore->IsBusy());
}
#endif
Handler::Handler()
{
#ifdef SERVER
    Ser = NULL;
#endif // SERVER
#ifdef CLIENT
    Cli = NULL;
#endif // CLIENT
}

Handler::~Handler()
{
}

send_info Handler::MessageHandler(char buf[1024])
{
    send_info clt;
    memset(&clt, 0, sizeof(clt));//清空结构体
    memcpy(&clt, buf, sizeof(clt));//把接收到的信息转换成结构体
    return clt;
}

void Handler::TaskDistributor(int Socket,send_info info)
{
    #ifdef SERVER
    Core* core = Ser->ServerCore;
    #endif // SERVER
    #ifdef CLIENT
    Core* core = Cli->ClientCore;
    #endif // CLIENT
    core->AddTask(Socket,info);
}

#ifdef SERVER
void Handler::SetOwner(server* Server)
{
    Ser = Server;
}
#endif

#ifdef CLIENT
void Handler::SetOwner(client* Client)
{
    Cli = Client;

}
#endif
