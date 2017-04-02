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

		bool secondRow = false; //  + mapSizes.first*SIZE/2
		for (auto &pair : tilesCoords) {
			tile.setPosition(convert2DToIso({ posX*SIZE / 2, posY*SIZE / 2 }).first, convert2DToIso({ posX*SIZE / 2 , posY*SIZE / 2 }).second);
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
	for (auto& tile : tiles) {
		cout << tile.getPosition().x << " " << tile.getPosition().y << endl;
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
	return true;
}

bool Map::getIsWalkable(pair<float, float> pair)
{
	//return tilesCoords[getTileCoordinates(pair).first * mapSizes.first + getTileCoordinates(pair).second].second;
	return true;
}

pair<float, float> Map::getTileCenterFromTileCoordinate(pair<float, float> pair)
{
	return { pair.first*SIZE + SIZE / 2, pair.second*SIZE + SIZE / 2 };
}

bool Map::containsPoint(pair<float, float> point, pair<float, float> tileCenter)
{
	const int q2x = std::abs(point.first - tileCenter.first);
	const int q2y = abs(point.second - tileCenter.second);
	return ((2 * (SIZE / 4) * (SIZE / 2) - (SIZE / 4) * q2x - (SIZE / 2) * q2y) >= 0);
}

bool Map::rectContainsPoint(pair<float, float> point, pair<float, float> tileCoords)
{
	double pointX = point.first;
	double pointY = point.second;
	// This is the piece of code I found
	if (pointX >= tileCoords.first && pointX <= tileCoords.first + SIZE/2 &&
		pointY >= tileCoords.second && pointY <= tileCoords.second + SIZE/2)
		return true;

	return false;
}
