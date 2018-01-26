#pragma once
#include "SFML\Graphics.hpp"
class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, sf::Texture *texture);
	void ApplyToSprite(sf::RectangleShape& body);
	void Update(float delta_time);
	~Animation();
private:
	void Advance();
	static constexpr int number_of_frames = 7;
	static constexpr float hold_time = 0.1f;
	float time = 0.0f;
	sf::Texture* texture;
	sf::IntRect frames[number_of_frames];
	int frame_index = 0;
};

