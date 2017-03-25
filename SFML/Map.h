#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include<math.h>
#include "Player.h"
#include <vector>

#define SIZE 64

using namespace std;

class Map
{
public:
	Map();
	~Map();
	void drawMap(sf::RenderWindow& window);
	pair <float, float> convert2DToIso(pair<float, float> pair);
	pair <float, float> convertIsoTo2D(pair<float, float> pair);
	bool isWalkable(char x, char y);
	pair <float, float> getTileCoordinates(pair<float, float> pair);
	pair <float, float> get2dFromTileCoordinates(pair<float, float> pair);
	bool getIsWalkable(pair<float, float> pair);

private:
	sf::Texture tileTexture;
	sf::Sprite tile;
	sf::Vector2i loadcounter = sf::Vector2i(0, 0);
	vector<pair<pair<float, float>, bool>> tilesCoords;
	vector <sf::Sprite> tiles;
	pair <int, int> mapSizes = { 0,0 };
};

