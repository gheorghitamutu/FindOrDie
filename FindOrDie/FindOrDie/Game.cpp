#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

void Game::GameRun()
{
	sf::RenderWindow menuWindow(sf::VideoMode(800, 600), "Find Or Die!", sf::Style::None | sf::Style::Close);
	menuWindow.setVerticalSyncEnabled(true);
	menuWindow.setFramerateLimit(30);
	ResolutionMenu resolutionMenu(menuWindow.getSize().x, menuWindow.getSize().y);
	while (menuWindow.isOpen())
	{
		while (menuWindow.pollEvent(event))
		{
			resolutionMenu.options(event, menuWindow);
		}
		menuWindow.clear(sf::Color::Black);
		resolutionMenu.draw(menuWindow);
		menuWindow.display();
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(resolutionMenu.returnWindowWidth(), resolutionMenu.returnWindowHeight()), "Find Or Die!", sf::Style::Resize | sf::Style::Close, settings);
	window.setFramerateLimit(60);

	MainMenu menu(window.getSize().x, window.getSize().y);
	PauseMenu pauseMenu(window.getSize().x, window.getSize().y);
	CharacterSelectionMenu characterSelectionMenu(window.getSize().x, window.getSize().y);

	sf::View cam = window.getDefaultView();

	while (window.isOpen())
	{
		player.RestartClock();
		while (window.pollEvent(event))
		{
			menu.options(newGame, gamePause, inCharacterSelection, event, window);
			characterSelectionMenu.options(newGame, gamePause, inCharacterSelection, event, window, setTexture);
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::P:
					cout << "2DTop " << player.returnPlayer2DPosition().first << " " << player.returnPlayer2DPosition().second << endl;
					break;
				case sf::Keyboard::T:
					cout << map.getIsWalkable(player.returnPlayer2DPosition()) << endl;
					cout << "2DTop " << player.returnPlayer2DPosition().first << " " << player.returnPlayer2DPosition().second << endl;
					break;
				}
			}

			if (setTexture)
			{
				player.getTexture(characterSelectionMenu.returnTexture());
				setTexture = false;
			}

			pauseMenu.options(newGame, gamePause, inCharacterSelection, event, window);

			if (event.type == sf::Event::Closed) window.close();

			if (!gamePause && !newGame && !inCharacterSelection) { // if in game
				if (event.type == sf::Event::MouseWheelMoved) // Zomm in or out if the mouse wheel moves
				{
					cam.zoom(1.f + event.mouseWheel.delta*0.1f);
				}
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Space:
						centerCameraOnPlayer = !centerCameraOnPlayer;
						break;
					}
				case sf::Event::Resized:
					camera.getAspectRatio(window);
					break;
				}

				if (endGame) {
					switch (event.type)
					{
					case sf::Event::KeyReleased:
						switch (event.key.code)
						{
						case sf::Keyboard::Return:
							score.WriteScoreInFile();
							score.resetScore();
							enemies.clearMonsterVector();
							newGame = true;
							endGame = false;
							break;
						}
					}
				}
			}
		}
		if (!gamePause && !newGame && inCharacterSelection) characterSelectionMenu.draw(window);
		if (!gamePause && newGame && !inCharacterSelection) menu.draw(window);
		if (gamePause && !newGame && !inCharacterSelection) pauseMenu.draw(window);

		player.StartingPosition(newGame, window);

		if (!gamePause && !newGame && !inCharacterSelection)
		{
			if (!endGame) {
				player.Update(event, map);
				map.drawMap(window);
				enemies.createEnemy(window);

				enemies.goToPlayer({ player.returnPlayer2DPosition().first, player.returnPlayer2DPosition().second });

				camera.CameraPerspective(window, { player.returnPlayer2DPosition().first, player.returnPlayer2DPosition().second }, cam, centerCameraOnPlayer);

				enemies.Draw(window);

				chest.DrawChest(window);

				player.Draw(window, gamePause);

				camera.draggableCamera(window, event, centerCameraOnPlayer, cam);
			}
			else {
				score.DrawScore(window);
				cam.setCenter(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
				window.setView(cam);
			}
		}

		window.display();
		window.clear(sf::Color::Black);
	}
}
