#include "Astar.h"

using namespace std;

//���ڼ�¼�����б���Ԫ�صĸ���
int openListCount = 0;

//���ڼ�¼�ر��б���Ԫ�صĸ���
int closeListCount = 0;

//���ڼ�¼�ھӵĸ���
int neibNum = 0;

//������¼·�������ĵ�ĸ���
int AstackCount = 0;

//���ڼ�¼�ر��б����Ƿ����յ�
int FLAG = 0;

int startPointx, startPointy, endPointx, endPointy, sizex, sizey;

vector<vector<int>> Astar(int startPointX, int startPointY, int endPointX, int endPointY, const vector<vector<int>> &firstMap)
{
	auto be = firstMap.begin();

	const int sizeX = firstMap.size();
	const int sizeY = be->size();

	vector<vector<baseNode>> AstarMap = inputMap(sizeX,sizeY,firstMap);

	//�����б�����A*�㷨
	vector<baseNode> OpenList(sizeX*sizeY);

	//�ر��б�����A*�㷨
	vector<baseNode> CloseList(sizeX*sizeY);

	//��������������·��
	vector<baseNode> Astack(sizeX*sizeY);

	//�ھӽڵ�
	baseNode Neibo[8];

	startPointx = startPointX;
	startPointy = startPointY;
	endPointx = endPointX;
	endPointy = endPointY;
	sizex = sizeX;
	sizey = sizeY;

	return AstarO(Astack,Neibo,AstarMap,OpenList,CloseList);
}

vector<vector<baseNode>> inputMap(int sizeX,int sizeY, const vector<vector<int>> &firstMap)
{
	cout << "Ŀǰ��ͼ��СΪ" << sizeX << "*" << sizeY;

	vector<vector<baseNode>> AstarMap;
	vector<baseNode> temp(sizeY);

	for (int i=0;i<sizeX;++i)
	{
		AstarMap.push_back(temp);
	}

	for (int i=0;i<sizeX;++i)
	{
		for (int j=0;j<sizeY;++j)
		{
			AstarMap[i][j].weigt=firstMap[i][j];

			AstarMap[i][j].i = i;
			AstarMap[i][j].j = j;
		}
	}

	return AstarMap;
}

//���º�������A*�㷨��һ����///////////////////////////

//��һ��Ԫ�ز��뿪���б��У�ʹ�����б������С����ѵ�����/////////
void putInOpenList(baseNode &inList, vector<baseNode> &OpenList)
{
	++openListCount;

	OpenList[openListCount - 1] = inList;
	for (int i = openListCount - 1; i >0; i = (i - 1) / 2)
	{
		if (OpenList[i].f<OpenList[(i - 1) / 2].f)
		{
			OpenList[i] = OpenList[(i - 1) / 2];
			OpenList[(i - 1) / 2] = inList;
		}
		else
		{
			break;
		}
	}
}

//ȡ�������б���С����ѣ�����С����
struct baseNode readTopOpenList(vector<baseNode> &OpenList)
{
	return OpenList[0];
}

//��һ��Ԫ�ؼ���ر��б��У�ʹ�ر��б�����
void putInCloseList(baseNode &temp, vector<baseNode> &CloseList)
{
	CloseList[closeListCount] = temp;

	struct baseNode iter;
	for (int i = closeListCount; i>0; --i)
	{
		if ((CloseList[i].i*1000 + CloseList[i].j + 1)<(CloseList[i - 1].i*1000 + CloseList[i - 1].j + 1))
		{
			iter = CloseList[i];
			CloseList[i] = CloseList[i - 1];
			CloseList[i - 1] = iter;
		}
		else
		{
			break;
		}
	}
	++closeListCount;
}

//�ѿ����б��еĵ�ǰ�ڵ�ɾ����ʹ�������С����ѵ�����
void outOpenList(vector<baseNode> &OpenList)
{
	--openListCount;

	OpenList[0] = OpenList[openListCount];
	baseNode temp;

	for (int i = 0, p = 0; 2 * i + 1<openListCount; i = p)
	{
		if (2 * i + 2>openListCount - 1)
		{
			p = 2 * i + 1;
		}
		else
		{
			if (OpenList[2 * i + 1].f<OpenList[2 * i + 2].f)
			{
				p = 2 * i + 1;
			}
			else
			{
				p = 2 * i + 2;
			}
		}

		if (OpenList[p].f<OpenList[i].f)
		{
			temp = OpenList[p];
			OpenList[p] = OpenList[i];
			OpenList[i] = temp;
		}
		else
		{
			break;
		}
	}
}

