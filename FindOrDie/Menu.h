#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include <vector>
#include "GameStates.h"
class Menu
{
public:
	Menu();
	void draw(sf::RenderWindow & window, pair <float, float> position, float& textScale);

	void MoveUp();
	void MoveDown();
	void options(sf::Event& event, int menuNumber, class Player& player, class Map& map, GameStates& gameState);
	void pickMenu(int menuNumber);
	void setMenus();
	void setMenuPosition(pair <float, float>& position, float& textScale);
	void setDimensions(float widthD, float heightD);

public:
	int selectedItemIndex = 0;

	sf::Font font;
	sf::Text text;
	vector <sf::Text> main;
	vector <sf::Text> selectCharacter;
	vector <sf::Text> pause;

	vector <sf::Text> menu;

	int itemsMainMenu = 3;
	int itemsSelectCharacterMenu = 2;
	int itemsPauseMenu = 3;
	int menuNumber = 0;

	float width;
	float height;

	~Menu();
};

