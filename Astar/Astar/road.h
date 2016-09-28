#ifndef _ROAD_H_
#define _ROAD_H_

#include <iostream>
#include <vector>
#include <list>

class Road
{
public:
	Road() = default;
	Road(const int &size);

	void setStartPointOfRoad(const int &x,const int &y);
	void setEndPointOfRoad(const int &x, const int &y);
	void setSizeOfRoad(const int &sz);

	std::vector<int> getStartPointOfRoad();
	std::vector<int> getEndPointOfRoad();
	int getSizeOfRoad();

private:
	int roadSize = 0;

	int roadStartSiteX = 0;
	int roadStartSiteY = 0;

	int roadEndSiteX = 0;
	int roadEndSiteY = 0;
};

struct RoadMap
{
	//Funcs
	void addRoadToRoadMap(const Road &rd);

	//Data
	std::vector<Road> roads;
	int roadCount = 0;
};

#endif