//ɾ�������б���ָ����Ԫ�أ��ع���С�����
//��ע����������úܶ෽��ʵ�֣�ʾ���������ţ�
void outOpenList2(baseNode &iter, vector<baseNode> &OpenList)
{
	int number = openListCount - 1;
	vector<baseNode> openlist2(sizex*sizey);
	for (int i = 0; i < openListCount; ++i)
	{
		if (OpenList[i].i == iter.i&&OpenList[i].j == iter.j)
		{
			continue;
		}
		openlist2[i] = OpenList[i];
	}

	openListCount = 0;
	for (int i = 0; i < number; ++i)
	{
		putInOpenList(openlist2[i],OpenList);
	}
}

//����һ·�ϵ�ÿ���㣬�����������˸��ھӣ��������ھ��б�
void addNeibo(baseNode &iter,baseNode (&Neibo)[8], vector<vector<baseNode>> &AstarMap)
{
	neibNum = 0;

	for (int i = iter.i - 1; i <= iter.i + 1; ++i)
	{
		for (int j = iter.j - 1; j <= iter.j + 1; ++j)
		{
			if (i >= 0 && i <= sizex - 1 && j >= 0 && j <= sizey - 1)
			{
				if (i == iter.i&&j == iter.j)
				{
				}
				else
				{
					AstarMap[i][j].h = manhatten(i, j);

					Neibo[neibNum] = AstarMap[i][j];
					++neibNum;
				}
			}
		}
	}
}

//�鿴�ٽ����Ƿ��ڿ����б��еĺ���
int isInOpenList(baseNode &neibo, vector<baseNode> &OpenList)
{
	for (int i = 0; i < openListCount - 1; ++i)
	{
		if (OpenList[i].i == neibo.i&&OpenList[i].j == neibo.j)
		{
			return 1;
		}
	}
	return 0;
}

