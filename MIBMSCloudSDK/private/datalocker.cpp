#include "datalocker.h"

datalocker::datalocker()
{
}

datalocker::~datalocker() 
{
}

 char* datalocker::_lock_data_char(char STR[1024])
{
	char NewStr[1024];
	for (int i = 0; i < 1024; i++)
	{
		if (STR[i]== '\0')
		{
			NewStr[i] = '\0';
			break;
		}
		else
		{
			NewStr[i] = STR[i] * 2 - 1;
		}
	}
	char* CH = NewStr;
	return CH;
}

 char* datalocker::_unlock_data_char(char STR[1024])
 {
	 char NewStr[1024];
	 for (int i = 0; i < 1024; i++)
	 {
		 if (STR[i] == '\0')
		 {
			 NewStr[i] = '\0';
			 break;
		 }
		 else
		 {
			 NewStr[i] = (STR[i]+1)/2;
		 }
	 }
	 char* CH = NewStr;
	 return CH;
 }
