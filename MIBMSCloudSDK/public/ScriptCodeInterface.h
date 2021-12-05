#pragma once
#include <iostream>
#include <Python.h>
#include<string>

class PythonScriptInterface
{

public:
	PythonScriptInterface();
	~PythonScriptInterface();
	class Face
	{
	public:
		
		PyObject* FModule = PyImport_ImportModule("Face");
		PyObject* Fun_ImgToBase64 = PyObject_GetAttrString(FModule, "ImgToBase64");
		PyObject* Fun_Base64ToImg = PyObject_GetAttrString(FModule, "Base64ToImg");

		std::string ImgToBase64(std::string ImgCachePath);
		void Base64ToImg(std::string Str, std::string ImgCachePath);
	private:
	};
private:
	
};