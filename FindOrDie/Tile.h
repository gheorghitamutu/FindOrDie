#pragma once
#include "SFML\Graphics.hpp"

class Tile
{
public:
	Tile();
	Tile(bool is_walkable, sf::Vector2f position, sf::IntRect texture_rectangle, sf::Texture* texture);
	~Tile();
	void SetIsWalkable(bool is_walkable);
	bool GetIsWalkable();
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();
	void SetTexture(sf::Texture* texture);
	void SetTextureRect(sf::IntRect texture_rectangle);
	sf::Sprite* GetSprite();
	void SetColor(sf::Color color);

private:
	sf::Sprite* tile;

	bool is_walkable = true;
};

