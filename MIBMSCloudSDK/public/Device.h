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
	void Reboot();
	void SetValue(char info_content[1024]);

private:
	jsonhandler* Handler;
};