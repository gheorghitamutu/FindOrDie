#include "Player.h"
#include "Map.h"

Player::Player()
{
	setTexture();
	Animation();

	playerBody.setSize(sf::Vector2f(25.f, 25.f));
	playerBody.setPosition({ 100, 100 });
	playerBody.setOrigin(playerBody.getSize() / 2.0f);
	playerBody.setTexture(&texture);
}

void Player::Update(sf::Event event, Map& map)
{
	movement.x = 0.0f;
	movement.y = 0.0f;

	shiftIncreaseSpeed = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))shiftIncreaseSpeed = 2;
	diagRunSpeed = speed*deltaTime*shiftIncreaseSpeed;
	normalRunSpeed = speed*deltaTime * shiftIncreaseSpeed;
	diagSpeed = speed*deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 16;
		movement.x -= diagRunSpeed;
		movement.y += diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 18;
		movement.x += diagRunSpeed;
		movement.y += diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 17;
		movement.x -= diagRunSpeed;
		movement.y -= diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 19;
		movement.x += diagRunSpeed;
		movement.y -= diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		row = 12;
		movement.x -= diagSpeed;
		movement.y += diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		row = 14;
		movement.x += diagSpeed;
		movement.y += diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		row = 13;
		movement.x -= diagSpeed;
		movement.y -= diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		row = 15;
		movement.x += diagSpeed;
		movement.y -= diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 4;
		movement.y += normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 5;
		movement.x -= normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 6;
		movement.x += normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 7;
		movement.y -= normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		row = 0;
		movement.y += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		row = 1;
		movement.x -= speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		row = 2;
		movement.x += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		row = 3;
		movement.y -= speed*deltaTime;
	}
	else { // idle animation
		if (row == 0 || row == 4)row = 8;
		else if (row == 1 || row == 5)row = 9;
		else if (row == 2 || row == 6)row = 10;
		else if (row == 3 || row == 7)row = 11;
		else if (row == 13 || row == 17)row = 21;
		else if (row == 12 || row == 16)row = 20;
		else if (row == 14 || row == 18)row = 22;
		else if (row == 15 || row == 19)row = 23;
	}

	int x = 0, y = 0;
	bool roadClear = true;
	for (auto& tile : map.tiles) {
		x++;
		if (x == map.mapSizes.first) {
			x = 0;
			y++;
		}	
		if (map.rectContainsPoint({ returnPlayer2DPosition().first + movement.x, returnPlayer2DPosition().second + movement.y },
		                       { tile.first.getPosition().x, tile.first.getPosition().y })) {
			if (!tile.second) {
				if (map.containsPoint({ returnPlayer2DPosition().first + movement.x, returnPlayer2DPosition().second + movement.y },
				{ tile.first.getPosition().x + SIZE / 2, tile.first.getPosition().y + SIZE / 2 })) {
					roadClear = false;
				}
			}
		}
	}

	if(roadClear)playerBody.move(movement);
	Update(row, deltaTime*shiftIncreaseSpeed);
	playerBody.setTextureRect(uvRect);
}

void Player::Draw(sf::RenderWindow& window, bool gamePause)
{	
	window.draw(playerBody);
}

void Player::RestartClock()
{
	deltaTime = clock.restart().asSeconds();
}

void Player::StartingPosition(bool newGame, sf::RenderWindow& window)
{
	if (newGame)playerBody.setPosition({ 100, 100 });
}

void Player::getTexture(bool woman)
{	
	if (woman)texture.loadFromFile("Animation/Woman/fullPlayerAnimations.png");
}

void Player::setTexture()
{
	texture.loadFromFile("Animation/Man/fullPlayerAnimations.png");
}

pair <float, float> Player::returnPlayer2DPosition()
{
	return{ playerBody.getPosition().x, playerBody.getPosition().y };
}

void Player::Animation()
{
	currentImage.x = 0;
	uvRect.width = texture.getSize().x / float(imageCount.x);
	uvRect.height = texture.getSize().y / float(imageCount.y);
	
}

void Player::Update(int row, float deltaTime)
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

pair<float, float> Player::convert2DToIso(pair<float, float> pair)
{
	return{ pair.first - pair.second, (pair.first + pair.second) / 2 };
}

pair<float, float> Player::convertIsoTo2D(pair<float, float> pair)
{
	return{ (2 * pair.second + pair.first) / 2, (2 * pair.second - pair.first) / 2 };
}



Player::~Player()
{
}