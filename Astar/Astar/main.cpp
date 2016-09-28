#include "main.h"
#include "Astar.h"

using namespace std;

int main()
{
	runThis();

	return 0;
}

void runThis()
{
	cout << "自动寻路程序\n" << endl;

	bool flag1 = false;
	MapOfHouse thisMap;

	while (true)
	{
		cout << "请输入对应的序号进行操作：" << endl;
		cout << "1、构建地图地形信息" << endl;
		cout << "2、从txt文件中构建小区地形信息" << endl;
		cout << "3、把地图地形信息保存到txt文件" << endl;
		cout << "4、查看地图地形信息" << endl;
		cout << "5、设定起点和终点并寻路" << endl;
		cout << "6、清除之前所有的设定" << endl;

		int userInput = 0;
		cin >> userInput;

		switch (userInput)
		{
		case 1:
		{
			buildMapInfo(thisMap,flag1);
		}
		break;

		case 2:
		{
			if (flag1)
			{
				cout << "已经有之前设定好的地图地形信息，是否覆盖（Y/N）?" << endl;

				char temp;
				cin >> temp;

				if (temp == 'Y' || temp == 'y')
				{
					clearRemember(thisMap);
					cout << "请输入要从中读取数据的地图文件名字：" << endl;
					string nam;
					cin >> nam;

					cout << "请输入要从中读取数据的路口数据文件名字：" << endl;
					string nam2;
					cin >> nam2;

					if (thisMap.readMapFromTxt(nam, nam2))
					{
						flag1 = true;

						cout << "成功读取文件内的地图数据\n" << endl;
					}
				}
				else
				{
					cout << "保留了之前的地图数据\n" << endl;
				}
			}
			else
			{
				cout << "请输入要从中读取数据的地图文件名字：" << endl;
				string nam;
				cin >> nam;

				cout << "请输入要从中读取数据的路口数据文件名字：" << endl;
				string nam2;
				cin >> nam2;

				if (thisMap.readMapFromTxt(nam, nam2))
				{
					flag1 = true;

					cout << "成功读取文件内的地图数据\n" << endl;
				}
			}
		}
		break;

		case 3:
		{
			if (flag1)
			{
				cout << "请输入要保存数据的地图文件名字：" << endl;
				string nam;
				cin >> nam;

				cout << "请输入要保存数据的路口数据文件名字：" << endl;
				string nam2;
				cin >> nam2;

				thisMap.saveMapToTxt(nam,nam2);
			}
			else
			{
				cout << "首先你得先有一张地图" << endl;
			}
		}
		break;

		case 4:
		{
			cout << "地图里0代表不可通过的格子，1代表可以通过的格子，你也可以把地图保存为txt文件，之后用记事本打开txt文件，并改变txt文件中地图格子的权值（比如1为容易通过的路，9为很难通过但是存在的路线）\n" << endl;

			if (flag1)
			{
				thisMap.showMap();
			}
			else
			{
				cout << "首先你得先有一张地图" << endl;
			}
		}
		break;

		case 5:
		{
			findAWay(thisMap, flag1);
		}
		break;

		case 6:
		{
			if (flag1)
			{
				cout << "\n" << endl;
				flag1 = false;

				clearRemember(thisMap);
			}
			else
			{
				cout << "请先构建地图地形信息\n" << endl;
			}
		}
		break;

		default:
			cout << "输入有误，请重新输入！\n" << endl;
			break;
		}
	}
}

void buildMapInfo(MapOfHouse &thisMap,bool &flag)
{
	if (flag)
	{
		cout << "已经有之前设定好的地图地形信息，是否覆盖（Y/N）?\n" << endl;

		char temp;
		cin >> temp;

		if (temp == 'Y' || temp == 'y')
		{
			clearRemember(thisMap);
			cout << "现在可以进行重新设定地图地形了\n" << endl;

			int mx = 0, my = 0;

			cout << "请输入地图长度：" << endl;
			cin >> my;
			cout << "请输入地图宽度：" << endl;
			cin >> mx;

			MapOfHouse am(mx, my);

			thisMap = am;
		}
		else if (temp == 'N' || temp == 'n')
		{
			cout << "保留了之前的地图数据\n" << endl;
		}
		else
		{
			cout << "输入有误，请重新选择要进行的操作！\n" << endl;
		}
	}
	else
	{
		flag = true;
		cout << "现在可以设定地图地形信息了\n" << endl;

		int mx = 0, my = 0;

		cout << "请输入地图长度：" << endl;
		cin >> my;
		cout << "请输入地图宽度：" << endl;
		cin >> mx;

		MapOfHouse am(mx, my);

		thisMap = am;
	}
}

void findAWay(MapOfHouse &thisMap, bool &flag)
{
	if (flag)
	{
		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

		cout << "请输入起点横坐标（下标从1开始）" << endl;
		cin >> y1;
		cout << "请输入起点纵坐标（下标从1开始）" << endl;
		cin >> x1;

		cout << "请输入终点横坐标（下标从1开始）" << endl;
		cin >> y2;
		cout << "请输入终点纵坐标（下标从1开始）" << endl;
		cin >> x2;

		cout << "开始寻路：" << endl;

		vector<vector<int>> roadis;
		vector<vector<int>> xmap = thisMap.backLandFrom();

		roadis = Astar(x1 - 1, y1 - 1, x2 - 1, y2 - 1, xmap);

		vector<int> T1;
		T1.push_back(x1 - 1);
		T1.push_back(y1 - 1);

		roadis.push_back(T1);

		vector<int> T2;
		T2.push_back(x2 - 1);
		T2.push_back(y2 - 1);

		roadis.push_back(T2);

		cout << endl;

		auto be = xmap.begin();

		const int Sx = xmap.size();
		const int Sy = be->size();

		for (int i = 0; i<Sx; ++i)
		{
			for (int j = 0; j<Sy; ++j)
			{
				bool PriA = false;
				for (auto &lk : roadis)
				{
					if (i == lk[0] && j == lk[1])
					{
						cout << "A ";
						PriA = true;
						break;
					}
				}

				if (!PriA)
				{
					cout << "X ";
				}
			}
			cout << endl;
		}

		cout << "寻路成功，X为路径之外地块，A为要走的路" << endl;
	}
	else
	{
		cout << "请先构建地图地形信息\n" << endl;
	}
}

void clearRemember(MapOfHouse &thisMap)
{
	MapOfHouse of;
	thisMap = of;
}