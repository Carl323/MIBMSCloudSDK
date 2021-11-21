#include "MethodsLibrary.h"
#include "ModulesListContainer.h"
#include "TaskInfo.h"
#include <vector>
#include <ctime>
#include <string>
#include <thread>
using namespace std;


ModuleClientInfo VectorErgodic_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList)
	{
		for (auto iter = ModulesList.begin(); iter != ModulesList.end(); iter++)
		{
			if ((*iter).ClientSocket == TClientSocket)
			{
				return *iter;
				break;
			}
		}
		ModuleClientInfo Empty={NULL};
		return Empty;
	}

void VectorElementDelete_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList)
{
	for (auto iter = ModulesList.begin(); iter != ModulesList.end(); iter++)
	{
		if ((*iter).ClientSocket == TClientSocket) ModulesList.erase(iter);
	}
}

void VectorElementDelete_TaskInfo(int TClientSocket, vector<TaskInfo> Tasks) 
{
	for (auto iter = Tasks.begin(); iter != Tasks.end(); iter++)
	{
		if ((*iter).client == TClientSocket) Tasks.erase(iter);
	}
}

void Delay(int time)//timeÎªÃëÊý 
{
	int T = time * 1000;
	clock_t now = clock();
	while (clock() - now < T);
}

unsigned int GetCPUCoresNum()
{
	return std::max(std::thread::hardware_concurrency(),(unsigned int)1);
}