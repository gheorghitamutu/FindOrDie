#include "SFML\Graphics.hpp"
#include "Chests.h"

Chests::Chests()
{
	body.setSize(sf::Vector2f(25.0f, 25.0f));
	body.setPosition(chestNumber*350.0f, 850.0f);
	body.setOrigin(body.getSize() / 2.0f);
	texture.loadFromFile("Animation/Chest/chest.png");
	body.setTexture(&texture);
}

void Chests::DrawChest(sf::RenderWindow & window)
{
	window.draw(body);
}

void Chests::GetNumberOfChest(int & number)
{
	chestNumber = number;
	body.setPosition(chestNumber*250.0f, 550.0f);
}

void Chests::LoadTexture()
{
	texture.loadFromFile("Animation/Chest/chest.png");
	if (!texture.loadFromFile("Animation/Chest/chest.png")) std::cout << "Can t load" << std::endl;
}

Chests::~Chests()
{
}
