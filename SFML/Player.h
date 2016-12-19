#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "CharacterSelectionMenu.h"
class Player
{
public:
	Player(sf::Texture* texture);
	~Player();
	void Update();
	void Draw(sf::RenderWindow& window);
	void RestartClock();
private:
	sf::Texture texture;
	sf::RectangleShape body;
	Animation animation;
	unsigned int row = 0;
	float speed = 50.0f; // movement speed
	sf::Clock clock;
	float deltaTime = 0.0f;
};

