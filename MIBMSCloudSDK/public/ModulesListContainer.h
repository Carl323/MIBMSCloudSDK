/*
This file is part of MIBMSCloudSystem Project.
ModulesListContainer.h/.cpp��ServerOnly��
Copyright (c) 2021 SuYichen.
*/
#pragma once
#include <stdio.h>
#include "MIBMSCloudApp.h"
#include "WinSock2.h"

#include <vector>
#include <string>

#include "Device.h"
#ifdef  SERVER
class ModulesListContainer
{
public:
	ModulesListContainer();
	std::string GetModuleName(SOCKET Client);
	void AddClientInfoToList(Device ClientInfo);
	void RemoveClientFromList(SOCKET Client);
	void RemoveModuleFromList(std::string ModuleName);
	Device GetDevice(std::string ModuleName);
	std::vector<Device> ModulesList;
	std::string RQs;
	std::string CQs;
private:
	
};
#endif //  SERVER ONLY