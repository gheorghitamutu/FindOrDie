#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "CharacterSelectionMenu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Map.h"
#include "Camera.h"
#include "ResolutionMenu.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include "Chests.h"
#include "Score.h"
class Game
{
public:
	Game();
	~Game();

	void GameRun();


	Chests chest;
	Score score;
	sf::Event event;

	Enemy enemies;
	Map map;
	Camera camera;

	Player player;

	bool newGame = true;
	bool gamePause = false;
	bool inCharacterSelection = false;
	bool centerCameraOnPlayer = false;
	bool setTexture = false;
	bool endGame = false;
};

