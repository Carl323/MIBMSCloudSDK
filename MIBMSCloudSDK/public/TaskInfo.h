#pragma once
#include "send_info.h"
#include "WinSock2.h"

struct RecvTaskInfo
{
	SOCKET client;
	send_info Sinfo;
};

struct SendTaskInfo
{
    #ifdef SERVER
	int client;
    #endif // SERVER
	send_info Sinfo;
};