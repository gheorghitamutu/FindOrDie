#pragma once
#include "SFML\Graphics.hpp"
#include "math.h"
#include<iostream>
#include "Map.h"
using namespace std;

class Player
{
public:
	Player();
	~Player();
	void Update(sf::Event event, class Map& map);
	void Draw(sf::RenderWindow& window, bool gamePause);
	void RestartClock();
	void StartingPosition(bool newGame, sf::RenderWindow& window);
	void getTexture(bool woman);
	void setTexture();
	void Update(int row, float deltaTime);
	void Animation();

	pair <float, float> convert2DToIso(pair<float, float> pair);
	pair <float, float> convertIsoTo2D(pair<float, float> pair);

	sf::IntRect uvRect;
	pair <float, float> returnPlayer2DPosition();
	sf::Texture texture;

private:
	sf::RectangleShape playerBody;
	sf::Clock clock;
	sf::Vector2f movement;

	sf::Vector2u imageCount = sf::Vector2u(8, 24);
	sf::Vector2u currentImage;

	bool cameraPerspective = true;
	unsigned int row = 0;
	unsigned int shiftIncreaseSpeed;
	float speed = 25.0f; // movement speed
	float deltaTime = 0.0f;
	float diagRunSpeed;
	float normalRunSpeed;
	float diagSpeed;
	float totalTime = 0.0f;
	float switchTime = 0.1f;
};

