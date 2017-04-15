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
	position = sf::Mouse::getPosition(window);
	cameraCenter = playerView.getCenter();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		clock.restart().asSeconds();
		timeElapsed = clock.getElapsedTime();
		while (timeElapsed.asSeconds() <= 0.05)
		{
			timeElapsed = clock.getElapsedTime();
		}
	if (event.type == sf::Event::MouseMoved)
		{
		deltaPosition.x = (position.x - sf::Mouse::getPosition(window).x);
		deltaPosition.y = (position.y - sf::Mouse::getPosition(window).y) * 2;
			if (initialPosition) 
			{
				initialPosition = !initialPosition;
				centerCameraOnPlayer = false;
				playerView.setCenter(lastKnownPosition.first, lastKnownPosition.second);
			}
			playerView.setCenter(cameraCenter.x + deltaPosition.x, cameraCenter.y + deltaPosition.y);
		}
	}
	else
	{
		initialPosition = true;
		playerView.setCenter(lastKnownPosition.first, lastKnownPosition.second);
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
