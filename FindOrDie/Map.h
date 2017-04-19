#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include<math.h>
#include <vector>
#include <random>
#include <thread>

using namespace std;

class Map
{
public:
	Map();
	~Map();
	void drawMap(sf::RenderWindow& window);
	void drawOnlyViewedTiles(sf::View view);
	pair <float, float> convert2DToIso(pair<float, float> pair);
	pair <float, float> convertIsoTo2D(pair<float, float> pair);
	bool isWalkable(pair<int, int> pair);
	pair <float, float> getTileCenterFromTileCoordinate(pair<float, float> pair);
	bool containsPoint(pair<float, float> point, vector<pair<float, float>> nonWalkableAreaCoords);
	bool isColliding(pair <float, float> returnPlayer2DPosition, sf::Vector2f bodySize, sf::Vector2f velocity);
	void createMap();
	vector<sf::Sprite> checkWhatToDraw();
	void setWhatToDraw(vector<sf::Sprite> drawTheseTiles);
	void setViewBounds(sf::FloatRect& viewBounds);
public:
	std::random_device rd;
	sf::Texture tileTexture;
	pair<sf::Sprite, bool> tile;
	vector<pair<pair<float, float>, bool>> tilesCoords;
	vector <pair<sf::Sprite, bool>> tiles;
	pair <int, int> mapDimensions;
	vector<vector<pair<float, float>>> nonWalkableObjects;

	struct Point
	{
		float x;
		float y;
	};

	Point extreme;

	bool onSegment(Point p, Point q, Point r);
	int orientation(Point p, Point q, Point r);
	bool doIntersect(Point p1, Point q1, Point p2, Point q2);
	bool isInside(Point polygon[], int n, Point p);

	static constexpr int tileSize = 64;

	vector<sf::Sprite> drawThese;
	sf::FloatRect viewBounds;
};

