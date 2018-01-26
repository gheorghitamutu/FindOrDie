#include "Player.h"
#include "Map.h"
#include<math.h>
Player::Player()
{
	this->player_body.setSize(sf::Vector2f(20.f, 20.f));
	this->player_body.setPosition({ 100, 100 });
	this->player_body.setOrigin(8, -6);

	this->texture = nullptr;
}

Player::~Player()
{
	if (this->texture != nullptr)
	{
		delete this->texture;
	}
}

void Player::HandleEvents()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && !player_path.empty())
	{
		this->player_path.clear();
	}
	if (this->player_path.empty())
	{
		this->direction = { 0.0f, 0.0f };

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			this->direction.y += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->direction.x -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->direction.x += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			this->direction.y -= 1;
		}	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			this->direction.x *= 2;
			this->direction.y *= 2;
		}
		SetVelocity();
	}
}

void Player::Update(Map& map)
{
	this->delta_time = this->time.getElapsedTime().asSeconds();
	FollowPath();
	DecodeAnimationPath({ direction.x, direction.y });
	this->animations[int(this->current_animation)].Update(this->delta_time);
	this->animations[int(this->current_animation)].ApplyToSprite(this->player_body);

	map.DrawTilesOverPlayer(map.IsCollidingDrawOver(GetPlayerBodySize()));
	if (map.IsColliding(GetPlayerBodySize(), this->velocity*this->delta_time))
	{
		this->player_body.move(this->velocity*this->delta_time);
	}
	this->time.restart().asSeconds();
}

void Player::SetVelocity()
{
	this->velocity = this->direction * this->speed;
}

void Player::Draw(sf::RenderWindow& window)
{	
	window.draw(this->player_body);
}

void Player::StartingPosition(sf::RenderWindow& window)
{
	this->player_body.setPosition({ 100,100 });
}

void Player::SetTexture(string texture_type)
{	
	if (this->texture != nullptr)
	{
		delete this->texture;
	}
	this->texture = new sf::Texture;
	this->texture->loadFromFile("Animation/" + texture_type + "/fullPlayerAnimations.png");

	for (int index = 0; index<int(AnimationIndex::Count); index++)
	{
		this->animations[index] = Animation(
			(int)this->character_texture_size,
			int(index*this->character_texture_size),
			(int)this->character_texture_size,
			(int)this->character_texture_size,
			this->texture);
	}
}

void Player::SetPlayerPath(pair<string, pair<pair<int, int>, pair<int, int>>> path, vector <pair<sf::Sprite, bool>>& tiles, pair <int, int> map_dimensions)
{
	this->player_path.clear();
	this->tiles_to_be_colored.clear();
	pair<int, int> location = path.second.first;
	int tileNumber;
	if (path.first != "")
	{
		for (auto& elem : path.first)
		{
			location.second -= DecodePath(elem).first;
			location.first -= DecodePath(elem).second;
			tileNumber = location.first*map_dimensions.first + location.second;
			this->player_path.emplace_front(location,  pair<float,float>(tiles[tileNumber].first.getPosition().x + 32, tiles[tileNumber].first.getPosition().y + 32));
			this->tiles_to_be_colored.emplace_back(tileNumber);
		}
	}
}

pair<int, int> Player::DecodePath(const char character_direction)
{
	if (this->dir == 8)
	{
		if (character_direction == '4')
		{
			return{ 0,1 };
		}
		if (character_direction == '5')
		{
			return{ 1,1 };
		}
		if (character_direction == '6')
		{
			return{ 1,0 };
		}
		if (character_direction == '3')
		{
			return{ -1,1 };
		}
		if (character_direction == '0')
		{
			return{ 0,-1 };
		}
		if (character_direction == '1')
		{
			return{ -1,-1 };
		}
		if (character_direction == '2')
		{
			return{ -1,0 };
		}
		if (character_direction == '7')
		{
			return{ 1,-1 };
		}
	}
	else if (this->dir == 4)
	{
		if (character_direction == '2')
		{
			return{ 0,1 };
		}
		if (character_direction == '3')
		{
			return{ 1,0 };
		}
		if (character_direction == '0')
		{
			return{ 0,-1 };
		}
		if (character_direction == '1')
		{
			return{ -1,0 };
		}
	}
	return { 0,0 };
}

pair<float, float> Player::DecodeDirections()
{
	if (!this->player_path.empty())
	{
		pair<float, float> d_math_vector = { this->player_path.back().second.first - this->player_body.getPosition().x, this->player_path.back().second.second - this->player_body.getPosition().y };
		float d_math_vector_length = sqrt(d_math_vector.first*d_math_vector.first + d_math_vector.second*d_math_vector.second);
		pair<float, float> d_math_vector_normalized = { d_math_vector.first / d_math_vector_length ,d_math_vector.second / d_math_vector_length };
		return d_math_vector_normalized;
	}

	return { 0,0 };
}

