/*
This file is part of MIBMSCloudSystem Project.
Core.h/.cpp - The Core of Server/Client.
Copyright (c) 2021 SuYichen.
*/
#include "Core.h"

#ifdef SERVER
Core::Core()
{
    MLC = new ModulesListContainer;
}
Core::~Core()
{
    delete MLC;
}
#endif // SERVER

#ifdef CLIENT
Core::Core()
{
}
Core::~Core()
{
}
#endif // CLIENT


void Core::GenerateNewClient(int client,char ModuleID[20],int Length, char info_content[1024])
{
    #ifdef SERVER

    #endif//  SERVER
    #ifdef CLIENT

    #endif // CLIENT

}


void Core::CommandHandler(int client, char ModuleID[20], int Length, char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT

   #endif // CLIENT
}

void Core::InfoReportHandler(int client, char ModuleID[20], int Length, char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT

   #endif // CLIENT

}

void Core::ErrorReportHandler(int client, char ModuleID[20], int Length, char info_content[1024])
{
   #ifdef SERVER

   #endif//  SERVER
   #ifdef CLIENT

   #endif // CLIENT

}

void Core::WarningReportHandler(int client, char ModuleID[20], int Length, char info_content[1024])
{
    #ifdef SERVER

    #endif//  SERVER
    #ifdef CLIENT

    #endif // CLIENT

}