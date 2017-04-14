#pragma once
class GameStates
{
public:
	GameStates();
	~GameStates();

	enum class GameState
	{
		MainMenu,
		CharacterSelection,
		Running,
		Pause,
		Exit
	};

	GameState getCurrentState();
	void setCurrentState(GameState state);

private:
	GameState gameState = GameState::MainMenu;
};

