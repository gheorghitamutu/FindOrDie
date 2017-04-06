#pragma once
#include "Player.h"
class Chests
{
public:
	Chests();
	void DrawChest(sf::RenderWindow& window);
	void GetNumberOfChest(int& number);
	void LoadTexture();

	sf::RectangleShape body;
	sf::Texture texture;

	int chestNumber = 1;
	int score = 0;
	~Chests();
};

