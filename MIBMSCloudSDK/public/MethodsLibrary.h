#pragma once
#include "ModulesListContainer.h"
#include <vector>
using namespace std;

ModuleClientInfo VectorErgodic_ModuleClientInfo(char TModuleID[20], vector<ModuleClientInfo> ModulesList);
void VectorElementDelete_ModuleClientInfo(char TModuleID[20], vector<ModuleClientInfo> ModulesList);