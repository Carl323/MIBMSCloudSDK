/*
This file is part of MIBMSCloudSystem Project.
ModulesListContainer.h/.cpp£¨ServerOnly£©
Copyright (c) 2021 SuYichen.
*/
#include "MIBMSCloudApp.h"

#ifdef  SERVER
#include "ModulesListContainer.h"
#include "MethodsLibrary.h"
#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;



ModulesListContainer::ModulesListContainer()
{
	std::vector<ModuleClientInfo> ModulesList ={};
}
void ModulesListContainer::AddClientInfoToList(ModuleClientInfo ClientInfo)
{
    ModulesList.emplace_back(ClientInfo);
}
void ModulesListContainer::RemoveClientFromList(ModuleClientInfo ClientInfo)
{
	VectorElementDelete_ModuleClientInfo(ClientInfo.ModuleID, ModulesList);
}
int ModulesListContainer::GetModuleSilentSocket(char MoudleID) {
	ModuleClientInfo TargetModuleInfo=VectorErgodic_ModuleClientInfo(&MoudleID,ModulesList);
	return TargetModuleInfo.ClientSocket;
}
#endif