#include "ServersManager.h"
#include "MethodsLibrary.h"
#include "stdio.h"
#include <iostream>
#include <string>


#ifdef SERVER
int main() {
	ServersManager* SM = new ServersManager;
	Delay(1.5);
	SetColor(30, 50);
	printf("MIBMSCloudServer->WORKING\n");
	SetColor(1, 0);
	while (true)
	{
		/*std::string str;
		std::getline(cin, str);
		char STR[20];
		int i;
		for (i = 0; i < str.length(); i++)
		{
			STR[i] = str[i];
		}
		STR[str.length()] = '\0';
		cout << "命令行功能在当前版本SDK已被禁用\n" << endl;*/
	}
	/*bool state = true;
	while (true)
	{
	/state = !state;
	jsonsendler* JSender=NULL;
	sendhandler* SH=SM->GetServer()->ServerCore->SHandler;
	JSender=SH->CreatANewSendTask();
	SH->AddNewValue_int(JSender, "MesType", 1);
	SH->AddNewValue_string(JSender, "ModuleName", "LCD001");
	SH->AddNewValue_bool(JSender, "STATE",state);
	Core* SC = SM->GetServer()->ServerCore;
	int ts=SC->MLC->GetModuleSilentSocket("LCD001");
	if(ts!=0)SH->SendJson(ts,JSender);
	Delay(2);
	}*/
	return 0;
}
#endif // SERVER

#ifdef CLIENT
int main()
{
	client* cli=new client;
	std::thread* CP = new std::thread(&client::process,cli);
	while (1)
	{
	}
}
#endif // CLIENT
