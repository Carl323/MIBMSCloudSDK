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
	ModuleClientInfo titr = {};
	for (int i = 0; i < ModulesList.size(); i++)
	{
		if (ModulesList[i].ModuleName == ModuleName)
		{
			return ModulesList[i];
			break;
		}
	}
}//����ModuleName��ModuleList�л�ȡ����ModuleClientInfo������������򷵻�һ���յ�ModuleClientInfo��

ModuleClientInfo VectorErgodic_ModuleClientInfo_CN(int clientsocket, vector<ModuleClientInfo> ModulesList)
{
	ModuleClientInfo titr = {};
	for (int i = 0; i < ModulesList.size(); i++)
	{
		if (ModulesList[i].ClientSocket == clientsocket)
		{
			return ModulesList[i];
			break;
		}
	}
	return titr;
}//����ClientSocket��ModuleList�л�ȡ����ModuleClientInfo������������򷵻�һ���յ�ModuleClientInfo��

void VectorElementDelete_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList)
{
	for(int i=0;i<ModulesList.size();i++)
	{
		if (ModulesList[i].ClientSocket == TClientSocket) 
		{
			ModulesList.erase(ModulesList.begin() + i);
			break;
		}
	}
}

void VectorElementDelete_ModuleClientInfo_ModuleName(std::string ModuleName, vector<ModuleClientInfo> ModulesList)
{
	for (int i = 0; i < ModulesList.size(); i++)
	{
		if (ModulesList[i].ModuleName == ModuleName)
		{
			ModulesList.erase(ModulesList.begin() + i);
			break;
		}
	}
}
#endif // SERVER


void VectorElementDelete_TaskInfo(int TClientSocket, vector<RecvTaskInfo> Tasks) 
{
	for (int i = 0; i < Tasks.size(); i++)
	{
		if (Tasks[i].client == TClientSocket)
		{
			Tasks.erase(Tasks.begin() + i);
			break;
		}
	}
}

void Delay(int time)//timeΪ���� 
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
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ���������
	SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //�����ı�������ɫ
}