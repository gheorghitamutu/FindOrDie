#include "Player.h"
#include "Map.h"
#include<math.h>
Player::Player()
{
	playerBody.setSize(sf::Vector2f(20.f, 20.f));
	playerBody.setPosition({ 300, 300 });
	playerBody.setOrigin(8, -6);
}

void Player::HandleEvents(sf::Event& event)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && !playerPath.empty())
	{
		playerPath.clear();
	}
	if (playerPath.empty())
	{
		sf::Vector2f direction = { 0.0f, 0.0f };

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			direction.x -= 2;
			direction.y += 2;
			////currentAnimation = AnimationIndex::RunningSouthWest;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			direction.x += 2;
			direction.y += 2;
			//currentAnimation = AnimationIndex::RunningSouthEast;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			direction.x -= 2;
			direction.y -= 2;
			//currentAnimation = AnimationIndex::RunningNorthWest;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			direction.x += 2;
			direction.y -= 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			direction.x -= 1;
			direction.y += 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			direction.x += 1;
			direction.y += 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			direction.x -= 1;
			direction.y -= 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			direction.x += 1;
			direction.y -= 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			direction.y += 2;
			//currentAnimation = AnimationIndex::RunningSouth;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			direction.x -= 2;
			//currentAnimation = AnimationIndex::RunningWest;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			direction.x += 2;
			//currentAnimation = AnimationIndex::RunningEast;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			direction.y -= 2;
			//currentAnimation = AnimationIndex::RunningNorth;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			direction.y += 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			direction.x -= 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			direction.x += 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			direction.y -= 1;
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
}

void Player::Update(Map& map)
{
	deltaTime = time.getElapsedTime().asSeconds();
	goThroughPath();
	decodeAnimationPath({ velocity.x,velocity.y });
	animations[int(currentAnimation)].Update(deltaTime);
	animations[int(currentAnimation)].ApplyToSprite(playerBody);

	/* (currentAnimation == AnimationIndex::IdleEast ||
		currentAnimation == AnimationIndex::IdleNorth ||
		currentAnimation == AnimationIndex::IdleSouth ||
		currentAnimation == AnimationIndex::IdleWest ||
		currentAnimation == AnimationIndex::IdleNorthEast ||
		currentAnimation == AnimationIndex::IdleNorthWest ||
		currentAnimation == AnimationIndex::IdleSouthEast ||
		currentAnimation == AnimationIndex::IdleSouthWest ||
		currentAnimation == AnimationIndex::WalkingSouth ||
		currentAnimation == AnimationIndex::WalkingSouthEast ||
		currentAnimation == AnimationIndex::WalkingSouth || 
		currentAnimation == AnimationIndex::RunningSouth || 
		currentAnimation == AnimationIndex::RunningSouthEast || 
		currentAnimation == AnimationIndex::RunningSouthWest)
		*/

	map.drawTilesOverPlayer(map.isCollidingDrawOver(returnPlayer2DPosition(), returnPlayerBodySize()));
	if (map.isColliding(returnPlayer2DPosition(), returnPlayerBodySize(), velocity*deltaTime))
	{
		playerBody.move(velocity*deltaTime);
	}
	time.restart().asSeconds();
}

void Player::setDirection(sf::Vector2f direction)
{
	velocity = direction * speed;
}

void Player::Draw(sf::RenderWindow& window)
{	
	window.draw(playerBody);
}

void Player::StartingPosition(sf::RenderWindow& window)
{
	playerBody.setPosition({ 300, 300 });
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
	pair<int, int> location = path.second.first;
	int tileNumber;
	if (path.first != "")
	{
		for (auto& elem : path.first)
		{
			location.second -= decodePath(elem).first;
			location.first -= decodePath(elem).second;
			tileNumber = location.first*mapDimensions.first + location.second;
			playerPath.emplace_front(location,  pair<float,float>(tiles[tileNumber].first.getPosition().x + 32, tiles[tileNumber].first.getPosition().y+32)); //double check this
			tilesToBeColored.emplace_back(tileNumber);
		}
	}
}

pair<int, int> Player::decodePath(const char character)
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
		currentAnimation = AnimationIndex::WalkingSouth;
	}
	if (direction.first > 0.0f && direction.second > 0.0f)
	{
		currentAnimation = AnimationIndex::WalkingSouthEast;
	}
	if (direction.first > 0.0f && direction.second == 0.0f)
	{
		currentAnimation = AnimationIndex::WalkingEast;
	}
	if (direction.first < 0.0f && direction.second > 0.0f)
	{
		currentAnimation = AnimationIndex::WalkingSouthWest;
	}
	if (direction.first < 0.0f && direction.second == 0.0f)
	{
		currentAnimation = AnimationIndex::WalkingWest;
	}
	if (direction.first < 0.0f && direction.second < 0.0f)
	{
		currentAnimation = AnimationIndex::WalkingNorthWest;
	}
	if (direction.first == 0.0f && direction.second < 0.0f)
	{
		currentAnimation = AnimationIndex::WalkingNorth;
	}
	if (direction.first > 0.0f && direction.second < 0.0f)
	{
		currentAnimation = AnimationIndex::WalkingNorthEast;
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
			pair<float, float> direction = decodeDirections();
			direction.first *= 3;
			direction.second *= 3;
			setDirection({ direction.first, direction.second });
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
	return tilesToBeColored;
}

Player::~Player()
{
}