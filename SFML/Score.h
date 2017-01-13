#pragma once
#include <SFML/Graphics.hpp>
class Score
{
public:
	Score();
	~Score();
	void DrawScore(sf::RenderWindow &window, char score);


	sf::Font font;
	sf::Text yourScore;
};

