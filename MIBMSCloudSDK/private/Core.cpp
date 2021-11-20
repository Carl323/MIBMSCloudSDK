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
    Tasks = {};
    MLC = new ModulesListContainer;
    thread* t1=new thread(&Core::TaskHandler, this);
    thread* t2=new thread(&Core::TaskHandler, this);
    thread* t3=new thread(&Core::TaskHandler, this);
    thread* t4=new thread(&Core::TaskHandler, this);
    t1->join();
    t2->join();
    t3->join();
    t4->join();
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

void Core::TaskHandler()
{
    while (true)
    {
        if (sizeof(Tasks)>0)
        {
            some_mutex.lock();
            TaskInfo info = Tasks[0];
            VectorElementDelete_TaskInfo(info.client, Tasks);
            some_mutex.unlock();
            switch (Tasks[0].MessageType)
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