void Player::DecodeAnimationPath(pair<float, float> direction)
{
	if (direction.first == 0.0f && direction.second > 0.0f )
	{
		if (direction.second > this->walking_speed)
		{
			this->current_animation = AnimationIndex::RunningSouth;
		}
		else
		{
			this->current_animation = AnimationIndex::WalkingSouth;
		}
	}
	else if (direction.first > 0.0f && direction.second > 0.0f)
	{
		if (direction.first > this->walking_speed && direction.second > this->walking_speed)
		{
			this->current_animation = AnimationIndex::RunningSouthEast;
		}
		else
		{
			this->current_animation = AnimationIndex::WalkingSouthEast;
		}
	}
	else if (direction.first > 0.0f && direction.second == 0.0f)
	{
		if (direction.first > this->walking_speed)
		{
			this->current_animation = AnimationIndex::RunningEast;
		}
		else
		{
			this->current_animation = AnimationIndex::WalkingEast;
		}
	}
	else if (direction.first < 0.0f && direction.second > 0.0f)
	{
		if (direction.first < -this->walking_speed && direction.second > this->walking_speed)
		{
			this->current_animation = AnimationIndex::RunningSouthWest;
		}
		else
		{
			this->current_animation = AnimationIndex::WalkingSouthWest;
		}

	}
	else if (direction.first < 0.0f && direction.second == 0.0f)
	{
		if (direction.first < -this->walking_speed)
		{
			this->current_animation = AnimationIndex::RunningWest;
		}
		else
		{
			this->current_animation = AnimationIndex::WalkingWest;
		}
	}
	else if (direction.first < 0.0f && direction.second < 0.0f)
	{
		if (direction.first < -this->walking_speed && direction.second < -this->walking_speed)
		{
			this->current_animation = AnimationIndex::RunningNorthWest;
		}
		else
		{
			this->current_animation = AnimationIndex::WalkingNorthWest;
		}
	}
	else if (direction.first == 0.0f && direction.second < 0.0f)
	{
		if (direction.second < -this->walking_speed)
		{
			this->current_animation = AnimationIndex::RunningNorth;
		}
		else
		{
			this->current_animation = AnimationIndex::WalkingNorth;
		}
	}
	else if (direction.first > 0.0f && direction.second < 0.0f)
	{
		if (direction.first > this->walking_speed && direction.second < -this->walking_speed)
		{
			this->current_animation = AnimationIndex::RunningNorthEast;
		}
		else
		{
			this->current_animation = AnimationIndex::WalkingNorthEast;
		}
	}
	else
	{
		if (this->current_animation == AnimationIndex::WalkingSouth || this->current_animation == AnimationIndex::RunningSouth)
		{
			this->current_animation = AnimationIndex::IdleSouth;
		}
		else if (this->current_animation == AnimationIndex::WalkingNorth || this->current_animation == AnimationIndex::RunningNorth)
		{
			this->current_animation = AnimationIndex::IdleNorth;
		}
		else if (this->current_animation == AnimationIndex::WalkingEast || this->current_animation == AnimationIndex::RunningEast)
		{
			this->current_animation = AnimationIndex::IdleEast;
		}
		else if (this->current_animation == AnimationIndex::WalkingWest || this->current_animation == AnimationIndex::RunningWest)
		{
			this->current_animation = AnimationIndex::IdleWest;
		}
		else if (this->current_animation == AnimationIndex::WalkingSouthEast || this->current_animation == AnimationIndex::RunningSouthEast)
		{
			this->current_animation = AnimationIndex::IdleSouthEast;
		}
		else if (this->current_animation == AnimationIndex::WalkingNorthEast || this->current_animation == AnimationIndex::RunningNorthEast)
		{
			this->current_animation = AnimationIndex::IdleNorthEast;
		}
		else if (this->current_animation == AnimationIndex::WalkingSouthWest || this->current_animation == AnimationIndex::RunningSouthWest)
		{
			this->current_animation = AnimationIndex::IdleNorthWest;
		}
		else if (this->current_animation == AnimationIndex::WalkingNorthWest || this->current_animation == AnimationIndex::RunningNorthWest)
		{
			this->current_animation = AnimationIndex::IdleNorthWest;
		}
	}
}

void Player::FollowPath()
{
	if (!this->player_path.empty())
	{
		if (abs(this->player_body.getPosition().x - this->player_path.back().second.first) < 10 &&
			abs(this->player_body.getPosition().y - this->player_path.back().second.second) < 10)
		{
			this->player_path.pop_back();
		}
		else
		{
			this->direction = { DecodeDirections().first * 3, DecodeDirections().second * 3 };
			SetVelocity();
		}
	}
	else
	{
		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)))
		{
			this->direction = { 0,0 };
			SetVelocity();
		}
	}
}

pair <float, float> Player::GetPlayer2DPosition()
{
	return{ this->player_body.getPosition().x, this->player_body.getPosition().y };
}

sf::Vector2f Player::GetPlayerBodySize()
{
	return this->player_body.getSize();
}

vector<int> Player::GetTilesToBeColored()
{
	if (this->player_path.empty())
	{
		return {};
	}
	return this->tiles_to_be_colored;
}

void Player::SetEvent(sf::Event * event)
{
	this->player_event = event;
}