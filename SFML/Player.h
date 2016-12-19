#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "CharacterSelectionMenu.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
private:
	sf::Texture texture;
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
};

