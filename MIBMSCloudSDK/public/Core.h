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





class Core
{
public:
	Core();
	~Core();
	unsigned int CPUCoresNum;
	bool IsBusy();
	void AddTask(int MessageType,int client,send_info info);
#ifdef SERVER
	ModulesListContainer* MLC;
#endif // Server
private:
	std::vector<TaskInfo> Tasks;
	std::mutex some_mutex;
	void TaskHandler();
	void GenerateNewClient(int client, char info_content[1024]);
	void CommandHandler(int client, char info_content[1024]);
	void InfoReportHandler(int client,  char info_content[1024]);
	void ErrorReportHandler(int client,  char info_content[1024]);
	void WarningReportHandler(int client, char info_content[1024]);
};

