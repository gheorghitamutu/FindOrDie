#include "Map.h"



Map::Map()
{
	ifstream openfile("map.txt");
	if (openfile.is_open()) {
		string line;
		getline(openfile, line);
		tileTexture.loadFromFile(line);
		tile.setTexture(tileTexture);

		while (getline(openfile, line)) {
			mapSizes.first = 0;
			while (mapSizes.first < line.size()) {
				tilesCoords.push_back({ line[mapSizes.first++] - '0', line[mapSizes.first++] - '0' });
			}
			mapSizes.second++;
		}

		mapSizes.first = mapSizes.first / 2;

		float posX = 0, posY = 0;

		bool secondRow = false;
		for (auto &pair : tilesCoords) {
			if (posX == mapSizes.first * SIZE || posX == mapSizes.first * SIZE + 32) {
				if (secondRow) {
					posX = 0;
					secondRow = false;
				}
				else {
					posX = SIZE / 2;
					secondRow = true;
				}
				posY += SIZE / 4;
			}

			tile.setPosition(posX, posY);
			posX += SIZE;

			tile.setTextureRect(sf::IntRect(pair.first *  SIZE, pair.second *  SIZE, SIZE, SIZE));
			tiles.push_back(tile);
		}
	}
	else {
		cout << "MAP CAN T BE LOADED!" << endl;
	}
}


Map::~Map()
{
}

void Map::drawMap(sf::RenderWindow& window)
{
		for (auto &tile : tiles) window.draw(tile);
}

//void Map::CheckPlayerCollisionWithStaticObjects(Player & player)
//{
//	//collision player with walls
//	//std::cout << blocksPosition.size() << std::endl;
//	for (objectIterator = 0; objectIterator < blocksPosition.size(); objectIterator++)
//	{
//		player.GetCollider().CheckCollision(GetMapCollider(objectIterator), 0.0f);
//	}
//	
//}
