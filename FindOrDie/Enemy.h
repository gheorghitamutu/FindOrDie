#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include "Player.h"
#include "Map.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Draw(sf::RenderWindow& window);
	void goToPlayer(sf::Vector2f returnPlayerPosition);
	void createEnemy(sf::RenderWindow& window);
	void clearMonsterVector() { this->body.erase(body.begin(), body.end()); };
	void setTexture() { texture.loadFromFile("Animation/Monsters/zombie.png"); };
	void Animation();
	void Update();

	int ReturnMonsterVectorSize() { return body.size(); }

	float ReturnMonsterSpeed() { return speed; }

	std::vector <sf::RectangleShape> returnMonsterVector() { return body; }

	int returnNumberOfMonsters() { return this->body.size(); };
	
	sf::Texture texture;

	sf::Vector2u imageCount = sf::Vector2u(8, 8);
	sf::Vector2u currentImage;

	sf::IntRect uvRect;

	std::vector <sf::RectangleShape> body;
	sf::RectangleShape singleBody;

	unsigned int row = 0;
	int countSpawnTime = 1;
	int spawnTime = 3600;
	float speed = 0.20f; // * 60 frames/second = 60.0f
	float switchTime = 0.4f;
};

