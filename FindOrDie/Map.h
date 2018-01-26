#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <string>
#include<math.h>
#include <vector>
#include <random>
#include <thread>
#include "Pathfinding.h"

using namespace std;

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
	bool IsWalkable(pair<int, int> pair);
	bool ContainsPoint(pair<float, float> point, pair<vector<pair<float, float>>, int> non_walkable_area_coords);
	bool IsColliding(sf::Vector2f bodySize, sf::Vector2f velocity);
	pair <float, float> Convert2DToIso(pair<float, float> pair);
	pair <float, float> ConvertIsoTo2D(pair<float, float> pair);
	pair <float, float> GetTileCenterFromTileCoordinate(pair<float, float> pair);
	vector<sf::Sprite*> CheckWhatToDraw();
	vector<pair<float, float>> GetPolygonPoints(sf::Sprite* tile);
	int GetTileNumberWherePlayerIs(sf::Vector2f body_size);
	int GetTileNumberClicked(sf::RenderWindow& window);
	pair<string, pair<pair<int, int>, pair<int, int>>> SetFinishLocation(sf::Event event, sf::RenderWindow& window, sf::Vector2f bodySize);
	void SetStartLocation(sf::Vector2f body_size);
	pair <float, float> GetStartLocation();
	pair <float, float> GetFinishLocation();
	vector<pair<vector<pair<float, float>>, int>> GetFloorLevelTilesCoords();
	pair <int, int> GetMapDimensions();
	vector <pair<sf::Sprite, bool>> GetTiles();
	void ChangeTilesOpacity(vector<int> which_tiles);
	void SetPlayerPosition(pair <float, float> position);
	void SetEvent(sf::Event* event);
public:
	std::random_device rd;
	std::mt19937 gen { rd() };
	std::uniform_int_distribution<> dis{ 10, 150 };
	std::uniform_int_distribution<> dis2{ 1, 5 };
	sf::Texture tile_texture;
	pair<sf::Sprite, bool> tile;
	vector<pair<pair<float, float>, bool>> tile_type;
	vector<pair<vector<pair<float, float>>, int>> floor_level_tiles_coords;
	vector <pair<sf::Sprite, bool>> tiles;
	vector <pair<sf::Sprite, bool>> non_walkable_tiles;
	pair <int, int> map_dimensions;
	vector<pair<vector<pair<float, float>>, int>> non_walkable_objects;
	vector<pair<vector<pair<float, float>>, int>> can_draw_over_player_objects;

	vector<vector<int>> map_matrix;
	int dir = 4;
	vector <int> dx = { 1, 0, -1, 0 };
	vector<int> dy = { 0, 1, 0, -1 };
	/*int dir = 8;
	vector<int> dx = { 1, 1, 0, -1, -1, -1, 0, 1 };
	vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };*/
	pair<int, int> start_location;
	pair<int, int> finish_location;
	pair<string, pair<pair<int, int>, pair<int, int>>> player_path;

	int number_of_tiles;
	int tile_number_where_player_is = 0;
	int last_known_tile_number_where_player_is = -1;

	pair<float, float> extreme;

	bool onSegment(pair<float, float> p, pair<float, float> q, pair<float, float> r);
	int orientation(pair<float, float> p, pair<float, float> q, pair<float, float> r);
	bool doIntersect(pair<float, float> p1, pair<float, float> q1, pair<float, float> p2, pair<float, float> q2);
	bool isInside(vector<pair<float, float>> polygon, int n, pair<float, float> p);

	static constexpr int quarter_tile_size = 16;
	static constexpr int half_tile_size = 32;
	static constexpr int three_fourths_tile_size = 48;
	static constexpr int tile_size = 64;


	vector<sf::Sprite*> draw_these;
	sf::FloatRect view_bounds;

	vector<int> draw_tile_over_player;
	vector<int> last_known_tiles_over_player;

	vector<int> recolor_tiles;

	pair <float, float> player_position;

	sf::Event * event;
};

