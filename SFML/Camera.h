#pragma once
#include <SFML/Graphics.hpp>
class Camera
{
public:
	Camera();
	~Camera();
	void CameraNormal(sf::RenderWindow & window);
	void CameraPerspective(sf::RenderWindow& window, sf::Vector2f offset, sf::View camera, bool &centerCameraOnPlayer);
	void centerOnPlayer(sf::RenderWindow& window, sf::Vector2f(playerPosition));
	void getAspectRatio(sf::RenderWindow& window);
	void draggableCamera(sf::RenderWindow& window, sf::Event event, bool& centerCameraOnPlayer, sf::View &camera);
private: 
	sf::Vector2i position;
	sf::Vector2i deltaPosition;

	sf::Vector2f cameraCenter;
	sf::Vector2f lastKnownPosition;

	sf::Clock clock;

	sf::Time timeElapsed;

	sf::View camera;

	bool initialPosition = true; //camera
	
	float aspectRatio = 1.0f;
	
};

