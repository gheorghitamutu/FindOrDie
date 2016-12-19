#include "PauseMenu.h"



PauseMenu::PauseMenu(float width, float height)
{
	if (!font.loadFromFile("Fonts/texgyreheroscn-regular.otf"))
	{
		//handle error
	}
	pauseMenu[0].setFont(font);
	pauseMenu[0].setFillColor(sf::Color::Red);
	pauseMenu[0].setString("Resume Game");
	pauseMenu[0].setPosition(sf::Vector2f(width / 4.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	pauseMenu[0].setScale(sf::Vector2f(2.0f, 2.0f));

	pauseMenu[1].setFont(font);
	pauseMenu[1].setFillColor(sf::Color::White);
	pauseMenu[1].setString("Save Game");
	pauseMenu[1].setPosition(sf::Vector2f(width / 4.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	pauseMenu[1].setScale(sf::Vector2f(2.0f, 2.0f));

	pauseMenu[2].setFont(font);
	pauseMenu[2].setFillColor(sf::Color::White);
	pauseMenu[2].setString("Exit to Main Menu");
	pauseMenu[2].setPosition(sf::Vector2f(width / 4.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	pauseMenu[2].setScale(sf::Vector2f(2.0f, 2.0f));

	selectedItemIndex = 0;
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(pauseMenu[i]);
	}
}

void PauseMenu::MoveUp()
{
	if (selectedItemIndex >= 0) {
		pauseMenu[selectedItemIndex].setFillColor(sf::Color::White);
		if (selectedItemIndex>0)selectedItemIndex--;
		else selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		pauseMenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void PauseMenu::MoveDown()
{
	if (selectedItemIndex >= 0) {
		pauseMenu[selectedItemIndex].setFillColor(sf::Color::White);
		if (selectedItemIndex<MAX_NUMBER_OF_ITEMS - 1)selectedItemIndex++;
		else selectedItemIndex = 0;
		pauseMenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void PauseMenu::options(bool &newGame, bool &gamePause, bool &inCharacterSelection, sf::Event event, sf::RenderWindow & window)
{
	if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Escape) && !newGame && !gamePause)gamePause = true;
	if (gamePause && !newGame && !inCharacterSelection) {
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
					gamePause = false;
					break;

				case 1:
					break;

				case 2:
					gamePause = false;
					newGame = true;
					break;
				}
			}
		}
	}
}
