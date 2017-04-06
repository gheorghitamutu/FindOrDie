#include "Menu.h"
#include "Player.h"
#include "Map.h"

Menu::Menu()
{
	if (!font.loadFromFile("Fonts/texgyreheroscn-regular.otf"))
	{
		printf("Can't load font!\n");
	}
	else
	{
		text.setFont(font);
		text.setScale({ 2.f, 2.f });
		text.setFillColor(sf::Color::Red);
	}

	for (int i = 0; i < std::max(std::max(std::max(itemsMainMenu, itemsPauseMenu), itemsResMenu), itemsSelectCharacterMenu); i++)
	{
		if (i == 1)
		{
			text.setFillColor(sf::Color::White);
		}

		if (i < itemsMainMenu)main.push_back(text);
		if (i < itemsPauseMenu)pause.push_back(text);
		if (i < itemsSelectCharacterMenu)selectCharacter.push_back(text);
		if (i<itemsResMenu)selectResolution.push_back(text);
	}

	for (int i = 0; i < itemsResMenu; i++)
	{
		switch (i)
		{
		case 0:
			selectResolution[i].setString("800x600");
			break;
		case 1:
			selectResolution[i].setString("1024x768");
			break;
		case 2:
			selectResolution[i].setString("1366x768");
			break;
		case 3:
			selectResolution[i].setString("1600x900");
			break;
		case 4:
			selectResolution[i].setString("1920x1080");
			break;
		}
		selectResolution[i].setPosition({ (float)(width / 3), (float)(height / (itemsResMenu / (i / 1.4 + 1))) });
		selectResolution[i].setScale({ 1.f, 1.f });
	}

	menu = selectResolution;
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
					this->gameStateNumber = 1;
					if (selectedItemIndex == 0)
					{
						height = 600;
						width = 800;
					}
					if (selectedItemIndex == 1)
					{
						height = 768;
						width = 1024;
					}
					if (selectedItemIndex == 2)
					{
						height = 768;
						width = 1366;
					}
					if (selectedItemIndex == 3)
					{
						height = 900;
						width = 1600;
					}
					if (selectedItemIndex == 4)
					{
						height = 1080;
						width = 1920;
					}
					setMenus();
					resizeWindow(window);
					pickMenu(1);
					return this->gameStateNumber;
				}
				else if (menuNumber == 1)
				{
					if (selectedItemIndex == 0)
					{
						this->gameStateNumber = 2;
						map.createMap();
						pickMenu(2);
					}
					if (selectedItemIndex == 1)
					{
						// load game
					}
					if (selectedItemIndex == 2)
					{
						this->gameStateNumber = 6;
					}
					return this->gameStateNumber;
				}

				else if (menuNumber == 2)
				{
					gameStateNumber = 3;
					if (selectedItemIndex == 0)
					{
						player.setTextureMan();
					}
					if (selectedItemIndex == 1)
					{
						player.setTextureWoman();
					}
					pickMenu(3);
					return this->gameStateNumber;
				}
				else if (menuNumber == 3)
				{
					if (selectedItemIndex == 0)
					{
						this->gameStateNumber = 3;
					}
					if (selectedItemIndex == 1)
					{
						// save game
					}
					if (selectedItemIndex == 2)
					{
						this->gameStateNumber = 1;
						pickMenu(1);
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
		menu = selectResolution;
		break;
	case 1:
		menu = main;
		break;
	case 2:
		menu = selectCharacter;
		break;
	case 3:
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
		main[i].setPosition({ (float)(width / 3), (float)(height / (itemsMainMenu / (i / 1.4 + 0.4))) });
	}

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

void Menu::resizeWindow(sf::RenderWindow & window)
{
	window.create(sf::VideoMode((unsigned int)width, (unsigned int)height, 32), "Find or Die", sf::Style::Resize | sf::Style::Close);
	window.setPosition({ 0,0 });
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


Menu::~Menu()
{
}
