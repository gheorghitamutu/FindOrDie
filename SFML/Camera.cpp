#include "Camera.h"



Camera::Camera()
{
}



Camera::~Camera()
{
}

void Camera::CameraNormal(sf::RenderWindow& window)
{
	camera = window.getDefaultView();
	camera.setSize(camera.getSize().x, camera.getSize().y);
	camera.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setView(camera);
}


void Camera::CameraPerspective(sf::RenderWindow& window, sf::Vector2f offset)
{
	camera = window.getDefaultView();
	camera.setSize(camera.getSize().x, camera.getSize().y * 3);
	camera.setCenter(offset);
	camera.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setView(camera);
}
