#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include "Chests.h"
#include "Score.h"
#include "Menu.h"
class Game
{
public:
	enum GameState {
		SetResolution,
		MainMenu,
		CharacterSelection,
		Running,
		Pause, 
		End,
		Exit
	};

	~Game();

	void GameRun();
	void setGameState(int gameStateNumber);
	void processEvents(sf::RenderWindow& window);

	GameState gameState = SetResolution;

	Chests chest;
	Score score;
	Enemy enemies;
	Map map;
	Camera camera;
	Player player;
	Menu menu;

	sf::Event event;
	sf::View view;
	sf::ContextSettings settings;

	bool centerCameraOnPlayer = false;
	int gameStateNo = 0;
	float textScale = 0.f;
};

