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
				tilesCoords.push_back({ { line[mapSizes.first++] - '0', line[mapSizes.first++] - '0' }, isWalkable(line[mapSizes.first - 2],line[mapSizes.first - 1]) });
			}
			mapSizes.second++;
		}

		mapSizes.first = mapSizes.first / 2;

		float posX = 0, posY = 0;

		bool secondRow = false;
		for (auto &pair : tilesCoords) {
			tile.setPosition(convert2DToIso({ posX*SIZE / 2, posY*SIZE / 2 }).first, convert2DToIso({ posX*SIZE / 2, posY*SIZE / 2 }).second);
			tile.setTextureRect(sf::IntRect(pair.first.first *  SIZE, pair.first.second *  SIZE, SIZE, SIZE));
			tiles.push_back(tile);

			posX++;
			if (posX >= mapSizes.first) {
				posX = 0;
				posY++;
			}
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

pair<float, float> Map::convert2DToIso(pair<float, float> pair)
{
	return{ pair.first - pair.second, (pair.first + pair.second) / 2 };
}

pair<float, float> Map::convertIsoTo2D(pair<float, float> pair)
{
	return{ (2 * pair.second + pair.first) / 2, (2 * pair.second - pair.first) / 2 };
}

bool Map::isWalkable(char x, char y)
{
	if (x == '0' && y == '0') return false;
	if (x == '0' && y == '3') return true;
}
