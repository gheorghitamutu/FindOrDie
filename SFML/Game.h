#pragma once
#include<SFML\Graphics.hpp>
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
};

