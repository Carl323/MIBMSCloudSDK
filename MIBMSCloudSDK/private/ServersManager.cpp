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
	printf("��������ʼ����...");
	theserver = new server;
	thread* SP = new std::thread(&server::process, theserver);
	printf("��ʼ����ɣ�\n");
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
		printf("����������������������\n");
		Delay(3);
		delete theserver;
		theserver = new server;
		thread* SP = new std::thread(&server::process, theserver);
		printf("������ɣ�\n");
	}
	else
	{
		delete theserver;
		theserver = new server;
		thread* SP = new std::thread(&server::process, theserver);
		printf("������ɣ�\n");
	}
}

server* ServersManager::GetServer()
{
	return theserver;
}
#endif // SERVER