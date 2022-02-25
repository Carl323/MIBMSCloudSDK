#include "ServersManager.h"
#include "MethodsLibrary.h"
#include "stdio.h"
#include <iostream>
#include <string>


#ifdef SERVER
int main() {
	ServersManager* SM = new ServersManager;
	while (true)
	{

	}
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
