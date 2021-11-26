#pragma once

#include "json\json.h"

#if defined(__clang__) && (__POINTER_WIDTH__ == 64)
#pragma link "jsoncpp.a"
#else
#pragma link "jsoncpp.lib"
#endif

class jsonhandler
{
public:
	jsonhandler();
	~jsonhandler();
	std::string _get_Json_value_string(char stringtemp[1024], std::string key);
	int _get_Json_value_int(char stringtemp[1024], std::string key);
	bool _get_Json_value_bool(char stringtemp[1024],std::string key);
private:

};

class jsonsendler
{
public:
	jsonsendler();
	~jsonsendler();
	void AddKeyAndValue_int(std::string key,int value);
	void AddKeyAndValue_string(std::string key, std::string value);
	void AddKeyAndValue_bool(std::string key, bool value);
	std::string OutputJsonString();
private:
	Json::Value root;

};