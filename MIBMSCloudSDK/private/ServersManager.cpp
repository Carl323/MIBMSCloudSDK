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
	theserver->init();
	thread* SP = new std::thread(&server::process, theserver);
	printf("初始化完成！");
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
		Delay(9);
		delete theserver;
		theserver = new server;
	}
	else
	{
		delete theserver;
		theserver = new server;
	}
}

server* ServersManager::GetServer()
{
	return theserver;
}
#endif // SERVER