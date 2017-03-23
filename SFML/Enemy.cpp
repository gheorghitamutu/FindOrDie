#include "Enemy.h"
#include <math.h> 
#include <iostream>
#include <algorithm>
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
	for (auto &monster : body) window.draw(monster);
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
	//deltaTime /= (body.size()*speed); // fixing deltaTime divisions
	for (auto &monster : body) {
		if (monster.getPosition().x - returnPlayerPosition.x > speed || monster.getPosition().x - returnPlayerPosition.x < -speed)
		{
			if (round(monster.getPosition().x) < round(returnPlayerPosition.x)) {
				monster.move(speed, 0.0f);
				if (monster.getPosition().x < returnPlayerPosition.x) {
					right = true;
					row = 4;
				}
			}
			else if (round(monster.getPosition().x) > round(returnPlayerPosition.x)) {
				monster.move(-speed, 0.0f);
				if (monster.getPosition().x > returnPlayerPosition.x) {
					left = true;
					row = 0;
				}
			}
		}
		if (monster.getPosition().y - returnPlayerPosition.y > speed || monster.getPosition().y - returnPlayerPosition.y < -speed)
		{
			if (round(monster.getPosition().y) < round(returnPlayerPosition.y)) {
				monster.move(0.0f, speed);
				if (monster.getPosition().y < returnPlayerPosition.y) {
					if (right) row = 5;
					else if (left) row = 7;
					else row = 6;
				}
			}
			else if (round(monster.getPosition().y) > round(returnPlayerPosition.y))
			{
				monster.move(0.0f, -speed);
				if (monster.getPosition().x < returnPlayerPosition.x) {
					if (right) row = 3;
					else if (left) row = 1;
					else row = 2;
				}
			}
		}
		Update();
		monster.setTextureRect(uvRect);
	}
}


void Enemy::createEnemy(sf::RenderWindow & window)
{
	if (spawnTime/countSpawnTime == 1) {
		countSpawnTime = 0;
		body.push_back(singleBody);
		body.back().setSize(sf::Vector2f(12.50f, 12.50f));
		body.back().setTexture(&texture);
		body.back().setPosition(250.0f, 550.0f);
		body.back().setOrigin(body.back().getSize() / 2.0f);
	}
		countSpawnTime++;
}

void Enemy::Animation()
{
	currentImage.x = 0;
	uvRect.width = texture.getSize().x / float(imageCount.x);
	uvRect.height = texture.getSize().y / float(imageCount.y);
}

void Enemy::Update()
{
	currentImage.y = row;

	if (countSpawnTime % 10 == 0)currentImage.x++;
	if (currentImage.x >= imageCount.x)currentImage.x = 0;

	uvRect.left = currentImage.x*uvRect.width;
	uvRect.top = currentImage.y*uvRect.height;
}