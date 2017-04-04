#include "Map.h"
#include "Player.h"

Map::Map()
{
	tileTexture.loadFromFile("iso-64x64-building.png");
	tile.first.setTexture(tileTexture);
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

bool Map::isColliding(pair <float, float> position, sf::Vector2f bodySize, sf::Vector2f velocity)
{
	for (auto& tile : tiles) 
	{
		if ((velocity.x <= 0 && velocity.y <= 0) || (velocity.x >= 0 && velocity.y >= 0))
		{
			if (rectContainsPoint({ position.first + velocity.x, position.second + velocity.y + bodySize.y }, { tile.first.getPosition().x, tile.first.getPosition().y }))
			{
				if (!tile.second) {
					if (containsPoint({ position.first + velocity.x, position.second + velocity.y + bodySize.y }, { tile.first.getPosition().x + SIZE / 2, tile.first.getPosition().y + SIZE / 2 }))
					{
						return false;
					}
				}
			}
		}
		else if ((velocity.x <= 0 && velocity.y >= 0) || (velocity.x >= 0 && velocity.y <= 0))
		{
			if (rectContainsPoint({ position.first + bodySize.x + velocity.x, position.second + velocity.y + bodySize.y }, { tile.first.getPosition().x, tile.first.getPosition().y })) 
			{
				if (!tile.second) {
					if ((containsPoint({ position.first + bodySize.x + velocity.x, position.second + velocity.y + bodySize.y }, { tile.first.getPosition().x + SIZE / 2, tile.first.getPosition().y + SIZE })))
					{
						return false;
					}
				}
			}
		}
		/*if (rectContainsPoint({ position.first + velocity.x, position.second + velocity.y + bodySize.y }, { tile.first.getPosition().x, tile.first.getPosition().y }) ||
			rectContainsPoint({ position.first + bodySize.x + velocity.x, position.second + velocity.y + bodySize.y }, { tile.first.getPosition().x, tile.first.getPosition().y })) {
			if (!tile.second) {
				if (containsPoint({ position.first + velocity.x, position.second + velocity.y + bodySize.y },
				{ tile.first.getPosition().x + SIZE / 2, tile.first.getPosition().y + SIZE / 2 }) ||
					(containsPoint({ position.first + bodySize.x + velocity.x, position.second + velocity.y + bodySize.y },
					{ tile.first.getPosition().x + SIZE / 2, tile.first.getPosition().y + SIZE / 2 }))) {
					return false;
				}
			}
		}*/
	}

	return true;
}

void Map::createMap()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(10, 40);
	std::uniform_int_distribution<> dis2(1, 4);
	mapDimensions = { dis(gen), dis(gen) };
	tilesCoords.clear();
	tiles.clear();
	for (int i = 0; i < mapDimensions.second; i++)
	{
		for (int j = 0; j < mapDimensions.first; j++)
		{
			if (i == 0 || j == 0 || i == mapDimensions.second - 1 || j == mapDimensions.first - 1) {
				tilesCoords.push_back({ 0,0 });
			}
			else
			{
				if (dis2(gen) == 1)
				{
					tilesCoords.push_back({ 0,0 });
				}
				else
				{
					tilesCoords.push_back({ 0,3 });
				}
			}
		}
	}

	float posX = 0, posY = 0;
	for (auto &pair : tilesCoords)
	{
		tile.second = isWalkable({ (int)pair.first, (int)pair.second });
		tile.first.setPosition(convert2DToIso({ posX*SIZE / 2, posY*SIZE / 2 }).first, convert2DToIso({ posX*SIZE / 2 , posY*SIZE / 2 }).second);
		tile.first.setTextureRect(sf::IntRect(pair.first *  SIZE, pair.second *  SIZE, SIZE, SIZE));
		tiles.push_back(tile);

		posX++;
		if (posX >= mapDimensions.first)
		{
			posX = 0;
			posY++;
		}
	}
}
