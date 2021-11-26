/*
This file is part of MIBMSCloudSystem Project.
ModulesListContainer.h/.cpp£¨ServerOnly£©
Copyright (c) 2021 SuYichen.
*/
#include "MIBMSCloudApp.h"

#ifdef  SERVER
#include "ModulesListContainer.h"
#include "MethodsLibrary.h"
#include "send_info.h"
#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;



ModulesListContainer::ModulesListContainer()
{
	ModulesList ={};
}
void ModulesListContainer::AddClientInfoToList(ModuleClientInfo ClientInfo)
{
    ModulesList.emplace_back(ClientInfo);
}
void ModulesListContainer::RemoveClientFromList(ModuleClientInfo ClientInfo)
{
	VectorElementDelete_ModuleClientInfo(ClientInfo.ClientSocket, ModulesList);
}
int ModulesListContainer::GetModuleSilentSocket(std::string ModuleName) {
	ModuleClientInfo TargetModuleInfo=VectorErgodic_ModuleClientInfo(ModuleName,ModulesList);
	return TargetModuleInfo.ClientSocket;
}
#endif