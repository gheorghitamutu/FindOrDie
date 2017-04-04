#include "Game.h"

void Game::GameRun()
{
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Find Or Die!", sf::Style::Resize | sf::Style::Close, settings);
	window.setFramerateLimit(60);
	view = window.getDefaultView();

	while (window.isOpen())
	{
		player.RestartClock();
		while (window.pollEvent(event))
		{
			processEvents(window);
		}

		if (gameState == GameState::SetResolution)
		{
			menu.draw(window, { view.getCenter().x, view.getCenter().y }, textScale);
		}
		if (gameState == GameState::MainMenu)
		{
			menu.draw(window, { view.getCenter().x, view.getCenter().y }, textScale);
		}
		if (gameState == GameState::CharacterSelection)
		{
			menu.draw(window, { view.getCenter().x, view.getCenter().y }, textScale);
		}
		if (gameState == GameState::Pause)
		{
			menu.draw(window, { view.getCenter().x, view.getCenter().y }, textScale);
		}
		if (gameState == GameState::Running)
		{
			player.Update(event, map);
			camera.CameraPerspective(window, { player.returnPlayer2DPosition().first, player.returnPlayer2DPosition().second }, view, centerCameraOnPlayer);
			camera.draggableCamera(window, event, centerCameraOnPlayer, view);
			map.drawMap(window);
			enemies.Draw(window);
			chest.DrawChest(window);
			player.Draw(window);
		}
		if(gameState == GameState::End)
		{
				score.DrawScore(window);
				window.setView(view);
		}
		window.display();
		window.clear(sf::Color::Black);
	}
}

void Game::setGameState(int gameStateNumber)
{
	switch (gameStateNumber)
	{
	case 0:
		gameState = SetResolution;
		gameStateNo = 0;
		break;
	case 1:
		gameState = MainMenu;
		gameStateNo = 1;
		break;
	case 2:
		gameState = CharacterSelection;
		gameStateNo = 2;
		break;
	case 3:
		gameState = Running;
		gameStateNo = 3;
		break;
	case 4:
		gameState = Pause;
		gameStateNo = 4;
		break;
	case 5:
		gameState = End;
		gameStateNo = 5;
		break;
	case 6:
		gameState = Exit;
		gameStateNo = 6;
	    break;
	}
}

void Game::processEvents(sf::RenderWindow& window)
{

	if (event.type == sf::Event::Closed) {
		window.close();
	}
	if (gameState == GameState::SetResolution)
	{
		int returnedState = menu.options(event, window, 0, player, map);
		if (gameStateNo != returnedState && returnedState < 6 && returnedState >= 0)
		{
			view = window.getDefaultView();
			setGameState(returnedState);
		}

	}
	else if (gameState == GameState::MainMenu)
	{
		int returnedState = menu.options(event, window, 1, player, map);
		if (gameStateNo != returnedState && returnedState <= 6 && returnedState >= 0)
		{
			setGameState(returnedState);
		}
	}
	else if (gameState == GameState::CharacterSelection)
	{
		int returnedState = menu.options(event, window, 2, player, map);
		if (gameStateNo != returnedState && returnedState < 6 && returnedState >= 0)
		{
			setGameState(returnedState);
		}
		player.StartingPosition(window);
	}
	else if (gameState == GameState::Running)
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
				setGameState(4);
				break;
			}
		case sf::Event::Resized:
			camera.getAspectRatio(window);
			break;
		}

		enemies.createEnemy(window);
		enemies.goToPlayer({ player.returnPlayer2DPosition().first, player.returnPlayer2DPosition().second });
	}
	else if (gameState == GameState::Pause)
	{
		int returnedState = menu.options(event, window, 3, player, map);
		if (gameStateNo != returnedState && returnedState < 6 && returnedState >= 0)
		{
			view.zoom(1.f - textScale/10);
			setGameState(returnedState);
		}
	}
	else if (gameState == GameState::End) {
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Return:
				score.WriteScoreInFile();
				score.resetScore();
				enemies.clearMonsterVector();
				gameState = MainMenu;
				gameStateNo = 1;
				break;
			}
		}
		view.setCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	}
	else if (gameState == GameState::Exit)
	{
		window.close();
	}
}

Game::~Game()
{
}

