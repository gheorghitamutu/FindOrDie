#pragma once
#include <SFML\Graphics.hpp>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
class Score
{
public:
	Score();
	~Score();
	void DrawScore(sf::RenderWindow &window);
	void WriteScoreInFile();
	void updateScore() { score++; }
	void resetScore() { score = 0; }
	unsigned int getScore() { return score; }
	sf::Vector2f ReturnScorePosition() { return yourScore.getPosition(); }

	sf::Font font;
	sf::Text yourScore;
	unsigned int score;
};

