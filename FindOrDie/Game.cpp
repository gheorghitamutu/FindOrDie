#include "Game.h"
#include <future>
void Game::GameRun()
{
	sf::RenderWindow window(videoMode, "Find Or Die!", sf::Style::Resize, settings);
	window.setMouseCursorVisible(true);
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{ 
			processEvents(window);
		}
		window.clear(sf::Color::Black);
		if (gameState.getCurrentState() == GameStates::GameState::MainMenu)
		{
			camera.setMenuView(window);
			menu.draw(window);
		}
		else if (gameState.getCurrentState() == GameStates::GameState::CharacterSelection)
		{
			menu.draw(window);
		}
		else if (gameState.getCurrentState() == GameStates::GameState::Pause)
		{
			camera.setMenuView(window);
			menu.draw(window);
		}
		else if (gameState.getCurrentState() == GameStates::GameState::Running)
		{
			map.drawMap(window);
		//	enemies.Draw(window);
		//	chest.DrawChest(window);
			player.Update(map);
			player.Draw(window);
			camera.CameraFollowPlayer(window, player.returnPlayer2DPosition());
		}
		window.display();
	}
}


void Game::processEvents(sf::RenderWindow& window)
{
	if (event.type == sf::Event::Closed || gameState.getCurrentState() == GameStates::GameState::Exit) {
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
	}
	else if (gameState.getCurrentState() == GameStates::GameState::Running)
	{
		camera.draggableCamera(window, event);
		camera.zoomPlayerView(window, event);
		map.setViewBounds(camera.getPlayerViewBounds());
		map.setWhatToDraw();
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				player.setPlayerPath(map.setFinishLocation(event, window, player.returnPlayer2DPosition(), player.returnPlayerBodySize()), map.getTiles(), map.getMapDimensions());
				map.changeTilesOpacity(player.getTilesToBeColored());
			}
		}
		player.HandleEvents(event);
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				camera.centerOnPlayer(window, player.returnPlayer2DPosition());
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
		menu.options(event, player, map, gameState);
	}
}

void Game::getScreenResolution()
{
	videoMode = sf::VideoMode::getDesktopMode();
}

Game::Game()
{
	getScreenResolution();
	menu.setDimensions((float)videoMode.width, (float)videoMode.height);
	menu.setMenus();
	settings.antialiasingLevel = 2;
	camera.playerViewSetSize({ videoMode.width, videoMode.height });
	camera.playerViewSetCenter({ player.returnPlayer2DPosition() });
	camera.setLastKnownPosition(player.returnPlayer2DPosition());
	map.setViewBounds(camera.getPlayerViewBounds());
	GameRun();
}

Game::~Game()
{
}

