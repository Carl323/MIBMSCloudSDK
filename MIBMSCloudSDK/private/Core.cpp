/*
This file is part of MIBMSCloudSystem Project.
Core.h/.cpp - The Core of Server/Client.
Copyright (c) 2021 SuYichen.
*/
#include "Core.h"
#include "MethodsLibrary.h"
#include "TaskInfo.h"
#include <vector>
#include <mutex>
#include <thread>
#include <JsonHandler.h>
#include <MIBMSCloud.h>
#include <INIOperation.h>
#include <ScriptCodeInterface.h>

#ifdef SERVER
Core::Core()
{
    PSI = new PythonScriptInterface;
    CPUCoresNum = GetCPUCoresNum();
    signed int ThreadNumLimit = (CPUCoresNum/2);
    printf("Server is now running on a %d Logical Cores CPU \n",CPUCoresNum);
    RecvTasks = {};
    SHandler=new sendhandler;
    MLC = new ModulesListContainer;
    CMyINI* p = new CMyINI();
    p->ReadINI("./Configs/ServerSettings.ini");
    std::string TaskHanlerThreadsNum= p->GetValue("Performance", "TaskHanlerThreadsNum");
    int s = atoi(TaskHanlerThreadsNum.c_str());
    if (s < 1) s = 1;
    else if (s > ThreadNumLimit) s= ThreadNumLimit;
    vector<thread*> t;
    for (int i = 0; i < s; i++) 
    {
        t.emplace_back(new thread(&Core::TaskHandler,this));
    }
    printf("ServerCore->TaskHandler共启用了%d个线程\n",s);
}

Core::~Core()
{
    delete MLC;
    delete PSI;
}
void Core::AddTask(SOCKET client, char info[1024])
{
    
    RecvTaskInfo Newinfo = {client,*info};
    RecvTasks.emplace_back(Newinfo);
}
void Core::ModuleLogout(SOCKET client)
{
    MLC->RemoveClientFromList(client);
}
std::string Core::FindModule(SOCKET client)
{
    return MLC->GetModuleName(client);
}
#endif // SERVER

#ifdef CLIENT
Core::Core()
{
    RecvTasks = {};
    thread* t1 = new thread(&Core::TaskHandler, this);
    SHandler = new sendhandler;
}
Core::~Core()
{
}
void Core::AddTask(int user, send_info info)
{
    RecvTaskInfo Newinfo = { user,info };
    RecvTasks.emplace_back(Newinfo);
}
#endif // CLIENT



bool  Core::IsBusy()
{
    return (sizeof(RecvTasks)>0);
}

void Core::TaskHandler()
{
    while (true)
    {
        some_mutex.lock();
        if (RecvTasks.size() > 0)
        {
            RecvTaskInfo info = RecvTasks[0];
            RecvTasks.erase(RecvTasks.begin());
            some_mutex.unlock();
            jsonhandler* Jhandler = new jsonhandler;
            int MT = Jhandler->_get_Json_value_int(info.Sinfo, "MesType");
            delete Jhandler;
            switch (MT)
            {
            case API:
            {
                APIReader(info.client, info.Sinfo);
            }
            #ifdef SERVER
            case COM:
            {
                CommandHandler(info.client, info.Sinfo);
            }
            #endif//SERVER
            case REP:
            {
                InfoReportHandler(info.client, info.Sinfo);
            }
            case ERR:

            {
                ErrorReportHandler(info.client, info.Sinfo);
            }
            case WAR:
            {
                WarningReportHandler(info.client, info.Sinfo);
            }
            default:
                break;
            }
        }
        else
        {
            some_mutex.unlock();
        }
    }
}

void Core::APIReader(SOCKET client, char info_content[1024])
{
    std::string APIClass;
    jsonhandler* JHandler = new jsonhandler;
    std::string Key;
    Key = JHandler->_get_Json_value_string(info_content, "Key");
    APIClass = JHandler->_get_Json_value_string(info_content, "APIClass", "API");
    if (APIClass == "System")
    {
        APIClass_System(client,info_content);
    }//API_Class_System
    else if (APIClass == "FaceRecognition")
    {
         
      }//API_Class_FaceRecognition
    else if(APIClass == "Script")
    {

    }

    delete JHandler;
}

void Core::APIClass_System(SOCKET client, char info_content[1024])
{ 
    jsonhandler* JHandler = new jsonhandler;
    std::string APIName;
    APIName= JHandler->_get_Json_value_string(info_content, "APIName", "Args", "API");
    if(APIName== "GenerateNewClient")
    {
        std::string ID;
        std::string ModuleName;
        std::string Key;
        ID = JHandler->_get_Json_value_string(info_content, "ID", "Args", "API");
        ModuleName = JHandler->_get_Json_value_string(info_content, "ModuleName", "Args", "API");
        Key = JHandler->_get_Json_value_string(info_content, "Key");
        GenerateNewClient(client, ModuleName, ID, Key);
    }

    delete JHandler;
}

void Core::APIClass_FaceRecognition(SOCKET client, char info_content[1024])
{
    jsonhandler* JHandler = new jsonhandler;
    std::string APIName;
    APIName = JHandler->_get_Json_value_string(info_content, "APIName", "Args", "API");
    if (APIName == "DoFaceRecognition")
    {
        std::string ID;
        std::string ImgByte;
        ID = JHandler->_get_Json_value_string(info_content, "ID", "Args", "API");
        ImgByte = JHandler->_get_Json_value_string(info_content, "ImgByte", "Args", "API");
        //To Do FaceRecognition
    }

    delete JHandler;
}

void Core::APIClass_Script(SOCKET client, char info_content[1024])
{
    jsonhandler* JHandler = new jsonhandler;
    std::string APIName;
    APIName = JHandler->_get_Json_value_string(info_content, "APIName", "Args", "API");
    PSI->FunctionNavigation_Interface(APIName,info_content);
}

void Core::GenerateNewClient(SOCKET client, std::string ModuleName,std::string ID, std::string Key)
{
    #ifdef SERVER
    ModuleClientInfo MCInfo={client,ModuleName,ID};
    MLC->AddClientInfoToList(MCInfo);
    cout << "模块 " + ModuleName + " 已注册！" << endl;
    #endif//  SERVER
}


void Core::CommandHandler(SOCKET client,  char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT
   jsonhandler* JHandler = new jsonhandler;
   bool State = JHandler->_get_Json_value_bool(info_content,"STATE");
   delete JHandler;
   #endif // CLIENT
}

void Core::InfoReportHandler(SOCKET client, char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT

   #endif // CLIENT

}

void Core::ErrorReportHandler(SOCKET client, char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT

   #endif // CLIENT

}

void Core::WarningReportHandler(SOCKET client,char info_content[1024])
{
    #ifdef SERVER

    #endif//  SERVER
    #ifdef CLIENT

    #endif // CLIENT

}

