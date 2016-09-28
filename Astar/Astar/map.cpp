#include "map.h"
#include "Astar.h"

using namespace std;

MapOfHouse::MapOfHouse(const int &sizeX, const int &sizeY)
{
	vector<int> te(sizeY, 0);
	for (int i = 0; i<sizeX; ++i)
	{
		landFrom.push_back(te);
	}

	RoadMap houseMap;

	vector<vector<vector<int>>> MapRoads;

	while (true)
	{
		cout << "是否要输入一条路径？当前路径数：" << houseMap.roadCount << "(Y/N)？" << endl;

		char ca;
		cin >> ca;

		if (ca == 'Y' || ca == 'y')
		{
			cout << "请输入路宽：" << endl;
			int k = 0;
			cin >> k;

			Road temp(k);
			houseMap.addRoadToRoadMap(temp);
		}
		else
		{
			break;
		}
	}
	
	cout << "正在计算地图..." << endl;

	vector<vector<int>> Fmap;

	vector<int> tem(sizeY, 1);
	for (int i = 0; i<sizeX; ++i)
	{
		Fmap.push_back(tem);
	}

	for (int i = 0; i<houseMap.roadCount; ++i)
	{
		vector<int> oppo = houseMap.roads[i].getStartPointOfRoad();
		vector<int> vivo = houseMap.roads[i].getEndPointOfRoad();

		vector<vector<int>> returnRoad = Astar(oppo[0], oppo[1], vivo[0], vivo[1], Fmap);

		MapRoads.push_back(returnRoad);

		for (auto &r : returnRoad)
		{
			landFrom[r[0]][r[1]] = 1;
		}

		int yo = houseMap.roads[i].getSizeOfRoad();

		vector<int> tt1 = houseMap.roads[i].getStartPointOfRoad();
		vector<int> tt2 = houseMap.roads[i].getEndPointOfRoad();

		if (tt1[0] == tt2[0])
		{
			int xP = tt1[0];

			int yPBegin = tt1[1];
			int yPEnd = tt2[1];

			for (int hj = yPBegin; hj <= yPEnd; ++hj)
			{
				int xBegin = 0, xEnd = 0;

				if (yo % 2 == 0)
				{
					if ((xP - (yo / 2) - 1)<0)
					{
						xBegin = 0;
					}
					else
					{
						xBegin = (xP - ((yo / 2) - 1));
					}
				}
				else
				{
					if ((xP - (yo / 2))<0)
					{
						xBegin = 0;
					}
					else
					{
						xBegin = (xP - (yo / 2));
					}
				}

				if ((xP + (yo / 2))>sizeY - 1)
				{
					xEnd = sizeY - 1;
				}
				else
				{
					xEnd = (xP + (yo / 2));
				}

				for (int bb = yPBegin; bb <= yPEnd; ++bb)
				{
					for (int ss = xBegin; ss <= xEnd; ++ss)
					{
						landFrom[ss][bb] = 1;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i<sizeX; ++i)
			{
				for (int j = 0; j < sizeY; ++j)
				{
					bool flag = false;

					for (auto &vf : returnRoad)
					{
						if (vf[0] == i&&vf[1] == j)
						{
							flag = true;
							break;
						}
					}

					if (flag)
					{
						//左右
						int lvalue = 0, Rvalue = 0;
						if (yo % 2 == 0)
						{
							lvalue = yo / 2 - 1;
							Rvalue = yo / 2;
						}
						else
						{
							lvalue = yo / 2;
							Rvalue = yo / 2;
						}

						int xst = 0, xen = 0;
						if (j - lvalue<0)
						{
							xst = 0;
						}
						else
						{
							xst = j - lvalue;
						}

						if (j + Rvalue>sizeY - 1)
						{
							xen = sizeY - 1;

							j = sizeY - 1;
						}
						else
						{
							xen = j + Rvalue;

							j += (lvalue + 1);
						}

						for (int ho = xst; ho <= xen; ho++)
						{
							landFrom[i][ho] = 1;
						}
					}
				}
			}
		}
	}

	//计算交叉路口的个数和坐标
	vector<vector<int>> allRoadsPoint;

	for (auto &b : MapRoads)
	{
		for (auto &h : b)
		{
			allRoadsPoint.push_back(h);
		}
	}

	sort(allRoadsPoint.begin(), allRoadsPoint.end());

	auto iterf = allRoadsPoint.begin();
	auto oldN = iterf;

	while (iterf != (--allRoadsPoint.end()))
	{
		oldN = iterf;
		++iterf;
		if ((*oldN)[0] == (*iterf)[0] && (*oldN)[1] == (*iterf)[1])
		{
			roadCrossPoint.push_back(*oldN);

			allRoadsPoint.erase(oldN);

			iterf = allRoadsPoint.begin();
		}
	}

	showMap();
}

bool MapOfHouse::readMapFromTxt(string &filename1, string &filename2)
{
	//maptxt

	fstream thefile(filename1+".txt");

	if (thefile.is_open())
	{
		vector<string> maptxt;
		
		string temp; maptxt.push_back(temp);

		int i = 0;
		while (getline(thefile,maptxt[i]))
		{
			maptxt.push_back(temp);
			++i;
		}

		for (auto &r:maptxt)
		{
			vector<int> ty;
			for (auto &c:r)
			{
				int temp=0;
				stringstream cc;
				cc << c;
				cc >> temp;

				ty.push_back(temp);
			}

			landFrom.push_back(ty);
			ty.clear();
		}

		thefile.close();
	}
	else
	{
		cout << "文件不存在！" << endl;
		return false;
	}

	//roadtxt
	fstream thefile2(filename2 + ".txt");

	if (thefile2.is_open())
	{
		vector<vector<int>> trm;
		vector<int> tep;

		string s;
		while (getline(thefile2, s))
		{
			stringstream ss;
			ss << s;
			int tx = 0;
			ss >> tx;

			s.clear();
			ss.clear();
			int ty = 0;

			getline(thefile2, s);
			ss << s;
			ss >> ty;

			tep.push_back(tx);
			tep.push_back(ty);

			trm.push_back(tep);

			tep.clear();
		}

		roadCrossPoint = trm;

		thefile2.close();

		return true;
	}
	else
	{
		cout << "文件不存在！" << endl;
		return false;
	}
}

void MapOfHouse::saveMapToTxt(string &filename1,string &filename2)
{
	//maptxt

	string s="cd.>"+filename1+".txt";

	system(s.c_str());

	fstream fst(filename1 + ".txt");

	for(auto &t:landFrom)	
	{ 
		for (auto &r:t)
		{
			stringstream cc;
			cc << r;

			string c; cc >> c;

			fst << c;
		}
		fst << '\n';
	}

	fst.close();

	//roadtxt

	s = "cd.>" + filename2 + ".txt";

	system(s.c_str());

	fstream fst2(filename2 + ".txt");

	for (auto &r:roadCrossPoint)
	{
		for (auto &t:r)
		{
			string temo;
			stringstream se; se << t;
			se >> temo;
			temo += '\n';

			fst2 << temo;
		}
	}

	fst2.close();
}

void MapOfHouse::changeMapPoint(int x, int y, int value)
{
	landFrom[x][y] = value;
}

void MapOfHouse::showMap()
{
	cout << "地图样式如下:\n" << endl;

	for (auto &r: landFrom)
	{
		for (auto &i:r)
		{
			cout << i<<" ";
		}
		cout << endl;
	}

	cout << "共有"<<roadCrossPoint.size()<<"个完全重合路段" << endl;

	for (int i=0;i<roadCrossPoint.size();++i)
	{
		cout << "第"<<i+1<<"个交叉路口坐标：" << endl;

		cout << "X：" << roadCrossPoint[i][0] +1<< "\nY: " << roadCrossPoint[i][1] +1<< endl;
	}
}

std::vector<std::vector<int>> MapOfHouse::backLandFrom()
{
	return landFrom;
}