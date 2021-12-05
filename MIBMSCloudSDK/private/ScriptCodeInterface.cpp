#include "ScriptCodeInterface.h"

PythonScriptInterface::PythonScriptInterface()
{
	Py_Initialize();
	if (!Py_IsInitialized())
	{
		std::cout<<"初始化失败！"<<std::endl;
	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./Scripts/')");
}

PythonScriptInterface::~PythonScriptInterface()
{
	Py_Finalize(); 
}

std::string PythonScriptInterface::Face::ImgToBase64(std::string ImgCachePath)
{
	PyObject* args = Py_BuildValue("s", ImgCachePath.c_str());//给python函数参数赋值
	PyObject* pRet=PyObject_CallObject(Fun_ImgToBase64,args);//调用函数
	std::string res ="";
	PyArg_Parse(pRet, "s", &res);//转换返回类型
	return res;
}

void PythonScriptInterface::Face::Base64ToImg(std::string ImgStr, std::string ImgCachePath)
{
	PyObject* args = Py_BuildValue("ss",ImgStr.c_str(),ImgCachePath.c_str());//给python函数参数赋值
	PyObject_CallObject(Fun_Base64ToImg, args);//调用函数
}
