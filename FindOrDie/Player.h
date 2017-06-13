#pragma once
#include<list>
#include<iostream>
#include "SFML\Graphics.hpp"
#include "math.h"
#include "Map.h"
#include "Animation.h"
using namespace std;

class Player
{
public:
	Player();
	~Player();
	void HandleEvents();
	void Update(class Map& map);
	void setVelocity();
	void Draw(sf::RenderWindow& window);
	void StartingPosition(sf::RenderWindow& window);
	void setTexture(string textureType);
	void setPlayerPath(pair<string, pair<pair<int, int>, pair<int, int>>> path, vector <pair<sf::Sprite, bool>>& tiles, pair <int, int> mapDimensions);
	pair<int, int> decodePath(const char character);
	pair<float, float> decodeDirections();
	void decodeAnimationPath(pair<float, float> direction);
	void goThroughPath();
	pair <float, float> returnPlayer2DPosition();
	sf::Vector2f returnPlayerBodySize();
	vector<int> getTilesToBeColored();
	void setEvent(sf::Event* event);
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
	AnimationIndex currentAnimation = AnimationIndex::IdleSouth;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape playerBody;
	sf::Clock time;
	sf::Vector2f velocity = { 0,0 };

	bool cameraPerspective = true;
	unsigned int row = 0;
	static constexpr float speed = 30.0f; // movement speed
	static constexpr float characterTextureSize = 80.0f;
	float deltaTime = 0.0f;

	list<pair<pair<int,int>,pair<float, float>>> playerPath;
	vector<int> tilesToBeColored;
	
	int dir = 4;
	vector <int> dx={1, 0, -1, 0};
	vector <int> dy={0, 1, 0, -1};
	/*int dir = 8;
	vector<int> dx = { 1, 1, 0, -1, -1, -1, 0, 1 };
	vector<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };*/

	sf::Vector2f direction;
	const float walkingSpeed = 1.1f;

	sf::Event* playerEvent;
};

