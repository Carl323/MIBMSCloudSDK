#include "cmdtool.h"
#include "MethodsLibrary.h"

CMDTOOL::CMDTOOL()
{
	while (true)
	{
		SetColor(30, 50);
		cout << "MIBMSCloudServer->";
		std::string str;
		getline(cin, str);
		SetColor(1, 0);
		DoCommand(str);
	}

}

CMDTOOL::~CMDTOOL()
{
}

void CMDTOOL::DoCommand(std::string st)
{
	cout << "" << endl;
	cout << "命令行功能当前尚未实装，将在1.2.0R或以上版本可用！" << endl;
	cout << "" << endl;
}
