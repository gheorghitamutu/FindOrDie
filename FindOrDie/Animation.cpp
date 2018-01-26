#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, sf::Texture *texture)
{
	this->texture = texture;
	for (int i = 0; i < this->number_of_frames; i++)
	{
		this->frames[i] = { x + i*width, y, width, height };
	}
}

Animation::~Animation()
{
}

void Animation::ApplyToSprite(sf::RectangleShape* body)
{
	body->setTexture(this->texture);
	body->setTextureRect(this->frames[this->frame_index]);
}

void Animation::Update(float delta_time)
{
	this->time += delta_time;
	while (this->time >= this->hold_time)
	{
		this->time -= this->hold_time;
		Advance();
	}
}

void Animation::Advance()
{
	if (++this->frame_index >= this->number_of_frames)
	{
		this->frame_index = 0;
	}
}
