#pragma once
#include "SFML\Graphics.hpp"
class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, sf::Texture texture);
	void ApplyToSprite(sf::RectangleShape& body);
	void Update(float deltaTime);
	~Animation();
private:
	void Advance();
	static constexpr int numberOfFrames = 7;
	static constexpr float holdTime = 0.1f;
	float time = 0.0f;
	sf::Texture texture;
	sf::IntRect frames[numberOfFrames];
	int frameIndex = 0;
};

