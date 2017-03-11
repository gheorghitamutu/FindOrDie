#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
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
	void clearMonsterVector();
	void setTexture();
	void Animation();
	void Update(int row, float deltaTime);

	int ReturnMonsterVectorSize() { return body.size(); }

	float ReturnMonsterSpeed() { return speed; }

	std::vector <sf::RectangleShape> returnMonsterVector() { return body; }

	void CheckMonsterVectorCollision(Player& player, Map& map, bool& endGame);

	Collider GetCollider(sf::RectangleShape &monster) { return Collider(monster); }
	Collider GetColliderBetweenMonsters(sf::RectangleShape &monster) { return Collider(monster); }

	int returnNumberOfMonsters();
	
	sf::Texture texture;

	sf::Vector2u imageCount = sf::Vector2u(8, 8);
	sf::Vector2u currentImage;

	sf::IntRect uvRect;

	std::vector <sf::RectangleShape> body;
	sf::RectangleShape singleBody;

	int objectIterator = 0;
	unsigned int row = 0;
	float deltaTime = 0.0f;
	float totalTime = 0.0f;
	int countSpawnTime = 1;
	int spawnTime = 360;
	float speed = 1.0f; // * 60 frames/second = 60.0f
	float switchTime = 0.1f;
};

