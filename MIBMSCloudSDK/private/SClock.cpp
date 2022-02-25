#include "SClock.h"
#include <MethodsLibrary.h>

SClock::SClock(Control* ControlS)
{
	ControlScript = ControlS;
}

SClock::~SClock()
{

}

void SClock::TickCall()
{
	while (true)
	{
		ControlScript->Tick();
		Delay(1);
	}
}
