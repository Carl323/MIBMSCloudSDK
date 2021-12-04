#include "ScriptCodeInterface.h"

PythonScriptInterface::PythonScriptInterface()
{
	Py_Initialize();//ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��
	if (!Py_IsInitialized())
	{
		std::cout<<"��ʼ��ʧ�ܣ�"<<std::endl;
	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./Scripts/')");
	pModule = PyImport_ImportModule("PythonEnterprise");//������Ҫ���õ��ļ���hello.py
	if (pModule == NULL)
	{
		std::cout << "Python�ű�ȱʧ����ȷ�Ϻ���������" << std::endl;
		exit(0);
	}
	pNavigationFun= PyObject_GetAttrString(pModule,"FunctionNavigation");//������Ҫ���õĺ�����
}

PythonScriptInterface::~PythonScriptInterface()
{
	Py_Finalize(); // ���ʼ����Ӧ
}

void PythonScriptInterface::FunctionNavigation_Interface(std::string FuncName, char content[1024])
{
	std::string STR1 = FuncName;
	std::string STR2 = content;
	PyObject* args = Py_BuildValue("ss", STR1.c_str(), STR2.c_str());//��python����������ֵ
	PyObject_CallObject(pNavigationFun, args);//���ú���
}

