#pragma once
#include "Collider.h"
#include "Player.h"
class Chests
{
public:
	Chests();
	void DrawChest(sf::RenderWindow& window);
	void GetNumberOfChest(int& number);
	void LoadTexture();

	Collider GetChestCollider() { return Collider(body); }

	sf::RectangleShape body;
	sf::Texture texture;

	int chestNumber = 1;
	~Chests();
};

