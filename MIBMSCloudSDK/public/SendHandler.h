#pragma once
#include"JsonHandler.h"

class sendhandler
{
public:
	sendhandler();
	~sendhandler();
	void CreatANewSendTask(jsonsendler* JSender);
	void AddNewValue_int(jsonsendler* JSender,std::string key,int value);
	void AddNewValue_string(jsonsendler* JSender,std::string key,std::string value);
	void AddNewValue_bool(jsonsendler* JSender, std::string key, bool value);
private:

};