#pragma once
#include<list>
#include<iostream>
#include "SFML\Graphics.hpp"
#include "math.h"
#include "Map.h"
#include "Animation.h"

class Player
{
public:
	Player();
	~Player();
	void HandleEvents();
	void Update(class Map& map);
	void SetVelocity();
	void Draw(sf::RenderWindow& window);
	void StartingPosition(sf::RenderWindow& window);
	void SetTexture(std::string textureType);
	void SetPlayerPath(std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>> path, std::vector <class Tile*> tiles, std::pair <int, int> map_dimensions);
	std::pair<int, int> DecodePath(const char character_direction);
	std::pair<float, float> DecodeDirections();
	void DecodeAnimationPath(std::pair<float, float> direction);
	void FollowPath();
	std::pair <float, float> GetPlayer2DPosition();
	sf::Vector2f GetPlayerBodySize();
	std::vector<int> GetTilesToBeColored();
	void SetEvent(sf::Event* event);
public:
	enum class AnimationIndex
	{
		WalkingSouth,
		WalkingWest,
		WalkingEast,
		WalkingNorth,
		RunningSouth,
		RunningWest,
		RunningEast,
		RunningNorth,
		IdleSouth,
		IdleWest,
		IdleEast,
		IdleNorth,
		WalkingSouthWest,
		WalkingNorthWest,
		WalkingSouthEast,
		WalkingNorthEast,
		RunningSouthWest,
		RunningNorthWest,
		RunningSouthEast,
		RunningNorthEast,
		IdleSouthWest,
		IdleNorthWest,
		IdleSouthEast,
		IdleNorthEast,
		Count
	};

	Animation animations[(int)AnimationIndex::Count];
	AnimationIndex current_animation = AnimationIndex::IdleSouth;

	sf::Texture* texture;
	sf::Sprite sprite;
	sf::RectangleShape player_body;
	sf::Clock time;
	sf::Vector2f velocity = { 0,0 };

	bool camera_perspective = true;
	unsigned int row = 0;
	static constexpr float speed = 30.0f; // movement speed
	static constexpr float character_texture_size = 80.0f;
	float delta_time = 0.0f;

	std::list<std::pair<std::pair<int,int>, std::pair<float, float>>> player_path;
	std::vector<int> tiles_to_be_colored;
	
	int dir = 4;
	std::vector <int> dx = { 1, 0, -1, 0 };
	std::vector <int> dy = { 0, 1, 0, -1 };
	/*int dir = 8;
	vector<int> dx = { 1, 1, 0, -1, -1, -1, 0, 1 };
	vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };*/

	sf::Vector2f direction;
	const float walking_speed = 1.1f;

	sf::Event* player_event;
};

