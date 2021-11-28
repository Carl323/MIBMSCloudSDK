/*
This file is part of MIBMSCloudSystem Project.
ModulesListContainer.h/.cpp£¨ServerOnly£©
Copyright (c) 2021 SuYichen.
*/
#pragma once
#include "MIBMSCloudApp.h"
#include <stdio.h>
#include <vector>
#include <string>

#ifdef  SERVER
struct ModuleClientInfo
{
	int ClientSocket;
	std::string ModuleName;
};
class ModulesListContainer
{
public:
	ModulesListContainer();
	std::string GetModuleName(int Client);
	void AddClientInfoToList(ModuleClientInfo ClientInfo);
	void RemoveClientFromList(int Client);
	void RemoveModuleFromList(std::string ModuleName);
	int GetModuleSilentSocket(std::string ModuleName);
private:
	std::vector<ModuleClientInfo> ModulesList;
};
#endif //  SERVER ONLY