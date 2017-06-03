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
	void createMap();
	void setWhatToDraw();
	void setViewBounds(sf::FloatRect& viewBounds);
	void drawMap(sf::RenderWindow& window);
	void drawTilesOverPlayer(bool isColliding);
	bool isCollidingDrawOver(pair <float, float> position, sf::Vector2f bodySize);
	bool isWalkable(pair<int, int> pair);
	bool containsPoint(pair<float, float> point, pair<vector<pair<float, float>>, int> nonWalkableAreaCoords);
	bool isColliding(pair <float, float> returnPlayer2DPosition, sf::Vector2f bodySize, sf::Vector2f velocity);
	pair <float, float> convert2DToIso(pair<float, float> pair);
	pair <float, float> convertIsoTo2D(pair<float, float> pair);
	pair <float, float> getTileCenterFromTileCoordinate(pair<float, float> pair);
	vector<sf::Sprite*> checkWhatToDraw();
	vector<pair<float, float>> getPolygonPoints(sf::Sprite* tile);
	int getTileNumberWherePlayerIs(pair <float, float> position, sf::Vector2f bodySize);
public:
	std::random_device rd;
	sf::Texture tileTexture;
	pair<sf::Sprite, bool> tile;
	vector<pair<pair<float, float>, bool>> tilesCoords;
	vector<pair<vector<pair<float, float>>, int>> floorLevelTilesCoords;
	vector <pair<sf::Sprite, bool>> tiles;
	vector <pair<sf::Sprite, bool>> nonWalkableTiles;
	pair <int, int> mapDimensions;
	vector<pair<vector<pair<float, float>>, int>> nonWalkableObjects;
	vector<pair<vector<pair<float, float>>, int>> canDrawOverPlayerObjects;

	int numberOfTiles;
	int tileNumberWherePlayerIs = 0;
	int lastKnownTileNumberWherePlayerIs = -1;

	pair<float, float> extreme;

	bool onSegment(pair<float, float> p, pair<float, float> q, pair<float, float> r);
	int orientation(pair<float, float> p, pair<float, float> q, pair<float, float> r);
	bool doIntersect(pair<float, float> p1, pair<float, float> q1, pair<float, float> p2, pair<float, float> q2);
	bool isInside(vector<pair<float, float>> polygon, int n, pair<float, float> p);

	static constexpr int quarterTileSize = 16;
	static constexpr int halfTileSize = 32;
	static constexpr int threeFourthsTileSize = 48;
	static constexpr int tileSize = 64;


	vector<sf::Sprite*> drawThese;
	sf::FloatRect viewBounds;

	vector<int> drawTileOverPlayer;
	vector<int> lastKnownTilesOverPlayer;
};

