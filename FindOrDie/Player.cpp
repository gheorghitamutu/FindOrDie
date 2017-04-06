#include "Player.h"
#include "Map.h"

Player::Player()
{
	setTextureMan();
	Animation();
	playerBody.setSize(sf::Vector2f(25.f, 25.f));
	playerBody.setPosition({ 300, 300 });
	playerBody.setTexture(&texture);
}

void Player::Update(sf::Event event, Map& map)
{
	velocity.x = 0.0f;
	velocity.y = 0.0f;

	shiftIncreaseSpeed = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))shiftIncreaseSpeed = 2;
	diagRunSpeed = speed*deltaTime*shiftIncreaseSpeed;
	normalRunSpeed = speed*deltaTime * shiftIncreaseSpeed;
	diagSpeed = speed*deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 16;
		velocity.x -= diagRunSpeed;
		velocity.y += diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 18;
		velocity.x += diagRunSpeed;
		velocity.y += diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 17;
		velocity.x -= diagRunSpeed;
		velocity.y -= diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 19;
		velocity.x += diagRunSpeed;
		velocity.y -= diagRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		row = 12;
		velocity.x -= diagSpeed;
		velocity.y += diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		row = 14;
		velocity.x += diagSpeed;
		velocity.y += diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		row = 13;
		velocity.x -= diagSpeed;
		velocity.y -= diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		row = 15;
		velocity.x += diagSpeed;
		velocity.y -= diagSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 4;
		velocity.y += normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 5;
		velocity.x -= normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 6;
		velocity.x += normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 7;
		velocity.y -= normalRunSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		row = 0;
		velocity.y += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		row = 1;
		velocity.x -= speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		row = 2;
		velocity.x += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		row = 3;
		velocity.y -= speed*deltaTime;
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

	if (map.isColliding(returnPlayer2DPosition(), returnPlayerBodySize(), velocity))playerBody.move(velocity);
	Update(row, deltaTime*shiftIncreaseSpeed);
	playerBody.setTextureRect(uvRect);
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
	playerBody.setPosition({ 100, 100 });
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

sf::Vector2f Player::returnPlayerBodySize()
{
	return playerBody.getSize();
}



Player::~Player()
{
}