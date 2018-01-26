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

	GameState GetCurrentState();
	void SetCurrentState(GameState state);

private:
	GameState game_state = GameState::MainMenu;
};

