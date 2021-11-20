#pragma once

struct send_info
{
    int MessageType; //消息的类型
    int info_length; //发送的消息主体的长度
    char info_content[1024]; //消息主体
};