#include "ScriptCodeInterface.h"

PythonScriptInterface::PythonScriptInterface()
{
	Py_Initialize();
	if (!Py_IsInitialized())
	{
		std::cout<<"��ʼ��ʧ�ܣ�"<<std::endl;
	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./Scripts/')");
}

PythonScriptInterface::~PythonScriptInterface()
{
	Py_Finalize(); 
}

std::string Face::ImgToBase64(std::string ImgCachePath)
{
	PyObject* args = Py_BuildValue("s", ImgCachePath.c_str());//��python����������ֵ
	PyObject* pRet=PyObject_CallObject(Fun_ImgToBase64,args);//���ú���
	std::string res ="";
	PyArg_Parse(pRet, "s", &res);//ת����������
	return res;
}

void Face::Base64ToImg(std::string ImgStr, std::string ImgCachePath)
{
	PyObject* args = Py_BuildValue("ss",ImgStr.c_str(),ImgCachePath.c_str());//��python����������ֵ
	PyObject_CallObject(Fun_Base64ToImg, args);//���ú���
}

Control::Control(ModulesListContainer* MLC)
{
	DC = MLC;
}

void Control::Tick()
{
	some_mutex2.lock();
	PyObject* args = Py_BuildValue("ss","");//��python����������ֵ
	PyObject_CallObject(Fun_CMain, args);
	some_mutex2.unlock();
}
