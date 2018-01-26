#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include<vector>
#include <random>
#include "ANode.h"

class Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();
	std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> FindPath(std::pair<int, int> map_dimensions, std::vector<std::vector<int>> map,
		std::vector<int>& dx, std::vector<int>& dy,
		int& dir, const int & x_start, const int & y_start, const int & x_finish, const int & y_finish);
	void show_stuff(std::string path, std::pair<int, int> start_location, std::pair<int, int> map_Dimensions, std::vector<int>& dx, std::vector<int>& dy, std::vector<std::vector<int>> map);
};

