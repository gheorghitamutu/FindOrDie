#include "Score.h"



Score::Score()
{
	if (!font.loadFromFile("Fonts/texgyreheroscn-regular.otf"))
	{
	}
	yourScore.setFont(font);
	yourScore.setFillColor(sf::Color::Red);
	score = 0;
}


Score::~Score()
{
}

void Score::DrawScore(sf::RenderWindow & window)
{
//	std::cout << score << std::endl;
	yourScore.setString("Your score is " + std::to_string(score));
	yourScore.setPosition(window.getSize().x / 8.0f, window.getSize().y / 2.0f);

//	camera.setCenter(yourScore.getPosition().x, yourScore.getPosition().y);
	yourScore.setScale(sf::Vector2f(2.0f, 2.0f));
	window.draw(yourScore);
}

void Score::WriteScoreInFile()
{
	std::ofstream scoreFile("score.txt");
	if (scoreFile.is_open())
	{
		scoreFile << std::to_string(score) + "\n";
	}
}
