/*
This file is part of MIBMSCloudSystem Project.
ServersManager.h/.cpp - The Manager of Servers.(ServerOnly)
Copyright (c) 2021 SuYichen.
*/
#include "ServersManager.h"
#include "MIBMSCloud.h"
#include "MethodsLibrary.h"
#include <ctime> 

#ifdef SERVER
ServersManager::ServersManager()
{
	printf("服务器初始化中...");
	theserver = new server;
	thread* SP = new std::thread(&server::process, theserver);
	printf("初始化完成！\n");
}
ServersManager::~ServersManager()
{
	delete theserver;
}

void ServersManager::Reboot(bool Forced)
{
	if(!Forced)
	{
		while(!theserver->canrebootnow())
		{
			Delay(1);
		}
		theserver->sendrebootmessage();
		printf("将在三秒内重启服务器！\n");
		Delay(3);
		delete theserver;
		theserver = new server;
		thread* SP = new std::thread(&server::process, theserver);
		printf("重启完成！\n");
	}
	else
	{
		delete theserver;
		theserver = new server;
		thread* SP = new std::thread(&server::process, theserver);
		printf("重启完成！\n");
	}
}

server* ServersManager::GetServer()
{
	return theserver;
}
#endif // SERVER