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
	for (auto tile : drawThese)
	{
			window.draw(*tile);
	}
}

void Map::drawTilesOverPlayer(bool isColliding)
{
	if (isColliding)
	{
		for (auto &elem : drawTileOverPlayer)
		{
			nonWalkableTiles[elem].first.setColor(sf::Color(255, 255, 255, 160));
		}
	}
	else
	{
		for (auto& elem : lastKnownTilesOverPlayer)
		{
			nonWalkableTiles[elem].first.setColor(sf::Color(255, 255, 255, 255));
		}
		drawTileOverPlayer.clear();
		lastKnownTilesOverPlayer.clear();
	}
	
}

pair<float, float> Map::convert2DToIso(pair<float, float> pair)
{
	return { pair.first - pair.second, (pair.first + pair.second) / 2 };
}

pair<float, float> Map::convertIsoTo2D(pair<float, float> pair)
{
	return { (2 * pair.second + pair.first) / 2, (2 * pair.second - pair.first) / 2 };
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
	tileNumberWherePlayerIs = getTileNumberWherePlayerIs(position, bodySize);
	if (tileNumberWherePlayerIs != lastKnownTileNumberWherePlayerIs)
	{
		nonWalkableObjects.clear();
		if (tileNumberWherePlayerIs - mapDimensions.first - 1 >= 0 && !tiles[tileNumberWherePlayerIs - mapDimensions.first - 1].second)
		{
			nonWalkableObjects.emplace_back(floorLevelTilesCoords[tileNumberWherePlayerIs - mapDimensions.first - 1]);
		}
		if (tileNumberWherePlayerIs - mapDimensions.first >= 0 && !tiles[tileNumberWherePlayerIs - mapDimensions.first].second)
		{
			nonWalkableObjects.emplace_back(floorLevelTilesCoords[tileNumberWherePlayerIs - mapDimensions.first]);
		}
		if (tileNumberWherePlayerIs - mapDimensions.first + 1 >= 0 && !tiles[tileNumberWherePlayerIs - mapDimensions.first + 1].second)
		{
			nonWalkableObjects.emplace_back(floorLevelTilesCoords[tileNumberWherePlayerIs - mapDimensions.first + 1]);
		}
		if (tileNumberWherePlayerIs - 1 >= 0 && !tiles[tileNumberWherePlayerIs - 1].second)
		{
			nonWalkableObjects.emplace_back(floorLevelTilesCoords[tileNumberWherePlayerIs - 1]);
		}
		if (tileNumberWherePlayerIs + 1 < numberOfTiles && !tiles[tileNumberWherePlayerIs + 1].second)
		{
			nonWalkableObjects.emplace_back(floorLevelTilesCoords[tileNumberWherePlayerIs + 1]);
		}
		if (tileNumberWherePlayerIs + mapDimensions.first - 1 < numberOfTiles && !tiles[tileNumberWherePlayerIs + mapDimensions.first - 1].second)
		{
			nonWalkableObjects.emplace_back(floorLevelTilesCoords[tileNumberWherePlayerIs + mapDimensions.first - 1]);
		}
		if (tileNumberWherePlayerIs + mapDimensions.first < numberOfTiles && !tiles[tileNumberWherePlayerIs + mapDimensions.first].second)
		{
			nonWalkableObjects.emplace_back(floorLevelTilesCoords[tileNumberWherePlayerIs + mapDimensions.first]);
		}
		if (tileNumberWherePlayerIs + mapDimensions.first + 1 < mapDimensions.first*mapDimensions.second && !tiles[tileNumberWherePlayerIs + mapDimensions.first + 1].second)
		{
			nonWalkableObjects.emplace_back(floorLevelTilesCoords[tileNumberWherePlayerIs + mapDimensions.first + 1]);
		}
		lastKnownTileNumberWherePlayerIs = tileNumberWherePlayerIs;
	}
	for (auto& object : nonWalkableObjects)
	{
		if (containsPoint({ position.first + velocity.x, position.second + velocity.y + bodySize.y }, object ))
		{
			return false;
		}
	}
	return true;
}

