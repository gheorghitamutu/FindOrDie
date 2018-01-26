#include "Menu.h"
#include "Player.h"
#include "Map.h"
Menu::Menu()
{
	if (!this->font.loadFromFile("Fonts/neuropol.ttf"))
	{
		printf("Can't load font!\n");
	}
}

Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow& window)
{
	for (auto& lines : this->menu) {
		window.draw(lines);
	}
}

void Menu::MoveUp()
{
	this->menu[this->selected_item_index].setFillColor(sf::Color::Red);
	if (--this->selected_item_index < 0)
	{
		this->selected_item_index = (int)(this->menu.size() - 1);
	}
	this->menu[this->selected_item_index].setFillColor(sf::Color::White);

}

void Menu::MoveDown()
{
	this->menu[this->selected_item_index].setFillColor(sf::Color::Red);
	if (++this->selected_item_index > this->menu.size() - 1)
		{
		this->selected_item_index = 0;
		}
	this->menu[this->selected_item_index].setFillColor(sf::Color::White);
}

void Menu::Options(sf::Event& event, class Player& player, class Map& map, GameStates& game_state)
{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up)
			{
				MoveUp();
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				MoveDown();
			}
			
			if (event.key.code == sf::Keyboard::Return)
			{
				if (this->menuState == Menu::MenuState::Main)
				{
					if (this->selected_item_index == 0)
					{
						game_state.SetCurrentState(GameStates::GameState::CharacterSelection);
						this->menuState = Menu::MenuState::SelectCharacter;
						map.CreateMap();
					}
					if (this->selected_item_index == 1)
					{
						// load game
					}
					if (this->selected_item_index == 2)
					{
						game_state.SetCurrentState(GameStates::GameState::Exit);
					}
				}
				else if (this->menuState == Menu::MenuState::SelectCharacter)
				{
					if (this->selected_item_index == 0)
					{
						player.SetTexture("Man");
					}
					else if (this->selected_item_index == 1)
					{
						player.SetTexture("Woman");
					}
					this->menuState = Menu::MenuState::Pause;
					game_state.SetCurrentState(GameStates::GameState::Running);
				}

				else if (this->menuState == Menu::MenuState::Pause)
				{
					if (this->selected_item_index == 0)
					{
						game_state.SetCurrentState(GameStates::GameState::Running);
					}
					if (this->selected_item_index == 1)
					{
						// save game
					}
					if (this->selected_item_index == 2)
					{
						game_state.SetCurrentState(GameStates::GameState::MainMenu);
						this->menuState = Menu::MenuState::Main;
					}
				}
				PickMenu();
			}
		}
}

void Menu::PickMenu()
{
	this->selected_item_index = 0;
	switch (this->menuState)
	{
	case Menu::MenuState::Main:
		this->menu = this->main;
		break;
	case Menu::MenuState::SelectCharacter:
		this->menu = this->select_character;
		break;
	case Menu::MenuState::Pause:
		this->menu = this->pause;
		break;
	}
	this->menu[this->selected_item_index].setFillColor(sf::Color::White);
}

void Menu::SetDimensions(float width, float height)
{
	this->width = width;
	this->height = height;

	this->main = { { "New Game", this->font, this->font_size },{ "Load Game", this->font,  this->font_size },{ "Exit Game", this->font,  this->font_size } };
	this->select_character = { { "Male", this->font, this->font_size },{ "Female", this->font,  this->font_size } };
	this->pause = { { "Resume Game", this->font, this->font_size },{ "Save Game", this->font,  this->font_size },{ "Exit Game to Main Menu", this->font,  this->font_size } };

	int max_items_menu = std::max(std::max(this->items_main_menu, this->items_pause_menu), this->items_select_character_menu);
	float x_pos_origin = (float)(this->main[0].getString().getSize() * this->font_size / 2);
	float x_pos = (float)(width / 2);

	for (int i = 0; i < max_items_menu; i++)
	{
		if (i < this->items_main_menu)
		{
			this->main[i].setFillColor(sf::Color::Red);
			this->main[i].setOrigin(x_pos_origin, 0);
			this->main[i].setPosition({ x_pos, (float)(height / (max_items_menu / (i / 1.9 + 0.4))) });
		}
		if (i < this->items_pause_menu)
		{
			this->pause[i].setFillColor(sf::Color::Red);
			this->pause[i].setOrigin(x_pos_origin, 0);
			this->pause[i].setPosition({ x_pos, (float)(height / (max_items_menu / (i / 1.9 + 0.4))) });
		}
		if (i < this->items_select_character_menu)
		{
			this->select_character[i].setFillColor(sf::Color::Red);
			this->select_character[i].setOrigin(x_pos_origin, 0);
			this->select_character[i].setPosition({ x_pos,(float)(height / (max_items_menu / (i / 1.9 + 0.4))) });
		}
	}
	PickMenu();
}
