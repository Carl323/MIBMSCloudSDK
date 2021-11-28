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
}//����ModuleName��ModuleList�л�ȡ����ModuleClientInfo������������򷵻�һ���յ�ModuleClientInfo��

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
}//����ClientSocket��ModuleList�л�ȡ����ModuleClientInfo������������򷵻�һ���յ�ModuleClientInfo��

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
		itr++;//����ɾ�������������³���
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
		itr++;//����ɾ�������������³���
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
		itr++;//����ɾ�������������³���
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