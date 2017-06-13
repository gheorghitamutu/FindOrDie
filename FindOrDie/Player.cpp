#include "Player.h"
#include "Map.h"
#include<math.h>
Player::Player()
{
	playerBody.setSize(sf::Vector2f(20.f, 20.f));
	playerBody.setPosition({ 100, 100 });
	playerBody.setOrigin(8, -6);
}

void Player::HandleEvents()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && !playerPath.empty())
	{
		playerPath.clear();
	}
	if (playerPath.empty())
	{
		direction = { 0.0f, 0.0f };

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			direction.y += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			direction.x -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			direction.x += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			direction.y -= 1;
		}	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			direction.x *= 2;
			direction.y *= 2;
		}
		setVelocity();
	}
}

void Player::Update(Map& map)
{
	deltaTime = time.getElapsedTime().asSeconds();
	goThroughPath();
	decodeAnimationPath({ direction.x, direction.y });
	animations[int(currentAnimation)].Update(deltaTime);
	animations[int(currentAnimation)].ApplyToSprite(playerBody);

	map.drawTilesOverPlayer(map.isCollidingDrawOver(returnPlayerBodySize()));
	if (map.isColliding(returnPlayerBodySize(), velocity*deltaTime))
	{
		playerBody.move(velocity*deltaTime);
	}
	time.restart().asSeconds();
}

void Player::setVelocity()
{
	velocity = this->direction * speed;
}

void Player::Draw(sf::RenderWindow& window)
{	
	window.draw(playerBody);
}

void Player::StartingPosition(sf::RenderWindow& window)
{
	playerBody.setPosition({ 100,100 });
}

void Player::setTexture(string textureType)
{	
	texture.loadFromFile("Animation/" + textureType + "/fullPlayerAnimations.png");
	for (int i = 0; i<int(AnimationIndex::Count); i++)
	{
		animations[i] = Animation(characterTextureSize, i*characterTextureSize, characterTextureSize, characterTextureSize, texture);
	}
}

void Player::setPlayerPath(pair<string, pair<pair<int, int>, pair<int, int>>> path, vector <pair<sf::Sprite, bool>>& tiles, pair <int, int> mapDimensions)
{
	playerPath.clear();
	tilesToBeColored.clear();
	pair<int, int> location = path.second.first;
	int tileNumber;
	if (path.first != "")
	{
		for (auto& elem : path.first)
		{
			location.second -= decodePath(elem).first;
			location.first -= decodePath(elem).second;
			tileNumber = location.first*mapDimensions.first + location.second;
			playerPath.emplace_front(location,  pair<float,float>(tiles[tileNumber].first.getPosition().x + 32, tiles[tileNumber].first.getPosition().y + 32));
			tilesToBeColored.emplace_back(tileNumber);
		}
	}
}

pair<int, int> Player::decodePath(const char character)
{
	if (dir == 8)
	{
		if (character == '4')
		{
			return{ 0,1 };
		}
		if (character == '5')
		{
			return{ 1,1 };
		}
		if (character == '6')
		{
			return{ 1,0 };
		}
		if (character == '3')
		{
			return{ -1,1 };
		}
		if (character == '0')
		{
			return{ 0,-1 };
		}
		if (character == '1')
		{
			return{ -1,-1 };
		}
		if (character == '2')
		{
			return{ -1,0 };
		}
		if (character == '7')
		{
			return{ 1,-1 };
		}
	}
	else if (dir == 4)
	{
		if (character == '2')
		{
			return{ 0,1 };
		}
		if (character == '3')
		{
			return{ 1,0 };
		}
		if (character == '0')
		{
			return{ 0,-1 };
		}
		if (character == '1')
		{
			return{ -1,0 };
		}
	}
	return { 0,0 };
}

