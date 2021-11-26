/*
This file is part of MIBMSCloudSystem Project.
SendHandler.h/.cpp
Copyright (c) 2021 SuYichen.
*/
#pragma once
#include"JsonHandler.h"

class sendhandler
{
public:
	sendhandler();
	~sendhandler();
	jsonsendler* CreatANewSendTask();
	void AddNewValue_int(jsonsendler* JSender,std::string key,int value);
	void AddNewValue_string(jsonsendler* JSender,std::string key,std::string value);
	void AddNewValue_bool(jsonsendler* JSender, std::string key, bool value);
	void SendJson(int client, jsonsendler* JSender);
	void sendata(int TargetSocket, char sendbuf[1024]);

private:

};