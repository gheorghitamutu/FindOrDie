#include "Menu.h"
#include "Player.h"
#include "Map.h"
Menu::Menu()
{
	if (!font.loadFromFile("Fonts/neuropol.ttf"))
	{
		printf("Can't load font!\n");
	}
}

void Menu::draw(sf::RenderWindow& window)
{
	for (auto& lines : menu) {
		window.draw(lines);
	}
}

void Menu::MoveUp()
{
	menu[selectedItemIndex].setFillColor(sf::Color::Red);
	if (--selectedItemIndex < 0)
	{
		selectedItemIndex = (int)(menu.size() - 1);
	}
	menu[selectedItemIndex].setFillColor(sf::Color::White);

}

void Menu::MoveDown()
{
	menu[selectedItemIndex].setFillColor(sf::Color::Red);
	if (++selectedItemIndex > menu.size() - 1)
		{
			selectedItemIndex = 0;
		}
	menu[selectedItemIndex].setFillColor(sf::Color::White);
}

void Menu::options(sf::Event& event, class Player& player, class Map& map, GameStates& gameState)
{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				MoveUp();
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				MoveDown();
			}
			
			if (event.key.code == sf::Keyboard::Return)
			{
				if (menuState == Menu::MenuState::Main)
				{
					if (selectedItemIndex == 0)
					{
						gameState.setCurrentState(GameStates::GameState::CharacterSelection);
						menuState = Menu::MenuState::SelectCharacter;
						map.createMap();
					}
					if (selectedItemIndex == 1)
					{
						// load game
					}
					if (selectedItemIndex == 2)
					{
						gameState.setCurrentState(GameStates::GameState::Exit);
					}
				}
				else if (menuState == Menu::MenuState::SelectCharacter)
				{
					if (selectedItemIndex == 0)
					{
						player.setTexture("Man");
					}
					else if (selectedItemIndex == 1)
					{
						player.setTexture("Woman");
					}
					menuState = Menu::MenuState::Pause;
					gameState.setCurrentState(GameStates::GameState::Running);
				}

				else if (menuState == Menu::MenuState::Pause)
				{
					if (selectedItemIndex == 0)
					{
						gameState.setCurrentState(GameStates::GameState::Running);
					}
					if (selectedItemIndex == 1)
					{
						// save game
					}
					if (selectedItemIndex == 2)
					{
						gameState.setCurrentState(GameStates::GameState::MainMenu);
						menuState = Menu::MenuState::Main;
					}
				}
				pickMenu();
			}
		}
}

void Menu::pickMenu()
{
	selectedItemIndex = 0;
	switch (menuState)
	{
	case Menu::MenuState::Main:
		menu = main;
		break;
	case Menu::MenuState::SelectCharacter:
		menu = selectCharacter;
		break;
	case Menu::MenuState::Pause:
		menu = pause;
		break;
	}
	menu[selectedItemIndex].setFillColor(sf::Color::White);
}

void Menu::setDimensions(float widthD, float heightD)
{
	this->width = widthD;
	this->height = heightD;

	main = { { "New Game", font, fontSize },{ "Load Game", font,  fontSize },{ "Exit Game", font,  fontSize } };
	selectCharacter = { { "Male", font, fontSize },{ "Female", font,  fontSize } };
	pause = { { "Resume Game", font, fontSize },{ "Save Game", font,  fontSize },{ "Exit Game to Main Menu", font,  fontSize } };

	int maxItemsMenu = std::max(std::max(itemsMainMenu, itemsPauseMenu), itemsSelectCharacterMenu);
	float xPosOrigin = (float)(main[0].getString().getSize() * fontSize / 2);
	float xPos = (float)(width / 2);

	for (int i = 0; i < maxItemsMenu; i++)
	{
		if (i < itemsMainMenu)
		{
			main[i].setFillColor(sf::Color::Red);
			main[i].setOrigin(xPosOrigin, 0);
			main[i].setPosition({ xPos, (float)(height / (maxItemsMenu / (i / 1.9 + 0.4))) });
		}
		if (i < itemsPauseMenu)
		{
			pause[i].setFillColor(sf::Color::Red);
			pause[i].setOrigin(xPosOrigin, 0);
			pause[i].setPosition({ xPos, (float)(height / (maxItemsMenu / (i / 1.9 + 0.4))) });
		}
		if (i < itemsSelectCharacterMenu)
		{
			selectCharacter[i].setFillColor(sf::Color::Red);
			selectCharacter[i].setOrigin(xPosOrigin, 0);
			selectCharacter[i].setPosition({ xPos,(float)(height / (maxItemsMenu / (i / 1.9 + 0.4))) });
		}
	}
	pickMenu();
}

Menu::~Menu()
{
}
