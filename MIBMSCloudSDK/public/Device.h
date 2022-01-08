#pragma once

#include "JsonHandler.h"
#include <winsock2.h> 
#include<ws2tcpip.h>//定义socklen_t
#pragma comment(lib, "WS2_32")  // 链接到WS2_32.lib


class Device
{
public:
	Device();
	~Device();
	std::string GetDeveiceInfo_RQ(std::string key);
	std::string GetDeveiceInfo_CQ(std::string key);
	SOCKET ClientSocket;
	std::string ModuleName;
	std::string ModuleID;
	std::string Description;
	void Reboot();//重启设备
	void SetValue(char info_content[1024]);
	jsonhandler* Handler;
private:
	std::string Report_Quantity;
	std::string Controlled_Quantity;
};
