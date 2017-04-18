#include "Game.h"
#include <future>
void Game::GameRun()
{
	sf::RenderWindow window(videoMode, "Find Or Die!", sf::Style::Fullscreen, settings);
	window.setMouseCursorVisible(false);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{ 
			processEvents(window);
		}
		std::future<vector<sf::Sprite>> drawTheseTiles(std::async(&Map::checkWhatToDraw, &map));
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
			map.setWhatToDraw(drawTheseTiles.get());
			map.drawMap(window);
			player.Update(event, map);
			camera.CameraFollowPlayer(window, player.returnPlayer2DPosition());
		//	enemies.Draw(window);
		//	chest.DrawChest(window);
			player.Draw(window);
			player.RestartClock();
			
		}
		window.display();
		window.clear(sf::Color::Black);
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
		player.increasePlayerSpeed(event);
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
		map.setViewBounds(camera.getPlayerViewBounds());
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

