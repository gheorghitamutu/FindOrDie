#include "Enemy.h"
#include <math.h> 
#include <iostream>
#include <stdlib.h>
Enemy::Enemy()
{
	setTexture();
	Animation();
}


Enemy::~Enemy()
{
}

void Enemy::Draw(sf::RenderWindow & window)
{
	for (int j = 0; j <= numberOfMonsters; j++)window.draw(body[j]);
}

void Enemy::goToPlayer(sf::Vector2f returnPlayerPosition)
{
	deltaTime /= (numberOfMonsters*speed); // fixing deltaTime divisions
	for (int j = 0; j <= numberOfMonsters; j++) {
		if (body[j].getPosition().x - returnPlayerPosition.x > speed || body[j].getPosition().x - returnPlayerPosition.x < -speed)
		{
			if (round(body[j].getPosition().x) < round(returnPlayerPosition.x)) {
				body[j].move(speed, 0.0f);
				//	row = 1;
			}
			else if (round(body[j].getPosition().x) > round(returnPlayerPosition.x)) {
				body[j].move(-speed, 0.0f);
			//	row = 1;
			}
		}
		if (body[j].getPosition().y - returnPlayerPosition.y > speed || body[j].getPosition().y - returnPlayerPosition.y < -speed)
		{
			if (round(body[j].getPosition().y) < round(returnPlayerPosition.y)) {
				body[j].move(0.0f, speed);
				//	row = 1;
			}
			else if (round(body[j].getPosition().y) > round(returnPlayerPosition.y))
			{
				body[j].move(0.0f, -speed);
				//	row = 1;
			}
		}
		Update(row, deltaTime*speed);
		body[j].setTextureRect(uvRect);
	}
}

sf::Time Enemy::timer()
{
     return	timeElapsed = clock.getElapsedTime();
}

void Enemy::createEnemy(sf::RenderWindow & window)
{
	
	if (timer().asSeconds() >= numberOfMonsters*spawnTimeMonsters)
	{
		body.push_back(singleBody);
		body[numberOfMonsters].setSize(sf::Vector2f(50.0f, 50.0f));
		body[numberOfMonsters].setTexture(&texture);
		body[numberOfMonsters].setPosition((rand() % window.getSize().x) * 10, (rand() % +window.getSize().y) * 10);
		body[numberOfMonsters].setOrigin(body[numberOfMonsters].getSize() / 2.0f);
		std::cout << numberOfMonsters << std::endl; // !!!
		numberOfMonsters++;
	}
}

int Enemy::returnNumberOfMonsters()
{
	return numberOfMonsters;
}

void Enemy::setNumberOfMonsters(int number)
{
	this->numberOfMonsters = number;
	body.resize(numberOfMonsters);
	body.resize(500);
}

void Enemy::setTexture()
{
	texture.loadFromFile("Animation/Monsters/worm.png");
	if (!texture.loadFromFile("Animation/Monsters/worm.png"))std::cout << "NO!" << std::endl;
	else std::cout << "YES!" << std::endl;
}

void Enemy::Animation()
{
	currentImage.x = 0;
	uvRect.width = texture.getSize().x / float(imageCount.x);
	uvRect.height = texture.getSize().y / float(imageCount.y);
}

void Enemy::Update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x*uvRect.width;
	uvRect.top = currentImage.y*uvRect.height;
}

void Enemy::RestartClock()
{
	deltaTime = clock2.restart().asSeconds();
}