//�鿴ָ����temp�ڲ��ڹر��б��еĺ�����ʹ�����۰����
int isInCloseList(baseNode &temp, vector<baseNode> &CloseList)
{
	int low = 0, high = closeListCount - 1, mid = (low + high) / 2;

	for (; low <= high; mid = (low + high) / 2)
	{
		if ((CloseList[mid].i*1000 + CloseList[mid].j + 1) == (temp.i*1000 + temp.j + 1))
		{
			return 1;
		}
		else if ((CloseList[mid].i*1000 + CloseList[mid].j + 1) > (temp.i*1000 + temp.j + 1))
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return 0;
}

//A*�е�����ʽ������������ָ��λ�ú��յ�֮��������پ���
int manhatten(int i, int j)
{
	int a = (abs(endPointx - i) + abs(endPointy - j));
	if (a == 0)
	{
		FLAG = 1;
	}

	return a * 10;
}

//��ǰ���븸�׽ڵ�ľ���
int increment(baseNode &nthis)
{
	if ((abs(nthis.father->i - nthis.i) == 1) && (abs(nthis.father->j - nthis.j) == 1))
	{
		return 14 * nthis.weigt;
	}
	else if ((nthis.father->i - nthis.i) == 0 && (nthis.father->j - nthis.j) == 0)
	{
		return 0;
	}
	else
	{
		return 10 * nthis.weigt;
	}
}

//����õ�ǰ����Ϊ���ڵ�ʱ������Gֵ
int NewG(baseNode &nthis, baseNode &father)
{
	if (abs(father.i - nthis.i) == 1 && abs(father.j - nthis.j) == 1)
	{
		return father.g + 14;
	}
	else if (abs(father.i - nthis.i) == 0 && abs(father.j - nthis.j) == 0)
	{
		return father.g;
	}
	else
	{
		return father.g + 10;
	}
}

//��A*�㷨�Ľڵ㰴��������Astack����
void arrange(baseNode &iter, vector<baseNode> &Astack, vector<vector<baseNode>> &AstarMap)
{
	AstackCount = 0;
	for (; ; iter = AstarMap[iter.father->i][iter.father->j])
	{
		Astack[AstackCount] = iter;
		++AstackCount;
		if (iter.i == startPointx&&iter.j == startPointy)
		{
			break;
		}
	}
}

//Astar�ı���
vector<vector<int>> AstarO(vector<baseNode> &Astack, baseNode(&Neibo)[8], vector<vector<baseNode>> &AstarMap, vector<baseNode> &OpenList, vector<baseNode> &CloseList)
{
	//FLAG�����ж��յ��Ƿ��ڹر��б�
	FLAG = 0;
	//ÿ��ִ��A*�㷨������ʼ������/�ر��б�
	openListCount = 0;
	closeListCount = 0;

	//����һ��������,ÿ�ζ�����fֵ��С�Ľڵ�
	baseNode iter;

	//������������ĳ�ֵΪ���
	iter.i = startPointx;
	iter.j = startPointy;
	iter.weigt = AstarMap[startPointx][startPointy].weigt;

	//����û�и��ڵ㣬��ΪΨһGֵΪ0�ĵ�
	iter.g = 0;
	iter.h = manhatten(iter.i, iter.j);
	iter.f = iter.g + iter.h;

	//�����յ�
	baseNode ender;

	ender.i = endPointx;
	ender.j = endPointy;

	//�������뿪���б�
	putInOpenList(iter,OpenList);

	//�������б�Ϊ�ջ����յ��ڹر��б��У�����Ѱ��
	for (; openListCount != 0 && FLAG == 0;)
	{
		//ȡ�������б���fֵ��С�Ľڵ㣨֮һ��������Ϊiter����ǰ�㣩
		iter = readTopOpenList(OpenList);

		//����С��ӿ����б���ɾ��
		outOpenList(OpenList);

		//�ѵ�ǰ���¼�ڹر��б���
		putInCloseList(iter,CloseList);

		//�ѵ�ǰ����ھӼ����ھ��б�
		addNeibo(iter,Neibo, AstarMap);

		//����ÿ���ھӣ�������������в���
		for (int i = 0; i < neibNum; ++i)
		{
			//�������ھӽڵ㲻��ͨ������������ھӽڵ��ڹر��б��У��Թ���
			if (Neibo[i].weigt == 0 || isInCloseList(Neibo[i],CloseList))
			{
			}
			//�������ھӽڵ��Ѿ��ڿ����б���
			else if (isInOpenList(Neibo[i],OpenList))
			{
				if (NewG(Neibo[i], iter)<Neibo[i].g)
				{
					AstarMap[Neibo[i].i][Neibo[i].j].father = &AstarMap[iter.i][iter.j];
					AstarMap[Neibo[i].i][Neibo[i].j].g = AstarMap[iter.i][iter.j].g + increment(Neibo[i]);
					AstarMap[Neibo[i].i][Neibo[i].j].f = AstarMap[Neibo[i].i][Neibo[i].j].g + AstarMap[Neibo[i].i][Neibo[i].j].h;

					outOpenList2(Neibo[i],OpenList);
					putInOpenList(Neibo[i],OpenList);
				}
			}
			//�������ھӽڵ㲻�ڿ����б���
			else
			{
				AstarMap[Neibo[i].i][Neibo[i].j].father = Neibo[i].father = &AstarMap[iter.i][iter.j];
				AstarMap[Neibo[i].i][Neibo[i].j].g = AstarMap[iter.i][iter.j].g + increment(Neibo[i]);
				AstarMap[Neibo[i].i][Neibo[i].j].f = AstarMap[Neibo[i].i][Neibo[i].j].g + AstarMap[Neibo[i].i][Neibo[i].j].h;

				Neibo[i] = AstarMap[Neibo[i].i][Neibo[i].j];
				putInOpenList(Neibo[i],OpenList);
			}
		}
	}

	arrange(AstarMap[ender.i][ender.j], Astack, AstarMap);
	
	vector<vector<int>> finalMat;

	for (int i=0;i<AstackCount;++i)
	{
		vector<int> t2;

		t2.push_back(Astack[i].i);
		t2.push_back(Astack[i].j);

		finalMat.push_back(t2);
	}

	return finalMat;
}