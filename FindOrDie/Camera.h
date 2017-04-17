#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
class Camera
{
public:
	Camera();
	~Camera();
	void setMenuView(sf::RenderWindow & window);
	void CameraPerspective(sf::RenderWindow& window, std::pair<float, float>);
	void centerOnPlayer(sf::RenderWindow& window, sf::Vector2f(playerPosition));
	float getAspectRatio(std::pair<unsigned int, unsigned int> dimensions);
	void draggableCamera(sf::RenderWindow& window, sf::Event event);
	void zoomPlayerView(sf::Event event);
	void centerCameraOnPlayerBool();
	void playerViewSetSize(std::pair<unsigned int, unsigned int> dimensions);
private: 
	sf::Vector2i position;
	sf::Vector2i deltaPosition;

	sf::Vector2f cameraCenter;
	std::pair<float, float> lastKnownPosition;

	sf::Clock clock;

	sf::Time timeElapsed;

	sf::View playerView, menuView;

	bool initialPosition = true;
	bool centerCameraOnPlayer = true;
};

