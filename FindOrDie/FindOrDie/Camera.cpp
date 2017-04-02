#include "Camera.h"
#include <SFML\Graphics.hpp>
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


void Camera::CameraPerspective(sf::RenderWindow& window, sf::Vector2f offset, sf::View camera, bool &centerCameraOnPlayer)
{
	//	*camera = window.getDefaultView();  this crap keeps resetting the camera
//	camera.setSize(camera.getSize().x * aspectRatio, camera.getSize().y*2 );
	if (centerCameraOnPlayer) {
		camera.setCenter(offset);
		lastKnownPosition = offset;
	}
	else {
		if (initialPosition) camera.setCenter(lastKnownPosition);
		else {
			lastKnownPosition = camera.getCenter();
		}
	}
	camera.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setView(camera);
}

void Camera::centerOnPlayer(sf::RenderWindow& window, sf::Vector2f(playerPosition))
{
	camera.setCenter(playerPosition);
	window.setView(camera);
}

void Camera::getAspectRatio(sf::RenderWindow & window)
{
	aspectRatio = float(window.getSize().x) / float(window.getSize().y);
}

void Camera::draggableCamera(sf::RenderWindow & window, sf::Event event, bool& centerCameraOnPlayer, sf::View &camera)
{
	position = sf::Mouse::getPosition(window);
	cameraCenter = camera.getCenter();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		window.setMouseCursorVisible(false);
		clock.restart().asSeconds(); // Mos Craciun si prietenii sai
		timeElapsed = clock.getElapsedTime();
		while (timeElapsed.asSeconds() <= 0.05) {
			//std::cout << timeElapsed.asSeconds() << std::endl;
			timeElapsed = clock.getElapsedTime();
		}
	if (event.type == sf::Event::MouseMoved)
		{
		deltaPosition.x = (position.x - sf::Mouse::getPosition(window).x);// *8;
		deltaPosition.y = (position.y - sf::Mouse::getPosition(window).y)*2;// *8 * 2;
		//		std::cout << position.x << " " << sf::Mouse::getPosition(window).x << std::endl;
			if (initialPosition) {

				initialPosition = !initialPosition;
				centerCameraOnPlayer = false;
				camera.setCenter(lastKnownPosition.x, lastKnownPosition.y);
			}
			camera.setCenter(cameraCenter.x + deltaPosition.x, cameraCenter.y + deltaPosition.y);
		}
	}
	else {
		initialPosition = true;
		camera.setCenter(lastKnownPosition.x, lastKnownPosition.y);
		window.setMouseCursorVisible(true);
	}
}
