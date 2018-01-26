#include "GameStates.h"

GameStates::GameStates()
{
}


GameStates::~GameStates()
{
}

GameStates::GameState GameStates::GetCurrentState()
{
	return this->game_state;
}

void GameStates::SetCurrentState(GameState state)
{
	this->game_state = state;
}
