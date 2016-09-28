#include "road.h"

using namespace std;

Road::Road(const int &size)
{
	setSizeOfRoad(size);

	int xc = 0, yc = 0;
	cout << "����������·���ĺ����꣺�����㿪ʼ����ͼ���Ͻ�����Ϊ��1��N����" << endl;
	cin >> yc;
	cout << "����������·���������꣺�����㿪ʼ����ͼ���Ͻ�����Ϊ��1��1����" << endl;
	cin >> xc;
	
	setStartPointOfRoad(xc-1,yc-1);

	xc = 0, yc = 0;
	cout << "����������·�յ�ĺ����꣺�����㿪ʼ����ͼ���½�����Ϊ��N��N����" << endl;
	cin >> yc;
	cout << "����������·�յ�������꣺�����㿪ʼ����ͼ���½�����Ϊ��N��1����" << endl;
	cin >> xc;

	setEndPointOfRoad(xc-1, yc-1);

	cout << "·���趨���" << endl;
}

void Road::setStartPointOfRoad(const int &x, const int &y)
{
	roadStartSiteX = x;
	roadStartSiteY = y;
}

void Road::setEndPointOfRoad(const int &x, const int &y)
{
	roadEndSiteX = x;
	roadEndSiteY = y;
}

void Road::setSizeOfRoad(const int &sz)
{
	roadSize = sz;
}

vector<int> Road::getStartPointOfRoad()
{
	return {roadStartSiteX,roadStartSiteY};
}

vector<int> Road::getEndPointOfRoad()
{
	return {roadEndSiteX,roadEndSiteY};
}

int Road::getSizeOfRoad()
{
	return roadSize;
}

void RoadMap::addRoadToRoadMap(const Road & rd)
{
	roads.push_back(rd);

	++roadCount;
}