bool Map::isCollidingDrawOver(pair<float, float> position, sf::Vector2f bodySize)
{
		drawTileOverPlayer.clear();
		if (tileNumberWherePlayerIs - mapDimensions.first - 1 >= 0 &&
			containsPoint({ position.first, position.second + bodySize.y }, canDrawOverPlayerObjects[tileNumberWherePlayerIs - mapDimensions.first - 1]) &&
			!tiles[tileNumberWherePlayerIs - mapDimensions.first - 1].second)
		{
			drawTileOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs - mapDimensions.first - 1].second);
			lastKnownTilesOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs - mapDimensions.first - 1].second);
		}
		if (tileNumberWherePlayerIs - mapDimensions.first >= 0 &&
			!tiles[tileNumberWherePlayerIs - mapDimensions.first].second &&
			containsPoint({ position.first, position.second + bodySize.y }, canDrawOverPlayerObjects[tileNumberWherePlayerIs - mapDimensions.first]))
		{
			drawTileOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs - mapDimensions.first].second);
			lastKnownTilesOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs - mapDimensions.first].second);
		}
		if (tileNumberWherePlayerIs - mapDimensions.first + 1 >= 0 &&
			!tiles[tileNumberWherePlayerIs - mapDimensions.first + 1].second &&
			containsPoint({ position.first, position.second + bodySize.y }, canDrawOverPlayerObjects[tileNumberWherePlayerIs - mapDimensions.first + 1]))
		{
			drawTileOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs - mapDimensions.first + 1].second);
			lastKnownTilesOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs - mapDimensions.first + 1].second);
		}
		if (tileNumberWherePlayerIs - 1 >= 0 &&
			!tiles[tileNumberWherePlayerIs - 1].second &&
			containsPoint({ position.first, position.second + bodySize.y }, canDrawOverPlayerObjects[tileNumberWherePlayerIs - 1]))
		{
			drawTileOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs - 1].second);
			lastKnownTilesOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs - 1].second);
		}
		if (tileNumberWherePlayerIs + 1 < numberOfTiles &&
			!tiles[tileNumberWherePlayerIs + 1].second &&
			containsPoint({ position.first, position.second + bodySize.y }, canDrawOverPlayerObjects[tileNumberWherePlayerIs + 1]))
		{
			drawTileOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs + 1].second);
			lastKnownTilesOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs + 1].second);
		}
		if (tileNumberWherePlayerIs + mapDimensions.first - 1 < numberOfTiles &&
			!tiles[tileNumberWherePlayerIs + mapDimensions.first - 1].second &&
			containsPoint({ position.first, position.second + bodySize.y }, canDrawOverPlayerObjects[tileNumberWherePlayerIs + mapDimensions.first - 1]))
		{
			drawTileOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs + mapDimensions.first - 1].second);
			lastKnownTilesOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs + mapDimensions.first - 1].second);
		}
		if (tileNumberWherePlayerIs + mapDimensions.first < numberOfTiles &&
			!tiles[tileNumberWherePlayerIs + mapDimensions.first].second &&
			containsPoint({ position.first, position.second + bodySize.y }, canDrawOverPlayerObjects[tileNumberWherePlayerIs + mapDimensions.first]))
		{
			drawTileOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs + mapDimensions.first].second);
			lastKnownTilesOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs + mapDimensions.first].second);
		}
		if (tileNumberWherePlayerIs + mapDimensions.first + 1 < numberOfTiles &&
			!tiles[tileNumberWherePlayerIs + mapDimensions.first + 1].second &&
			containsPoint({ position.first, position.second + bodySize.y }, canDrawOverPlayerObjects[tileNumberWherePlayerIs + mapDimensions.first + 1]))
		{
			drawTileOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs + mapDimensions.first + 1].second);
			lastKnownTilesOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs + mapDimensions.first + 1].second);
		}
		if (!tiles[tileNumberWherePlayerIs].second &&
			containsPoint({ position.first, position.second + bodySize.y }, canDrawOverPlayerObjects[tileNumberWherePlayerIs]))
		{
			drawTileOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs].second);
			lastKnownTilesOverPlayer.emplace_back(canDrawOverPlayerObjects[tileNumberWherePlayerIs].second);
		}

		if (!(drawTileOverPlayer.size() == 0))
		{
			return true;
		}
		return false;
}

void Map::createMap()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(10, 150);
	std::uniform_int_distribution<> dis2(1, 5);
	mapDimensions = { dis(gen), dis(gen) };
	tilesCoords.clear();
	tiles.clear();
	nonWalkableObjects.clear();
	lastKnownTilesOverPlayer.clear();
	drawTileOverPlayer.clear();
	canDrawOverPlayerObjects.clear();
	nonWalkableTiles.clear();
	drawTileOverPlayer.clear();
	lastKnownTilesOverPlayer.clear();
	mapMatrix.clear();
	
	numberOfTiles = mapDimensions.first*mapDimensions.second;

	for (int i = 0; i < numberOfTiles; i++)
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
		tile.first.setTextureRect(sf::IntRect(3 *  tileSize, pair.first.second *  tileSize, tileSize, tileSize)); //floor level
		tiles.emplace_back(tile);

		tile.first.setTextureRect(sf::IntRect(pair.first.first *  tileSize, pair.first.second *  tileSize, tileSize, tileSize));
		nonWalkableTiles.emplace_back(tile);

		floorLevelTilesCoords.emplace_back(
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
				getPolygonPoints(&tile.first)
			},
				tileNumber
		});

		if (++posX >= mapDimensions.first)
		{
			posX = 0;
			posY++;
		}
		tileNumber++;
	}

	for (int y = 0; y<mapDimensions.second; y++)
	{
		mapMatrix.emplace_back(vector<int>(mapDimensions.first, 0));
	}

	int a = 0;
	for (auto& elem1 : mapMatrix)
	{
		for (auto& elem2 : elem1)
		{
			if (nonWalkableTiles[a++].second)
			{
				elem2 = 0;
			}
			else
			{
				elem2 = 1;
			}
		}
	}
	a = 0;
	for (auto& elem1 : mapMatrix)
	{
		for (auto& elem2 : elem1)
		{
			cout << elem2 << " ";
		}
		cout << endl;
	}
}

