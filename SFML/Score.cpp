#include "Score.h"



Score::Score()
{
	if (!font.loadFromFile("Fonts/texgyreheroscn-regular.otf"));
	yourScore.setFont(font);
	yourScore.setFillColor(sf::Color::Red);
}


Score::~Score()
{
}

void Score::DrawScore(sf::RenderWindow & window, std::string score)
{
//	std::cout << score << std::endl;
	yourScore.setString("Your score is " + score);
	yourScore.setPosition(window.getSize().x / 8.0f, window.getSize().y / 2.0f);
	//yourScore.setPosition(position.x, position.y);
//	camera.setCenter(yourScore.getPosition().x, yourScore.getPosition().y);
	yourScore.setScale(sf::Vector2f(2.0f, 2.0f));
	window.draw(yourScore);
}