pair<float, float> Player::decodeDirections()
{
	if (!playerPath.empty())
	{
		pair<float, float> dVector = { playerPath.back().second.first - playerBody.getPosition().x, playerPath.back().second.second - playerBody.getPosition().y };
		float dVectorLength = sqrt(dVector.first*dVector.first + dVector.second*dVector.second);
		pair<float, float> dVectorNormalized = { dVector.first / dVectorLength ,dVector.second / dVectorLength };
		return dVectorNormalized;
	}
	else
	{
		return { 0,0 };
	}
}

void Player::decodeAnimationPath(pair<float, float> direction)
{
	if (direction.first == 0.0f && direction.second > 0.0f )
	{
		if (direction.second > walkingSpeed)
		{
			currentAnimation = AnimationIndex::RunningSouth;
		}
		else
		{
			currentAnimation = AnimationIndex::WalkingSouth;
		}
	}
	else if (direction.first > 0.0f && direction.second > 0.0f)
	{
		if (direction.first > walkingSpeed && direction.second > walkingSpeed)
		{
			currentAnimation = AnimationIndex::RunningSouthEast;
		}
		else
		{
			currentAnimation = AnimationIndex::WalkingSouthEast;
		}
	}
	else if (direction.first > 0.0f && direction.second == 0.0f)
	{
		if (direction.first > walkingSpeed)
		{
			currentAnimation = AnimationIndex::RunningEast;
		}
		else
		{
			currentAnimation = AnimationIndex::WalkingEast;
		}
	}
	else if (direction.first < 0.0f && direction.second > 0.0f)
	{
		if (direction.first < -walkingSpeed && direction.second > walkingSpeed)
		{
			currentAnimation = AnimationIndex::RunningSouthWest;
		}
		else
		{
			currentAnimation = AnimationIndex::WalkingSouthWest;
		}

	}
	else if (direction.first < 0.0f && direction.second == 0.0f)
	{
		if (direction.first < -walkingSpeed)
		{
			currentAnimation = AnimationIndex::RunningWest;
		}
		else
		{
			currentAnimation = AnimationIndex::WalkingWest;
		}
	}
	else if (direction.first < 0.0f && direction.second < 0.0f)
	{
		if (direction.first < -walkingSpeed && direction.second < -walkingSpeed)
		{
			currentAnimation = AnimationIndex::RunningNorthWest;
		}
		else
		{
			currentAnimation = AnimationIndex::WalkingNorthWest;
		}
	}
	else if (direction.first == 0.0f && direction.second < 0.0f)
	{
		if (direction.second < -walkingSpeed)
		{
			currentAnimation = AnimationIndex::RunningNorth;
		}
		else
		{
			currentAnimation = AnimationIndex::WalkingNorth;
		}
	}
	else if (direction.first > 0.0f && direction.second < 0.0f)
	{
		if (direction.first > walkingSpeed && direction.second < -walkingSpeed)
		{
			currentAnimation = AnimationIndex::RunningNorthEast;
		}
		else
		{
			currentAnimation = AnimationIndex::WalkingNorthEast;
		}
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
}

void Player::goThroughPath()
{
	if (!playerPath.empty())
	{
		if (abs(playerBody.getPosition().x - playerPath.back().second.first) < 10 &&
			abs(playerBody.getPosition().y - playerPath.back().second.second) < 10)
		{
			playerPath.pop_back();
		}
		else
		{
			direction = { decodeDirections().first*3, decodeDirections().second*3 };
			setVelocity();
		}
	}
	else
	{
		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)))
		{
			direction = { 0,0 };
			setVelocity();
		}
	}
}

pair <float, float> Player::returnPlayer2DPosition()
{
	return{ playerBody.getPosition().x, playerBody.getPosition().y };
}

sf::Vector2f Player::returnPlayerBodySize()
{
	return playerBody.getSize();
}

vector<int> Player::getTilesToBeColored()
{
	if (playerPath.empty())
	{
		return {};
	}
	return tilesToBeColored;
}

void Player::setEvent(sf::Event * event)
{
	this->playerEvent = event;
}

Player::~Player()
{
}