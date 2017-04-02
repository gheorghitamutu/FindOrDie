#include "ResolutionMenu.h"
#include <iostream>

ResolutionMenu::ResolutionMenu(float width, float height)
{
	if (!font.loadFromFile("Fonts/texgyreheroscn-regular.otf"))
	{
		//handle error
	}
	// 800x600 1024x768 1366x768 1600x900 1920x1080
	title.setFont(font);
	title.setFillColor(sf::Color::White);
	title.setString("Choose your resolution");
	title.setPosition(sf::Vector2f(width / 6, height / 10));
	title.setScale(sf::Vector2f(1.3f, 1.3f));

	characterSelectionMenu[0].setFont(font);
	characterSelectionMenu[0].setFillColor(sf::Color::Red);
	characterSelectionMenu[0].setString("800x600");
	characterSelectionMenu[0].setPosition(sf::Vector2f(width / 6.0, height / (MAX_NUMBER_OF_ITEMS) * 1));
	characterSelectionMenu[0].setScale(sf::Vector2f(1.0f, 1.0f));

	characterSelectionMenu[1].setFont(font);
	characterSelectionMenu[1].setFillColor(sf::Color::White);
	characterSelectionMenu[1].setString("1024x768");
	characterSelectionMenu[1].setPosition(sf::Vector2f(width / 6.0, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	characterSelectionMenu[1].setScale(sf::Vector2f(1.0f, 1.0f));

	characterSelectionMenu[2].setFont(font);
	characterSelectionMenu[2].setFillColor(sf::Color::White);
	characterSelectionMenu[2].setString("1366x768");
	characterSelectionMenu[2].setPosition(sf::Vector2f(width / 6.0, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	characterSelectionMenu[2].setScale(sf::Vector2f(1.0f, 1.0f));

	characterSelectionMenu[3].setFont(font);
	characterSelectionMenu[3].setFillColor(sf::Color::White);
	characterSelectionMenu[3].setString("1600x900");
	characterSelectionMenu[3].setPosition(sf::Vector2f(width / 6.0, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));
	characterSelectionMenu[3].setScale(sf::Vector2f(1.0f, 1.0f));

	characterSelectionMenu[4].setFont(font);
	characterSelectionMenu[4].setFillColor(sf::Color::White);
	characterSelectionMenu[4].setString("1920x1080");
	characterSelectionMenu[4].setPosition(sf::Vector2f(width / 6.0, height / (MAX_NUMBER_OF_ITEMS + 1) * 5));
	characterSelectionMenu[4].setScale(sf::Vector2f(1.0f, 1.0f));

	selectedItemIndex = 0;
}

void ResolutionMenu::draw(sf::RenderWindow & window)
{
	window.draw(title);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {	
		window.draw(characterSelectionMenu[i]);
	}
}

void ResolutionMenu::MoveUp()
{
	if (selectedItemIndex >= 0) {
		characterSelectionMenu[selectedItemIndex].setFillColor(sf::Color::White);
		if (selectedItemIndex>0)selectedItemIndex--;
		else selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		characterSelectionMenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void ResolutionMenu::MoveDown()
{
	if (selectedItemIndex >= 0) {
		characterSelectionMenu[selectedItemIndex].setFillColor(sf::Color::White);
		if (selectedItemIndex<MAX_NUMBER_OF_ITEMS - 1)selectedItemIndex++;
		else selectedItemIndex = 0;
		characterSelectionMenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void ResolutionMenu::options(sf::Event event, sf::RenderWindow & window)
{
	switch (event.type) {
	case sf::Event::KeyReleased:
		switch (event.key.code) {
		case sf::Keyboard::Up:
			this->MoveUp();
			break;

		case sf::Keyboard::Down:
			this->MoveDown();
			break;

		case sf::Keyboard::Return:
			switch (this->GetPressedItem())
			{
			case 0:		
				window.clear(sf::Color::Black);
				window.close();
				height = 600;
				width = 800;
				break;
				// 800x600 1024x768 1366x768 1600x900 1920x1080
			case 1:
				window.clear(sf::Color::Black);
				window.close();
				height = 768;
				width = 1024;
				break;

			case 2:
				window.clear(sf::Color::Black);
				window.close();
				height = 768;
				width = 1366;
				break;

			case 3:
				window.clear(sf::Color::Black);
				window.close();
				height = 900;
				width = 1600;
				break;

			case 4:
				window.clear(sf::Color::Black);
				window.close();
				height = 1080;
				width = 1920;
				break;
			}
		}
	}
}

int ResolutionMenu::GetPressedItem()
{
	return selectedItemIndex;
}

float ResolutionMenu::returnWindowWidth()
{
	return width;
}

float ResolutionMenu::returnWindowHeight()
{
	return height;
}

ResolutionMenu::~ResolutionMenu()
{
}
