#include "Enemy.h"
#include <math.h> 
#include <iostream>
#include <stdlib.h>
Enemy::Enemy()
{
//	body.resize(500);
//	std::cout << body.size() << std::endl;
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
	for (int j = 0; j <= numberOfMonsters; j++) {
		if (body[j].getPosition().x - returnPlayerPosition.x > speed || body[j].getPosition().x - returnPlayerPosition.x < -speed)
		{
			if (round(body[j].getPosition().x) < round(returnPlayerPosition.x))body[j].move(speed, 0.0f);
			else if (round(body[j].getPosition().x) > round(returnPlayerPosition.x))body[j].move(-speed, 0.0f);
		}
		if (body[j].getPosition().y - returnPlayerPosition.y > speed || body[j].getPosition().y - returnPlayerPosition.y < -speed)
		{
			if (round(body[j].getPosition().y) < round(returnPlayerPosition.y))body[j].move(0.0f, speed);
			else if (round(body[j].getPosition().y) > round(returnPlayerPosition.y))body[j].move(0.0f, -speed);
		}
	}
	//std::cout << round(body.getPosition().x) << " " << round(body.getPosition().y) << std::endl;
	//std::cout << round(returnPlayerPosition.x)<< " " << round(returnPlayerPosition.y) << std::endl;
}

sf::Time Enemy::timer()
{
//	clock.restart().asSeconds(); 
     return	timeElapsed = clock.getElapsedTime();
	
}

void Enemy::createEnemy(sf::RenderWindow & window)
{
	if (timer().asSeconds() >= numberOfMonsters*spawnTimeMonsters)
	{
		body.push_back(singleBody);
		body[numberOfMonsters].setSize(sf::Vector2f(50.0f, 100.0f));
		body[numberOfMonsters].setPosition((rand() % window.getSize().x) * 10, (rand() % +window.getSize().y) * 10);
	//	std::cout << timer().asSeconds() << std::endl;
		body[numberOfMonsters].setOrigin(body[numberOfMonsters].getSize() / 2.0f);
		std::cout << numberOfMonsters << std::endl;
		numberOfMonsters++;
	}
}

int Enemy::returnNumberOfMonsters()
{
	return numberOfMonsters;
}

void Enemy::setNumberOfMonsters(int number)
{
	numberOfMonsters = number;
	body.resize(0);
	body.resize(500);
}
