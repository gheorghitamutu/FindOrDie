#include "Game.h"

void Game::GameRun()
{
	while (this->window.isOpen())
	{
		while (this->window.pollEvent(this->event))
		{ 
			ProcessEvents();
		}
		this->window.clear(sf::Color::Black);
		if (this->game_state.GetCurrentState() == GameStates::GameState::MainMenu)
		{
			this->camera.SetMenuView();
			this->menu.Draw(this->window);
		}
		else if (this->game_state.GetCurrentState() == GameStates::GameState::CharacterSelection)
		{
			this->camera.SetMenuView();
			this->menu.Draw(this->window);
		}
		else if (game_state.GetCurrentState() == GameStates::GameState::Pause)
		{
			this->camera.SetMenuView();
			this->menu.Draw(this->window);
		}
		else if (this->game_state.GetCurrentState() == GameStates::GameState::Running)
		{
			this->map.SetPlayerPosition(this->player.GetPlayer2DPosition());
			this->map.ChangeTilesOpacity(this->player.GetTilesToBeColored());
			this->map.SetViewBounds(this->camera.GetPlayerViewBounds());
			this->map.SetWhatToDraw();
			this->map.DrawMap(this->window);
		//	this->enemies.Draw(this->window);
		//	this->chest.DrawChest(this->window);
			this->player.Update(this->map);
			this->camera.setPlayerView();
			this->camera.CameraFollowPlayer(this->player.GetPlayer2DPosition());
			this->player.Draw(this->window);
		}
		this->window.display();
	}
}


void Game::ProcessEvents()
{
	if (this->event.type == sf::Event::Closed || this->game_state.GetCurrentState() == GameStates::GameState::Exit)
	{
		this->window.close();
	}
	if (this->game_state.GetCurrentState() == GameStates::GameState::MainMenu)
	{
		this->menu.Options(this->event, this->player, this->map, this->game_state);
	}
	else if (this->game_state.GetCurrentState() == GameStates::GameState::CharacterSelection)
	{
		this->menu.Options(this->event, this->player, this->map, this->game_state);
		this->player.StartingPosition(this->window);
		this->camera.setPlayerView();
	}
	else if (this->game_state.GetCurrentState() == GameStates::GameState::Running)
	{
		this->camera.DraggableCamera();
		this->camera.ZoomPlayerView();
		if (this->event.type == sf::Event::MouseButtonPressed)
		{
			if (this->event.mouseButton.button == sf::Mouse::Left)
			{
				this->player.SetPlayerPath(this->map.SetFinishLocation(this->event, this->window, this->player.GetPlayerBodySize()), this->map.GetTiles(), this->map.GetMapDimensions());
			}
		}
		this->player.HandleEvents();
		switch (this->event.type)
		{
		case sf::Event::KeyReleased:
			switch (this->event.key.code)
			{
			case sf::Keyboard::Space:
				this->camera.CenterOnPlayer(this->player.GetPlayer2DPosition());
				break;
			case sf::Keyboard::Escape:
				this->game_state.SetCurrentState(GameStates::GameState::Pause);
				break;
			}
		}
	    //this->enemies.createEnemy(this->window);
		//this->enemies.goToPlayer({ this->player.returnPlayer2DPosition().first, this->player.returnPlayer2DPosition().second });
	}
	else if (this->game_state.GetCurrentState() == GameStates::GameState::Pause)
	{
		this->camera.SetMenuView();
		this->menu.Options(this->event, this->player, this->map, this->game_state);
	}
}

void Game::GetScreenResolution()
{
	this->video_mode = sf::VideoMode::getDesktopMode();
}

Game::Game()
{
	this->settings.antialiasingLevel = 1;
	GetScreenResolution();
	this->window.create(video_mode, "Find Or Die!", sf::Style::Resize, this->settings);
	this->window.setMouseCursorVisible(true);
	this->window.setFramerateLimit(60);

	this->menu.SetDimensions((float)this->video_mode.width, (float)this->video_mode.height);

	this->camera.SetEvent(&this->event);
	this->camera.SetWindow(&this->window);
	this->camera.PlayerViewSetSize({ this->video_mode.width, this->video_mode.height });
	this->camera.PlayerViewSetCenter({ this->player.GetPlayer2DPosition() });
	this->camera.SetLastKnownPosition(this->player.GetPlayer2DPosition());
	this->camera.SetMenuView();

	this->map.SetEvent(&this->event);
	this->map.SetViewBounds(this->camera.GetPlayerViewBounds());

	this->player.SetEvent(&this->event);

	GameRun();
}

Game::~Game()
{
}

