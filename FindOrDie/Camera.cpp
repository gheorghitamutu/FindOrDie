#include "Camera.h"
#include <SFML\Graphics.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::SetMenuView()
{
	if (!this->is_menu_view)
	{
		this->menu_view = this->window->getDefaultView();
		this->window->setView(this->menu_view);
		this->is_player_view = false;
		this->is_menu_view = true;
	}
}

void Camera::setPlayerView()
{
	if (!this->is_player_view)
	{
		this->window->setView(this->player_view);
		this->is_player_view = true;
		this->is_menu_view = false;
	}
}


void Camera::CameraFollowPlayer(std::pair<float,float>& player_position)
{
	if (this->center_camera_on_player && this->last_known_position != player_position )
	{
		this->player_view.move(-(this->last_known_position.first - player_position.first), -(this->last_known_position.second - player_position.second));
		this->last_known_position = player_position;
		this->window->setView(this->player_view);
	}
	else
	{
		if (this->initial_position)
		{
			this->player_view.setCenter(last_known_position.first, last_known_position.second);
			this->window->setView(player_view);
			this->initial_position = false;
		}
	}
}

void Camera::SetLastKnownPosition(std::pair<float, float>& position)
{
	this->last_known_position = position;
}

float Camera::GetAspectRatio(std::pair<unsigned int, unsigned int> dimensions)
{
	return float(dimensions.first) / float(dimensions.second);
}

void Camera::DraggableCamera()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !this->right_click_pressed)
	{
		this->position = sf::Mouse::getPosition(*this->window);
		this->right_click_pressed = true;
		this->camera_center = this->player_view.getCenter();
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->right_click_pressed = false;
	}
	if (this->right_click_pressed)
	{
			this->delta_position.x = (this->position.x - sf::Mouse::getPosition(*this->window).x);
			this->delta_position.y = (this->position.y - sf::Mouse::getPosition(*this->window).y);
			if (this->initial_position || this->center_camera_on_player)
			{
				this->initial_position = false;
				this->center_camera_on_player = false;
			}
			this->player_view.setCenter(this->camera_center.x + this->delta_position.x, this->camera_center.y + this->delta_position.y);
			this->window->setView(this->player_view);
	}
}

void Camera::ZoomPlayerView()
{
	
	if (this->event->type == sf::Event::MouseWheelMoved)
	{
		this->player_view.zoom(1.f + event->mouseWheel.delta*0.1f);
		this->window->setView(player_view);
	}
}

void Camera::CenterOnPlayer(std::pair<float, float>& player_position)
{
	if (this->center_camera_on_player) {
		this->center_camera_on_player = false;
	}
	else
	{
		this->center_camera_on_player = true;
		this->player_view.setCenter({ player_position.first, player_position.second });
		this->window->setView(player_view);
	}
}

void Camera::PlayerViewSetSize(std::pair<unsigned int, unsigned int> dimensions)
{
	this->player_view.setSize((float)dimensions.second * GetAspectRatio(dimensions), (float)dimensions.second);
}

void Camera::PlayerViewSetCenter(std::pair<float, float> center)
{
	 this->player_view.setCenter({ center.first, center.second }); 
}

void Camera::SetEvent(sf::Event * event)
{
	this->event = event;
}

void Camera::SetWindow(sf::RenderWindow * window)
{
	this->window = window;
}

sf::FloatRect Camera::GetPlayerViewBounds()
{
		sf::FloatRect rt;
		rt.left = this->player_view.getCenter().x - this->player_view.getSize().x / 2.f;
		rt.top = this->player_view.getCenter().y - this->player_view.getSize().y / 2.f;
		rt.width = this->player_view.getSize().x;
		rt.height = this->player_view.getSize().y;
		return rt;
}
