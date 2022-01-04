#pragma once

#include "MIBMSCloud.h"
#include "JsonHandler.h"

class Device
{
public:
	Device();
	~Device();
	SOCKET ClientSocket;
	std::string ModuleName;
	std::string ModuleID;
	std::string Description;
	void Reboot();//÷ÿ∆Ù…Ë±∏
	void SetValue(char info_content[1024]);
	jsonhandler* Handler;
private:
	Json::Value Report_Quantity;
	Json::Value Controlled_Quantity;
};
