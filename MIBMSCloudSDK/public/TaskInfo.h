#pragma once
#include "send_info.h"
#include "WinSock2.h"

struct RecvTaskInfo
{
	SOCKET client;
	char Sinfo[1024];
};

struct SendTaskInfo
{
    #ifdef SERVER
	int client;
    #endif // SERVER
	send_info Sinfo;
};