#pragma once
#include "ModulesListContainer.h"
#include "TaskInfo.h"
#include <vector>
using namespace std;

#ifdef SERVER
ModuleClientInfo VectorErgodic_ModuleClientInfo_MN(std::string MoudleName, vector<ModuleClientInfo> ModulesList);//����ModuleName��ModuleList�л�ȡ����ModuleClientInfo������������򷵻�һ���յ�ModuleClientInfo��
ModuleClientInfo VectorErgodic_ModuleClientInfo_CN(int clientsocket, vector<ModuleClientInfo> ModulesList);//����ClientSocket��ModuleList�л�ȡ����ModuleClientInfo������������򷵻�һ���յ�ModuleClientInfo��
void VectorElementDelete_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList);
void VectorElementDelete_ModuleClientInfo_ModuleName(std::string ModuleName, vector<ModuleClientInfo> ModulesList);
void SetColor(unsigned short forecolor = 4, unsigned short backgroudcolor = 0);
#endif // SERVER

void VectorElementDelete_TaskInfo(int TClientSocket, vector<RecvTaskInfo> Tasks);
void Delay(int time);
unsigned int GetCPUCoresNum();