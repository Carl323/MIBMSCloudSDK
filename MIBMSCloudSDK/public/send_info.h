#pragma once

struct send_info
{
    int MessageType; //��Ϣ������
    int info_length; //���͵���Ϣ����ĳ���
    char info_content[1024]; //��Ϣ����
};