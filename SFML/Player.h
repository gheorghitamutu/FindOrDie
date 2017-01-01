#pragma once
#include <SFML/Graphics.hpp>
#include "math.h"
class Player
{
public:
	Player(sf::RenderWindow& window);
	~Player();
	void Update(sf::Event event);
	void Draw(sf::RenderWindow& window, bool gamePause);
	void RestartClock();
	void StartingPosition(bool newGame, sf::RenderWindow& window);
	void getTexture(bool woman);
	void setTexture();
	void Update(int row, float deltaTime);
	void Animation();

	sf::IntRect uvRect;
	sf::Vector2f returnPlayerPosition(); 
	sf::Texture texture;

private:
	sf::RectangleShape body;
	sf::Clock clock;
	sf::Vector2f movement;

	sf::Vector2u imageCount = sf::Vector2u(8, 24);
	sf::Vector2u currentImage;

	bool cameraPerspective = true;
	unsigned int row = 0;
	unsigned int shiftIncreaseSpeed;
	float speed = 80.0f; // movement speed
	float deltaTime = 0.0f;
	float diagRunSpeed;
	float normalRunSpeed;
	float diagSpeed;
	float totalTime = 0.0f;
	float switchTime = 0.1f;
};

