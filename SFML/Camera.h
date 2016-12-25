#pragma once
#include <SFML/Graphics.hpp>
class Camera
{
public:
	Camera();
	~Camera();
	void CameraNormal(sf::RenderWindow & window);
	void CameraPerspective(sf::RenderWindow& window, sf::Vector2f offset);
	sf::View camera;
private: 
};

