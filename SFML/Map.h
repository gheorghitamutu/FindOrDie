#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include<math.h>
#include "Player.h"
//#include "Enemy.h"
#include "Collider.h"
#include <vector>

#define SIZE 64

using namespace std;

class Map
{
public:
	Map();
	~Map();
	void drawMap(sf::RenderWindow& window);
	void CheckPlayerCollisionWithStaticObjects(Player& player);
	/*int ReturnBlocksPositionSize() { return blocksPosition.size(); }

	Collider GetMapCollider(int objectIterator) { return Collider(blocksPosition[objectIterator]); }*/

	int objectIterator = 0;
	
private:
	/*sf::Texture tileTexture;
	sf::Sprite tiles;
	sf::Vector2i map[320][320];
	sf::Vector2i loadcounter = sf::Vector2i(0, 0);
	std::vector <sf::RectangleShape> blocksPosition;
	sf::RectangleShape blockPosition;
	std::string tileLocation;*/

	sf::Texture tileTexture;
	sf::Sprite tile;
	sf::Vector2i loadcounter = sf::Vector2i(0, 0);
	vector<pair<float, float>> tilesCoords;
	vector <sf::Sprite> tiles;
	pair <int, int> mapSizes = { 0,0 };
};

