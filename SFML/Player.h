#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "CharacterSelectionMenu.h"
#include "math.h"
class Player
{
public:
	Player(sf::Texture* texture, sf::RenderWindow& window);
	~Player();
	void Update(sf::Event event);
	void Draw(sf::RenderWindow& window, bool gamePause);
	void RestartClock();
	void CameraY(sf::RenderWindow& window);
	void NormalCameraY(sf::RenderWindow& window);
private:
	sf::Texture texture;
	sf::RectangleShape body;
	sf::View camera;
	sf::Clock clock;
	sf::Vector2f movement;
	Animation animation;
	unsigned int row = 0;
	unsigned int shiftIncreaseSpeed;
	float speed = 100.0f; // movement speed
	float deltaTime = 0.0f;
	float diagRunSpeed;
	float normalRunSpeed;
	float diagSpeed;
};

