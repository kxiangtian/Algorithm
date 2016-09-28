#include "process_control.h"

using namespace std;

void testStart()
{
	int flag1 = 0, flag2 = 0;
	for (; ; )
	{
		cout << "地铁建设程序\n" << endl;

		cout << "1.输入地铁中的站点\n" << endl;
		cout << "2.输入各站点间的距离\n" << endl;
		cout << "3.计算最小生成树并且输出地铁建设建议\n" << endl;
		cout << "0.退出\n" << endl;

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
				cout << "请先输入地铁中的站点\n" << endl;
			}
			break;

		case 3:
			if (flag1 == 1 && flag2 == 1)
			{
				Kruskal();
				cout << "成功计算建设建议\n" << endl;
			}
			else
			{
				cout << "请先输入地铁中的站点和站点间的距离\n" << endl;
			}
			break;

		case 0:
			return;
			break;

		default:
			cout << "输入错误，请重新输入\n" << endl;
			break;
		}
	}
}