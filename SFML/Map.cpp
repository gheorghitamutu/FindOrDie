#include "Map.h"



Map::Map()
{
	std::ifstream openfile("map.txt");
	if (openfile.is_open())
	{		
		openfile >> tileLocation;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture); // textures file
	//	tiles.setRotation(45.f);
		//tiles.setPosition(tiles.getPosition().x/2, tiles.getPosition().y);
		while (!openfile.eof())
		{
			std::string str;
			openfile >> str;
			char x = str[0], y = str[2];
			if (!isdigit(x) || !isdigit(y))
			{
				map[loadcounter.x][loadcounter.y] = sf::Vector2i(-1, -1);
			}
			else
			{
				map[loadcounter.x][loadcounter.y] = sf::Vector2i(x - '0', y - '0'); //ASCII values e.g.49-48
			}
			if (openfile.peek() == '\n')
			{
				loadcounter.x = 0;
				loadcounter.y++;
			}
			else
			{
				loadcounter.x++;
			}
		}
	}
	else {
		std::cout << "MAP CAN T BE LOADED!" << std::endl;
	}
	std::cout << loadcounter.x << std::endl;
	std::cout << loadcounter.y << std::endl;
}


Map::~Map()
{
}

void Map::drawMap(sf::RenderWindow& window)
{
	for (int j = 0; j <loadcounter.y; j++)
	{
		
		for (int i = 0; i <= loadcounter.x; i++)
		{
			if (map[i][j].x != -1 && map[i][j].y != -1)
			{
				if (j % 2 == 0) tiles.setPosition(((i) *SIZE), ((j *0.25)*SIZE));
				else tiles.setPosition(((i)*(SIZE))+32, ((j *0.25) *SIZE));
				tiles.setTextureRect(sf::IntRect(map[i][j].x *  SIZE, map[i][j].y *  SIZE, SIZE, SIZE));
				window.draw(tiles);
			}
		}
	}
	//for (int i = 0; i <= loadcounter.x; i++)
	//{

	//	for (int j = 0; j <=i; j++)
	//	{
	//		
	//		if (map[i][j].x != -1 && map[i][j].y != -1)
	//		{
	//		//	std::cout << i << " " << j << std::endl;
	//			
	//if (j % 2 == 0) tiles.setPosition(((i)*SIZE), ((j *0.25)*SIZE));
	//else tiles.setPosition(((i)*(SIZE)) + 32, ((j *0.25) *SIZE));
	//tiles.setTextureRect(sf::IntRect(map[i][j].x *  SIZE, map[i][j].y *  SIZE, SIZE, SIZE));
	//			window.draw(tiles);
	//		}
	//	}
	//}
	//for (int i = 0; i <= loadcounter.x; i++) {
	//	if (map[i][0].x != -1 && map[0][i].y != -1)
	//	{
	//		if (i % 2 == 0) tiles.setPosition(((i*0.5) *SIZE), -(SIZE / 2) + ((0 * 0.5)*SIZE));
	//		else tiles.setPosition(((i*0.5)*(SIZE)), -(SIZE / 4) + ((0 * 0.5) *SIZE));
	//		tiles.setTextureRect(sf::IntRect(map[i][0].x *  SIZE, map[i][0].y *  SIZE, SIZE, SIZE));
	//		//window.draw(tiles);
	//		if (i % 2 == 0) tiles.setPosition(((0 * 0.5) *SIZE), -(SIZE / 2) + ((i * 0.5)*SIZE));
	//		else tiles.setPosition(((0 * 0.5)*(SIZE)), -(SIZE / 4) + ((i * 0.5) *SIZE));
	//		tiles.setTextureRect(sf::IntRect(map[0][i].x *  SIZE, map[0][i].y *  SIZE, SIZE, SIZE));
	//		window.draw(tiles);
	//	}
	//}
}
