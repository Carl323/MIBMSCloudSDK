#include "SendHandler.h"
#include <JsonHandler.h>

sendhandler::sendhandler()
{

}

sendhandler::~sendhandler()
{

}

jsonsendler* sendhandler::CreatANewSendTask()
{
	jsonsendler* JSendler = new jsonsendler;
	return JSendler;
}

void sendhandler::AddNewValue_int(jsonsendler* JSender, std::string key, int value)
{
	JSender->AddKeyAndValue_int(key,value);
}

void sendhandler::AddNewValue_string(jsonsendler* JSender, std::string key, std::string value)
{
	JSender->AddKeyAndValue_string(key,value);
}

void sendhandler::AddNewValue_bool(jsonsendler* JSender, std::string key, bool value)
{
	JSender->AddKeyAndValue_bool(key, value);
}

