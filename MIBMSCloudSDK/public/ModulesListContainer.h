/*
This file is part of MIBMSCloudSystem Project.
ModulesListContainer.h/.cpp£¨ServerOnly£©
Copyright (c) 2021 SuYichen.
*/
#pragma once
#include "MIBMSCloudApp.h"
#include "WinSock2.h"
#include <stdio.h>
#include <vector>
#include <string>

#ifdef  SERVER
struct ModuleClientInfo
{
	SOCKET ClientSocket;
	std::string ModuleName;
};
class ModulesListContainer
{
public:
	ModulesListContainer();
	std::string GetModuleName(SOCKET Client);
	void AddClientInfoToList(ModuleClientInfo ClientInfo);
	void RemoveClientFromList(SOCKET Client);
	void RemoveModuleFromList(std::string ModuleName);
	SOCKET GetModuleSilentSocket(std::string ModuleName);
private:
	std::vector<ModuleClientInfo> ModulesList;
};
#endif //  SERVER ONLY