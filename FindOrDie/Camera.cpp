#include "Camera.h"
#include <SFML\Graphics.hpp>
Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setMenuView(sf::RenderWindow& window)
{
	menuView = window.getDefaultView();
	window.setView(menuView);
}


void Camera::CameraPerspective(sf::RenderWindow& window, std::pair<float,float> offset)
{
	if (centerCameraOnPlayer)
	{
		playerView.setCenter(offset.first, offset.second);
		lastKnownPosition = offset;
	}
	else
	{
		if (initialPosition)
		{
			playerView.setCenter(lastKnownPosition.first, lastKnownPosition.second);
		}
		else
		{
			lastKnownPosition.first = playerView.getCenter().x;
			lastKnownPosition.second = playerView.getCenter().y;
		}
	}
	window.setView(playerView);
}

void Camera::centerOnPlayer(sf::RenderWindow& window, sf::Vector2f(playerPosition))
{
	playerView.setCenter(playerPosition);
	window.setView(playerView);
}

float Camera::getAspectRatio(std::pair<unsigned int, unsigned int> dimensions)
{
	return float(dimensions.first) / float(dimensions.second);
}

void Camera::draggableCamera(sf::RenderWindow & window, sf::Event event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !rightClickWasPressed)
	{
		position = sf::Mouse::getPosition(window);
		rightClickWasPressed = true;
		cameraCenter = playerView.getCenter();
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		rightClickWasPressed = false;
	}
	if (rightClickWasPressed)
	{
			deltaPosition.x = (position.x - sf::Mouse::getPosition(window).x);
			deltaPosition.y = (position.y - sf::Mouse::getPosition(window).y);
			if (initialPosition || centerCameraOnPlayer)
			{
				initialPosition = false;
				centerCameraOnPlayer = false;
			}
			playerView.setCenter(cameraCenter.x + deltaPosition.x, cameraCenter.y + deltaPosition.y);
	}
}

void Camera::zoomPlayerView(sf::Event event)
{
	playerView.zoom(1.f + event.mouseWheel.delta*0.1f);
}

void Camera::centerCameraOnPlayerBool()
{
	centerCameraOnPlayer = !centerCameraOnPlayer;
}

void Camera::playerViewSetSize(std::pair<unsigned int, unsigned int> dimensions)
{
	playerView.setSize(dimensions.second * getAspectRatio(dimensions), dimensions.second);
}
