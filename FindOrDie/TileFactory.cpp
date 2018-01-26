#include "TileFactory.h"

TileFactory::TileFactory()
{
	this->tile_texture = new sf::Texture;
	this->tile_texture->loadFromFile("iso-64x64-building.png");

	this->last_tile = nullptr;
}


TileFactory::~TileFactory()
{
}

void TileFactory::SetIsWalkable(bool is_walkable)
{
	this->is_walkable = is_walkable;
}

bool TileFactory::GetIsWalkable()
{
	return this->is_walkable;
}

void TileFactory::SetPosition(float x_position, float y_position)
{
	this->tile_position.x = x_position;
	this->tile_position.y = y_position;
}

sf::Vector2f TileFactory::GetPosition()
{
	return this->tile_position;
}

void TileFactory::SetTextureRectangle(sf::IntRect texture_rectangle)
{
	this->texture_rectangle = texture_rectangle;
}

Tile* TileFactory::FedTile()
{
	Tile* tile = new Tile(this->is_walkable, this->tile_position, this->texture_rectangle, this->tile_texture);
	this->last_tile = tile;
	this->tiles.emplace_back(tile);
	return tile;
}

void TileFactory::SetLastTile(Tile* last_tile)
{
	this->last_tile = last_tile;
}

Tile* TileFactory::GetLastTile()
{
	return this->last_tile;
}

void TileFactory::EmptyFactory()
{
	for (auto tile : this->tiles)
	{
		delete tile;
	}
	tiles.clear();
}
