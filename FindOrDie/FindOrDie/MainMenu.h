#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class MainMenu
{
public:
	MainMenu(float width, float height);
	~MainMenu();
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void options(bool &newGame, bool &gamePause, bool &inCharacterSelection, sf::Event event, sf::RenderWindow &window);
	int GetPressedItem() { return selectedItemIndex; }
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

