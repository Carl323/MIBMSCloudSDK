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

#ifdef SERVER
Core::Core()
{
    CPUCoresNum = GetCPUCoresNum();
    printf("Server is now running on a %d Logical Cores CPU \n",CPUCoresNum);
    Tasks = {};
    MLC = new ModulesListContainer;
    if (CPUCoresNum >= 1)
    {
        thread* t1 = new thread(&Core::TaskHandler, this);
        printf("已启动线程A！\n");
    }
    if (CPUCoresNum >= 2)
    {
        thread* t2 = new thread(&Core::TaskHandler, this);
        printf("已启动线程B！\n");
    }
    if (CPUCoresNum >= 4) 
    {
        thread* t3 = new thread(&Core::TaskHandler, this);
        printf("已启动线程C！\n");
    }
    if (CPUCoresNum >= 8)
    {
        thread* t4 = new thread(&Core::TaskHandler, this);
        printf("已启动线程D！\n");
    }
}

Core::~Core()
{
    delete MLC;
}
void Core::AddTask(int MessageType, int client, send_info info)
{
    TaskInfo Newinfo = { MessageType,client,info };
    Tasks.emplace_back(Newinfo);
}
#endif // SERVER

#ifdef CLIENT
Core::Core()
{
    Tasks = {};
}
Core::~Core()
{
}
#endif // CLIENT

bool  Core::IsBusy()
{
    return (sizeof(Tasks)>0);
}

void Core::TaskHandler()
{
    while (true)
    {
        if (Tasks.size()>0)
        {
            some_mutex.lock();
            TaskInfo info = Tasks[0];
            VectorElementDelete_TaskInfo(info.client, Tasks);
            some_mutex.unlock();
            switch (Tasks[1].MessageType)
            {
            case GENERATE:
            {
                GenerateNewClient(info.client, info.Sinfo.info_content);
            }
            case COMMAND:
            {  
                CommandHandler(info.client, info.Sinfo.info_content);
            }
            case INFOREPORT:
            {
                InfoReportHandler(info.client, info.Sinfo.info_content);
            }
            case ERRORREPORT:
                
            {
                ErrorReportHandler(info.client, info.Sinfo.info_content);
            }
            case WARNINGREPORT:
            {    
                WarningReportHandler(info.client, info.Sinfo.info_content);
            }
            default:  
                break;
            }
        }
        else
        {
            Delay(1);
        }
    }
}

void Core::GenerateNewClient(int client, char info_content[1024])
{
    #ifdef SERVER

    #endif//  SERVER
    #ifdef CLIENT

    #endif // CLIENT

}


void Core::CommandHandler(int client,  char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT

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