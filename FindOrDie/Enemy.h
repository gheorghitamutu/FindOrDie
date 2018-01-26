#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include "Player.h"
#include "Map.h"
#include <math.h>
#include <iostream>
#include <algorithm>

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Draw(sf::RenderWindow& window);
	void GoToPlayer(sf::Vector2f return_player_position);
	void CreateEnemy(sf::RenderWindow& window);
	void ClearMonsterVector();
	void SetTexture();
	void Animation();
	void Update();

	int GetMonsterVectorSize();

	float GetMonsterSpeed();

	std::vector <sf::RectangleShape> GetMonsterVector();

	int GetNumberOfMonsters();
	
	sf::Texture* texture;

	sf::Vector2u image_count = sf::Vector2u(8, 8);
	sf::Vector2u current_image;

	sf::IntRect uv_rect;

	std::vector <sf::RectangleShape> body;
	sf::RectangleShape single_body;

	unsigned int row = 0;
	int count_spawn_time = 1;
	int spawn_time = 3600;
	float speed = 0.20f; // * 60 frames/second = 60.0f
	float switch_time = 0.4f;
};

