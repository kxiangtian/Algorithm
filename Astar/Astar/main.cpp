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
	cout << "�Զ�Ѱ·����\n" << endl;

	bool flag1 = false;
	MapOfHouse thisMap;

	while (true)
	{
		cout << "�������Ӧ����Ž��в�����" << endl;
		cout << "1��������ͼ������Ϣ" << endl;
		cout << "2����txt�ļ��й���С��������Ϣ" << endl;
		cout << "3���ѵ�ͼ������Ϣ���浽txt�ļ�" << endl;
		cout << "4���鿴��ͼ������Ϣ" << endl;
		cout << "5���趨�����յ㲢Ѱ·" << endl;
		cout << "6�����֮ǰ���е��趨" << endl;

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
				cout << "�Ѿ���֮ǰ�趨�õĵ�ͼ������Ϣ���Ƿ񸲸ǣ�Y/N��?" << endl;

				char temp;
				cin >> temp;

				if (temp == 'Y' || temp == 'y')
				{
					clearRemember(thisMap);
					cout << "������Ҫ���ж�ȡ���ݵĵ�ͼ�ļ����֣�" << endl;
					string nam;
					cin >> nam;

					cout << "������Ҫ���ж�ȡ���ݵ�·�������ļ����֣�" << endl;
					string nam2;
					cin >> nam2;

					if (thisMap.readMapFromTxt(nam, nam2))
					{
						flag1 = true;

						cout << "�ɹ���ȡ�ļ��ڵĵ�ͼ����\n" << endl;
					}
				}
				else
				{
					cout << "������֮ǰ�ĵ�ͼ����\n" << endl;
				}
			}
			else
			{
				cout << "������Ҫ���ж�ȡ���ݵĵ�ͼ�ļ����֣�" << endl;
				string nam;
				cin >> nam;

				cout << "������Ҫ���ж�ȡ���ݵ�·�������ļ����֣�" << endl;
				string nam2;
				cin >> nam2;

				if (thisMap.readMapFromTxt(nam, nam2))
				{
					flag1 = true;

					cout << "�ɹ���ȡ�ļ��ڵĵ�ͼ����\n" << endl;
				}
			}
		}
		break;

		case 3:
		{
			if (flag1)
			{
				cout << "������Ҫ�������ݵĵ�ͼ�ļ����֣�" << endl;
				string nam;
				cin >> nam;

				cout << "������Ҫ�������ݵ�·�������ļ����֣�" << endl;
				string nam2;
				cin >> nam2;

				thisMap.saveMapToTxt(nam,nam2);
			}
			else
			{
				cout << "�����������һ�ŵ�ͼ" << endl;
			}
		}
		break;

		case 4:
		{
			cout << "��ͼ��0������ͨ���ĸ��ӣ�1�������ͨ���ĸ��ӣ���Ҳ���԰ѵ�ͼ����Ϊtxt�ļ���֮���ü��±���txt�ļ������ı�txt�ļ��е�ͼ���ӵ�Ȩֵ������1Ϊ����ͨ����·��9Ϊ����ͨ�����Ǵ��ڵ�·�ߣ�\n" << endl;

			if (flag1)
			{
				thisMap.showMap();
			}
			else
			{
				cout << "�����������һ�ŵ�ͼ" << endl;
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
				cout << "���ȹ�����ͼ������Ϣ\n" << endl;
			}
		}
		break;

		default:
			cout << "�����������������룡\n" << endl;
			break;
		}
	}
}

void buildMapInfo(MapOfHouse &thisMap,bool &flag)
{
	if (flag)
	{
		cout << "�Ѿ���֮ǰ�趨�õĵ�ͼ������Ϣ���Ƿ񸲸ǣ�Y/N��?\n" << endl;

		char temp;
		cin >> temp;

		if (temp == 'Y' || temp == 'y')
		{
			clearRemember(thisMap);
			cout << "���ڿ��Խ��������趨��ͼ������\n" << endl;

			int mx = 0, my = 0;

			cout << "�������ͼ���ȣ�" << endl;
			cin >> my;
			cout << "�������ͼ��ȣ�" << endl;
			cin >> mx;

			MapOfHouse am(mx, my);

			thisMap = am;
		}
		else if (temp == 'N' || temp == 'n')
		{
			cout << "������֮ǰ�ĵ�ͼ����\n" << endl;
		}
		else
		{
			cout << "��������������ѡ��Ҫ���еĲ�����\n" << endl;
		}
	}
	else
	{
		flag = true;
		cout << "���ڿ����趨��ͼ������Ϣ��\n" << endl;

		int mx = 0, my = 0;

		cout << "�������ͼ���ȣ�" << endl;
		cin >> my;
		cout << "�������ͼ��ȣ�" << endl;
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

		cout << "�������������꣨�±��1��ʼ��" << endl;
		cin >> y1;
		cout << "��������������꣨�±��1��ʼ��" << endl;
		cin >> x1;

		cout << "�������յ�����꣨�±��1��ʼ��" << endl;
		cin >> y2;
		cout << "�������յ������꣨�±��1��ʼ��" << endl;
		cin >> x2;

		cout << "��ʼѰ·��" << endl;

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

		cout << "Ѱ·�ɹ���XΪ·��֮��ؿ飬AΪҪ�ߵ�·" << endl;
	}
	else
	{
		cout << "���ȹ�����ͼ������Ϣ\n" << endl;
	}
}

void clearRemember(MapOfHouse &thisMap)
{
	MapOfHouse of;
	thisMap = of;
}