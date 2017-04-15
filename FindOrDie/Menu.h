#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include <vector>
#include "GameStates.h"
class Menu
{
public:
	Menu();
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void options(sf::Event& event, class Player& player, class Map& map, GameStates& gameState);
	void pickMenu();
	void setMenus();
	void setDimensions(float widthD, float heightD);

public:
	int selectedItemIndex = 0;

	enum class MenuState {
		Main,
		SelectCharacter,
		Pause
	};

	MenuState menuState = Menu::MenuState::Main;

	sf::Font font;
	sf::Text text;
	vector <sf::Text> main;
	vector <sf::Text> selectCharacter;
	vector <sf::Text> pause;

	vector <sf::Text> menu;

	int itemsMainMenu = 3;
	int itemsSelectCharacterMenu = 2;
	int itemsPauseMenu = 3;

	float width;
	float height;

	~Menu();
};

