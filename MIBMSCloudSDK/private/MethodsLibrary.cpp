#include "MethodsLibrary.h"
#include "ModulesListContainer.h"
#include <vector>
using namespace std;


ModuleClientInfo VectorErgodic_ModuleClientInfo(char TModuleID[20], vector<ModuleClientInfo> ModulesList)
	{
		for (auto iter = ModulesList.begin(); iter != ModulesList.end(); iter++)
		{
			if ((*iter).ModuleID == TModuleID) 
			{
				return *iter;
				break;
			}
		}
		ModuleClientInfo Empty={"0",0};
		return Empty;
	}

void VectorElementDelete_ModuleClientInfo(char TModuleID[20], vector<ModuleClientInfo> ModulesList)
{
	for (auto iter = ModulesList.begin(); iter != ModulesList.end(); iter++)
	{
		if ((*iter).ModuleID == TModuleID) ModulesList.erase(iter);
	}
}
