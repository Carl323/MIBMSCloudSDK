#include "ServersManager.h"
#include "MethodsLibrary.h"
#include "stdio.h"
#include <iostream>
#include <string>


#ifdef SERVER
int main() {
	ServersManager* SM = new ServersManager;
	Delay(1.5);
	while (true)
	{
		printf("\n\033[31;43mMIBMSCloudServer\033[0m ->");
		std::string str;
		std::getline(cin, str);
		char STR[20];
		int i;
		for (i = 0; i < str.length(); i++)
		{
			STR[i] = str[i];
		}
		STR[str.length()] = '\0';
		cout << "命令行功能在当前版本SDK已被禁用\n" << endl;
	}
}
#endif // SERVER