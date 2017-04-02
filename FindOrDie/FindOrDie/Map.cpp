#include "Map.h"

Map::Map()
{
	ifstream openfile("map.txt");
	if (openfile.is_open()) {
		string line;
		getline(openfile, line);
		tileTexture.loadFromFile(line);
		tile.first.setTexture(tileTexture);

		while (getline(openfile, line)) {
			mapSizes.first = 0;
			while (mapSizes.first < line.size()) {
				tilesCoords.push_back( { line[mapSizes.first++] - '0', line[mapSizes.first++] - '0' } );
			}
			mapSizes.second++;
		}

		mapSizes.first = mapSizes.first / 2;

		float posX = 0, posY = 0;

		bool secondRow = false;
		for (auto &pair : tilesCoords) {
			tile.second = isWalkable({ (int)pair.first, (int)pair.second });
			tile.first.setPosition(convert2DToIso({ posX*SIZE / 2, posY*SIZE / 2 }).first, convert2DToIso({ posX*SIZE / 2 , posY*SIZE / 2 }).second);
			tile.first.setTextureRect(sf::IntRect(pair.first *  SIZE, pair.second *  SIZE, SIZE, SIZE));
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
		cout << tile.first.getPosition().x << " " << tile.first.getPosition().y << endl;
	}
}


Map::~Map()
{
}

void Map::drawMap(sf::RenderWindow& window)
{
	for (auto &tile : tiles) window.draw(tile.first);
}

pair<float, float> Map::convert2DToIso(pair<float, float> pair)
{
	return{ pair.first - pair.second, (pair.first + pair.second) / 2 };
}

pair<float, float> Map::convertIsoTo2D(pair<float, float> pair)
{
	return{ (2 * pair.second + pair.first) / 2, (2 * pair.second - pair.first) / 2 };
}

bool Map::isWalkable(pair<int, int> pair)
{
	if (pair.first == 0 && pair.second == 0) return false;
	if (pair.first == 0 && pair.second == 3) return true;
	return true;
}


pair<float, float> Map::getTileCenterFromTileCoordinate(pair<float, float> pair)
{
	return { pair.first*SIZE + SIZE / 2, pair.second*SIZE + SIZE / 2 };
}

bool Map::containsPoint(pair<float, float> point, pair<float, float> tileCenter)
{
	const int q2x = abs(point.first - tileCenter.first);
	const int q2y = abs(point.second - tileCenter.second);
	return ((2 * (SIZE / 4) * (SIZE / 2) - (SIZE / 4) * q2x - (SIZE / 2) * q2y) >= 0);
}

bool Map::rectContainsPoint(pair<float, float> point, pair<float, float> tileCoords)
{
	double pointX = point.first;
	double pointY = point.second;
	if (point.first >= tileCoords.first && point.first <= tileCoords.first + SIZE &&
		point.second >= tileCoords.second && point.second <= tileCoords.second + SIZE)
		return true;

	return false;
}
