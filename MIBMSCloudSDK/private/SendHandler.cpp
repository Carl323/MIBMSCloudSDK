/*
This file is part of MIBMSCloudSystem Project.
SendHandler.h/.cpp
Copyright (c) 2021 SuYichen.
*/
#include "SendHandler.h"
#include <JsonHandler.h>
#include <send_info.h>
#include <WinSock2.h>
#include <iostream>

sendhandler::sendhandler()
{

}

sendhandler::~sendhandler()
{

}

jsonsendler* sendhandler::CreatANewSendTask()
{
		return new jsonsendler;
}

void sendhandler::AddNewValue_int(jsonsendler* JSender, std::string key, int value)
{
	JSender->AddKeyAndValue_int(key,value);
}

void sendhandler::AddNewValue_string(jsonsendler* JSender, std::string key, std::string value)
{
	JSender->AddKeyAndValue_string(key,value);
}

void sendhandler::AddNewValue_bool(jsonsendler* JSender, std::string key, bool value)
{
	JSender->AddKeyAndValue_bool(key, value);
}

void sendhandler::SendJson(int TargetSocket, jsonsendler* JSender)
{
	std::string TargetStr = JSender->OutputJsonString();
    //std::cout << TargetStr <<std::endl;
	delete JSender;
    char p[1024];
    int i;
    for (i = 0; i < TargetStr.length(); i++)
        p[i] = TargetStr[i];
    p[i] = '\0';
    std::cout << "�·���Ϣ��\n";
    std::cout << p<< std::endl;
    send(TargetSocket, p, sizeof(p) - 1, 0);
}

void sendhandler::sendata(int TargetSocket, char sendbuf[1024])
{
    char snd_buf[1024];
    send_info sndinfo;
    //�����Ϣ����Ļ��棬�����µ���Ϣ����д��ṹ���
    memset(sndinfo.info_content, 0, sizeof(sndinfo.info_content));
    for (int i = 0; i < (sizeof(sendbuf)); ++i)
    {
        sndinfo.info_content[i] = sendbuf[i];
    }
    //��մ�������Ϣ�Ļ����
    memset(snd_buf, 0, 1024);
    //�ṹ��ת�����ַ�����
    memcpy(snd_buf, &sndinfo, sizeof(sndinfo));
    //����Ϣ���͸��ͻ���
    send(TargetSocket, snd_buf, sizeof(snd_buf) - 1, 0);
}