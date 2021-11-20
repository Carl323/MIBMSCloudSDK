#pragma once
#include "ModulesListContainer.h"
#include "TaskInfo.h"
#include <vector>
using namespace std;

ModuleClientInfo VectorErgodic_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList);
void VectorElementDelete_ModuleClientInfo(int TClientSocket, vector<ModuleClientInfo> ModulesList);
void VectorElementDelete_TaskInfo(int TClientSocket, vector<TaskInfo> Tasks);
void Delay(int time);