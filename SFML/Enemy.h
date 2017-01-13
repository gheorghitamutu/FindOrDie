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
	void setNumberOfMonsters(int number);
	void setTexture();
	void Animation();
	void Update(int row, float deltaTime);
	void RestartClock();

	int ReturnMonsterVectorSize() { return body.size(); }

	float ReturnMonsterSpeed() { return speed; }

	std::vector <sf::RectangleShape> returnMonsterVector() { return body; }

	void CheckMonsterVectorCollision(Player& player, Map& map, bool& endGame);

	Collider GetCollider() { return Collider(body[monstersIterator]); }
	Collider GetColliderBetweenMonsters() { return Collider(body[secondMonstersIterator]); }

	int returnNumberOfMonsters();
	
	sf::Texture texture;

	sf::Vector2u imageCount = sf::Vector2u(8, 8);
	sf::Vector2u currentImage;

	sf::IntRect uvRect;

	sf::Time timer();


	std::vector <sf::RectangleShape> body;
	sf::RectangleShape singleBody;

	sf::Clock clock;
	sf::Clock clock2;

	sf::Time timeElapsed;

	int objectIterator = 0;
	int monstersIterator = 0;
	int secondMonstersIterator = 0;
	unsigned int row = 0;
	int numberOfMonsters = 0;
	float deltaTime = 0.0f;
	float totalTime = 0.0f;
	float spawnTimeMonsters = 01.0f;
	float speed = 2.0f; // * 60 frames/second = 60.0f
	float switchTime = 0.1f;
};

