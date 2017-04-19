#include "Player.h"
#include "Map.h"

Player::Player()
{
	setTextureMan();
	playerBody.setSize(sf::Vector2f(25.f, 25.f));
	playerBody.setPosition({ 300, 300 });
	playerBody.setTexture(&texture);
	for(int i = 0; i<int(AnimationIndex::Count); i++)
	{
		animations[i] = Animation(characterTextureSize, i*characterTextureSize, characterTextureSize, characterTextureSize, texture);
	}

}

void Player::HandleEvents(sf::Event& event)
{
	sf::Vector2f direction = { 0.0f, 0.0f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		direction.x -= 1;
		direction.y += 1;
		currentAnimation = AnimationIndex::RunningSouthWest;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		direction.x += 1;
		direction.y += 1;
		currentAnimation = AnimationIndex::RunningSouthEast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		direction.x -= 1;
		direction.y -= 1;
		currentAnimation = AnimationIndex::RunningNorthWest;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		direction.x += 1;
		direction.y -= 1;
		currentAnimation = AnimationIndex::RunningNorthEast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		direction.x -= 1;
		direction.y += 1;
		currentAnimation = AnimationIndex::WalkingSouthWest;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		direction.x += 1;
		direction.y += 1;
		currentAnimation = AnimationIndex::WalkingSouthEast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		direction.x -= 1;
		direction.y -= 1;
		currentAnimation = AnimationIndex::WalkingNorthWest;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		direction.x += 1;
		direction.y -= 1;
		currentAnimation = AnimationIndex::WalkingNorthEast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		direction.y += 1;
		currentAnimation = AnimationIndex::RunningSouth;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		direction.x -= 1;
		currentAnimation = AnimationIndex::RunningWest;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		direction.x += 1;
		currentAnimation = AnimationIndex::RunningEast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		direction.y -= 1;
		currentAnimation = AnimationIndex::RunningNorth;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		direction.y += 1;
		currentAnimation = AnimationIndex::WalkingSouth;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		direction.x -= 1;
		currentAnimation = AnimationIndex::WalkingWest;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		direction.x += 1;
		currentAnimation = AnimationIndex::WalkingEast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		direction.y -= 1;
		currentAnimation = AnimationIndex::WalkingNorth;
	}
	else
	{
		if (currentAnimation == AnimationIndex::WalkingSouth || currentAnimation == AnimationIndex::RunningSouth)
		{
			currentAnimation = AnimationIndex::IdleSouth;
		}
		else if (currentAnimation == AnimationIndex::WalkingNorth || currentAnimation == AnimationIndex::RunningNorth)
		{
			currentAnimation = AnimationIndex::IdleNorth;
		}
		else if (currentAnimation == AnimationIndex::WalkingEast || currentAnimation == AnimationIndex::RunningEast)
		{
			currentAnimation = AnimationIndex::IdleEast;
		}
		else if (currentAnimation == AnimationIndex::WalkingWest || currentAnimation == AnimationIndex::RunningWest)
		{
			currentAnimation = AnimationIndex::IdleWest;
		}
		else if (currentAnimation == AnimationIndex::WalkingSouthEast || currentAnimation == AnimationIndex::RunningSouthEast)
		{
			currentAnimation = AnimationIndex::IdleSouthEast;
		}
		else if (currentAnimation == AnimationIndex::WalkingNorthEast || currentAnimation == AnimationIndex::RunningNorthEast)
		{
			currentAnimation = AnimationIndex::IdleNorthEast;
		}
		else if (currentAnimation == AnimationIndex::WalkingSouthWest || currentAnimation == AnimationIndex::RunningSouthWest)
		{
			currentAnimation = AnimationIndex::IdleNorthWest;
		}
		else if (currentAnimation == AnimationIndex::WalkingNorthWest || currentAnimation == AnimationIndex::RunningNorthWest)
		{
			currentAnimation = AnimationIndex::IdleNorthWest;
		}
	}
	setDirection(direction);
}

void Player::Update(float deltaTime, Map& map)
{
	animations[int(currentAnimation)].Update(deltaTime);
	animations[int(currentAnimation)].ApplyToSprite(playerBody);
	if (map.isColliding(returnPlayer2DPosition(), returnPlayerBodySize(), velocity*deltaTime))
	{
		playerBody.move(velocity*deltaTime);
	}
}

void Player::setDirection(sf::Vector2f direction)
{
	velocity = direction * speed;
}

void Player::Draw(sf::RenderWindow& window)
{	
	window.draw(playerBody);
}

void Player::RestartClock()
{
	deltaTime = clock.restart().asSeconds();
}

void Player::StartingPosition(sf::RenderWindow& window)
{
	playerBody.setPosition({ 400, 400 });
}

void Player::setTextureWoman()
{	
	texture.loadFromFile("Animation/Woman/fullPlayerAnimations.png");
}

void Player::setTextureMan()
{
	texture.loadFromFile("Animation/Man/fullPlayerAnimations.png");
}

pair <float, float> Player::returnPlayer2DPosition()
{
	return{ playerBody.getPosition().x, playerBody.getPosition().y };
}

pair<float, float> Player::convert2DToIso(pair<float, float> pair)
{
	return{ pair.first - pair.second, (pair.first + pair.second) / 2 };
}

pair<float, float> Player::convertIsoTo2D(pair<float, float> pair)
{
	return{ (2 * pair.second + pair.first) / 2, (2 * pair.second - pair.first) / 2 };
}

sf::Vector2f Player::returnPlayerBodySize()
{
	return playerBody.getSize();
}

Player::~Player()
{
}