#include "Enemy.h"

Enemy::Enemy()
{
	SetTexture();
	Animation();
}

Enemy::~Enemy()
{
}

void Enemy::Draw(sf::RenderWindow & window)
{
	for (auto &monster : this->body) window.draw(monster);
}

void Enemy::GoToPlayer(sf::Vector2f return_player_position)
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
	for (auto &monster : this->body) {
		if (monster.getPosition().x - return_player_position.x > this->speed || monster.getPosition().x - return_player_position.x < -this->speed)
		{
			if (round(monster.getPosition().x) < round(return_player_position.x))
			{
				monster.move(this->speed, 0.0f);
				if (monster.getPosition().x < return_player_position.x)
				{
					right = true;
					this->row = 4;
				}
			}
			else if (round(monster.getPosition().x) > round(return_player_position.x)) 
			{
				monster.move(-this->speed, 0.0f);
				if (monster.getPosition().x > return_player_position.x) 
				{
					left = true;
					this->row = 0;
				}
			}
		}
		if (monster.getPosition().y - return_player_position.y > this->speed || monster.getPosition().y - return_player_position.y < -this->speed)
		{
			if (round(monster.getPosition().y) < round(return_player_position.y))
			{
				monster.move(0.0f, this->speed);
				if (monster.getPosition().y < return_player_position.y)
				{
					if (right)
					{
						this->row = 5;
					}
					else if (left)
					{
						this->row = 7;
					}
					else
					{
						this->row = 6;
					}
				}
			}
			else if (round(monster.getPosition().y) > round(return_player_position.y))
			{
				monster.move(0.0f, -speed);
				if (monster.getPosition().x < return_player_position.x)
				{
					if (right)
					{
						this->row = 3;
					}
					else if (left)
					{
						this->row = 1;
					}
					else
					{
						this->row = 2;
					}
				}
			}
		}
		Update();
		monster.setTextureRect(this->uv_rect);
	}
}


void Enemy::CreateEnemy(sf::RenderWindow & window)
{
	if (this->spawn_time / this->count_spawn_time == 1)
	{
		this->count_spawn_time = 0;
		this->body.push_back(this->single_body);
		this->body.back().setSize(sf::Vector2f(12.50f, 12.50f));
		this->body.back().setTexture(&this->texture);
		this->body.back().setPosition(250.0f, 550.0f);
		this->body.back().setOrigin(this->body.back().getSize() / 2.0f);
	}
	this->count_spawn_time++;
}

void Enemy::ClearMonsterVector()
{
	this->body.erase(this->body.begin(), this->body.end());
}

void Enemy::SetTexture()
{
	this->texture.loadFromFile("Animation/Monsters/zombie.png"); 
}

void Enemy::Animation()
{
	this->current_image.x = 0;
	this->uv_rect.width = (int)(this->texture.getSize().x / float(this->image_count.x));
	this->uv_rect.height = (int)(this->texture.getSize().y / float(this->image_count.y));
}

void Enemy::Update()
{
	this->current_image.y = this->row;

	if (this->count_spawn_time % 10 == 0)
	{
		this->current_image.x++;
	}
	if (this->current_image.x >= this->image_count.x)
	{
		this->current_image.x = 0;
	}

	this->uv_rect.left = this->current_image.x*this->uv_rect.width;
	this->uv_rect.top = this->current_image.y*this->uv_rect.height;
}

int Enemy::GetMonsterVectorSize()
{
	return (int)(this->body.size());
}

float Enemy::GetMonsterSpeed()
{
	return this->speed;
}

std::vector<sf::RectangleShape> Enemy::GetMonsterVector()
{
	return this->body;
}

int Enemy::GetNumberOfMonsters()
{
	return (int)(this->body.size());
}
