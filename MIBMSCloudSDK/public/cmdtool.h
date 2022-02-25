#pragma once
#include "stdio.h"
#include <iostream>
#include <string>

class CMDTOOL
{
public:
	CMDTOOL();
	~CMDTOOL();

private:
	void DoCommand(std::string st);
};

