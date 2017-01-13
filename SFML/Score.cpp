#include "Score.h"



Score::Score()
{
	if (!font.loadFromFile("Fonts/texgyreheroscn-regular.otf"));

}


Score::~Score()
{
}

void Score::DrawScore(sf::RenderWindow & window, char score)
{
	yourScore.setFont(font);
	yourScore.setFillColor(sf::Color::Red);
	yourScore.setString("Your score is ");
	yourScore.setPosition(window.getSize().x / 2.0f, window.getSize().y / 1.0f);
	yourScore.setScale(sf::Vector2f(2.0f, 2.0f));
	window.draw(yourScore);
}
