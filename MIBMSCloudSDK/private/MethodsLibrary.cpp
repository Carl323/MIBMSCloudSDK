#include "MethodsLibrary.h"
#include "ModulesListContainer.h"
#include "TaskInfo.h"
#include "WinSock2.h"
#include <vector>
#include <ctime>
#include <string>
#include <thread>

using namespace std;


#ifdef SERVER
unsigned int GetCPUCoresNum()
{
	return std::max(std::thread::hardware_concurrency(), (unsigned int)1);
}

Device VectorErgodic_ModuleClientInfo_MN(std::string ModuleName, vector<Device> ModulesList)
{
	Device titr = {};
	for (int i = 0; i < ModulesList.size(); i++)
	{
		if (ModulesList[i].ModuleName == ModuleName)
		{
			return ModulesList[i];
			break;
		}
	}
}//����ModuleName��ModuleList�л�ȡ����ModuleClientInfo������������򷵻�һ���յ�ModuleClientInfo��

Device VectorErgodic_ModuleClientInfo_CN(SOCKET clientsocket, vector<Device> ModulesList)
{
	Device titr = {};
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

void VectorElementDelete_ModuleClientInfo(SOCKET TClientSocket, vector<Device> ModulesList)
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

void VectorElementDelete_ModuleClientInfo_ModuleName(std::string ModuleName, vector<Device> ModulesList)
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


void VectorElementDelete_TaskInfo(SOCKET TClientSocket, vector<RecvTaskInfo> Tasks) 
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

void Delay(float time)//timeΪ���� 
{
	float T = time * 1000;
	clock_t now = clock();
	while (clock() - now < T);
}



#include <Windows.h>
void SetColor(unsigned short forecolor, unsigned short backgroudcolor)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ���������
	SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //�����ı�������ɫ
}