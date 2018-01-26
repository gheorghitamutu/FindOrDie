#include "SFML\Graphics.hpp"
#include "Chests.h"

Chests::Chests()
{
	this->body.setSize(sf::Vector2f(25.0f, 25.0f));
	this->body.setPosition(this->chest_number*350.0f, 850.0f);
	this->body.setOrigin(this->body.getSize() / 2.0f);

	this->texture = new sf::Texture;
	this->texture->loadFromFile("Animation/Chest/chest.png");
	this->body.setTexture(this->texture);
}

void Chests::DrawChest(sf::RenderWindow & window)
{
	window.draw(this->body);
}

void Chests::GetNumberOfChest(int & number)
{
	this->chest_number = number;
	this->body.setPosition(this->chest_number*250.0f, 550.0f);
}

void Chests::LoadTexture()
{
	if (this->texture != nullptr)
	{
		delete texture;
	}
	this->texture = new sf::Texture;
	this->texture->loadFromFile("Animation/Chest/chest.png");
	if (!this->texture->loadFromFile("Animation/Chest/chest.png"))
	{
		std::cout << "Can t load" << std::endl;
	}
}

Chests::~Chests()
{
	if (this->texture != nullptr)
	{
		delete texture;
	}
}
