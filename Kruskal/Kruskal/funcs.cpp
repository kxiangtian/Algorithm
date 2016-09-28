#include "funcs.h"

using namespace std;

const int MaxNum = 100;

//////ȫ�ֱ���
//�ص�
string placeName[MaxNum];
//�ص����
int placeNameCount = 0;

//��
struct vex mapVex[MaxNum*MaxNum];
//�ߵĸ���
int mapVexCount = 0;

//ȷ�Ͻ����ı�
struct vex buildVex[MaxNum*MaxNum];
//ȷ�Ͻ����ıߵĸ���
int buildVexCount = 0;

//��ϵ����
int linkUnion[MaxNum][MaxNum] = { 0 };
//ÿ���ϵ�ĸ���
int linkUnionCount[MaxNum] = { 0 };


//////����
//���վ��
void addPlace()
{
	cout << "������վ�������" << endl;

	cin >> placeNameCount;

	for (int i = 0; i < placeNameCount; ++i)
	{
		cout << "�������" << i + 1 << "��վ�������" << endl;
		cin >> placeName[i];
	}
	cout << "���վ������" << endl << endl;
}

//ʹ�ߵ��б��մ�С��������
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

//��ӱ�
void addLink()
{
	for (; ; )
	{
		int v1 = 0, v2 = 0, weigh = 0;
		struct vex temp;

		cout << "������һ��վ�����ţ�" << endl;
		cout << "��С��վ�������1" << endl;
		cout << "��Ҳ��������0����������" << endl;

		cin >> v1;

		if (v1 == 0)
		{
			cout << "��ɾ�������" << endl;
			break;
		}

		cout << "����������վ������������һ��վ�����ţ�" << endl;
		cin >> v2;

		temp.i = v1 - 1;
		temp.j = v2 - 1;

		cout << "������վ��" << v1 << "��վ��" << v2 << "֮��ľ��룺" << endl;
		cin >> weigh;
		temp.weigh = weigh;

		putInMapVex(temp);
		cout << "\n�������������վ������:" << endl;
	}
}

//Ѱ�ҵ����ڵļ��ϣ�������һ���Ӧ�Ĺ�ϵ���ϵ�һά�����±�
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

//KrusKal�㷨����
void Kruskal()
{
	//���ڴ�С��������б߼�����ÿһ����
	for (int i = 0; buildVexCount != placeNameCount - 1; ++i)
	{
		int pointI = mapVex[i].i;
		int pointJ = mapVex[i].j;

		//�����������ڵļ���
		int UnionI = findUnion(pointI);
		int UnionJ = findUnion(pointJ);

		//��������ߵ��������㲻����ͬһ����ϵ���ϣ�ִ��������䣬����ʲôҲ����
		if (!(UnionI == UnionJ&&UnionI != -1))
		{
			//���������㶼�����κι�ϵ������
			if (UnionI == UnionJ)
			{
				if (UnionI == -1)
				{
					//�ҵ���ϵ���϶�ά�����л�û�м���Ԫ�ص���һ��
					for (int i = 0; i < placeNameCount; ++i)
					{
						if (linkUnionCount[i] == 0)
						{
							break;
						}
					}
					//�������ߵ������˵㶼������һ�еĹ�ϵ������
					linkUnion[i][0] = pointI;
					linkUnion[i][1] = pointJ;
					linkUnionCount[i] = 2;
				}
			}
			else
			{
				//����˵�1���ڹ�ϵ��������Ҷ˵�2�Ѿ�����һ����ϵ����
				if (UnionI == -1 && UnionJ<-1)
				{
					//���¶˵�2���ڵļ��ϣ�ʹ������˵�1
					linkUnion[UnionJ][linkUnionCount[UnionJ]] = pointI;
					++linkUnionCount[UnionJ];
				}
				//����˵�2���ڹ�ϵ��������Ҷ˵�1�Ѿ�����һ����ϵ����
				else if (UnionJ == -1 && UnionI<-1)
				{
					//���¶˵�1���ڵļ��ϣ�ʹ������˵�2
					linkUnion[UnionI][linkUnionCount[UnionI]] = pointJ;
					++linkUnionCount[UnionI];
				}
				//����˵�1�Ͷ˵�2�ڲ�ͬ�ļ�����
				else
				{
					//���ڶ˵�2���ڼ��ϵ�ÿһ����
					for (int j = 0; j < linkUnionCount[UnionJ]; ++j)
					{
						//�Ƚ϶˵�1���ڼ��ϵ�ÿһ����
						int i = 0;
						for (; i < linkUnionCount[UnionI]; ++i)
						{
							//�������������ȣ�ʲô������
							if (linkUnion[UnionI][i] == linkUnion[UnionJ][j])
							{
								break;
							}
						}

						//�����˶˵�1�������ÿһ��������û��ƥ��
						if (i == linkUnionCount[UnionI])
						{
							//�����û�г����ڶ˵�1���ڼ�����ĵ����˵�1���ڵļ���
							linkUnion[UnionI][linkUnionCount[UnionI]] = linkUnion[UnionJ][j];
							++linkUnionCount[UnionI];
						}
					}
					//��ն˵�2���ڵĹ�ϵ�б�
					linkUnionCount[UnionJ] = 0;
				}
			}

			//�������߼���ȷ�Ͻ����ı�
			struct vex temp;
			temp.i = mapVex[i].i;
			temp.j = mapVex[i].j;
			temp.weigh = mapVex[i].weigh;

			buildVex[buildVexCount] = temp;
			++buildVexCount;
		}
	}

	//mix�����������
	int mix = 0;
	//����ȷ�Ͻ���·�߼�����ÿһ��Ԫ�أ�������ǵ���Ϣ
	for (int i = 0; i < buildVexCount; ++i)
	{
		cout << "Ӧ����ĵ�" << i + 1 << "����·��" << endl;
		cout << "�����ţ�" << buildVex[i].i + 1 << endl;
		cout << "������ƣ�" << placeName[buildVex[i].i] << endl;
		cout << "�յ���ţ�" << buildVex[i].j + 1 << endl;
		cout << "�յ����ƣ�" << placeName[buildVex[i].j] << endl;;
		cout << "·����̣�" << buildVex[i].weigh << "\n" << endl;

		mix += buildVex[i].weigh;
	}
	cout << "���������" << mix << "\n" << endl;
}