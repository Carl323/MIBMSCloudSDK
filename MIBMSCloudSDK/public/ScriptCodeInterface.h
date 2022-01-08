#pragma once
#include "ModulesListContainer.h"
#include <iostream>
#include <Python.h>
#include <mutex>
#include<string>

class PythonScriptInterface
{

public:
	PythonScriptInterface();
	~PythonScriptInterface();
	
private:
	
};

class Face : public PythonScriptInterface
{
public:
	PyObject* FModule = PyImport_ImportModule("Face");
	PyObject* Fun_ImgToBase64 = PyObject_GetAttrString(FModule, "ImgToBase64");
	PyObject* Fun_Base64ToImg = PyObject_GetAttrString(FModule, "Base64ToImg");
	std::string ImgToBase64(std::string ImgCachePath);
	void Base64ToImg(std::string Str, std::string ImgCachePath);

private:

};
class Control : public PythonScriptInterface
{
public:
	Control(ModulesListContainer* MLC);
	PyObject* CModule = PyImport_ImportModule("Control");
	PyObject* Fun_CMain = PyObject_GetAttrString(CModule, "Main");
	ModulesListContainer* DC;
	void Tick();
private:
	std::mutex some_mutex2;
};