#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>

class Map
{
public:
	Map();
	~Map();
	void drawMap(sf::RenderWindow& window);
	
	
	sf::Texture tileTexture;
	sf::Sprite tiles;
	sf::Vector2i map[100][100];
	sf::Vector2i loadcounter = sf::Vector2i(0, 0);

	std::string tileLocation;
};

