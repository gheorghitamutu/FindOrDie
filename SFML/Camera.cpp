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


void Camera::CameraPerspective(sf::RenderWindow& window, sf::Vector2f offset, sf::View camera, bool &centerCameraOnPlayer)
{
	//	*camera = window.getDefaultView();  this crap keeps resetting the camera
	camera.setSize(camera.getSize().x * aspectRatio, camera.getSize().y * 2);
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
			
		//	std::cout << window.getSize().x << " " << window.getSize().x << std::endl;
		//	std::cout <<sf::Mouse::getPosition(window).x << " " <<sf::Mouse::getPosition(window).y << std::endl;
			// left click...
			// get global mouse position
			//clock.restart().asSeconds();
			//timeElapsed = clock.getElapsedTime();
			//while (timeElapsed.asSeconds() <= 0.1) {
			//	//std::cout << timeElapsed.asSeconds() << std::endl;
			//	timeElapsed = clock.getElapsedTime();
			//}
			//std::cout << "AICI" << std::endl;

		/*	std::cout << position.x << " " << position.y << std::endl;*/

		//	std::cout << position.x - sf::Mouse::getPosition(window).x << " " << position.y - sf::Mouse::getPosition(window).y << std::endl;
		
		deltaPosition.x = (position.x - sf::Mouse::getPosition(window).x);// *8;
		deltaPosition.y = (position.y - sf::Mouse::getPosition(window).y)*2;// *8 * 2;
		//		std::cout << position.x << " " << sf::Mouse::getPosition(window).x << std::endl;


			if (initialPosition) {

				initialPosition = !initialPosition;
				centerCameraOnPlayer = false;
				camera.setCenter(lastKnownPosition.x, lastKnownPosition.y);
			}
			//	else if (x != 0 && y != 0) {
		//	if (position.x != sf::Mouse::getPosition(window).x&&position.y != sf::Mouse::getPosition(window).y)camera.setCenter(camera.getCenter().x + x, camera.getCenter().y + y);
			//	if(position.x!= sf::Mouse::getPosition(window).x&&position.y != sf::Mouse::getPosition(window).y)camera.setCenter(camera.getCenter().x + sf::Mouse::getPosition(window).x, camera.getCenter().x + sf::Mouse::getPosition(window).y);
			//	camera.setCenter(camera.getCenter().x+sf::Mouse::getPosition(window).x, camera.getCenter().y+sf::Mouse::getPosition(window).y);
				//window.setView(camera);
	//		if (x <  position.x/2)camera.move((camera.getCenter().x + x)*0.1, 0);
		//	if (y <  position.y/2)camera.move(0, (camera.getCenter().y + y)*0.1);
		//	if (x >  position.x/2)camera.move((camera.getCenter().x - x)*0.1, 0);
			/*if (y > position.y / 2) {
				camera.setCenter(0, (camera.getCenter().y - y));
				position.y -= y;
			}*/
			camera.setCenter(cameraCenter.x + deltaPosition.x, cameraCenter.y + deltaPosition.y);
			//}


		/*if (x == 0)camera.move(0, 0);
		if (y == 0)camera.move(0, 0);*/


		//	std::cout << camera.getCenter().x << " " << camera.getCenter().y<<std::endl;
			//window.setView(camera);
		}


	}
	else {
		initialPosition = true;
		camera.setCenter(lastKnownPosition.x, lastKnownPosition.y);
		window.setMouseCursorVisible(true);
	}
//	initialPosition = true;

}
