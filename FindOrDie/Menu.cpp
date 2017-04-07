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
		text.setScale({ 2.f, 2.f });
		text.setFillColor(sf::Color::Red);
	}

	for (int i = 0; i < std::max(std::max(itemsMainMenu, itemsPauseMenu), itemsSelectCharacterMenu); i++)
	{
		if (i == 1)
		{
			text.setFillColor(sf::Color::White);
		}

		if (i < itemsMainMenu)main.push_back(text);
		if (i < itemsPauseMenu)pause.push_back(text);
		if (i < itemsSelectCharacterMenu)selectCharacter.push_back(text);
	}
}

void Menu::draw(sf::RenderWindow& window, pair <float, float> position, float& textScale)
{
	setMenuPosition(position, textScale);
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

int Menu::options(sf::Event& event, sf::RenderWindow &window, int menuNumber, class Player& player, class Map& map)
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
				if (menuNumber == 0)
				{
					if (selectedItemIndex == 0)
					{
						this->gameStateNumber = 1;
						map.createMap();
						pickMenu(1);
					}
					if (selectedItemIndex == 1)
					{
						// load game
						return 1000;
					}
					if (selectedItemIndex == 2)
					{
						this->gameStateNumber = 5;
					}
					return this->gameStateNumber;
				}
				else if (menuNumber == 1)
				{
					gameStateNumber = 2;
					if (selectedItemIndex == 0)
					{
						player.setTextureMan();
					}
					if (selectedItemIndex == 1)
					{
						player.setTextureWoman();
					}
					pickMenu(2);
					return this->gameStateNumber;
				}

				else if (menuNumber == 2)
				{
					if (selectedItemIndex == 0)
					{
						this->gameStateNumber = 2;
					}
					if (selectedItemIndex == 1)
					{
						// save game
						return 1000;
					}
					if (selectedItemIndex == 2)
					{
						this->gameStateNumber = 0;
						pickMenu(0);
					}
					return this->gameStateNumber;
				}
			}
		}
		return 1000;
}

void Menu::pickMenu(int menuNumber)
{
	selectedItemIndex = 0;
	switch (menuNumber) {
	case 0:
		menu = main;
		break;
	case 1:
		menu = selectCharacter;
		break;
	case 2:
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
		main[i].setPosition({ (float)(width / 3), (float)(height / (itemsSelectCharacterMenu / (i / 1.4 + 0.4))) });
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
		selectCharacter[i].setPosition({ (float)(width / 3), (float)(height / (itemsSelectCharacterMenu / (i / 1.4 + 0.4))) });
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
		pause[i].setPosition({ (float)(width / 3), (float)(height / (itemsPauseMenu / (i / 1.4 + 0.4))) });
	}
}

void Menu::setMenuPosition(pair <float, float>& position, float& textScale)
{
	int i = 0;
	for (auto& lines : menu) {
		lines.setPosition(position.first - width/3, position.second + i - height/3);
		lines.setScale({ 1.f + textScale, 1.f + textScale });
		i += 100;
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
