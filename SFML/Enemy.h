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
	void setNumberOfMonsters(int number);
	void setTexture();
	void Animation();
	void Update(int row, float deltaTime);
	void RestartClock();

	int returnNumberOfMonsters();
	
	sf::Texture texture;

	sf::Vector2u imageCount = sf::Vector2u(6, 8);
	sf::Vector2u currentImage;

	sf::IntRect uvRect;

	sf::Time timer();


	std::vector <sf::RectangleShape> body;
	sf::RectangleShape singleBody;

	sf::Clock clock;
	sf::Clock clock2;

	sf::Time timeElapsed;

	unsigned int row = 0;
	int numberOfMonsters = 0;
	float deltaTime = 0.0f;
	float totalTime = 0.0f;
	float spawnTimeMonsters = 0.10f;
	float speed = 0.10f;
	float switchTime = 0.1f;
};

