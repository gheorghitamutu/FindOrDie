#include "Game.h"

void Game::GameRun()
{
	sf::RenderWindow window(videoMode, "Find Or Die!", sf::Style::Fullscreen, settings);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);
	view = window.getDefaultView();
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			processEvents(window);
		}
		window.clear(sf::Color::Black);
		if (gameState.getCurrentState() == GameStates::GameState::MainMenu)
		{
			menu.draw(window, { view.getCenter().x, view.getCenter().y }, textScale);
		}
		else if (gameState.getCurrentState() == GameStates::GameState::CharacterSelection)
		{
			menu.draw(window, { view.getCenter().x, view.getCenter().y }, textScale);
		}
		else if (gameState.getCurrentState() == GameStates::GameState::Pause)
		{
			menu.draw(window, { view.getCenter().x, view.getCenter().y }, textScale);
		}
		else if (gameState.getCurrentState() == GameStates::GameState::Running)
		{
			player.Update(event, map);
			camera.CameraPerspective(window, { player.returnPlayer2DPosition().first, player.returnPlayer2DPosition().second }, view, centerCameraOnPlayer);
			camera.draggableCamera(window, event, centerCameraOnPlayer, view);
			map.drawMap(window);
		//	enemies.Draw(window);
		//	chest.DrawChest(window);
			player.Draw(window);
			player.RestartClock();
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
		menu.options(event, 0, player, map, gameState);
	}
	else if (gameState.getCurrentState() == GameStates::GameState::CharacterSelection)
	{
		menu.options(event, 1, player, map, gameState);
		player.StartingPosition(window);
	}
	else if (gameState.getCurrentState() == GameStates::GameState::Running)
	{
		if (event.type == sf::Event::MouseWheelMoved) // Zomm in or out if the mouse wheel moves
		{
			view.zoom(1.f + event.mouseWheel.delta*0.1f);
			textScale += event.mouseWheel.delta*0.1f;
			cout << textScale << endl;
		}
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
				centerCameraOnPlayer = !centerCameraOnPlayer;
				break;
			case sf::Keyboard::Escape:
				gameState.setCurrentState(GameStates::GameState::Pause);
				break;
			}
		case sf::Event::Resized:
			camera.getAspectRatio(window);
			break;
		}

		enemies.createEnemy(window);
		enemies.goToPlayer({ player.returnPlayer2DPosition().first, player.returnPlayer2DPosition().second });
	}
	else if (gameState.getCurrentState() == GameStates::GameState::Pause)
	{
		menu.options(event, 2, player, map, gameState);
		view.zoom(1.f - textScale/10);
	}
}

void Game::getScreenResolution()
{
	videoMode = sf::VideoMode::getDesktopMode();
}

Game::Game()
{
	getScreenResolution();
	menu.setDimensions(videoMode.width, videoMode.height);
	menu.setMenus();
	settings.antialiasingLevel = 2;

	GameRun();
}

Game::~Game()
{
}

