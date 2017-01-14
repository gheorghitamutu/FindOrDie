#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Score
{
public:
	Score();
	~Score();
	void DrawScore(sf::RenderWindow &window, std::string score);

	sf::Vector2f ReturnScorePosition() { return yourScore.getPosition(); }

	sf::Font font;
	sf::Text yourScore;
};

