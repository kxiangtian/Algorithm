#include <iostream>
#include "CRC.h"

using namespace std;

int main()
{
	while (1)
	{
		cout << "CRC��������\n" << endl;

		//ԭʼ��
		string codeOfInput;
		//������
		string codeOfBuild;


		//////////////////����//////////////////
		cout << "������ԭʼ�룡" << endl;
		cin >> codeOfInput;

		cout << "�����������룡" << endl;
		cin >> codeOfBuild;
		///////////////////////////////////////

		////////////////���///////////////////
		cout << "\n���ɵ�CRCΪ��" << CRC(codeOfInput, codeOfBuild)<<"\n"<<endl;
	}

	return 0;
}