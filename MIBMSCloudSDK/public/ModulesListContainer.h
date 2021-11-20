/*
This file is part of MIBMSCloudSystem Project.
ModulesListContainer.h/.cpp£¨ServerOnly£©
Copyright (c) 2021 SuYichen.
*/
#pragma once
#include "MIBMSCloudApp.h"
#include <stdio.h>
#include <vector>

#ifdef  SERVER
struct ModuleClientInfo
{
	int ClientSocket;
};
class ModulesListContainer
{
public:
	ModulesListContainer();
	void AddClientInfoToList(ModuleClientInfo ClientInfo);
	void RemoveClientFromList(ModuleClientInfo ClientInfo);
	int GetModuleSilentSocket(int ClientSocket);
private:
	std::vector<ModuleClientInfo> ModulesList;
};
#endif //  SERVER ONLY