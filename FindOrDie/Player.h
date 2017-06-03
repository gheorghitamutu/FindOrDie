#pragma once
#include "SFML\Graphics.hpp"
#include "math.h"
#include<iostream>
#include "Map.h"
#include "Animation.h"
using namespace std;

class Player
{
public:
	Player();
	~Player();
	void HandleEvents(sf::Event& event);
	void Update(class Map& map);
	void setDirection(sf::Vector2f direction);
	void Draw(sf::RenderWindow& window);
	void StartingPosition(sf::RenderWindow& window);
	void setTexture(string textureType);
	pair <float, float> returnPlayer2DPosition();
	sf::Vector2f returnPlayerBodySize();
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
	bool drawOver = false;
	unsigned int row = 0;
	static constexpr float speed = 25.0f; // movement speed
	static constexpr float characterTextureSize = 80.0f;
	float deltaTime = 0.0f;

};

