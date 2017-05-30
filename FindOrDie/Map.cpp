#include "Map.h"
#include "Player.h"

Map::Map()
{
	tileTexture.loadFromFile("iso-64x64-building.png");
	tile.first.setTexture(tileTexture);
	extreme = { 10000, 0 };
}

Map::~Map()
{
}

void Map::drawMap(sf::RenderWindow& window)
{
	for (auto &tile : drawThese)
	{
			window.draw(tile);
	}
}

void Map::drawTilesOverPlayer(sf::RenderWindow & window)
{
	if (drawTileOverPlayer > -1)
	{
		window.draw(tiles[drawTileOverPlayer].first);
	}
	drawTileOverPlayer = -1;
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
	return { pair.first*tileSize + tileSize / 2, pair.second*tileSize + tileSize / 2 };
}


bool Map::containsPoint(pair<float, float> point, pair<vector<pair<float, float>>, int> nonWalkableAreaCoords)
{
	vector<pair<float, float>>polygon1;
	for(auto &object : nonWalkableAreaCoords.first)
	{
		polygon1.emplace_back(object);
	}
	return isInside(polygon1, polygon1.size(), { point.first, point.second });
}

bool Map::isColliding(pair <float, float> position, sf::Vector2f bodySize, sf::Vector2f velocity)
{
	for (auto& object : nonWalkableObjects)
	{
		if (containsPoint({ position.first + velocity.x, position.second + velocity.y + bodySize.y }, object ))
		{
			return false;
		}
	}
	return true;

	//// for simple bounding box collision
	//for (auto& tile : tiles)
	//{
	//	if (tile.first.getGlobalBounds().contains(position.first + velocity.x, position.second + velocity.y + bodySize.y) && !tile.second)
	//	{

	//		return false;
	//	}
	//}
	//return true;
}

void Map::isCollidingDrawOver(pair<float, float> position, sf::Vector2f bodySize)
{
	for (auto& object : canDrawOverPlayerObjects)
	{
		if (containsPoint({ position.first, position.second + bodySize.y }, object))
		{

			drawTileOverPlayer = object.second;
		}
	}
}

void Map::createMap()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(10, 30);
	std::uniform_int_distribution<> dis2(1, 8);
	mapDimensions = { dis(gen), dis(gen) };
	tilesCoords.clear();
	tiles.clear();
	nonWalkableObjects.clear();

	for (int i = 0; i < mapDimensions.first*mapDimensions.second; i++)
	{
			if (dis2(gen) == 1 ||
				i < mapDimensions.first ||
				i % mapDimensions.first  == 0 || 
				i % mapDimensions.first  == mapDimensions.first - 1 || 
				i > mapDimensions.first*(mapDimensions.second-1)) 
			{
				tilesCoords.emplace_back(pair<float,float>( 0, 0 ), false);
			}
			else
				{
					tilesCoords.emplace_back(pair<float, float>(3, 0), false);
				}
	}

	float posX = 0, posY = 0;
	int tileNumber = 0;
	for (auto &pair : tilesCoords)
	{
		tile.second = isWalkable({ (int)pair.first.first, (int)pair.first.second });
		tile.first.setPosition(convert2DToIso({ posX*(tileSize / 2), posY*(tileSize / 2) }).first, convert2DToIso({ posX*(tileSize / 2) , posY*(tileSize / 2) }).second);
		tile.first.setTextureRect(sf::IntRect(pair.first.first *  tileSize, pair.first.second *  tileSize, tileSize, tileSize));
		tiles.emplace_back(tile);

		if (!tile.second)
		{
			nonWalkableObjects.emplace_back(
				std::pair<vector<std::pair<float, float>>, int>
			{ 
				{
					{ tile.first.getPosition().x + halfTileSize, tile.first.getPosition().y + halfTileSize },
					{ tile.first.getPosition().x, tile.first.getPosition().y + threeFourthsTileSize },
					{ tile.first.getPosition().x + halfTileSize, tile.first.getPosition().y + tileSize },
					{ tile.first.getPosition().x + tileSize, tile.first.getPosition().y + threeFourthsTileSize }
				},
					tileNumber
			});

			canDrawOverPlayerObjects.emplace_back(
				std::pair<vector<std::pair<float, float>>, int>
			{
				{
					{ tile.first.getPosition().x + halfTileSize, tile.first.getPosition().y},
					{ tile.first.getPosition().x               , tile.first.getPosition().y + quarterTileSize },
					{ tile.first.getPosition().x               , tile.first.getPosition().y + threeFourthsTileSize },
					{ tile.first.getPosition().x + halfTileSize, tile.first.getPosition().y + tileSize },
					{ tile.first.getPosition().x + tileSize    , tile.first.getPosition().y + threeFourthsTileSize },
					{ tile.first.getPosition().x + tileSize    , tile.first.getPosition().y + quarterTileSize }
				},
					tileNumber
			});
		}

		if (++posX >= mapDimensions.first)
		{
			posX = 0;
			posY++;
		}
		tileNumber++;
	}
}

vector<sf::Sprite> Map::checkWhatToDraw()
{
	std::vector<sf::Sprite> drawTheseLocal;
	for (auto &tile : tiles)
	{
		if (tile.first.getGlobalBounds().intersects(viewBounds))
		{
			drawTheseLocal.emplace_back(tile.first);
		}
	}
	return drawTheseLocal;
}


void Map::setWhatToDraw(vector<sf::Sprite> drawTheseTiles)
{
	drawThese = drawTheseTiles;
}

void Map::setViewBounds(sf::FloatRect& viewBounds)
{
	this->viewBounds = viewBounds;
    //this is for drawing tiles on the entire view
	//this->viewBounds.height += 300;
	//this->viewBounds.width += 300;
	//this is for drawing tiles on a smaller area of a view | this can also be done with a viewport
	this->viewBounds.left += 150;
	this->viewBounds.top += 150;
	this->viewBounds.height -= 300;
	this->viewBounds.width -= 400;
}

bool Map::onSegment(pair<float, float> p, pair<float, float> q, pair<float, float> r)
{
	if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) && q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second))
	{
		return true;
	}	
	return false;
}

int Map::orientation(pair<float, float> p, pair<float, float> q, pair<float, float> r)
{
	int val = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
	if (val == 0)
	{
		return 0;
	}
	return (val > 0) ? 1 : 2;
}

bool Map::doIntersect(pair<float, float> p1, pair<float, float> q1, pair<float, float> p2, pair<float, float> q2)
{
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);
	if ((o1 != o2 && o3 != o4) ||
		(o1 == 0 && onSegment(p1, p2, q1)) ||
		(o2 == 0 && onSegment(p1, q2, q1)) ||
		(o3 == 0 && onSegment(p2, p1, q2)) ||
		(o4 == 0 && onSegment(p2, q1, q2)))
	{
		return true;
	}
	return false; 
}

bool Map::isInside(vector<pair<float, float>> polygon, int n, pair<float, float> p)
{
	if (n < 3)
	{
		return false;
	}
	extreme.second = p.second;
	int count = 0, i = 0, next;
	do
	{
		next = (i + 1) % n;
		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			if (orientation(polygon[i], p, polygon[next]) == 0)
			{
				return onSegment(polygon[i], p, polygon[next]);
			}
			count++;
		}
		i = next;
	} while (i != 0);
	return count & 1;
}