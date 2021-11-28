#include "MethodsLibrary.h"
#include "ModulesListContainer.h"
#include "TaskInfo.h"
#include <vector>
#include <ctime>
#include <string>
#include <thread>

using namespace std;

#ifdef SERVER
ModuleClientInfo VectorErgodic_ModuleClientInfo_MN(std::string ModuleName, vector<ModuleClientInfo> ModulesList)
{
	vector<ModuleClientInfo>::iterator itr = ModulesList.begin();
	ModuleClientInfo titr = {};
	while (itr != ModulesList.end())
	{
		if ((*itr).ModuleName == ModuleName)
		{
			titr = (*itr);
			break;
		}
	}
	return titr;
}//按照ModuleName从ModuleList中获取整个ModuleClientInfo，如果不存在则返回一个空的ModuleClientInfo。

ModuleClientInfo VectorErgodic_ModuleClientInfo_CN(int clientsocket, vector<ModuleClientInfo> ModulesList)
{
	vector<ModuleClientInfo>::iterator itr = ModulesList.begin();
	ModuleClientInfo titr = {};
	while (itr != ModulesList.end())
	{
		if ((*itr).ClientSocket == clientsocket)
		{
			titr = (*itr);
			break;
		}
	}
	return titr;
}//按照ClientSocket从ModuleList中获取整个ModuleClientInfo，如果不存在则返回一个空的ModuleClientInfo。

void VectorElementDelete_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList)
{
	vector<ModuleClientInfo>::iterator itr = ModulesList.begin();
	while (itr != ModulesList.end())
	{
		if ((*itr).ClientSocket == TClientSocket)
		{
			ModulesList.erase(itr);
			break;
		}
		itr++;//这里删除后迭代器会更新出错
	}
}

void VectorElementDelete_ModuleClientInfo_ModuleName(std::string ModuleName, vector<ModuleClientInfo> ModulesList)
{
	vector<ModuleClientInfo>::iterator itr = ModulesList.begin();
	while (itr != ModulesList.end())
	{
		if ((*itr).ModuleName == ModuleName)
		{
			ModulesList.erase(itr);
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

#include <Windows.h>
void SetColor(unsigned short forecolor, unsigned short backgroudcolor)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //获取缓冲区句柄
	SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //设置文本及背景色
}