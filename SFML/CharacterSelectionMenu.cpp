#include "CharacterSelectionMenu.h"


CharacterSelectionMenu::CharacterSelectionMenu(float width, float height)
{
	if (!font.loadFromFile("Fonts/texgyreheroscn-regular.otf"))
	{
		//handle error
	}
	characterSelectionMenu[0].setFont(font);
	characterSelectionMenu[0].setFillColor(sf::Color::Red);
	characterSelectionMenu[0].setString("Male");
	characterSelectionMenu[0].setPosition(sf::Vector2f(width / 4.5, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	characterSelectionMenu[0].setScale(sf::Vector2f(2.0f, 2.0f));

	characterSelectionMenu[1].setFont(font);
	characterSelectionMenu[1].setFillColor(sf::Color::White);
	characterSelectionMenu[1].setString("Female");
	characterSelectionMenu[1].setPosition(sf::Vector2f(width / 2.0, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	characterSelectionMenu[1].setScale(sf::Vector2f(2.0f, 2.0f));

	selectedItemIndex = 0;
}


CharacterSelectionMenu::~CharacterSelectionMenu()
{
}

void CharacterSelectionMenu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		window.draw(characterSelectionMenu[i]);
	}
}

void CharacterSelectionMenu::MoveUp()
{
	if (selectedItemIndex >= 0) {
		characterSelectionMenu[selectedItemIndex].setFillColor(sf::Color::White);
		if (selectedItemIndex>0)selectedItemIndex--;
		else selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		characterSelectionMenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}

}

void CharacterSelectionMenu::MoveDown()
{
	if (selectedItemIndex >= 0) {
		characterSelectionMenu[selectedItemIndex].setFillColor(sf::Color::White);
		if (selectedItemIndex<MAX_NUMBER_OF_ITEMS - 1)selectedItemIndex++;
		else selectedItemIndex = 0;
		characterSelectionMenu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void CharacterSelectionMenu::options(bool &newGame, bool &gamePause, bool &inCharacterSelection, sf::Event event, sf::RenderWindow &window, sf::Texture &texture)
{
	if (!gamePause && !newGame && inCharacterSelection) {
		switch (event.type) {
		case sf::Event::KeyReleased:
			switch (event.key.code) {
			case sf::Keyboard::Left:
				this->MoveUp();
				break;

			case sf::Keyboard::Right:
				this->MoveDown();
				break;

			case sf::Keyboard::Space:
				switch (this->GetPressedItem())
				{
				case 0:
					texture.loadFromFile("Animation/Man/fullPlayerAnimations.png");
					inCharacterSelection = false;
					break;

				case 1:
					texture.loadFromFile("Animation/Woman/fullPlayerAnimations.png");
					inCharacterSelection = false;
					break;
				}
			}

		}
		//no idea why this works
		//later edit: small idea why this works
		Player player(&texture, window);
	}
}

