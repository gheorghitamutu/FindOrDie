#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture);
	~Animation();

	void Update(int row, float deltaTime);

public:
	sf::IntRect uvRect;
private:
	sf::Vector2u imageCount = sf::Vector2u(8, 24);
	sf::Vector2u currentImage;
	float totalTime = 0.0f;
	float switchTime = 0.1f;
};

