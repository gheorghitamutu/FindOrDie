#include "Player.h"

Player::Player(sf::Texture* texture):
	animation(texture)
{
	texture->setSmooth(true);
	body.setSize(sf::Vector2f(50.0f, 50.0f));
	body.setPosition(1920 / 2.0f, 1080 / 2.0f);
	body.setTexture(texture);
}


Player::~Player()
{
}

void Player::Update()
{
	sf::Vector2f movement(0.0f, 0.0f);
	unsigned int shiftIncreaseSpeed = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))shiftIncreaseSpeed = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 16;
		movement.x -= speed*deltaTime*shiftIncreaseSpeed;
		movement.y += speed*deltaTime*shiftIncreaseSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 18;
		movement.x += speed*deltaTime * shiftIncreaseSpeed;
		movement.y += speed*deltaTime * shiftIncreaseSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 17;
		movement.x -= speed*deltaTime * shiftIncreaseSpeed;
		movement.y -= speed*deltaTime * shiftIncreaseSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 19;
		movement.x += speed*deltaTime * shiftIncreaseSpeed;
		movement.y -= speed*deltaTime * shiftIncreaseSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		row = 12;
		movement.x -= speed*deltaTime;
		movement.y += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		row = 14;
		movement.x += speed*deltaTime;
		movement.y += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		row = 13;
		movement.x -= speed*deltaTime;
		movement.y -= speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		row = 15;
		movement.x += speed*deltaTime;
		movement.y -= speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 4;
		movement.y += speed*deltaTime * shiftIncreaseSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 5;
		movement.x -= speed*deltaTime * shiftIncreaseSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 6;
		movement.x += speed*deltaTime * shiftIncreaseSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		row = 7;
		movement.y -= speed*deltaTime * shiftIncreaseSpeed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		row = 0;
		movement.y += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		row = 1;
		movement.x -= speed*deltaTime;
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) { 
	//		body.setPosition(body.getPosition().x - 10, body.getPosition().y);
	//	}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		row = 2;
		movement.x += speed*deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		row = 3;
		movement.y -= speed*deltaTime;
	}
	else {
		if (row == 0 || row == 4)row = 8;
		else if (row == 1 || row == 5)row = 9;
		else if (row == 2 || row == 6)row = 10;
		else if (row == 3 || row == 7)row = 11;
		else if (row == 13 || row == 17)row = 21;
		else if (row == 12 || row == 16)row = 20;
		else if (row == 14 || row == 18)row = 22;
		else if (row == 15 || row == 19)row = 23;
	}
	animation.Update(row, deltaTime*shiftIncreaseSpeed);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::RestartClock()
{
	deltaTime = clock.restart().asSeconds();
}
