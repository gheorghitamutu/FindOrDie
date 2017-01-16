#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
class Score
{
public:
	Score();
	~Score();
	void DrawScore(sf::RenderWindow &window, std::string score);
	void WriteScoreInFile(std::string score);
	sf::Vector2f ReturnScorePosition() { return yourScore.getPosition(); }

	sf::Font font;
	sf::Text yourScore;
};

