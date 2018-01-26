#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include "Chests.h"
#include "Menu.h"
#include "GameStates.h"

class Game
{
public:

	 Game();
	~Game();

	void GameRun();
	void ProcessEvents();
	void GetScreenResolution();

	sf::Event event;

	Chests chest;
	Enemy enemies;
	Map map;
	Player player;
	Camera camera;
	Menu menu;

	sf::ContextSettings settings;

	sf::VideoMode video_mode;

	GameStates game_state;

	sf::RenderWindow window;
};

