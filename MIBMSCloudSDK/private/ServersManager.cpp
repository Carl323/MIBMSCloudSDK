/*
This file is part of MIBMSCloudSystem Project.
ServersManager.h/.cpp - The Manager of Servers.(ServerOnly)
Copyright (c) 2021 SuYichen.
*/
#include "ServersManager.h"
#include "MIBMSCloud.h"
#include <ctime> 

#ifdef SERVER
ServersManager::ServersManager()
{
	theserver = new server;
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
			Delay(1000);
		}
		theserver->sendrebootmessage();
		Delay(9*1000);
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

void Delay(int time)//time*1000ÎªÃëÊý 
{
	clock_t now =clock();
	while(clock()-now<time);
}
#endif // SERVER