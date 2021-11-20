#pragma once

#include "MIBMSCloudApp.h"
#include <MIBMSCloud.h>
#include <stdio.h>
#include <vector>

using namespace std;

#ifdef SERVER
class ServersManager
{
public:
	ServersManager();
	~ServersManager();
	void Reboot(bool Forced);
	server* GetServer();
private:
	server* theserver;
};
#endif // SERVER

