#pragma once
#include <SFML/Graphics.hpp>
#include "string.h"



class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	~TileMap();
	
	
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	std::string tileset = "Animation/Man/fullPlayerAnimations.png";
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

