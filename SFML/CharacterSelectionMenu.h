#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"

#define MAX_NUMBER_OF_ITEMS 2

class CharacterSelectionMenu
{
public:
	CharacterSelectionMenu(float width, float height);
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void options(bool &newGame, bool &gamePause, bool &inCharacterSelection, sf::Event event, sf::RenderWindow &window, sf::Texture &texture);
	int GetPressedItem() { return selectedItemIndex; }
	~CharacterSelectionMenu();
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text characterSelectionMenu[MAX_NUMBER_OF_ITEMS];
};
