#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

class Camera
{
public:
	Camera();
	~Camera();
	void SetMenuView();
	void SetPlayerView();
	void CameraFollowPlayer(std::pair<float, float> &player_position);
	void SetLastKnownPosition(std::pair<float, float> &position);
	float GetAspectRatio(std::pair<unsigned int, unsigned int> dimensions);
	void DraggableCamera();
	void ZoomPlayerView();
	void CenterOnPlayer(std::pair<float, float>& player_position);
	void PlayerViewSetSize(std::pair<unsigned int, unsigned int> dimensions);
	void PlayerViewSetCenter(std::pair<float, float> center);
	void SetEvent(sf::Event* event);
	void SetWindow(sf::RenderWindow* window);
	sf::FloatRect GetPlayerViewBounds();

private: 
	sf::Vector2i position;
	sf::Vector2i delta_position;

	sf::Vector2f camera_center;
	std::pair<float, float> last_known_position;

	sf::Clock clock;

	sf::Time time_elapsed;

	sf::View player_view, menu_view;

	sf::Event* event;
	sf::RenderWindow* window;

	bool right_click_pressed = false;
	bool initial_position = true;
	bool center_camera_on_player = true;
	bool is_player_view = false;
	bool is_menu_view = false;
};

