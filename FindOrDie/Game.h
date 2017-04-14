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
	void processEvents(sf::RenderWindow& window);
	void getScreenResolution();

	Chests chest;
	Enemy enemies;
	Map map;
	Camera camera;
	Player player;
	Menu menu;

	sf::Event event;
	sf::View view;
	sf::ContextSettings settings;

	sf::VideoMode videoMode;

	GameStates gameState;

	bool centerCameraOnPlayer = false;
	int gameStateNo = 0;
	float textScale = 0.f;
};

