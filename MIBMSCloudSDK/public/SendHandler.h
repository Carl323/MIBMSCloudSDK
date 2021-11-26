#pragma once

class sendhandler
{
public:
	sendhandler();
	~sendhandler();
	jsonsendler* CreatANewSendTask();
	void AddNewValue_int(jsonsendler* JSender,std::string key,int value);
	void AddNewValue_string(jsonsendler* JSender,std::string key,std::string value);
	void AddNewValue_bool(jsonsendler* JSender, std::string key, bool value);
private:

};