#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "road.h"

class MapOfHouse
{
public:
	MapOfHouse() = default;
	MapOfHouse(const int &sizeX,const int &sizeY);

	bool readMapFromTxt(std::string &filename1, std::string &filename2);
	void saveMapToTxt(std::string &filename1, std::string &filename2);

	void changeMapPoint(int x,int y,int value);

	void showMap();

	std::vector<std::vector<int>> roadCrossPoint;

	std::vector<std::vector<int>> backLandFrom();
private:
	std::vector<std::vector<int>> landFrom;
};

#endif