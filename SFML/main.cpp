#include<SFML\Graphics.hpp>
#include "Player.h"
#include "CharacterSelectionMenu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "Map.h"
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Find Or Die!", sf::Style::Resize | sf::Style::Close, settings);

	sf::View cam = window.getDefaultView();

	MainMenu menu(window.getSize().x, window.getSize().y);
	PauseMenu pauseMenu(window.getSize().x, window.getSize().y);
	CharacterSelectionMenu characterSelectionMenu(window.getSize().x, window.getSize().y);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Animation/Man/fullPlayerAnimations.png");
	Player player(&playerTexture);

	Map newMap;

	bool newGame = true;
	bool gamePause = false;
	bool inCharacterSelection = false;


	const int level[] =
	{
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 2,
		0, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 2,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 2,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 2,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 2,
		0, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 2,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 2,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 2,
		0, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 2,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 2,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 2,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 2,
		0, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 2,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2,
	};

	// create the tilemap from the level definition
	TileMap map(sf::Vector2u(64, 64), level, 16, 16);

	

	while (window.isOpen())
	{
		player.RestartClock();

		sf::Event event;
		while (window.pollEvent(event))
		{
			menu.options(newGame, gamePause, inCharacterSelection, event, window);
			characterSelectionMenu.options(newGame, gamePause, inCharacterSelection, event, window, playerTexture);		
			pauseMenu.options(newGame, gamePause, inCharacterSelection, event, window);
			if (event.type == sf::Event::Closed) window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) cam.zoom(1.05f);
	     	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) cam.zoom(0.95f);

		}

		window.clear(sf::Color(80, 100, 50));
		if (!gamePause && !newGame && inCharacterSelection) characterSelectionMenu.draw(window);
		if (!gamePause && newGame && !inCharacterSelection) menu.draw(window);
		if (gamePause && !newGame && !inCharacterSelection) pauseMenu.draw(window);
		if (!gamePause && !newGame && !inCharacterSelection) {
		window.setView(cam);
	//	window.draw(map);
		newMap.drawMap(window);
		player.Update();
		player.Draw(window);
		}
		window.display();
	}
	return 0;
}