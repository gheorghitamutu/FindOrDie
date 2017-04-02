#pragma once
#include "SFML\Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 5
class ResolutionMenu
{
	public:
		ResolutionMenu(float width, float height);
		void draw(sf::RenderWindow &window);
		void MoveUp();
		void MoveDown();
		void options(sf::Event event, sf::RenderWindow &window);
		int GetPressedItem();
		
		float returnWindowWidth();
		float returnWindowHeight();
		float height;
		float width;
		~ResolutionMenu();
	private:
		int selectedItemIndex;

		sf::Font font;
		sf::Text title;
		sf::Text characterSelectionMenu[MAX_NUMBER_OF_ITEMS];
	};

