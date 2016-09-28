#include <iostream>
#include "CRC.h"

using namespace std;

int main()
{
	while (1)
	{
		cout << "CRC测试样例\n" << endl;

		//原始码
		string codeOfInput;
		//生成码
		string codeOfBuild;


		//////////////////输入//////////////////
		cout << "请输入原始码！" << endl;
		cin >> codeOfInput;

		cout << "请输入生成码！" << endl;
		cin >> codeOfBuild;
		///////////////////////////////////////

		////////////////输出///////////////////
		cout << "\n生成的CRC为：" << CRC(codeOfInput, codeOfBuild)<<"\n"<<endl;
	}

	return 0;
}