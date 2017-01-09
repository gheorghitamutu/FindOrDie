#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Draw(sf::RenderWindow& window);
	void goToPlayer(sf::Vector2f returnPlayerPosition);
	void createEnemy(sf::RenderWindow& window);

	int returnNumberOfMonsters();
	void setNumberOfMonsters(int number);

	sf::Time timer();


	std::vector <sf::RectangleShape> body;
	sf::RectangleShape singleBody;
	//sf::RectangleShape body[500];

	sf::Clock clock;

	sf::Time timeElapsed;

	int numberOfMonsters = 0;
	float spawnTimeMonsters = 1.0f;

	float speed = 01.0f;
};

