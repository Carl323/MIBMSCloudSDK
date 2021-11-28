/*
This file is part of MIBMSCloudSystem Project.
ModulesListContainer.h/.cpp��ServerOnly��
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
std::string ModulesListContainer::GetModuleName(int Client)
{
	return VectorErgodic_ModuleClientInfo_CN(Client,ModulesList).ModuleName;
	 
}
void ModulesListContainer::AddClientInfoToList(ModuleClientInfo ClientInfo)
{
	RemoveModuleFromList(ClientInfo.ModuleName);
    ModulesList.emplace_back(ClientInfo);
}
void ModulesListContainer::RemoveClientFromList(int Client)
{
	cout << "ģ�� ";
	cout <<GetModuleName(Client);
	cout << " ��ע����" << endl;
	VectorElementDelete_ModuleClientInfo(Client, ModulesList);
}
void ModulesListContainer::RemoveModuleFromList(std::string ModuleName)
{
	VectorElementDelete_ModuleClientInfo_ModuleName(ModuleName, ModulesList);
}
int ModulesListContainer::GetModuleSilentSocket(std::string ModuleName) {
	ModuleClientInfo TargetModuleInfo=VectorErgodic_ModuleClientInfo_MN(ModuleName,ModulesList);
	return TargetModuleInfo.ClientSocket;
}
#endif