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
	cout << "�����й��ܵ�ǰ��δʵװ������1.2.0R�����ϰ汾���ã�" << endl;
	cout << "" << endl;
}