vector<sf::Sprite*> Map::checkWhatToDraw()
{
	std::vector<sf::Sprite*> drawTheseLocal;
	for (auto &tile : tiles)
	{
		if (tile.first.getGlobalBounds().intersects(viewBounds))
		{
			drawTheseLocal.emplace_back(&tile.first);
		}
	}

	for (auto &tile : nonWalkableTiles)
	{
		if (tile.first.getGlobalBounds().intersects(viewBounds))
		{
			drawTheseLocal.emplace_back(&tile.first);
		}
	}

	return drawTheseLocal;
}

vector<pair<float, float>> Map::getPolygonPoints(sf::Sprite* tile)
{
	return vector<pair<float, float>>
		{
			{ (*tile).getPosition().x + halfTileSize, (*tile).getPosition().y},
			{ (*tile).getPosition().x               , (*tile).getPosition().y + quarterTileSize },
			{ (*tile).getPosition().x               , (*tile).getPosition().y + threeFourthsTileSize },
			{ (*tile).getPosition().x + halfTileSize, (*tile).getPosition().y + tileSize },
			{ (*tile).getPosition().x + tileSize    , (*tile).getPosition().y + threeFourthsTileSize },
			{ (*tile).getPosition().x + tileSize    , (*tile).getPosition().y + quarterTileSize }
	};
}

int Map::getTileNumberWherePlayerIs(pair <float, float> position, sf::Vector2f bodySize)
{
	for (auto& floorTile : floorLevelTilesCoords)
	{
		if (containsPoint({ position.first,position.second + bodySize.y }, floorTile))
		{
			return floorTile.second;
		}
	}
}

int Map::getTileNumberClicked(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	std::cout << "mouse x: " << worldPos.x << std::endl;
	std::cout << "mouse y: " << worldPos.y << std::endl;
	for (auto& floorTile : floorLevelTilesCoords)
	{
		if (containsPoint({ worldPos.x, worldPos.y }, floorTile))
		{
			std::cout << "tileNumber: " << floorTile.second << std::endl;
			return floorTile.second;
		}
	}
	return -1;
}

pair<string, pair<pair<int, int>, pair<int, int>>> Map::setFinishLocation(sf::Event event, sf::RenderWindow& window, pair <float, float> position, sf::Vector2f bodySize)
{
	int tileNumberClicked = getTileNumberClicked(event, window);
	if (tileNumberClicked > -1)
	{
		if (tiles[tileNumberClicked].second)
		{
			this->finishLocation = {
				tileNumberClicked / mapDimensions.first,
				tileNumberClicked % mapDimensions.first
			};
			std::cout << "finishLocation: " << finishLocation.first <<" "<< finishLocation.second<< std::endl;
			setStartLocation(position, bodySize);
			Pathfinding* path = new Pathfinding();
			playerPath = path->pathFind(mapDimensions, mapMatrix, dx, dy, dir, startLocation.first, startLocation.second, finishLocation.first, finishLocation.second);
			delete path;
		}
	}
	return playerPath;
}

void Map::setStartLocation(pair <float, float> position, sf::Vector2f bodySize)
{
	int tileNumberPlayerIs = getTileNumberWherePlayerIs(position, bodySize);
	if (tileNumberPlayerIs > -1)
	{
			this->startLocation = {
				tileNumberPlayerIs / mapDimensions.first,
				tileNumberPlayerIs % mapDimensions.first
			};
			std::cout << "startLocation: " << startLocation.first << " " << startLocation.second << std::endl;
	}
}

pair<float, float> Map::getStartLocation()
{
	return startLocation;
}

pair<float, float> Map::getFinishLocation()
{
	return finishLocation;
}

vector<pair<vector<pair<float, float>>, int>> Map::getFloorLevelTilesCoords()
{
	return floorLevelTilesCoords;
}

pair<int, int> Map::getMapDimensions()
{
	return mapDimensions;
}

vector<pair<sf::Sprite, bool>> Map::getTiles()
{
	return tiles;
}

void Map::changeTilesOpacity(vector<int> whichTiles)
{
	for (auto& elem : whichTiles)
	{
		tiles[elem].first.setColor(sf::Color(255, 255, 255, 10));
		nonWalkableTiles[elem].first.setColor(sf::Color(255, 255, 255, 10));
	}
}

void Map::setWhatToDraw()
{
	drawThese = checkWhatToDraw();
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