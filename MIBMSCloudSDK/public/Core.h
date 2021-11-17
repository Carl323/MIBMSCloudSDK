/*
This file is part of MIBMSCloudSystem Project.
Core.h/.cpp - The Core of Server/Client.
Copyright (c) 2021 SuYichen.
*/

#pragma once

#include "ModulesListContainer.h"

class Core
{
public:
	Core();
	~Core();
	void GenerateNewClient(int client, char ModuleID[20], int Length, char info_content[1024]);
	void CommandHandler(int client, char ModuleID[20], int Length, char info_content[1024]);
	void InfoReportHandler(int client, char ModuleID[20], int Length, char info_content[1024]);
	void ErrorReportHandler(int client, char ModuleID[20], int Length, char info_content[1024]);
	void WarningReportHandler(int client, char ModuleID[20], int Length, char info_content[1024]);
#ifdef SERVER
	ModulesListContainer* MLC;
#endif // Server
private:

};

