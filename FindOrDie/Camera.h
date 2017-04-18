#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
class Camera
{
public:
	Camera();
	~Camera();
	void setMenuView(sf::RenderWindow & window);
	void CameraFollowPlayer(sf::RenderWindow& window, std::pair<float, float>& playerPosition);
	void setLastKnownPosition(std::pair<float, float>& position);
	float getAspectRatio(std::pair<unsigned int, unsigned int> dimensions);
	void draggableCamera(sf::RenderWindow& window, sf::Event event);
	void zoomPlayerView(sf::RenderWindow& window, sf::Event event);
	void centerOnPlayer(sf::RenderWindow& window, std::pair<float, float>& playerPosition);
	void playerViewSetSize(std::pair<unsigned int, unsigned int> dimensions);
	void playerViewSetCenter(std::pair<float, float> center);
	sf::FloatRect getPlayerViewBounds();

private: 
	sf::Vector2i position;
	sf::Vector2i deltaPosition;

	sf::Vector2f cameraCenter;
	std::pair<float, float> lastKnownPosition;

	sf::Clock clock;

	sf::Time timeElapsed;

	sf::View playerView, menuView;

	bool rightClickWasPressed = false;
	bool initialPosition = true;
	bool centerCameraOnPlayer = true;
};

