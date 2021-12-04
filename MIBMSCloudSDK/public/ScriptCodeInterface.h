#pragma once
#include <iostream>
#include <Python.h>
#include<string>

class PythonScriptInterface
{

public:
	PythonScriptInterface();
	~PythonScriptInterface();
	void FunctionNavigation_Interface(std::string FuncName,char content[1024]);
private:
	PyObject* pModule = NULL;
	PyObject* pNavigationFun = NULL;
};