#pragma once

class datalocker
{
public:
	datalocker();
	~datalocker();
	char* _lock_data_char(char STR[1024]);
	char* _unlock_data_char(char STR[1024]);
};