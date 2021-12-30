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
#include <WinSock2.h>
using namespace std;



ModulesListContainer::ModulesListContainer()
{
	ModulesList ={};
}
std::string ModulesListContainer::GetModuleName(SOCKET Client)
{
	return VectorErgodic_ModuleClientInfo_CN(Client,ModulesList).ModuleName;
	 
}
void ModulesListContainer::AddClientInfoToList(Device ClientInfo)
{
	RemoveModuleFromList(ClientInfo.ModuleName);
    ModulesList.emplace_back(ClientInfo);
}
void ModulesListContainer::RemoveClientFromList(SOCKET Client)
{
	cout << "Ä£¿é ";
	cout <<GetModuleName(Client);
	cout << " ÒÑ×¢Ïú£¡" << endl;
	VectorElementDelete_ModuleClientInfo(Client, ModulesList);
}
void ModulesListContainer::RemoveModuleFromList(std::string ModuleName)
{
	VectorElementDelete_ModuleClientInfo_ModuleName(ModuleName, ModulesList);
}
Device ModulesListContainer::GetDevice(std::string ModuleName) {
	Device DVC=VectorErgodic_ModuleClientInfo_MN(ModuleName,ModulesList);
	return DVC;
}
#endif