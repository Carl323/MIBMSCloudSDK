#include "SClock.h"

SClock::SClock(Control* ControlS)
{
	ControlScript = ControlS;
}

SClock::~SClock()
{
}

void SClock::TickCall()
{
	ControlScript->Tick();
}
