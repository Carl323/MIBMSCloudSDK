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

#ifdef SERVER
Core::Core()
{
    CPUCoresNum = GetCPUCoresNum();
    printf("Server is now running on a %d Logical Cores CPU \n",CPUCoresNum);
    RecvTasks = {};
    SHandler=new sendhandler;
    MLC = new ModulesListContainer;
    thread* t1 = new thread(&Core::TaskHandler, this);
    printf("已启动线程A！\n");
    thread* t2 = new thread(&Core::TaskHandler, this);
    printf("已启动线程B！\n");
    thread* t3 = new thread(&Core::TaskHandler, this);
    printf("已启动线程C！\n");
    thread* t4 = new thread(&Core::TaskHandler, this);
    printf("已启动线程D！\n");
    
}

Core::~Core()
{
    delete MLC;
}
void Core::AddTask(int client, send_info info)
{
    
    RecvTaskInfo Newinfo = {client,info};
    RecvTasks.emplace_back(Newinfo);
}
void Core::ModuleLogout(int client)
{
    MLC->RemoveClientFromList(client);
}
std::string Core::FindModule(int client)
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
            int MT = Jhandler->_get_Json_value_int(info.Sinfo.info_content, "MesType");
            delete Jhandler;
            switch (MT)
            {
            case GEN:
            {
                GenerateNewClient(info.client, info.Sinfo.info_content);
            }
            #ifdef SERVER
            case COM:
            {
                CommandHandler(info.client, info.Sinfo.info_content);
            }
            #endif//SERVER
            case REP:
            {
                InfoReportHandler(info.client, info.Sinfo.info_content);
            }
            case ERR:

            {
                ErrorReportHandler(info.client, info.Sinfo.info_content);
            }
            case WAR:
            {
                WarningReportHandler(info.client, info.Sinfo.info_content);
            }
            default:
                break;
            }
        }
        else
        {
            some_mutex.unlock();
            Delay(1);
        }
    }
}



void Core::GenerateNewClient(int client, char info_content[1024])
{
    #ifdef SERVER
    std::string ModuleName;
    jsonhandler* JHandler=new jsonhandler;
    ModuleName=JHandler->_get_Json_value_string(info_content, "ModuleName");
    ModuleClientInfo MCInfo={client,ModuleName};
    cout << "模块 "+ModuleName+" 已注册！" << endl;
    MLC->AddClientInfoToList(MCInfo);
    #endif//  SERVER
    #ifdef CLIENT

    #endif // CLIENT

}


void Core::CommandHandler(int client,  char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT
   jsonhandler* JHandler = new jsonhandler;
   bool State = JHandler->_get_Json_value_bool(info_content,"STATE");
   delete JHandler;
   #endif // CLIENT
}

void Core::InfoReportHandler(int client, char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT

   #endif // CLIENT

}

void Core::ErrorReportHandler(int client, char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT

   #endif // CLIENT

}

void Core::WarningReportHandler(int client,char info_content[1024])
{
    #ifdef SERVER

    #endif//  SERVER
    #ifdef CLIENT

    #endif // CLIENT

}

