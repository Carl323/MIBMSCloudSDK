#include "ScriptCodeInterface.h"

PythonScriptInterface::PythonScriptInterface()
{
	Py_Initialize();//使用python之前，要调用Py_Initialize();这个函数进行初始化
	if (!Py_IsInitialized())
	{
		std::cout<<"初始化失败！"<<std::endl;
	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./Scripts/')");
	pModule = PyImport_ImportModule("PythonEnterprise");//这里是要调用的文件名hello.py
	if (pModule == NULL)
	{
		std::cout << "Python脚本缺失，请确认后重新运行" << std::endl;
		exit(0);
	}
	pNavigationFun= PyObject_GetAttrString(pModule,"FunctionNavigation");//这里是要调用的函数名
}

PythonScriptInterface::~PythonScriptInterface()
{
	Py_Finalize(); // 与初始化对应
}

void PythonScriptInterface::FunctionNavigation_Interface(std::string FuncName, char content[1024])
{
	std::string STR1 = FuncName;
	std::string STR2 = content;
	PyObject* args = Py_BuildValue("ss", STR1.c_str(), STR2.c_str());//给python函数参数赋值
	PyObject_CallObject(pNavigationFun, args);//调用函数
}

