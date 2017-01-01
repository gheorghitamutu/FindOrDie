#include<SFML\Graphics.hpp>
#include "Player.h"
#include "CharacterSelectionMenu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Map.h"
#include "Camera.h"
#include "ResolutionMenu.h"
#include <iostream>
int main()
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
			if (eva.type == sf::Event::Closed) return 0;
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
	Map newMap;

	Camera camera;
	sf::View cam = mainWindow.getDefaultView();

	bool newGame = true;
	bool gamePause = false;
	bool inCharacterSelection = false;
	bool centerCameraOnPlayer = false;
	bool setTexture = false;

	while (mainWindow.isOpen())
	{
		player.RestartClock();
		
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			menu.options(newGame, gamePause, inCharacterSelection, event, mainWindow);

			characterSelectionMenu.options(newGame, gamePause, inCharacterSelection, event, mainWindow, setTexture);
			if (setTexture) {
				player.getTexture(characterSelectionMenu.returnTexture());
				setTexture = false;
			}

			pauseMenu.options(newGame, gamePause, inCharacterSelection, event, mainWindow);

			if (event.type == sf::Event::Closed) mainWindow.close();

			if (!gamePause && !newGame && !inCharacterSelection) { // if in game
				switch (event.type) {
				case sf::Event::KeyReleased:
					switch (event.key.code) {
					case sf::Keyboard::Space:
						centerCameraOnPlayer = !centerCameraOnPlayer;
						break;
					}
				case sf::Event::Resized:
					    camera.getAspectRatio(mainWindow);
					    break;
				}
			}	

			if(event.type == sf::Event::MouseWheelMoved) // Zomm in or out if the mouse wheel moves
	           {
	              cam.zoom(1.f + event.mouseWheel.delta*0.1f);
	           }
		}
		
		if (!gamePause && !newGame && inCharacterSelection) characterSelectionMenu.draw(mainWindow);
		if (!gamePause && newGame && !inCharacterSelection) menu.draw(mainWindow);
		if (gamePause && !newGame && !inCharacterSelection) pauseMenu.draw(mainWindow);

		player.StartingPosition(newGame, mainWindow);

		if (!gamePause && !newGame && !inCharacterSelection) {
		newMap.drawMap(mainWindow);
		player.Update(event);
		camera.CameraPerspective(mainWindow, player.returnPlayerPosition(), cam, centerCameraOnPlayer);
		player.Draw(mainWindow, gamePause);
		camera.draggableCamera(mainWindow, event, centerCameraOnPlayer, cam);
		}
		else camera.CameraNormal(mainWindow); // just changing between cameras

		mainWindow.display();
		mainWindow.clear(sf::Color::Black);
	}
	return 0;
}