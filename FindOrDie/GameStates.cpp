#include "GameStates.h"



GameStates::GameStates()
{
}


GameStates::~GameStates()
{
}

GameStates::GameState GameStates::getCurrentState()
{
	return this->gameState;
}

void GameStates::setCurrentState(GameState state)
{
	this->gameState = state;
}
