#include "Game.h"
void Game::GameRun()
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{ 
			processEvents();
		}
		window.clear(sf::Color::Black);
		if (gameState.getCurrentState() == GameStates::GameState::MainMenu)
		{
			camera.setMenuView();
			menu.draw(window);
		}
		else if (gameState.getCurrentState() == GameStates::GameState::CharacterSelection)
		{
			camera.setMenuView();
			menu.draw(window);
		}
		else if (gameState.getCurrentState() == GameStates::GameState::Pause)
		{
			camera.setMenuView();
			menu.draw(window);
		}
		else if (gameState.getCurrentState() == GameStates::GameState::Running)
		{
			map.setPlayerPosition(player.returnPlayer2DPosition());
			map.changeTilesOpacity(player.getTilesToBeColored());
			map.setViewBounds(camera.getPlayerViewBounds());
			map.setWhatToDraw();
			map.drawMap(window);
		//	enemies.Draw(window);
		//	chest.DrawChest(window);
			player.Update(map);
			camera.setPlayerView();
			camera.CameraFollowPlayer(player.returnPlayer2DPosition());
			player.Draw(window);
		}
		window.display();
	}
}


void Game::processEvents()
{
	if (event.type == sf::Event::Closed || gameState.getCurrentState() == GameStates::GameState::Exit)
	{
		window.close();
	}
	if (gameState.getCurrentState() == GameStates::GameState::MainMenu)
	{
		menu.options(event, player, map, gameState);
	}
	else if (gameState.getCurrentState() == GameStates::GameState::CharacterSelection)
	{
		menu.options(event, player, map, gameState);
		player.StartingPosition(window);
		camera.setPlayerView();
	}
	else if (gameState.getCurrentState() == GameStates::GameState::Running)
	{
		camera.draggableCamera();
		camera.zoomPlayerView();
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				player.setPlayerPath(map.setFinishLocation(event, window, player.returnPlayerBodySize()), map.getTiles(), map.getMapDimensions());
			}
		}
		player.HandleEvents();
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				camera.centerOnPlayer(player.returnPlayer2DPosition());
				break;
			case sf::Keyboard::Escape:
				gameState.setCurrentState(GameStates::GameState::Pause);
				break;
			}
		}
	    //enemies.createEnemy(window);
		//enemies.goToPlayer({ player.returnPlayer2DPosition().first, player.returnPlayer2DPosition().second });
	}
	else if (gameState.getCurrentState() == GameStates::GameState::Pause)
	{
		camera.setMenuView();
		menu.options(event, player, map, gameState);
	}
}

void Game::getScreenResolution()
{
	videoMode = sf::VideoMode::getDesktopMode();
}

Game::Game()
{
	settings.antialiasingLevel = 1;
	getScreenResolution();
	window.create(videoMode, "Find Or Die!", sf::Style::Resize, settings);
	window.setMouseCursorVisible(true);
	window.setFramerateLimit(60);

	menu.setDimensions((float)videoMode.width, (float)videoMode.height);

	camera.setEvent(&this->event);
	camera.setWindow(&this->window);
	camera.playerViewSetSize({ videoMode.width, videoMode.height });
	camera.playerViewSetCenter({ player.returnPlayer2DPosition() });
	camera.setLastKnownPosition(player.returnPlayer2DPosition());
	camera.setMenuView();

	map.setEvent(&this->event);
	map.setViewBounds(camera.getPlayerViewBounds());

	player.setEvent(&this->event);

	GameRun();
}

Game::~Game()
{
}

