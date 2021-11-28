#pragma once
#include "ModulesListContainer.h"
#include "TaskInfo.h"
#include <vector>
using namespace std;

#ifdef SERVER
ModuleClientInfo VectorErgodic_ModuleClientInfo_MN(std::string MoudleName, vector<ModuleClientInfo> ModulesList);//按照ModuleName从ModuleList中获取整个ModuleClientInfo，如果不存在则返回一个空的ModuleClientInfo。
ModuleClientInfo VectorErgodic_ModuleClientInfo_CN(int clientsocket, vector<ModuleClientInfo> ModulesList);//按照ClientSocket从ModuleList中获取整个ModuleClientInfo，如果不存在则返回一个空的ModuleClientInfo。
void VectorElementDelete_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList);
void VectorElementDelete_ModuleClientInfo_ModuleName(std::string ModuleName, vector<ModuleClientInfo> ModulesList);
void SetColor(unsigned short forecolor = 4, unsigned short backgroudcolor = 0);
#endif // SERVER

void VectorElementDelete_TaskInfo(int TClientSocket, vector<RecvTaskInfo> Tasks);
void Delay(int time);
unsigned int GetCPUCoresNum();