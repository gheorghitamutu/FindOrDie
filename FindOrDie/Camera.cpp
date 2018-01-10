#include "Camera.h"
#include <SFML\Graphics.hpp>
Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setMenuView()
{
	if (!isMenuView)
	{
		menuView = window->getDefaultView();
		window->setView(menuView);
		isPlayerView = false;
		isMenuView = true;
	}
}

void Camera::setPlayerView()
{
	if (!isPlayerView)
	{
		window->setView(playerView);
		isPlayerView = true;
		isMenuView = false;
	}
}


void Camera::CameraFollowPlayer(std::pair<float,float>& playerPosition)
{
	if (centerCameraOnPlayer && lastKnownPosition != playerPosition )
	{
		playerView.move(-(lastKnownPosition.first - playerPosition.first), -(lastKnownPosition.second - playerPosition.second));
		lastKnownPosition = playerPosition;
		window->setView(playerView);
	}
	else
	{
		if (initialPosition)
		{
			playerView.setCenter(lastKnownPosition.first, lastKnownPosition.second);
			window->setView(playerView);
			initialPosition = false;
		}
	}
}

void Camera::setLastKnownPosition(std::pair<float, float>& position)
{
	lastKnownPosition = position;
}

float Camera::getAspectRatio(std::pair<unsigned int, unsigned int> dimensions)
{
	return float(dimensions.first) / float(dimensions.second);
}

void Camera::draggableCamera()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !rightClickWasPressed)
	{
		position = sf::Mouse::getPosition(*window);
		rightClickWasPressed = true;
		cameraCenter = playerView.getCenter();
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		rightClickWasPressed = false;
	}
	if (rightClickWasPressed)
	{
			deltaPosition.x = (position.x - sf::Mouse::getPosition(*window).x);
			deltaPosition.y = (position.y - sf::Mouse::getPosition(*window).y);
			if (initialPosition || centerCameraOnPlayer)
			{
				initialPosition = false;
				centerCameraOnPlayer = false;
			}
			playerView.setCenter(cameraCenter.x + deltaPosition.x, cameraCenter.y + deltaPosition.y);
			window->setView(playerView);
	}
}

void Camera::zoomPlayerView()
{
	
	if (this->event->type==sf::Event::MouseWheelMoved)
	{
		playerView.zoom(1.f + event->mouseWheel.delta*0.1f);
		window->setView(playerView);
	}
}

void Camera::centerOnPlayer(std::pair<float, float>& playerPosition)
{
	if (centerCameraOnPlayer) {
		centerCameraOnPlayer = false;
	}
	else
	{
		centerCameraOnPlayer = true;
		playerView.setCenter({ playerPosition.first, playerPosition.second });
		window->setView(playerView);
	}
}

void Camera::playerViewSetSize(std::pair<unsigned int, unsigned int> dimensions)
{
	playerView.setSize((float)dimensions.second * getAspectRatio(dimensions), (float)dimensions.second);
}

void Camera::playerViewSetCenter(std::pair<float, float> center)
{
	 playerView.setCenter({ center.first, center.second }); 
}

void Camera::setEvent(sf::Event * event)
{
	this->event = event;
}

void Camera::setWindow(sf::RenderWindow * window)
{
	this->window = window;
}

sf::FloatRect Camera::getPlayerViewBounds()
{
		sf::FloatRect rt;
		rt.left = playerView.getCenter().x - playerView.getSize().x / 2.f;
		rt.top = playerView.getCenter().y - playerView.getSize().y / 2.f;
		rt.width = playerView.getSize().x;
		rt.height = playerView.getSize().y;
		return rt;
}
