#include "road.h"

using namespace std;

Road::Road(const int &size)
{
	setSizeOfRoad(size);

	int xc = 0, yc = 0;
	cout << "请输入这条路起点的横坐标：（从零开始，地图右上角坐标为（1，N））" << endl;
	cin >> yc;
	cout << "请输入这条路起点的纵坐标：（从零开始，地图左上角坐标为（1，1））" << endl;
	cin >> xc;
	
	setStartPointOfRoad(xc-1,yc-1);

	xc = 0, yc = 0;
	cout << "请输入这条路终点的横坐标：（从零开始，地图右下角坐标为（N，N））" << endl;
	cin >> yc;
	cout << "请输入这条路终点的纵坐标：（从零开始，地图左下角坐标为（N，1））" << endl;
	cin >> xc;

	setEndPointOfRoad(xc-1, yc-1);

	cout << "路线设定完毕" << endl;
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