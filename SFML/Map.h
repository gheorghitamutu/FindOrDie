#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include<math.h>
#define SIZE 64
class Map
{
public:
	Map();
	~Map();
	void drawMap(sf::RenderWindow& window);
	
private:
	sf::Texture tileTexture;
	sf::Sprite tiles;
	sf::Vector2i map[300][300];
	sf::Vector2i loadcounter = sf::Vector2i(0, 0);
//	sf::View camera;
	std::string tileLocation;
};

