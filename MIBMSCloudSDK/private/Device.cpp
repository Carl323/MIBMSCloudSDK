#include "Device.h"

Device::Device()
{
	jsonhandler* Handler = new jsonhandler;
}

Device::~Device()
{
	delete Handler;
}

std::string GetDeveiceInfo(std::string key)
{

	return std::string();
}

void Device::Reboot()
{

}

void Device::SetValue(char info_content[1024])
{

	Json::Value valRoot;
	Json::Reader reader;
	reader.parse(info_content, valRoot);
    Json::Value::Members members;
    members = valRoot.getMemberNames();   // 获取所有key的值
    for (Json::Value::Members::iterator iterMember = members.begin(); iterMember != members.end(); iterMember++)   // 遍历每个key
    {
        std::string strKey = *iterMember;
        if (valRoot[strKey.c_str()].isString())
        {
            std::string strVal = valRoot[strKey.c_str()].asString();

        }
        else if (valRoot[strKey.c_str()].isInt())
        {
            int iVal = valRoot[strKey.c_str()].asInt();

        }
        else if (valRoot[strKey.c_str()].isDouble())
        {
            double dVal = valRoot[strKey.c_str()].asDouble();

        }
        else
        {
            std::string strVal = valRoot[strKey.c_str()].toStyledString();

        }
    }
}

