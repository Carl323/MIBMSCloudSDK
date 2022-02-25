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
#include <INIOperation.h>
#include <datalocker.h>




server::server()
{
    ServerCore = new Core;
    listener = 0;
    apilistener = 0;
    CMyINI* p = new CMyINI();
    p->ReadINI("./Configs/ServerSettings.ini");
    std::string s_ip = p->GetValue("Network", "SERVER_IP");
    SERVER_IP = StringToChar(s_ip);
    cout << "��ǰ������IP:";
    cout << SERVER_IP << endl;
    std::string s_port = p->GetValue("Network", "SERVER_PORT");
    SERVER_PORT = atoi(s_port.c_str());
    cout << "��ǰ������Device�˿�:";
    cout << SERVER_PORT << endl;
    std::string apis_port = p->GetValue("Network", "API_SERVER_PORT");
    API_SERVER_PORT = atoi(apis_port.c_str());
    cout << "��ǰ������Client�˿�:";
    cout <<API_SERVER_PORT<<endl;
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = SERVER_PORT;
    apiserverAddr.sin_family = PF_INET;
    apiserverAddr.sin_port = API_SERVER_PORT;
    inet_pton(AF_INET,SERVER_IP, &serverAddr.sin_addr.s_addr);//���ַ�������ת��uint32_t
    inet_pton(AF_INET, SERVER_IP, &apiserverAddr.sin_addr.s_addr);
    
}
server::~server()
{
    delete ServerCore;
    
}
//��ʼ�����������ܴ��������׽��֣��󶨶˿ڣ������м���
void server::init()
{
    int   Ret;
    WSADATA   wsaData;                        // ���ڳ�ʼ���׽��ֻ���
    // ��ʼ��WinSock����
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSAStartup()   failed   with   error   %d\n", Ret);
        WSACleanup();
    }


    listener = socket(AF_INET, SOCK_STREAM, 0);//����ipv4,TCP����
    if (listener == -1) { printf("Error at socket(): %ld\n", WSAGetLastError()); perror("listener failed"); exit(1); }
    printf("Listner�����ɹ�\n");

    unsigned long ul = 1;
    if (ioctlsocket(listener, FIONBIO, (unsigned long*)&ul) == -1) { perror("ioctl failed"); exit(1); };
    ///////////////////////////////////////////////////////////////////
    //�м�Ĳ����󶨵ĵ�ַ�����IPV4����///////////////////
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
    socnum.push_back(listener);//�������׽��ּ���
}

void server::APIS_init()
{
    int   Ret;
    WSADATA   wsaData;                        // ���ڳ�ʼ���׽��ֻ���
    // ��ʼ��WinSock����
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSAStartup()   failed   with   error   %d\n", Ret);
        WSACleanup();
    }


    apilistener = socket(AF_INET, SOCK_STREAM, 0);//����ipv4,TCP����
    if (apilistener == -1) { printf("Error at socket(): %ld\n", WSAGetLastError()); perror("listener failed"); exit(1); }
    printf("Listner�����ɹ�\n");

    unsigned long ul = 1;
    if (ioctlsocket(apilistener, FIONBIO, (unsigned long*)&ul) == -1) { perror("ioctl failed"); exit(1); };
    ///////////////////////////////////////////////////////////////////
    //�м�Ĳ����󶨵ĵ�ַ�����IPV4����///////////////////
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
    if (bind(apilistener, (struct sockaddr*)&apiserverAddr, sizeof(apiserverAddr)) < 0)
    {
        perror("bind error");
        exit(1);
    }
    if (listen(apilistener, 6) < 0) { perror("listen failed"); exit(1); };
}

