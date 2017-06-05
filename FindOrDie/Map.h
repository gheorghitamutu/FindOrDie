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
#include "Pathfinding.h"
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
	int getTileNumberClicked(sf::Event event, sf::RenderWindow& window);
	pair<string, pair<pair<int, int>, pair<int, int>>> setFinishLocation(sf::Event event, sf::RenderWindow& window, pair <float, float> position, sf::Vector2f bodySize);
	void setStartLocation(pair <float, float> position, sf::Vector2f bodySize);
	pair <float, float> getStartLocation();
	pair <float, float> getFinishLocation();
	vector<pair<vector<pair<float, float>>, int>> getFloorLevelTilesCoords();
	pair <int, int> getMapDimensions();
	vector <pair<sf::Sprite, bool>> getTiles();
	void changeTilesOpacity(vector<int> whichTiles);
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

	vector<vector<int>> mapMatrix;
	//int dir = 4;
	//vector <int> dx={1, 0, -1, 0};
	//vector<int> dy={0, 1, 0, -1};
	int dir = 8;
	vector<int> dx = { 1, 1, 0, -1, -1, -1, 0, 1 };
	vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };
	pair<int, int> startLocation;
	pair<int, int> finishLocation;
	pair<string, pair<pair<int, int>, pair<int, int>>> playerPath;

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

