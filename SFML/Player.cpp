#include "Player.h"

Player::Player(sf::Texture* texture, sf::RenderWindow& window):
	animation(texture)
{

	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setPosition(window.getSize().x / 2.0f, window.getSize().y / 1.0f);
	body.setTexture(texture);
}


Player::~Player()
{
}

void Player::Update(sf::Event event)
{
	movement.x = 0.0f;
	movement.y = 0.0f;
	shiftIncreaseSpeed = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))shiftIncreaseSpeed = 3;
	diagRunSpeed = sqrt(speed*deltaTime*shiftIncreaseSpeed + speed*deltaTime*shiftIncreaseSpeed);
	normalRunSpeed = speed*deltaTime * shiftIncreaseSpeed;
	diagSpeed = sqrt(speed*deltaTime + speed*deltaTime);

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
		/*switch (event.type) {
		case sf::Event::KeyReleased:
			switch (event.key.code) {
			case sf::Keyboard::Space:
				body.setPosition(body.getPosition().x - 10, body.getPosition().y);
				break;
			}
		}*/
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
	camera = window.getDefaultView();
	camera.setSize(camera.getSize().x, camera.getSize().y * 3);
	camera.setCenter(body.getPosition());
	camera.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setView(camera);
	window.draw(body);
}

void Player::RestartClock()
{
	deltaTime = clock.restart().asSeconds();
}
