#include "Map.h"



Map::Map()
{
	std::ifstream openfile("map.txt");
	if (openfile.is_open())
	{		
		std::getline(openfile, tileLocation);
	//	std::cout << tileLocation << std::endl;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture); // textures file
		std::string str;
		std::getline(openfile, str); // width
		loadcounter.x = atoi(str.c_str());
		std::getline(openfile, str); // height
		loadcounter.y = atoi(str.c_str());
		for (int i = 0; i < loadcounter.x; i++) {
			std::getline(openfile, str);
			int k = 0;
			for (int j = 0; j < loadcounter.y*3; j+=3) {
				char x = str[j], y = str[j + 1];
				map[i][k] = sf::Vector2i(x - '0', y - '0'); //ASCII values e.g.49-48
				//map collisions
				if ((x == '2' && y == '5')|| (x == '0' && y == '0'))
				{
					if (k % 2 == 0) blockPosition.setPosition(((i)*SIZE), ((k *0.25)*SIZE));
					else blockPosition.setPosition(((i)*(SIZE)) + (SIZE / 2), ((k *0.25) *SIZE));
					blockPosition.setSize(sf::Vector2f(SIZE*1.5, SIZE*1.5));
					tiles.setTextureRect(sf::IntRect(map[i][j].x *  SIZE, map[i][j].y *  SIZE, SIZE, SIZE));
				//	std::cout << blockPosition.getPosition().x << " " << blockPosition.getPosition().y << std::endl;
					blocksPosition.push_back(blockPosition);
				}
				
				//
				k++;
			}
		}
	}
	else {
		//std::cout << "MAP CAN T BE LOADED!" << std::endl;
	}

}


Map::~Map()
{
}

void Map::drawMap(sf::RenderWindow& window)
{
	for (int j = 0; j <loadcounter.y; j++)
	{		
		for (int i = 0; i < loadcounter.x; i++)
		{
			if (map[i][j].x != -1 && map[i][j].y != -1)
			{
				if (j % 2 == 0) tiles.setPosition(((i) *SIZE), ((j *0.25)*SIZE));
				else tiles.setPosition(((i)*(SIZE))+(SIZE/2), ((j *0.25) *SIZE));
				tiles.setTextureRect(sf::IntRect(map[i][j].x *  SIZE, map[i][j].y *  SIZE, SIZE, SIZE));
		//		if (map[i][j].x == 3) std::cout << tiles.getPosition().x << " " << tiles.getPosition().y << std::endl;
				window.draw(tiles);
			}
		}
	}
}

void Map::CheckPlayerCollisionWithStaticObjects(Player & player)
{
	//collision player with walls
	//std::cout << blocksPosition.size() << std::endl;
	for (objectIterator = 0; objectIterator < blocksPosition.size(); objectIterator++)
	{
		player.GetCollider().CheckCollision(GetMapCollider(objectIterator), 0.0f);
	}
	
}
