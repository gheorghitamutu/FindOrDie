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


void Camera::CameraFollowPlayer(sf::RenderWindow& window, std::pair<float,float>& playerPosition)
{
	if (centerCameraOnPlayer && lastKnownPosition != playerPosition )
	{
		playerView.move(-(lastKnownPosition.first - playerPosition.first), -(lastKnownPosition.second - playerPosition.second));
		lastKnownPosition = playerPosition;
		window.setView(playerView);
	}
	else
	{
		if (initialPosition)
		{
			playerView.setCenter(lastKnownPosition.first, lastKnownPosition.second);
			initialPosition = false;
		}
	}
}

void Camera::centerOnPlayer(sf::RenderWindow& window, sf::Vector2f& playerPosition)
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
			window.setView(playerView);
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
