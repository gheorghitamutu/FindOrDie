#pragma once
#include "Player.h"
class Chests
{
public:
	Chests();
	~Chests();
	void DrawChest(sf::RenderWindow& window);
	void GetNumberOfChest(int& number);
	void LoadTexture();

	sf::RectangleShape body;
	sf::Texture texture;

	int chest_number = 1;
	int score = 0;
};

