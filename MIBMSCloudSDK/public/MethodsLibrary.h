#pragma once
#include "ModulesListContainer.h"
#include "TaskInfo.h"
#include <vector>
using namespace std;

#ifdef SERVER
ModuleClientInfo VectorErgodic_ModuleClientInfo(std::string MoudleName, vector<ModuleClientInfo> ModulesList);
void VectorElementDelete_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList);
#endif // SERVER

void VectorElementDelete_TaskInfo(int TClientSocket, vector<RecvTaskInfo> Tasks);
void Delay(int time);
unsigned int GetCPUCoresNum();