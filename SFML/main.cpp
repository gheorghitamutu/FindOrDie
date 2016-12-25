#include<SFML\Graphics.hpp>
#include "Player.h"
#include "CharacterSelectionMenu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Map.h"
#include "Camera.h"
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Find Or Die!", sf::Style::Resize | sf::Style::Close, settings);

	

	MainMenu menu(window.getSize().x, window.getSize().y);
	PauseMenu pauseMenu(window.getSize().x, window.getSize().y);
	CharacterSelectionMenu characterSelectionMenu(window.getSize().x, window.getSize().y);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Animation/Man/fullPlayerAnimations.png");
	Player player(&playerTexture, window);

	Map newMap;

	Camera camera;

	bool newGame = true;
	bool gamePause = false;
	bool inCharacterSelection = false;

	while (window.isOpen())
	{
		player.RestartClock();
		sf::View cam = window.getDefaultView();
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

		window.clear(sf::Color::Black);
		if (!gamePause && !newGame && inCharacterSelection) characterSelectionMenu.draw(window);
		if (!gamePause && newGame && !inCharacterSelection) menu.draw(window);
		if (gamePause && !newGame && !inCharacterSelection) pauseMenu.draw(window);
		player.StartingPosition(newGame, window);
		if (!gamePause && !newGame && !inCharacterSelection) {
		newMap.drawMap(window);
		player.Update(event);
		player.Draw(window, gamePause);
		}
		else camera.CameraNormal(window); // just changing between cameras
		window.display();
	}
	return 0;
}