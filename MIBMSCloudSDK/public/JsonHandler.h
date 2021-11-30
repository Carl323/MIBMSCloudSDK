/*
This file is part of MIBMSCloudSystem Project.
JsonHandler.h/.cpp
Copyright (c) 2021 SuYichen.
*/
#pragma once

#include "json\json.h"

class jsonhandler
{
public:
	jsonhandler();
	~jsonhandler();
	std::string _get_Json_value_string(char stringtemp[1024], std::string key);
	std::string _get_Json_value_string(char stringtemp[1024], std::string key,std::string ROOT);
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