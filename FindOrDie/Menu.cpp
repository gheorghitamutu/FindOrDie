#include "Menu.h"
#include "Player.h"
#include "Map.h"
Menu::Menu()
{
	if (!font.loadFromFile("Fonts/neuropol.ttf"))
	{
		printf("Can't load font!\n");
	}
	else
	{
		text.setFont(font);
		text.setScale({ 1.5f, 1.5f });
		text.setFillColor(sf::Color::Red);
	}

	for (int i = 0; i < std::max(std::max(itemsMainMenu, itemsPauseMenu), itemsSelectCharacterMenu); i++)
	{
		if (i == 1)
		{
			text.setFillColor(sf::Color::White);
		}

		if (i < itemsMainMenu)main.emplace_back(text);
		if (i < itemsPauseMenu)pause.emplace_back(text);
		if (i < itemsSelectCharacterMenu)selectCharacter.emplace_back(text);
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
	if (selectedItemIndex >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		if (selectedItemIndex>0)selectedItemIndex--;
		else selectedItemIndex = menu.size() - 1;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		if (selectedItemIndex < menu.size() - 1)
			{
				selectedItemIndex++;
			}
			else
			{
				selectedItemIndex = 0;
			}
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
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
					gameState.setCurrentState(GameStates::GameState::Running);
					menuState = Menu::MenuState::Pause;
					if (selectedItemIndex == 0)
					{
						player.setTexture("Man");
					}
					if (selectedItemIndex == 1)
					{
						player.setTexture("Woman");
					}
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
	switch (menuState) {
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
}

void Menu::setMenus()
{
	for (int i = 0; i < itemsMainMenu; i++)
	{
		switch (i)
		{
		case 0:
			main[i].setString("New Game");
			break;
		case 1:
			main[i].setString("Load Game");
			break;
		case 2:
			main[i].setString("Exit Game");
			break;
		}
		main[i].setPosition({ (float)(width / 3), (float)(height / (itemsSelectCharacterMenu / (i / 1.9 + 0.4))) });
	}
	menu = main;
	for (int i = 0; i < itemsSelectCharacterMenu; i++)
	{
		switch (i)
		{
		case 0:
			selectCharacter[i].setString("Male");
			break;
		case 1:
			selectCharacter[i].setString("Female");
			break;
		}
		selectCharacter[i].setPosition({ (float)(width / 3), (float)(height / (itemsSelectCharacterMenu / (i / 1.9 + 0.4))) });
	}

	for (int i = 0; i < itemsPauseMenu; i++)
	{
		switch (i)
		{
		case 0:
			pause[i].setString("Resume Game");
			break;
		case 1:
			pause[i].setString("Save Game");
			break;
		case 2:
			pause[i].setString("Exit Game to Main Menu");
			break;
		}
		pause[i].setPosition({ (float)(width / 3), (float)(height / (itemsPauseMenu / (i / 1.9 + 0.4))) });
	}
}

void Menu::setDimensions(float widthD, float heightD)
{
	this->width = widthD;
	this->height = heightD;
}

Menu::~Menu()
{
}
