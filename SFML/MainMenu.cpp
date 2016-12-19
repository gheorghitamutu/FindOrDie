#include "MainMenu.h"


MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("Fonts/texgyreheroscn-regular.otf"))
	{
		//handle error
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("New Game");
	menu[0].setPosition(sf::Vector2f(width / 4.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	menu[0].setScale(sf::Vector2f(2.0f, 2.0f));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Load Game");
	menu[1].setPosition(sf::Vector2f(width / 4.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	menu[1].setScale(sf::Vector2f(2.0f, 2.0f));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit Game");
	menu[2].setPosition(sf::Vector2f(width / 4.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	menu[2].setScale(sf::Vector2f(2.0f, 2.0f));

	selectedItemIndex = 0;
}


MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

void MainMenu::MoveUp()
{
	if (selectedItemIndex  >= 0) {	
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		if(selectedItemIndex>0)selectedItemIndex--;
		else selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MainMenu::MoveDown()
{
	if (selectedItemIndex >= 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		if(selectedItemIndex<MAX_NUMBER_OF_ITEMS - 1)selectedItemIndex++;
		else selectedItemIndex = 0;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
	
}

void MainMenu::options(bool &newGame, bool &gamePause, bool &inCharacterSelection,  sf::Event event, sf::RenderWindow &window)
{
	if (!gamePause && newGame && !inCharacterSelection) {
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
					inCharacterSelection = true;
					newGame = false;
					break;

				case 1:
					break;

				case 2:
					window.close();
					break;
				}
			}

		}

	}
	
}
