#pragma once
#include "ModulesListContainer.h"
#include "TaskInfo.h"
#include "WinSock2.h"
#include <vector>
using namespace std;

#ifdef SERVER
ModuleClientInfo VectorErgodic_ModuleClientInfo_MN(std::string MoudleName, vector<ModuleClientInfo> ModulesList);//按照ModuleName从ModuleList中获取整个ModuleClientInfo，如果不存在则返回一个空的ModuleClientInfo。
ModuleClientInfo VectorErgodic_ModuleClientInfo_CN(SOCKET clientsocket, vector<ModuleClientInfo> ModulesList);//按照ClientSocket从ModuleList中获取整个ModuleClientInfo，如果不存在则返回一个空的ModuleClientInfo。
void VectorElementDelete_ModuleClientInfo(SOCKET TClientSocket, vector<ModuleClientInfo> ModulesList);
void VectorElementDelete_ModuleClientInfo_ModuleName(std::string ModuleName, vector<ModuleClientInfo> ModulesList);
void SetColor(unsigned short forecolor = 4, unsigned short backgroudcolor = 0);
#endif // SERVER

void VectorElementDelete_TaskInfo(SOCKET TClientSocket, vector<RecvTaskInfo> Tasks);
void Delay(int time);
unsigned int GetCPUCoresNum();
static int getNumericValue(char str) {
	int ia = str - '0';
	return ia;
};
static char* StringToChar(std::string str) {
	char* p = (char*)str.data();
	return p;
};