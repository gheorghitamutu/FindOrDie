#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, sf::Texture texture)
{
	this->texture = texture;
	for (int i = 0; i < numberOfFrames; i++)
	{
		frames[i] = { x + i*width, y, width, height };
	}
}

void Animation::ApplyToSprite(sf::RectangleShape& body)
{
	body.setTexture(&texture);
	body.setTextureRect(frames[frameIndex]);
}

void Animation::Update(float deltaTime)
{
	time += deltaTime;
	while (time >= holdTime)
	{
		time -= holdTime;
		Advance();
	}
}

Animation::~Animation()
{
}

void Animation::Advance()
{
	if (++frameIndex >= numberOfFrames)
	{
		frameIndex = 0;
	}
}
