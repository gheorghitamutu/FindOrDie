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

void Map::drawOnlyViewedTiles(sf::View view)
{
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


bool Map::containsPoint(pair<float, float> point, vector<pair<float, float>> nonWalkableAreaCoords)
{
	Point polygon1[] = { { nonWalkableAreaCoords[0].first, nonWalkableAreaCoords[0].second },
						 { nonWalkableAreaCoords[1].first, nonWalkableAreaCoords[1].second },
						 { nonWalkableAreaCoords[2].first, nonWalkableAreaCoords[2].second },
						 { nonWalkableAreaCoords[3].first, nonWalkableAreaCoords[3].second } };
	return isInside(polygon1, 4, { point.first, point.second });
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

void Map::createMap()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(100, 100);
	std::uniform_int_distribution<> dis2(1, 8);
	mapDimensions = { dis(gen), dis(gen) };
	tilesCoords.clear();
	tiles.clear();
	nonWalkableObjects.clear();
	for (int i = 0; i < mapDimensions.second; i++)
	{
		for (int j = 0; j < mapDimensions.first; j++)
		{
			if (i == 0 || j == 0 || i == mapDimensions.second - 1 || j == mapDimensions.first - 1) {
				tilesCoords.push_back({ { 0,0 }, false });
			}
			else
			{
				if (dis2(gen) == 1)
				{
					tilesCoords.push_back({ { 0,0 }, false });
				}
				else
				{
					tilesCoords.push_back({ {3,0}, true });
				}
			}
		}
	}

	float posX = 0, posY = 0;
	for (auto &pair : tilesCoords)
	{
		tile.second = isWalkable({ (int)pair.first.first, (int)pair.first.second });
		tile.first.setPosition(convert2DToIso({ posX*(SIZE / 2), posY*(SIZE / 2) }).first, convert2DToIso({ posX*(SIZE / 2) , posY*(SIZE / 2) }).second);
		tile.first.setTextureRect(sf::IntRect(pair.first.first *  SIZE, pair.first.second *  SIZE, SIZE, SIZE));
		tiles.push_back(tile);

		if (!isWalkable({ (int)pair.first.first, (int)pair.first.second }))
		{
			std::vector<std::pair<float, float>> points;
			std::pair<float, float> tileOrigin;
			tileOrigin = { tile.first.getPosition().x, tile.first.getPosition().y };
			points.push_back({ tileOrigin.first + SIZE / 2, tileOrigin.second + SIZE / 2    });
			points.push_back({ tileOrigin.first           , tileOrigin.second + SIZE * 0.75 });
			points.push_back({ tileOrigin.first + SIZE / 2, tileOrigin.second + SIZE        });
			points.push_back({ tileOrigin.first + SIZE    , tileOrigin.second + SIZE * 0.75 });
			nonWalkableObjects.push_back(points);
		}

		posX++;
		if (posX >= mapDimensions.first)
		{
			posX = 0;
			posY++;
		}
	}
}

vector<sf::Sprite> Map::checkWhatToDraw()
{
	std::vector<sf::Sprite> drawTheseLocal;
	for (auto &tile : tiles)
	{
		if (tile.first.getGlobalBounds().intersects(viewBounds))
		{
			drawTheseLocal.push_back(tile.first);
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
	this->viewBounds.left += 300;
	this->viewBounds.top += 300;
	this->viewBounds.height -= 500;
	this->viewBounds.width -= 500;
}

bool Map::onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
	{
		return true;
	}	
	return false;
}

int Map::orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}

bool Map::doIntersect(Point p1, Point q1, Point p2, Point q2)
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

bool Map::isInside(Point polygon[], int n, Point p)
{
	if (n < 3)
	{
		return false;
	}
	extreme.y = p.y;
	int count = 0, i = 0;
	do
	{
		int next = (i + 1) % n;
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