void server::process()
{

    int mount = 0;
    fd_set fds;
    FD_ZERO(&fds);//��fds����
    init();
    //������ǲ��ϵļ��
    printf("������������\n");
    SetColor(120, 20);
    printf("--Powerd By MIBMSCloudSDK V%s--\n",SDKVersion);
    SetColor(1,0);
    vector<int> SWD;
    while (1)
    {
        mount = int(socnum.size());
        //��fdsÿ�ζ����¸�ֵ
        for (int i = 0; i < mount; ++i)
        {
            FD_SET(socnum[i], &fds);
        }

        struct timeval timeout = { 0,50000 };//ÿ��Select�ȴ�����
        switch (select(0, &fds, NULL, NULL, &timeout))
        {
        case -1:
        {
            perror("select\n");
            printf("Error at socket(): %ld\n", WSAGetLastError());
            cout<<mount<<endl;
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
            //�������е�ÿһ���׽��ֶ���ʣ��Ķ��׽��ֽ��бȽϵõ���ǰ������
            for (int i = 0; i < mount; ++i)
            {
                //�����һ���׽��ֿɶ�����Ϣ����Ҫ��������
                if (i == 0 && FD_ISSET(socnum[i], &fds))
                {
                    struct sockaddr_in client_address;
                    socklen_t client_addrLength = sizeof(struct sockaddr_in);
                    //����һ���û����׽���
                    SOCKET clientfd = accept(listener, (struct sockaddr*)&client_address, &client_addrLength);
                    //����û�
                    socnum.push_back(clientfd);

                }
                else if (i != 0 && FD_ISSET(socnum[i], &fds))
                {
                    char buf[1024];
                    memset(buf, '\0', sizeof(buf));
                    int size = recv(socnum[i], buf, sizeof(buf) - 1, 0);
                    //����Ƿ����
                    if (size == 0 || size == -1)
                    {
                        closesocket(socnum[i]);//�ȹر�����׽���
                        ServerCore->ModuleLogout(socnum[i]);//��ҵ����ע����ModuleClient
                        SWD.push_back(i);
                    }
                    //����û�е���
                    else
                    {
                        Handler *handler=new Handler;
                        handler->SetOwner(this);
                        char NewBuf[1024];
                        //datalocker* unlocker = new datalocker;
                        //strcpy_s(NewBuf,unlocker->_unlock_data_char(buf));
                        strcpy_s(NewBuf,buf);
                        handler->TaskDistributor(socnum[i], NewBuf);
                        delete(handler);
                    }

                }
            }
            for (int X = 0; X < SWD.size(); X++)
            {
                FD_CLR(socnum[SWD[X]], &fds);//���б��б���ɾ��
                socnum.erase(socnum.begin() + SWD[X]);//��vector������ɾ��
            }
            SWD.clear();
            break;
        }
        }

    }
}
void server::APIS_process()
{

    int mount = 0;
    fd_set fds_AS;
    FD_ZERO(&fds_AS);//��fds����
    APIS_init();
    //������ǲ��ϵļ��
    printf("������������\n");
    SetColor(120, 20);
    printf("--Powerd By MIBMSCloudSDK V%s--\n", SDKVersion);
    SetColor(1, 0);
    vector<int> SWD;
    while (1)
    {
        mount = int(socnum_AS.size());
        //��fdsÿ�ζ����¸�ֵ
        for (int i = 0; i < mount; ++i)
        {
            FD_SET(socnum_AS[i], &fds_AS);
        }

        struct timeval timeout = { 0,50000 };//ÿ��Select�ȴ�����
        switch (select(0, &fds_AS, NULL, NULL, &timeout))
        {
        case -1:
        {
            perror("select\n");
            printf("Error at socket(): %ld\n", WSAGetLastError());
            cout << mount << endl;
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
            //�������е�ÿһ���׽��ֶ���ʣ��Ķ��׽��ֽ��бȽϵõ���ǰ������
            for (int i = 0; i < mount; ++i)
            {
                //�����һ���׽��ֿɶ�����Ϣ����Ҫ��������
                if (i == 0 && FD_ISSET(socnum_AS[i], &fds_AS))
                {
                    struct sockaddr_in client_address;
                    socklen_t client_addrLength = sizeof(struct sockaddr_in);
                    //����һ���û����׽���
                    SOCKET clientfd = accept(apilistener, (struct sockaddr*)&client_address, &client_addrLength);
                    //����û�
                    socnum_AS.push_back(clientfd);

                }
                else if (i != 0 && FD_ISSET(socnum_AS[i], &fds_AS))
                {
                    char buf[1024];
                    memset(buf, '\0', sizeof(buf));
                    int size = recv(socnum_AS[i], buf, sizeof(buf) - 1, 0);
                    //����Ƿ����
                    if (size == 0 || size == -1)
                    {
                        closesocket(socnum_AS[i]);//�ȹر�����׽���
                        //
                        SWD.push_back(i);
                    }
                    //����û�е���
                    else
                    {
                        //To Do
                    }

                }
            }
            for (int X = 0; X < SWD.size(); X++)
            {
                FD_CLR(socnum_AS[SWD[X]], &fds_AS);//���б��б���ɾ��
                socnum_AS.erase(socnum_AS.begin() + SWD[X]);//��vector������ɾ��
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
Handler::Handler()
{
    Ser = NULL;
}

Handler::~Handler()
{
}

send_info Handler::MessageHandler(char buf[1024])
{
    send_info clt;
    memset(&clt, 0, sizeof(clt));//��սṹ��
    memcpy(&clt, buf, sizeof(clt));//�ѽ��յ�����Ϣת���ɽṹ��
    return clt;
}

void Handler::TaskDistributor(SOCKET Socket,char info[1024])
{
    Core* core = Ser->ServerCore;
    core->AddTask(Socket,info);
}

void Handler::SetOwner(server* Server)
{
    Ser = Server;
}

