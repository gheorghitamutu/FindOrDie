#include "Enemy.h"
#include <math.h> 
#include <iostream>
#include <stdlib.h>
#include "Map.h"
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
	// 0 - LEFT
	// 1 - LEFT UP
	// 2 - UP
	// 3 - RIGHT UP
	// 4 - RIGHT 
	// 5 - DOWN RIGHT
	// 6 - DOWN 
	// 7 - DOWN LEFT
	bool right = false;
	bool left = false;
	deltaTime /= (numberOfMonsters*speed); // fixing deltaTime divisions
	for (int j = 0; j <= numberOfMonsters; j++) {
		if (body[j].getPosition().x - returnPlayerPosition.x > speed || body[j].getPosition().x - returnPlayerPosition.x < -speed)
		{
			if (round(body[j].getPosition().x) < round(returnPlayerPosition.x)) {
				body[j].move(speed, 0.0f);
				if (body[j].getPosition().x < returnPlayerPosition.x) {
					right = true;
					row = 4;
				}
			}
			else if (round(body[j].getPosition().x) > round(returnPlayerPosition.x)) {
				body[j].move(-speed, 0.0f);
				if (body[j].getPosition().x > returnPlayerPosition.x) {
					left = true;
					row = 0;
				}
			}
		}
		if (body[j].getPosition().y - returnPlayerPosition.y > speed || body[j].getPosition().y - returnPlayerPosition.y < -speed)
		{
			if (round(body[j].getPosition().y) < round(returnPlayerPosition.y)) {
				body[j].move(0.0f, speed);
				if (body[j].getPosition().y < returnPlayerPosition.y) {
					if (right) row = 5;
					else if (left) row = 7;
					else row = 6;
				}
			}
			else if (round(body[j].getPosition().y) > round(returnPlayerPosition.y))
			{
				body[j].move(0.0f, -speed);
				if (body[j].getPosition().x < returnPlayerPosition.x) {
					if (right) row = 3;
					else if (left) row = 1;
					else row = 2;
				}
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
		body[numberOfMonsters].setSize(sf::Vector2f(25.0f, 25.0f));
		body[numberOfMonsters].setTexture(&texture);
		//body[numberOfMonsters].setPosition((rand() % window.getSize().x) * 10, (rand() % +window.getSize().y) * 10);
		body[numberOfMonsters].setPosition(250.0f, 550.0f);
		body[numberOfMonsters].setOrigin(body[numberOfMonsters].getSize() / 2.0f);
	//	std::cout << numberOfMonsters << std::endl; // !!!
		numberOfMonsters++;
	}
}

int Enemy::returnNumberOfMonsters()
{
	return numberOfMonsters;
}

void Enemy::setNumberOfMonsters(int number)
{
	//std::cout << body.size() << std::endl;
	numberOfMonsters = 1;
	body.clear();
//	body.resize(numberOfMonsters);
	body.resize(2);
}

void Enemy::setTexture()
{
	texture.loadFromFile("Animation/Monsters/zombie.png");
	//if (!texture.loadFromFile("Animation/Monsters/zombie.png"))std::cout << "NO!" << std::endl;
	//else std::cout << "YES!" << std::endl;
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

void Enemy::CheckMonsterVectorCollision(Player& player, Map& map, bool& endGame)
{
	//collision player with monster
	for (monstersIterator = 0; monstersIterator < numberOfMonsters; monstersIterator++)
	{
		if (player.GetCollider().CheckPlayerCollision(GetCollider()))endGame = true;
	}
	//colision monster with monster
	for (monstersIterator = 0; monstersIterator < numberOfMonsters; monstersIterator++)
	{
		for (secondMonstersIterator = 0; secondMonstersIterator < numberOfMonsters; secondMonstersIterator++) 
		{
			if(monstersIterator!=secondMonstersIterator)GetCollider().CheckCollision(GetColliderBetweenMonsters(), 40.0f);
		}
	}
    //collision monster with walls
	for (objectIterator = 0; objectIterator < map.ReturnBlocksPositionSize(); objectIterator++)
	{
		for (monstersIterator = 0; monstersIterator < numberOfMonsters; monstersIterator++)
		{
			GetCollider().CheckCollision(map.GetMapCollider(objectIterator), -100 * speed); //????
		}
	}
}
