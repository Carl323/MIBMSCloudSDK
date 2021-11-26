#pragma once
#include "send_info.h"

struct RecvTaskInfo
{
	int client;
	send_info Sinfo;
};

struct SendTaskInfo
{
    #ifdef SERVER
	int client;
    #endif // SERVER
	send_info Sinfo;
};