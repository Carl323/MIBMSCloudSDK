#include "Device.h"

Device::Device()
{
	Handler = new jsonhandler;
	ClientSocket = NULL;
}

Device::~Device()
{
	delete Handler;
}

std::string Device::GetDeveiceInfo_RQ(std::string key)
{
	std::string X = Handler->_get_Json_value_string(Report_Quantity.c_str(), key);
	return X;
}

std::string Device::GetDeveiceInfo_CQ(std::string key)
{
	std::string Y = Handler->_get_Json_value_string(Controlled_Quantity.c_str(), key);
	return Y;
}

void Device::Reboot()
{

}

void Device::SetValue(char info_content[1024])
{
	Report_Quantity = Handler->_get_Json_value_string(info_content, "Report");
	Controlled_Quantity = Handler->_get_Json_value_string(info_content, "Controlled");
}