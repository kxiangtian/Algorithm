#ifndef _ASTAR_H_
#define _ASTAR_H

#include <iostream>
#include <cmath>
#include <vector>

//һ���Ƚϻ����Ľṹ�壬���ں͵�ͼ����
struct baseNode
{
	int i=0;
	int j=0;
	int weigt=0;

	int f=0;
	int g=0;
	int h=0;

	struct baseNode *father=nullptr;
};

std::vector<std::vector<baseNode>> inputMap(int sizeX, int sizeY, const std::vector<std::vector<int>> &firstMap);
std::vector<std::vector<int>> Astar(int startPointX, int startPointY, int endPointX, int endPointY, const std::vector<std::vector<int>> &firstMap);

void putInOpenList(baseNode &inList, std::vector<baseNode> &OpenList);

//ȡ�������б���С����ѣ�����С����
baseNode readTopOpenList(std::vector<baseNode> &OpenList);

//��һ��Ԫ�ؼ���ر��б��У�ʹ�ر��б�����
void putInCloseList(baseNode &temp, std::vector<baseNode> &CloseList);

//�ѿ����б��еĵ�ǰ�ڵ�ɾ����ʹ�������С����ѵ�����
void outOpenList(std::vector<baseNode> &OpenList);

//��ע����������úܶ෽��ʵ�֣�ʾ���������ţ�
void outOpenList2(baseNode &iter, std::vector<baseNode> &OpenList);

//����һ·�ϵ�ÿ���㣬�����������˸��ھӣ��������ھ��б�
void addNeibo(baseNode &iter, baseNode(&Neibo)[8], std::vector<std::vector<baseNode>> &AstarMap);

//�鿴�ٽ����Ƿ��ڿ����б��еĺ���
int isInOpenList(baseNode &neibo, std::vector<baseNode> &OpenList);

//�鿴ָ����temp�ڲ��ڹر��б��еĺ�����ʹ�����۰����
int isInCloseList(baseNode &temp, std::vector<baseNode> &CloseList);

//A*�е�����ʽ������������ָ��λ�ú��յ�֮��������پ���
int manhatten(int i, int j);

//��ǰ���븸�׽ڵ�ľ���
int increment(baseNode &nthis);

//����õ�ǰ����Ϊ���ڵ�ʱ������Gֵ
int NewG(baseNode &nthis, baseNode &father);

//��A*�㷨�Ľڵ㰴��������Astack����
void arrange(baseNode &iter, std::vector<baseNode> &Astack, std::vector<std::vector<baseNode>> &AstarMap);

//Astar�ı���
std::vector<std::vector<int>> AstarO(std::vector<baseNode> &Astack, baseNode(&Neibo)[8], std::vector<std::vector<baseNode>> &AstarMap, std::vector<baseNode> &OpenList, std::vector<baseNode> &CloseList);

#endif