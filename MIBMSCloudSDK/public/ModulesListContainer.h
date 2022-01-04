/*
This file is part of MIBMSCloudSystem Project.
ModulesListContainer.h/.cpp��ServerOnly��
Copyright (c) 2021 SuYichen.
*/
#pragma once
#include "MIBMSCloudApp.h"
#include "WinSock2.h"
#include <stdio.h>
#include <vector>
#include <string>

#ifdef  SERVER
class Device
{
public:
	SOCKET ClientSocket;
	std::string ModuleName;
	std::string ModuleID;
};
class ModulesListContainer
{
public:
	ModulesListContainer();
	std::string GetModuleName(SOCKET Client);
	void AddClientInfoToList(Device ClientInfo);
	void RemoveClientFromList(SOCKET Client);
	void RemoveModuleFromList(std::string ModuleName);
	Device GetDevice(std::string ModuleName);
private:
	std::vector<Device> ModulesList;
};
#endif //  SERVER ONLY