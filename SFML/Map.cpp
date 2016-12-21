#include "Map.h"



Map::Map()
{
	std::ifstream openfile("map.txt");
	if (openfile.is_open())
	{		
		openfile >> tileLocation;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture);
		tiles.setRotation(45.f);
		tiles.setPosition(tiles.getPosition().x, tiles.getPosition().y * 2);
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
				map[loadcounter.x][loadcounter.y] =
					sf::Vector2i(x - '0', y - '0'); //ASCII values e.g.49-48
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
}


Map::~Map()
{
}

void Map::drawMap(sf::RenderWindow& window)
{
	for (int i = 0; i<loadcounter.x; i++)
	{
		for (int j = 0; j<loadcounter.y; j++)
		{
			if (map[i][j].x != -1 && map[i][j].y != -1)
			{
				if (i % 2 == 0) tiles.setPosition((i) * (sqrt(SIZE*SIZE + SIZE*SIZE))/2, j * (sqrt(SIZE*SIZE + SIZE*SIZE)));
				else tiles.setPosition((i) * sqrt(SIZE*SIZE + SIZE*SIZE)/2, (j - 0.5) * sqrt(SIZE*SIZE + SIZE*SIZE));
				tiles.setTextureRect(sf::IntRect(map[i][j].x *  SIZE, map[i][j].y *  SIZE, SIZE, SIZE));
			//	camera = window.getDefaultView();			
			//	camera.setSize(camera.getSize().x, camera.getSize().y *2);
			//	camera.setCenter(camera.getSize() *.5f);
			//	window.setView(camera);
				window.draw(tiles);
			//	window.setView(window.getDefaultView());	
			}
			
		}
	}
	
}
