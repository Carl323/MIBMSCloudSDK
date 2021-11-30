/*
This file is part of MIBMSCloudSystem Project.
SendHandler.h/.cpp
Copyright (c) 2021 SuYichen.
*/
#include "SendHandler.h"
#include "datalocker.h"
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
    std::cout << TargetStr <<std::endl;
	delete JSender;
    char p[1024];
    int i;
    for (i = 0; i < TargetStr.length(); i++)
        p[i] = TargetStr[i];
    p[i] = '\0';
    send(TargetSocket, p, sizeof(p) - 1, 0);
}

void sendhandler::sendata(int TargetSocket, char sendbuf[1024])
{
    
    char sndbuf[1024];
    datalocker* locker = new datalocker;
    strcpy_s(sndbuf,locker->_lock_data_char(sendbuf));
    delete locker;
    std::cout << "发送信息：\n" << sndbuf << std::endl;
    //将消息发送给客户端
    send(TargetSocket, sndbuf, sizeof(sndbuf) - 1, 0);
}