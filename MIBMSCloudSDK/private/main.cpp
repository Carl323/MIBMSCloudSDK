#include "ServersManager.h"
#include "MethodsLibrary.h"
#include "stdio.h"
#include <iostream>
#include <string>


#ifdef SERVER
int main() {
	ServersManager* SM = new ServersManager;
	Delay(3);
	while (true)
	{
		printf("MIBMSCloudServer->");
		std::string str;
		std::getline(cin, str);
		char STR[20];
		int i;
		for (i = 0; i < str.length(); i++)
		{
			STR[i] = str[i];
		}
		STR[str.length()] = '\0';
		cout << "�����й����ڵ�ǰ�汾SDKδ������ɣ��ѱ�����\n" << endl;
	}
}
#endif // SERVER