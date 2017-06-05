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
using namespace std;
class Pathfinding
{
public:
	Pathfinding();
	pair<string, pair<pair<int, int>, pair<int, int>>> pathFind(pair<int, int> mapDimensions, vector<vector<int>> map,
		vector<int>& dx, vector<int>& dy,
		int& dir, const int & xStart, const int & yStart, const int & xFinish, const int & yFinish);
	void showStuff(string path, pair<int, int> startLocation, pair<int, int> mapDimensions, vector<int>& dx, vector<int>& dy, vector<vector<int>> map);
	~Pathfinding();
};

