#include "Game.h"



Game::Game()
{
	
}


Game::~Game()
{
}

void Game::GameRun()
{
	sf::RenderWindow widow(sf::VideoMode(800, 600), "Find Or Die!", sf::Style::None | sf::Style::Close);
	widow.setVerticalSyncEnabled(true);
	widow.setFramerateLimit(30);
	ResolutionMenu resolutionMenu(widow.getSize().x, widow.getSize().y);
	while (widow.isOpen())
	{
		sf::Event eva;
		while (widow.pollEvent(eva))
		{
			resolutionMenu.options(eva, widow);
			//if (eva.type == sf::Event::Closed) return 0;
		}
		widow.clear(sf::Color::Black);
		resolutionMenu.draw(widow);
		widow.display();
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow mainWindow(sf::VideoMode(resolutionMenu.returnWindowWidth(), resolutionMenu.returnWindowHeight()), "Find Or Die!", sf::Style::Resize | sf::Style::Close, settings);
	mainWindow.setFramerateLimit(60);

	MainMenu menu(mainWindow.getSize().x, mainWindow.getSize().y);
	PauseMenu pauseMenu(mainWindow.getSize().x, mainWindow.getSize().y);
	CharacterSelectionMenu characterSelectionMenu(mainWindow.getSize().x, mainWindow.getSize().y);

	Player player(mainWindow);

	Enemy enemies;

	Map newMap;

	Camera camera;
	sf::View cam = mainWindow.getDefaultView();

	Chests chest;

	bool newGame = true;
	bool gamePause = false;
	bool inCharacterSelection = false;
	bool centerCameraOnPlayer = false;
	bool setTexture = false;
	bool endGame = false;

	int yourScore = 0;
	Score score;

	while (mainWindow.isOpen())
	{
		player.RestartClock();
		enemies.RestartClock();
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			menu.options(newGame, gamePause, inCharacterSelection, event, mainWindow);

			characterSelectionMenu.options(newGame, gamePause, inCharacterSelection, event, mainWindow, setTexture);
			if (setTexture)
			{
				player.getTexture(characterSelectionMenu.returnTexture());
				setTexture = false;
			}

			pauseMenu.options(newGame, gamePause, inCharacterSelection, event, mainWindow);

			if (event.type == sf::Event::Closed) mainWindow.close();

			if (!gamePause && !newGame && !inCharacterSelection) { // if in game
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
					camera.getAspectRatio(mainWindow);
					break;
				}
			}

			if (endGame) {
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Return:
						score.WriteScoreInFile(std::to_string(yourScore));
						newGame = true;
						endGame = false;
						break;
					}
				}
			}

			if (event.type == sf::Event::MouseWheelMoved) // Zomm in or out if the mouse wheel moves
			{
				cam.zoom(1.f + event.mouseWheel.delta*0.1f);
			}
		}

		if (!gamePause && !newGame && inCharacterSelection) characterSelectionMenu.draw(mainWindow);
		if (!gamePause && newGame && !inCharacterSelection) menu.draw(mainWindow);
		if (gamePause && !newGame && !inCharacterSelection) pauseMenu.draw(mainWindow);
		if (newGame)
		{
			enemies.setNumberOfMonsters(1);
			yourScore = 0;
		}

		player.StartingPosition(newGame, mainWindow);

		if (!gamePause && !newGame && !inCharacterSelection)
		{
			if (!endGame) {
				newMap.drawMap(mainWindow);
				enemies.createEnemy(mainWindow);
				player.Update(event);

				//check collisions: player and enemy; enemy and enemy
				enemies.CheckMonsterVectorCollision(player, newMap, endGame);
				//check collision: walls with player and enemies
				newMap.CheckPlayerCollisionWithStaticObjects(player);
				//check collision: chests with player
				if(chest.CheckCollision(player)) yourScore++;

				enemies.goToPlayer(player.returnPlayerPosition());

				camera.CameraPerspective(mainWindow, player.returnPlayerPosition(), cam, centerCameraOnPlayer);

				player.Draw(mainWindow, gamePause);

				enemies.Draw(mainWindow);

				chest.DrawChest(mainWindow);

				camera.draggableCamera(mainWindow, event, centerCameraOnPlayer, cam);
			}
			else {
				score.DrawScore(mainWindow, std::to_string(yourScore));
				cam.setCenter(mainWindow.getSize().x / 2.0f, mainWindow.getSize().y / 2.0f);
				mainWindow.setView(cam);
			}
		}

		mainWindow.display();
		mainWindow.clear(sf::Color::Black);
	}
}
