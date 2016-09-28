#include "funcs.h"

using namespace std;

const int MaxNum = 100;

//////全局变量
//地点
string placeName[MaxNum];
//地点个数
int placeNameCount = 0;

//边
struct vex mapVex[MaxNum*MaxNum];
//边的个数
int mapVexCount = 0;

//确认建立的边
struct vex buildVex[MaxNum*MaxNum];
//确认建立的边的个数
int buildVexCount = 0;

//关系集合
int linkUnion[MaxNum][MaxNum] = { 0 };
//每组关系的个数
int linkUnionCount[MaxNum] = { 0 };


//////函数
//添加站点
void addPlace()
{
	cout << "请输入站点个数：" << endl;

	cin >> placeNameCount;

	for (int i = 0; i < placeNameCount; ++i)
	{
		cout << "请输入第" << i + 1 << "个站点的名称" << endl;
		cin >> placeName[i];
	}
	cout << "完成站点输入" << endl << endl;
}

//使边的列表按照从小到大排序
void putInMapVex(vex &temp)
{
	mapVex[mapVexCount] = temp;

	for (int i = mapVexCount; i > 0; --i)
	{
		if (mapVex[i].weigh<mapVex[i - 1].weigh)
		{
			mapVex[i] = mapVex[i - 1];
			mapVex[i - 1] = temp;
		}
		else
		{
			break;
		}
	}
	++mapVexCount;
}

//添加边
void addLink()
{
	for (; ; )
	{
		int v1 = 0, v2 = 0, weigh = 0;
		struct vex temp;

		cout << "请输入一个站点的序号：" << endl;
		cout << "最小的站点序号是1" << endl;
		cout << "你也可以输入0来结束输入" << endl;

		cin >> v1;

		if (v1 == 0)
		{
			cout << "完成距离输入" << endl;
			break;
		}

		cout << "请输入和这个站点相连的另外一个站点的序号：" << endl;
		cin >> v2;

		temp.i = v1 - 1;
		temp.j = v2 - 1;

		cout << "请输入站点" << v1 << "和站点" << v2 << "之间的距离：" << endl;
		cin >> weigh;
		temp.weigh = weigh;

		putInMapVex(temp);
		cout << "\n请继续输入两个站点的序号:" << endl;
	}
}

//寻找点所在的集合，返回这一点对应的关系集合的一维数组下标
int findUnion(int point)
{
	for (int i = 0; i < placeNameCount; ++i)
	{
		for (int j = 0; j < linkUnionCount[i]; ++j)
		{
			if (linkUnion[i][j] == point)
			{
				return i;
			}
		}
	}
	return -1;
}

//KrusKal算法本体
void Kruskal()
{
	//对于从小到大的现有边集合中每一条边
	for (int i = 0; buildVexCount != placeNameCount - 1; ++i)
	{
		int pointI = mapVex[i].i;
		int pointJ = mapVex[i].j;

		//查找他们所在的集合
		int UnionI = findUnion(pointI);
		int UnionJ = findUnion(pointJ);

		//如果这条边的两个顶点不属于同一个关系集合，执行下面语句，否则什么也不做
		if (!(UnionI == UnionJ&&UnionI != -1))
		{
			//当这两个点都不在任何关系集合中
			if (UnionI == UnionJ)
			{
				if (UnionI == -1)
				{
					//找到关系集合二维数组中还没有加入元素的那一行
					for (int i = 0; i < placeNameCount; ++i)
					{
						if (linkUnionCount[i] == 0)
						{
							break;
						}
					}
					//把这条边的两个端点都加入那一行的关系集合中
					linkUnion[i][0] = pointI;
					linkUnion[i][1] = pointJ;
					linkUnionCount[i] = 2;
				}
			}
			else
			{
				//如果端点1不在关系集合里，并且端点2已经属于一个关系集合
				if (UnionI == -1 && UnionJ<-1)
				{
					//更新端点2所在的集合，使其包含端点1
					linkUnion[UnionJ][linkUnionCount[UnionJ]] = pointI;
					++linkUnionCount[UnionJ];
				}
				//如果端点2不在关系集合里，并且端点1已经属于一个关系集合
				else if (UnionJ == -1 && UnionI<-1)
				{
					//更新端点1所在的集合，使其包含端点2
					linkUnion[UnionI][linkUnionCount[UnionI]] = pointJ;
					++linkUnionCount[UnionI];
				}
				//如果端点1和端点2在不同的集合里
				else
				{
					//对于端点2所在集合的每一个点
					for (int j = 0; j < linkUnionCount[UnionJ]; ++j)
					{
						//比较端点1所在集合的每一个点
						int i = 0;
						for (; i < linkUnionCount[UnionI]; ++i)
						{
							//如果这两个点相等，什么都不做
							if (linkUnion[UnionI][i] == linkUnion[UnionJ][j])
							{
								break;
							}
						}

						//遍历了端点1集合里的每一个点后，如果没有匹配
						if (i == linkUnionCount[UnionI])
						{
							//把这个没有出现在端点1所在集合里的点放入端点1所在的集合
							linkUnion[UnionI][linkUnionCount[UnionI]] = linkUnion[UnionJ][j];
							++linkUnionCount[UnionI];
						}
					}
					//清空端点2所在的关系列表
					linkUnionCount[UnionJ] = 0;
				}
			}

			//把这条边加入确认建立的边
			struct vex temp;
			temp.i = mapVex[i].i;
			temp.j = mapVex[i].j;
			temp.weigh = mapVex[i].weigh;

			buildVex[buildVexCount] = temp;
			++buildVexCount;
		}
	}

	//mix记载总里程数
	int mix = 0;
	//对于确认建立路线集合中每一个元素，输出它们的信息
	for (int i = 0; i < buildVexCount; ++i)
	{
		cout << "应建设的第" << i + 1 << "条线路：" << endl;
		cout << "起点序号：" << buildVex[i].i + 1 << endl;
		cout << "起点名称：" << placeName[buildVex[i].i] << endl;
		cout << "终点序号：" << buildVex[i].j + 1 << endl;
		cout << "终点名称：" << placeName[buildVex[i].j] << endl;;
		cout << "路线里程：" << buildVex[i].weigh << "\n" << endl;

		mix += buildVex[i].weigh;
	}
	cout << "总里程数：" << mix << "\n" << endl;
}