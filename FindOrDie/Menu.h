#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include <vector>
#include "GameStates.h"
#include <string>

class Menu
{
public:
	Menu();
	~Menu();
	void Draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void Options(sf::Event& event, class Player& player, class Map& map, GameStates& game_state);
	void PickMenu();
	void SetDimensions(float width, float height);

public:
	int selected_item_index = 0;

	enum class MenuState
	{
		Main,
		SelectCharacter,
		Pause
	};

	MenuState menuState = Menu::MenuState::Main;

	sf::Font* font;
	sf::Text text;
	std::vector <sf::Text> main;
	std::vector <sf::Text> select_character;
	std::vector <sf::Text> pause;

	std::vector <sf::Text> menu;

	int items_main_menu = 3;
	int items_select_character_menu = 2;
	int items_pause_menu = 3;

	float width;
	float height;

	unsigned int font_size = 50;
};

