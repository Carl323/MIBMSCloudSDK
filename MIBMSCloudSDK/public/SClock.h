#pragma once

#include "ScriptCodeInterface.h"
class SClock
{
public:
	SClock(Control* ControlS);
	~SClock();
	Control* ControlScript;
	void TickCall();
};