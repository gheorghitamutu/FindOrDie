#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <cctype>
#include <string>
#include <math.h>
#include <vector>
#include <random>
#include "Pathfinding.h"
#include "TileFactory.h"

class Map
{
public:
	Map();
	~Map();
	void CreateMap();
	void SetWhatToDraw();
	void SetViewBounds(sf::FloatRect& view_bounds);
	void DrawMap(sf::RenderWindow& window);
	void DrawTilesOverPlayer(bool is_colliding);
	bool IsCollidingDrawOver(sf::Vector2f body_size);
	bool IsWalkable(std::pair<int, int> pair);
	bool ContainsPoint(std::pair<float, float> point, std::pair<std::vector<std::pair<float, float>>, int> non_walkable_area_coords);
	bool IsColliding(sf::Vector2f body_size, sf::Vector2f velocity);
	std::pair <float, float> Convert2DToIso(std::pair<float, float> pair);
	std::pair <float, float> ConvertIsoTo2D(std::pair<float, float> pair);
	std::pair <float, float> GetTileCenterFromTileCoordinate(std::pair<float, float> pair);
	std::vector<Tile*> CheckWhatToDraw();
	std::vector<std::pair<float, float>> GetPolygonPoints(Tile*);
	int GetTileNumberWherePlayerIs(sf::Vector2f body_size);
	int GetTileNumberClicked(sf::RenderWindow& window);
	std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> SetFinishLocation(sf::Event event, sf::RenderWindow& window, sf::Vector2f body_size);
	void SetStartLocation(sf::Vector2f body_size);
	std::pair <float, float> GetStartLocation();
	std::pair <float, float> GetFinishLocation();
	std::vector<std::pair<std::vector<std::pair<float, float>>, int>> GetFloorLevelTilesCoords();
	std::pair <int, int> GetMapDimensions();
	std::vector <Tile*> GetTiles();
	void ChangeTilesOpacity(std::vector<int> which_tiles);
	void SetPlayerPosition(std::pair <float, float> position);
	void SetEvent(sf::Event* event);
public:
	std::random_device rd;
	std::mt19937 gen { rd() };
	std::uniform_int_distribution<> dis{ 10, 150 };
	std::uniform_int_distribution<> dis2{ 1, 5 };

	std::vector<std::pair<std::pair<float, float>, bool>> tile_type;
	std::vector<std::pair<std::vector<std::pair<float, float>>, int>> floor_level_tiles_coords;
	std::vector <Tile*> tiles;
	std::vector <Tile*> non_walkable_tiles;
	std::pair <int, int> map_dimensions;
	std::vector<std::pair<std::vector<std::pair<float, float>>, int>> non_walkable_objects;
	std::vector<std::pair<std::vector<std::pair<float, float>>, int>> can_draw_over_player_objects;

	std::vector<std::vector<int>> map_matrix;
	int dir = 4;
	std::vector <int> dx = { 1, 0, -1, 0 };
	std::vector<int> dy = { 0, 1, 0, -1 };
	/*int dir = 8;
	vector<int> dx = { 1, 1, 0, -1, -1, -1, 0, 1 };
	vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };*/
	std::pair<int, int> start_location;
	std::pair<int, int> finish_location;
	std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> player_path;

	int number_of_tiles;
	int tile_number_where_player_is = 0;
	int last_known_tile_number_where_player_is = -1;

	std::pair<float, float> extreme;

	bool OnSegment(std::pair<float, float> p, std::pair<float, float> q, std::pair<float, float> r);
	int Orientation(std::pair<float, float> p, std::pair<float, float> q, std::pair<float, float> r);
	bool DoIntersect(std::pair<float, float> p1, std::pair<float, float> q1, std::pair<float, float> p2, std::pair<float, float> q2);
	bool IsInside(std::vector<std::pair<float, float>> polygon, int n, std::pair<float, float> p);

	static constexpr int quarter_tile_size = 16;
	static constexpr int half_tile_size = 32;
	static constexpr int three_fourths_tile_size = 48;
	static constexpr int tile_size = 64;


	std::vector<Tile*> draw_these;
	sf::FloatRect view_bounds;

	std::vector<int> draw_tile_over_player;
	std::vector<int> last_known_tiles_over_player;

	std::vector<int> recolor_tiles;

	std::pair <float, float> player_position;

	sf::Event* event;

	TileFactory* tile_factory;
};

