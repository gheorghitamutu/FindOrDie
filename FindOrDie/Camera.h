#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
class Camera
{
public:
	Camera();
	~Camera();
	void setMenuView();
	void setPlayerView();
	void CameraFollowPlayer(std::pair<float, float>& playerPosition);
	void setLastKnownPosition(std::pair<float, float>& position);
	float getAspectRatio(std::pair<unsigned int, unsigned int> dimensions);
	void draggableCamera();
	void zoomPlayerView();
	void centerOnPlayer(std::pair<float, float>& playerPosition);
	void playerViewSetSize(std::pair<unsigned int, unsigned int> dimensions);
	void playerViewSetCenter(std::pair<float, float> center);
	void setEvent(sf::Event* event);
	void setWindow(sf::RenderWindow* window);
	sf::FloatRect getPlayerViewBounds();

private: 
	sf::Vector2i position;
	sf::Vector2i deltaPosition;

	sf::Vector2f cameraCenter;
	std::pair<float, float> lastKnownPosition;

	sf::Clock clock;

	sf::Time timeElapsed;

	sf::View playerView, menuView;

	sf::Event* event;
	sf::RenderWindow* window;

	bool rightClickWasPressed = false;
	bool initialPosition = true;
	bool centerCameraOnPlayer = true;
	bool isPlayerView = false;
	bool isMenuView = false;
};

