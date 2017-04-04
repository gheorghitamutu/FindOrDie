#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include <vector>

class Menu
{
public:
	Menu();
	void draw(sf::RenderWindow & window);

	void MoveUp();
	void MoveDown();
	int options(sf::Event& event, sf::RenderWindow &window, int menuNumber, class Player& player, class Map& map);
	void pickMenu(int menuNumber);
	void setMenus();
	void resizeWindow(sf::RenderWindow &window);

public:
	int selectedItemIndex = 0;

	sf::Font font;
	sf::Text text;
	vector <sf::Text> selectResolution;
	vector <sf::Text> main;
	vector <sf::Text> selectCharacter;
	vector <sf::Text> pause;

	vector <sf::Text> menu;

	int width = 800;
	int height = 600;
	int itemsResMenu = 5;
	int itemsMainMenu = 3;
	int itemsSelectCharacterMenu = 2;
	int itemsPauseMenu = 3;
	int menuNumber = 0;
	int gameStateNumber = 0;

	~Menu();
};

