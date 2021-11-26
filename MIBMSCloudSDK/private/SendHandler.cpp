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
    std::cout << "下发信息：\n";
    std::cout << p<< std::endl;
    send(TargetSocket, p, sizeof(p) - 1, 0);
}

void sendhandler::sendata(int TargetSocket, char sendbuf[1024])
{
    char snd_buf[1024];
    send_info sndinfo;
    //清空消息主体的缓存，并将新的消息主体写入结构体↓
    memset(sndinfo.info_content, 0, sizeof(sndinfo.info_content));
    for (int i = 0; i < (sizeof(sendbuf)); ++i)
    {
        sndinfo.info_content[i] = sendbuf[i];
    }
    //清空待发送消息的缓存↓
    memset(snd_buf, 0, 1024);
    //结构体转换成字符串↓
    memcpy(snd_buf, &sndinfo, sizeof(sndinfo));
    //将消息发送给客户端
    send(TargetSocket, snd_buf, sizeof(snd_buf) - 1, 0);
}