#pragma once
#include "Tile.h"
#include <vector>

class TileFactory
{
public:
	TileFactory();
	~TileFactory();
	void SetIsWalkable(bool is_walkable);
	bool GetIsWalkable();
	void SetPosition(float x_position, float y_position);
	sf::Vector2f GetPosition();
	void SetTextureRectangle(sf::IntRect texture_rectangle);
	Tile* FedTile();
	void SetLastTile(Tile* last_tile);
	Tile* GetLastTile();
	void EmptyFactory();
private:
	std::vector<Tile*> tiles;

	sf::Texture *tile_texture;

	bool is_walkable = true;

	sf::Vector2f tile_position = { 0, 0 };

	sf::IntRect texture_rectangle;

	Tile* last_tile;
};

