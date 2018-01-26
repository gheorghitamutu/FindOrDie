#include "Tile.h"

Tile::Tile()
{
	this->tile = new sf::Sprite;
}

Tile::Tile(bool is_walkable, sf::Vector2f position, sf::IntRect texture_rectangle, sf::Texture* texture)
{
	this->tile = new sf::Sprite;
	SetIsWalkable(is_walkable);
	SetPosition(position);
	SetTexture(texture);
	SetTextureRect(texture_rectangle);
}


Tile::~Tile()
{
	if (this->tile != nullptr)
	{
		delete this->tile;
	}
}

void Tile::SetIsWalkable(bool is_walkable)
{
	this->is_walkable = is_walkable;
}

bool Tile::GetIsWalkable()
{
	return this->is_walkable;
}

void Tile::SetPosition(sf::Vector2f position)
{
	this->tile->setPosition(position);
}

sf::Vector2f Tile::GetPosition()
{
	return this->tile->getPosition();
}

void Tile::SetTexture(sf::Texture * texture)
{
	this->tile->setTexture(*texture);
}

void Tile::SetTextureRect(sf::IntRect texture_rectangle)
{
	this->tile->setTextureRect(texture_rectangle);
}

sf::Sprite * Tile::GetSprite()
{
	return this->tile;
}

void Tile::SetColor(sf::Color color)
{
	this->tile->setColor(color);
}
