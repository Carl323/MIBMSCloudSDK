/*
This file is part of MIBMSCloudSystem Project.
Core.h/.cpp - The Core of Server/Client.
Copyright (c) 2021 SuYichen.
*/

#pragma once

#include "ModulesListContainer.h"
#include "send_info.h"
#include "TaskInfo.h"
#include "stdio.h"
#include <vector>
#include <mutex>
#include <SendHandler.h>

class Core
{
public:
	Core();
	~Core();
	unsigned int CPUCoresNum;
	bool IsBusy();
	void AddTask(SOCKET client,char info[1024]);
	sendhandler* SHandler;
#ifdef SERVER
	void ModuleLogout(SOCKET client);
	std::string FindModule(SOCKET client);
	ModulesListContainer* MLC;
#endif // Server
private:
	std::vector<RecvTaskInfo> RecvTasks;
	std::mutex some_mutex;
	void TaskHandler();
	void APIReader(SOCKET client, char info_content[1024]);
	void CommandHandler(SOCKET client, char info_content[1024]);
	void InfoReportHandler(SOCKET client,  char info_content[1024]);
	void ErrorReportHandler(SOCKET client,  char info_content[1024]);
	void WarningReportHandler(SOCKET client, char info_content[1024]);

	//API
	void GenerateNewClient(SOCKET client, std::string ModuleName, std::string ID, std::string Key);
};

