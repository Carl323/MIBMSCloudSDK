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
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr.s_addr);//���ַ�������ת��uint32_t
}

client::~client()
{
    delete ClientCore;
}

void client::init()
{
    int   Ret;
    WSADATA   wsaData;                        // ���ڳ�ʼ���׽��ֻ���
                                              // ��ʼ��WinSock����
    if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        printf("WSAStartup()   failed   with   error   %d\n", Ret);
        WSACleanup();

    }

    user = socket(AF_INET, SOCK_STREAM, 0);//����ipv4,TCP����
    if (user <= 0)
    {
        perror("establish client faild");
        printf("Error at socket(): %ld\n", WSAGetLastError());
        exit(1);
    };
    printf("establish succesfully\n");//�����ɹ�
    //����ʽ�ĵȴ�����������
    if (connect(user, (const sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect to server faild");
        printf("Error at socket(): %ld\n", WSAGetLastError());
        exit(1);
    }
    printf("connect IP:%s  Port:%d  succesfully\n", SERVER_IP, SERVER_PORT);//�����ɹ�
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
    FD_ZERO(&fdread);//��fds����
    FD_ZERO(&fedwrite);//��fds����
    init();
    

    while (1)
    {
        FD_SET(user, &fdread);
        if (writing == 0) FD_SET(user, &fedwrite);

        struct timeval timeout = { 1,0 };//ÿ��Select�ȴ�����
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
            if (FD_ISSET(user, &fdread))//���ж��¼�
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
                FD_ZERO(&fedwrite);//��fedwrite����
                writing = 1;//��ʾ����д��
                //std::thread sendtask(bind(user,(SOCKADDR*)&serverAddr, sizeof(serverAddr)));
                //sendtask.detach();//�����̺߳������̷����һ��಻Ӱ��
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
    inet_pton(AF_INET,SERVER_IP, &serverAddr.sin_addr.s_addr);//���ַ�������ת��uint32_t
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

void server::process()
{

    int mount = 0;
    fd_set fds;
    FD_ZERO(&fds);//��fds����
    init();
    //������ǲ��ϵļ��
    printf("������������\n");
    printf("--Powerd By MIBMSCloudSDK V%s--\n",SDKVersion);
    vector<int> SWD;
    while (1)
    {
        cout << "\n processing \n" << endl;
        mount = socnum.size();
        //��fdsÿ�ζ����¸�ֵ
        for (int i = 0; i < mount; ++i)
        {
            FD_SET(socnum[i], &fds);
        }

        struct timeval timeout = { 1,0 };//ÿ��Select�ȴ�����
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
            //�������е�ÿһ���׽��ֶ���ʣ��Ķ��׽��ֽ��бȽϵõ���ǰ������
            for (int i = 0; i < mount; ++i)
            {
                //�����һ���׽��ֿɶ�����Ϣ����Ҫ��������
                if (i == 0 && FD_ISSET(socnum[i], &fds))
                {
                    struct sockaddr_in client_address;
                    socklen_t client_addrLength = sizeof(struct sockaddr_in);
                    //����һ���û����׽���
                    int clientfd = accept(listener, (struct sockaddr*)&client_address, &client_addrLength);
                    //����û�������������ʾ��Ϣ����֪ͨ�û����ӳɹ�
                    socnum.push_back(clientfd);
                    char ID[1024];
                    sprintf_s(ID, "�ͻ���ID: % d,", clientfd);
                    char buf[30] = "��ӭʹ������¥���Ʒ���\n";
                    strcat_s(ID, buf);
                    send(clientfd, ID, sizeof(ID) - 1, 0);//��ȥ���һ��'/0'
                }
                if (i != 0 && FD_ISSET(socnum[i], &fds))
                {
                    char buf[1024];
                    memset(buf, '\0', sizeof(buf));
                    int size = recv(socnum[i], buf, sizeof(buf) - 1, 0);
                    //����Ƿ����
                    if (size == 0 || size == -1)
                    {
                        closesocket(socnum[i]);//�ȹر�����׽���
                        cout << "\nģ�� "+ ServerCore->FindModule(socnum[i]) +"  ��ע��" << endl;
                        //ServerCore->ModuleLogout(socnum[i]);//��ҵ����ע����ModuleClient
                        SWD.push_back(i);
                    }
                    //����û�е���
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
                FD_CLR(socnum[SWD[X]], &fds);//���б��б���ɾ��
                socnum.erase(socnum.begin() + SWD[X]);//��vector������ɾ��
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
    memset(&clt, 0, sizeof(clt));//��սṹ��
    memcpy(&clt, buf, sizeof(clt));//�ѽ��յ�����Ϣת���ɽṹ��
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
