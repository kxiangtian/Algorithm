#include "process_control.h"

using namespace std;

void testStart()
{
	int flag1 = 0, flag2 = 0;
	for (; ; )
	{
		cout << "�����������\n" << endl;

		cout << "1.��������е�վ��\n" << endl;
		cout << "2.�����վ���ľ���\n" << endl;
		cout << "3.������С��������������������轨��\n" << endl;
		cout << "0.�˳�\n" << endl;

		int user_input = 0;
		cin >> user_input;

		switch (user_input)
		{
		case 1:
			addPlace();
			flag1 = 1;
			break;

		case 2:
			if (flag1 == 1)
			{
				addLink();
				flag2 = 1;
			}
			else
			{
				cout << "������������е�վ��\n" << endl;
			}
			break;

		case 3:
			if (flag1 == 1 && flag2 == 1)
			{
				Kruskal();
				cout << "�ɹ����㽨�轨��\n" << endl;
			}
			else
			{
				cout << "������������е�վ���վ���ľ���\n" << endl;
			}
			break;

		case 0:
			return;
			break;

		default:
			cout << "�����������������\n" << endl;
			break;
		}
	}
}