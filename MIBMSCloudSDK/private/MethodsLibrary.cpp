#include "MethodsLibrary.h"
#include "ModulesListContainer.h"
#include "TaskInfo.h"
#include <vector>
#include <ctime>
#include <string>
#include <thread>
using namespace std;

#ifdef SERVER
ModuleClientInfo VectorErgodic_ModuleClientInfo(std::string ModuleName, vector<ModuleClientInfo> ModulesList)
{
	vector<ModuleClientInfo>::iterator itr = ModulesList.begin();
	while (itr != Tasks.end())
	{
		if ((*itr).ModuleName == ModuleName)
		{
			return *itr;
			break;
		}
	}
	ModuleClientInfo Empty = { NULL };
	return Empty;
}

void VectorElementDelete_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList)
{
	vector<ModuleClientInfo>::iterator itr = ModulesList.begin();
	while (itr != Tasks.end())
	{
		if ((*itr).ClientSocket == TClientSocket)
		{
			Tasks.erase(itr);
			break;
		}
		itr++;//这里删除后迭代器会更新出错
	}
}

void VectorElementDelete_ModuleClientInfo_ModuleName(std::string ModuleName, vector<ModuleClientInfo> ModulesList)
{
	vector<ModuleClientInfo>::iterator itr = ModulesList.begin();
	while (itr != Tasks.end())
	{
		if ((*itr).ModuleName == ModuleName)
		{
			Tasks.erase(itr);
			break;
		}
		itr++;//这里删除后迭代器会更新出错
	}
}
#endif // SERVER


void VectorElementDelete_TaskInfo(int TClientSocket, vector<RecvTaskInfo> Tasks) 
{
	vector<RecvTaskInfo>::iterator itr = Tasks.begin();
	while (itr != Tasks.end())
	{
		if ((*itr).client == TClientSocket)
		{
			Tasks.erase(itr);
			break;
		}
		itr++;//这里删除后迭代器会更新出错
	}
}

void Delay(int time)//time为秒数 
{
	int T = time * 1000;
	clock_t now = clock();
	while (clock() - now < T);
}

unsigned int GetCPUCoresNum()
{
	return std::max(std::thread::hardware_concurrency(),(unsigned int)1);
}

