#include "Map.h"
#include "Player.h"

Map::Map()
{
	this->tile_texture = new sf::Texture;
	this->tile_texture->loadFromFile("iso-64x64-building.png");
	this->tile.first.setTexture(*(this->tile_texture));
	this->extreme = { 10000, 0 };
}

Map::~Map()
{
	if (this->tile_texture == nullptr)
	{
		delete this->tile_texture;
	}
}

void Map::DrawMap(sf::RenderWindow& window)
{
	for (auto tile : this->draw_these)
	{
			window.draw(*tile);
	}
}

void Map::DrawTilesOverPlayer(bool is_colliding)
{
	if (is_colliding)
	{
		for (auto &elem : this->draw_tile_over_player)
		{
			this->non_walkable_tiles[elem].first.setColor(sf::Color(255, 255, 255, 160));
		}
	}
	else
	{
		for (auto& elem : this->last_known_tiles_over_player)
		{
			this->non_walkable_tiles[elem].first.setColor(sf::Color(255, 255, 255, 255));
		}
		this->draw_tile_over_player.clear();
		this->last_known_tiles_over_player.clear();
	}
	
}

pair<float, float> Map::Convert2DToIso(pair<float, float> pair)
{
	return { pair.first - pair.second, (pair.first + pair.second) / 2 };
}

pair<float, float> Map::ConvertIsoTo2D(pair<float, float> pair)
{
	return { (2 * pair.second + pair.first) / 2, (2 * pair.second - pair.first) / 2 };
}

bool Map::IsWalkable(pair<int, int> pair)
{
	if (pair.first == 0 && pair.second == 0) return false;
	if (pair.first == 0 && pair.second == 3) return true;
	return true;
}

pair<float, float> Map::GetTileCenterFromTileCoordinate(pair<float, float> pair)
{
	return { pair.first*tile_size + tile_size / 2, pair.second*this->tile_size + this->tile_size / 2 };
}

bool Map::ContainsPoint(pair<float, float> point, pair<vector<pair<float, float>>, int> non_walkable_area_coords)
{
	vector<pair<float, float>>polygon;
	for(auto &object : non_walkable_area_coords.first)
	{
		polygon.emplace_back(object);
	}
	return IsInside(polygon, (int)polygon.size(), { point.first, point.second });
}

bool Map::IsColliding(sf::Vector2f body_size, sf::Vector2f velocity)
{
	this->tile_number_where_player_is = GetTileNumberWherePlayerIs(body_size);
	if (this->tile_number_where_player_is != this->last_known_tile_number_where_player_is)
	{
		this->non_walkable_objects.clear();
		if (this->tile_number_where_player_is - this->map_dimensions.first - 1 >= 0 && !this->tiles[this->tile_number_where_player_is - this->map_dimensions.first - 1].second)
		{
			this->non_walkable_objects.emplace_back(this->floor_level_tiles_coords[this->tile_number_where_player_is - this->map_dimensions.first - 1]);
		}
		if (this->tile_number_where_player_is - this->map_dimensions.first >= 0 && !this->tiles[this->tile_number_where_player_is - this->map_dimensions.first].second)
		{
			this->non_walkable_objects.emplace_back(this->floor_level_tiles_coords[this->tile_number_where_player_is - this->map_dimensions.first]);
		}
		if (this->tile_number_where_player_is - this->map_dimensions.first + 1 >= 0 && !this->tiles[this->tile_number_where_player_is - this->map_dimensions.first + 1].second)
		{
			this->non_walkable_objects.emplace_back(this->floor_level_tiles_coords[this->tile_number_where_player_is - this->map_dimensions.first + 1]);
		}
		if (this->tile_number_where_player_is - 1 >= 0 && !this->tiles[this->tile_number_where_player_is - 1].second)
		{
			this->non_walkable_objects.emplace_back(this->floor_level_tiles_coords[this->tile_number_where_player_is - 1]);
		}
		if (this->tile_number_where_player_is + 1 < this->number_of_tiles && !this->tiles[this->tile_number_where_player_is + 1].second)
		{
			this->non_walkable_objects.emplace_back(this->floor_level_tiles_coords[this->tile_number_where_player_is + 1]);
		}
		if (this->tile_number_where_player_is + this->map_dimensions.first - 1 < this->number_of_tiles && !this->tiles[this->tile_number_where_player_is + this->map_dimensions.first - 1].second)
		{
			this->non_walkable_objects.emplace_back(this->floor_level_tiles_coords[this->tile_number_where_player_is + this->map_dimensions.first - 1]);
		}
		if (this->tile_number_where_player_is + this->map_dimensions.first < this->number_of_tiles && !this->tiles[this->tile_number_where_player_is + this->map_dimensions.first].second)
		{
			this->non_walkable_objects.emplace_back(this->floor_level_tiles_coords[this->tile_number_where_player_is + this->map_dimensions.first]);
		}
		if (this->tile_number_where_player_is + this->map_dimensions.first + 1 < this->map_dimensions.first*this->map_dimensions.second && !this->tiles[this->tile_number_where_player_is + this->map_dimensions.first + 1].second)
		{
			this->non_walkable_objects.emplace_back(this->floor_level_tiles_coords[this->tile_number_where_player_is + this->map_dimensions.first + 1]);
		}
		this->last_known_tile_number_where_player_is = this->tile_number_where_player_is;
	}
	for (auto& object : this->non_walkable_objects)
	{
		if (ContainsPoint({ this->player_position.first + velocity.x, this->player_position.second + velocity.y + body_size.y }, object ))
		{
			return false;
		}
	}
	return true;
}

bool Map::IsCollidingDrawOver(sf::Vector2f body_size)
{
		this->draw_tile_over_player.clear();
		if (this->tile_number_where_player_is - this->map_dimensions.first - 1 >= 0 &&
			ContainsPoint({ this->player_position.first, this->player_position.second + body_size.y }, this->can_draw_over_player_objects[this->tile_number_where_player_is - this->map_dimensions.first - 1]) &&
			!this->tiles[this->tile_number_where_player_is - this->map_dimensions.first - 1].second)
		{
			this->draw_tile_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is - this->map_dimensions.first - 1].second);
			this->last_known_tiles_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is - this->map_dimensions.first - 1].second);
		}
		if (this->tile_number_where_player_is - this->map_dimensions.first >= 0 &&
			!this->tiles[this->tile_number_where_player_is - this->map_dimensions.first].second &&
			ContainsPoint({ this->player_position.first, this->player_position.second + body_size.y }, this->can_draw_over_player_objects[this->tile_number_where_player_is - this->map_dimensions.first]))
		{
			this->draw_tile_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is - this->map_dimensions.first].second);
			this->last_known_tiles_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is - this->map_dimensions.first].second);
		}
		if (this->tile_number_where_player_is - this->map_dimensions.first + 1 >= 0 &&
			!this->tiles[this->tile_number_where_player_is - this->map_dimensions.first + 1].second &&
			ContainsPoint({ this->player_position.first, this->player_position.second + body_size.y }, this->can_draw_over_player_objects[this->tile_number_where_player_is - this->map_dimensions.first + 1]))
		{
			this->draw_tile_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is - this->map_dimensions.first + 1].second);
			this->last_known_tiles_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is - this->map_dimensions.first + 1].second);
		}
		if (this->tile_number_where_player_is - 1 >= 0 &&
			!this->tiles[this->tile_number_where_player_is - 1].second &&
			ContainsPoint({ this->player_position.first, this->player_position.second + body_size.y }, this->can_draw_over_player_objects[this->tile_number_where_player_is - 1]))
		{
			this->draw_tile_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is - 1].second);
			this->last_known_tiles_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is - 1].second);
		}
		if (this->tile_number_where_player_is + 1 < this->number_of_tiles &&
			!this->tiles[this->tile_number_where_player_is + 1].second &&
			ContainsPoint({ this->player_position.first, this->player_position.second + body_size.y }, this->can_draw_over_player_objects[this->tile_number_where_player_is + 1]))
		{
			this->draw_tile_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is + 1].second);
			this->last_known_tiles_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is + 1].second);
		}
		if (this->tile_number_where_player_is + this->map_dimensions.first - 1 < this->number_of_tiles &&
			!this->tiles[this->tile_number_where_player_is + this->map_dimensions.first - 1].second &&
			ContainsPoint({ this->player_position.first, this->player_position.second + body_size.y }, this->can_draw_over_player_objects[this->tile_number_where_player_is + this->map_dimensions.first - 1]))
		{
			this->draw_tile_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is + this->map_dimensions.first - 1].second);
			this->last_known_tiles_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is + this->map_dimensions.first - 1].second);
		}
		if (this->tile_number_where_player_is + this->map_dimensions.first < this->number_of_tiles &&
			!this->tiles[this->tile_number_where_player_is + this->map_dimensions.first].second &&
			ContainsPoint({ this->player_position.first, this->player_position.second + body_size.y }, this->can_draw_over_player_objects[this->tile_number_where_player_is + this->map_dimensions.first]))
		{
			this->draw_tile_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is + this->map_dimensions.first].second);
			this->last_known_tiles_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is + this->map_dimensions.first].second);
		}
		if (this->tile_number_where_player_is + this->map_dimensions.first + 1 < this->number_of_tiles &&
			!this->tiles[this->tile_number_where_player_is + this->map_dimensions.first + 1].second &&
			ContainsPoint({ this->player_position.first, this->player_position.second + body_size.y }, this->can_draw_over_player_objects[this->tile_number_where_player_is + this->map_dimensions.first + 1]))
		{
			this->draw_tile_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is + this->map_dimensions.first + 1].second);
			this->last_known_tiles_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is + this->map_dimensions.first + 1].second);
		}
		if (!this->tiles[this->tile_number_where_player_is].second &&
			ContainsPoint({ this->player_position.first, this->player_position.second + body_size.y }, this->can_draw_over_player_objects[this->tile_number_where_player_is]))
		{
			this->draw_tile_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is].second);
			this->last_known_tiles_over_player.emplace_back(this->can_draw_over_player_objects[this->tile_number_where_player_is].second);
		}

		if (!(this->draw_tile_over_player.size() == 0))
		{
			return true;
		}
		return false;
}

void Map::CreateMap()
{
	this->tile_type.clear();
	this->floor_level_tiles_coords.clear();
	this->tiles.clear();
	this->non_walkable_objects.clear();
	this->last_known_tiles_over_player.clear();
	this->draw_tile_over_player.clear();
	this->can_draw_over_player_objects.clear();
	this->non_walkable_tiles.clear();
	this->draw_tile_over_player.clear();
	this->last_known_tiles_over_player.clear();
	this->map_matrix.clear();
	this->recolor_tiles.clear();
	this->draw_these.clear();
	
	this->map_dimensions = { this->dis(this->gen), this->dis(this->gen) };
	this->number_of_tiles = this->map_dimensions.first*this->map_dimensions.second;

	for (int i = 0; i < this->number_of_tiles; i++)
	{
			if (this->dis2(this->gen) == 1 ||
				i < this->map_dimensions.first ||
				i % this->map_dimensions.first  == 0 || 
				i % this->map_dimensions.first  == this->map_dimensions.first - 1 ||
				i > this->map_dimensions.first*(this->map_dimensions.second-1))
			{
				this->tile_type.emplace_back(pair<float,float>( 0, 0 ), false);
			}
			else
			{
				this->tile_type.emplace_back(pair<float, float>(3, 0), false);
			}
	}

	float pos_x = 0, pos_y = 0;
	int tile_number = 0;
	for (auto &pair : this->tile_type)
	{
		this->tile.second = IsWalkable({ (int)pair.first.first, (int)pair.first.second });
		this->tile.first.setPosition(Convert2DToIso({ pos_x*(this->tile_size / 2), pos_y*(this->tile_size / 2) }).first, Convert2DToIso({ pos_x*(this->tile_size / 2) , pos_y*(this->tile_size / 2) }).second);
		this->tile.first.setTextureRect(sf::IntRect(3 * this->tile_size, (int)(pair.first.second *  this->tile_size), this->tile_size, this->tile_size)); //floor level
		this->tiles.emplace_back(this->tile);

		this->tile.first.setTextureRect(sf::IntRect((int)(pair.first.first *  this->tile_size), (int)(pair.first.second *  this->tile_size), this->tile_size, this->tile_size));
		this->non_walkable_tiles.emplace_back(this->tile);

		this->floor_level_tiles_coords.emplace_back(
			std::pair<vector<std::pair<float, float>>, int>
		{
			{
				{ this->tile.first.getPosition().x + this->half_tile_size, this->tile.first.getPosition().y + this->half_tile_size },
				{ this->tile.first.getPosition().x, this->tile.first.getPosition().y + this->three_fourths_tile_size },
				{ this->tile.first.getPosition().x + this->half_tile_size, this->tile.first.getPosition().y + this->tile_size },
				{ this->tile.first.getPosition().x + this->tile_size, this->tile.first.getPosition().y + this->three_fourths_tile_size }
			},
				tile_number
		});

		can_draw_over_player_objects.emplace_back(
			std::pair<vector<std::pair<float, float>>, int>
		{
			{
				GetPolygonPoints(&this->tile.first)
			},
				tile_number
		});

		if (++pos_x >= this->map_dimensions.first)
		{
			pos_x = 0;
			pos_y++;
		}
		tile_number++;
	}

	for (int y = 0; y<this->map_dimensions.second; y++)
	{
		this->map_matrix.emplace_back(vector<int>(this->map_dimensions.first, 0));
	}

	int index = 0;
	for (auto& elem1 : this->map_matrix)
	{
		for (auto& elem2 : elem1)
		{
			if (this->non_walkable_tiles[index++].second)
			{
				elem2 = 0;
			}
			else
			{
				elem2 = 1;
			}
		}
	}
}

vector<sf::Sprite*> Map::CheckWhatToDraw()
{
	std::vector<sf::Sprite*> draw_these_local;
	for (auto &tile : this->tiles)
	{
		if (tile.first.getGlobalBounds().intersects(view_bounds))
		{
			draw_these_local.emplace_back(&tile.first);
		}
	}

	for (auto &tile : this->non_walkable_tiles)
	{
		if (tile.first.getGlobalBounds().intersects(view_bounds))
		{
			draw_these_local.emplace_back(&tile.first);
		}
	}
	return draw_these_local;
}

vector<pair<float, float>> Map::GetPolygonPoints(sf::Sprite* tile)
{
	return vector<pair<float, float>>
	{
			{ (*tile).getPosition().x + this->half_tile_size, (*tile).getPosition().y},
			{ (*tile).getPosition().x						, (*tile).getPosition().y + this->quarter_tile_size },
			{ (*tile).getPosition().x						, (*tile).getPosition().y + this->three_fourths_tile_size },
			{ (*tile).getPosition().x + this->half_tile_size, (*tile).getPosition().y + this->tile_size },
			{ (*tile).getPosition().x + this->tile_size		, (*tile).getPosition().y + this->three_fourths_tile_size },
			{ (*tile).getPosition().x + this->tile_size		, (*tile).getPosition().y + this->quarter_tile_size }
	};
}

int Map::GetTileNumberWherePlayerIs(sf::Vector2f body_size)
{
	for (auto& floor_tile : this->floor_level_tiles_coords)
	{
		if (ContainsPoint({ this->player_position.first,this->player_position.second + body_size.y }, floor_tile))
		{
			return floor_tile.second;
		}
	}

	return -1;
}

int Map::GetTileNumberClicked(sf::RenderWindow& window)
{
	sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
	sf::Vector2f world_pos = window.mapPixelToCoords(pixel_pos);
	for (auto& floor_tile : this->floor_level_tiles_coords)
	{
		if (ContainsPoint({ world_pos.x, world_pos.y }, floor_tile))
		{
			return floor_tile.second;
		}
	}
	return -1;
}

pair<string, pair<pair<int, int>, pair<int, int>>> Map::SetFinishLocation(sf::Event event, sf::RenderWindow& window, sf::Vector2f body_size)
{
	int tile_number_clicked = GetTileNumberClicked(window);
	if (tile_number_clicked > -1)
	{
		if (this->tiles[tile_number_clicked].second)
		{
			this->finish_location = {
				tile_number_clicked / this->map_dimensions.first,
				tile_number_clicked % this->map_dimensions.first
			};
			SetStartLocation(body_size);
			Pathfinding* path = new Pathfinding();
			this->player_path = path->FindPath(this->map_dimensions, this->map_matrix, this->dx, this->dy, this->dir, 
				this->start_location.first, this->start_location.second, this->finish_location.first, this->finish_location.second);
			delete path;
		}
	}
	return this->player_path;
}

void Map::SetStartLocation(sf::Vector2f body_size)
{
	int tile_number_player_is = GetTileNumberWherePlayerIs(body_size);
	if (tile_number_player_is > -1)
	{
			this->start_location = {
				tile_number_player_is / this->map_dimensions.first,
				tile_number_player_is % this->map_dimensions.first
			};
	}
}

pair<float, float> Map::GetStartLocation()
{
	return this->start_location;
}

pair<float, float> Map::GetFinishLocation()
{
	return this->finish_location;
}

vector<pair<vector<pair<float, float>>, int>> Map::GetFloorLevelTilesCoords()
{
	return this->floor_level_tiles_coords;
}

pair<int, int> Map::GetMapDimensions()
{
	return this->map_dimensions;
}

vector<pair<sf::Sprite, bool>> Map::GetTiles()
{
	return this->tiles;
}

void Map::ChangeTilesOpacity(vector<int> which_tiles)
{
	if (which_tiles.size() == 0 || (which_tiles.size() != this->recolor_tiles.size() && this->recolor_tiles.size() != 0 || this->event->mouseButton.button == sf::Mouse::Left))
	{
		for (auto& elem : this->recolor_tiles)
		{
			this->non_walkable_tiles[elem].first.setColor(sf::Color(255, 255, 255, 255));
			this->tiles[elem].first.setColor(sf::Color(255, 255, 255, 255));
		}
		this->recolor_tiles.clear();
	}
	if (which_tiles.size() != 0)
	{
		this->recolor_tiles = which_tiles;
		for (auto& elem : which_tiles)
		{
			this->tiles[elem].first.setColor(sf::Color(255, 255, 255, 30));
			this->non_walkable_tiles[elem].first.setColor(sf::Color(255, 255, 255, 30));
		}
	}
}

void Map::SetPlayerPosition(pair<float, float> position)
{
	this->player_position = position;
}

void Map::SetEvent(sf::Event * event)
{
	this->event = event;
}

void Map::SetWhatToDraw()
{
	this->draw_these.clear();
	this->draw_these = CheckWhatToDraw();
}

void Map::SetViewBounds(sf::FloatRect& view_bounds)
{
	this->view_bounds = view_bounds;
    //this is for drawing tiles on the entire view
	this->view_bounds.height += 300;
	this->view_bounds.width += 300;
	//this is for drawing tiles on a smaller area of a view | this can also be done with a viewport
	//this->viewBounds.left += 150;
	//this->viewBounds.top += 150;
	//this->viewBounds.height -= 300;
	//this->viewBounds.width -= 400;
}

bool Map::OnSegment(pair<float, float> p, pair<float, float> q, pair<float, float> r)
{
	if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) && q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second))
	{
		return true;
	}	
	return false;
}

int Map::orientation(pair<float, float> p, pair<float, float> q, pair<float, float> r)
{
	int val = (int)((q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second));
	if (val == 0)
	{
		return 0;
	}
	return (val > 0) ? 1 : 2;
}

bool Map::DoIntersect(pair<float, float> p1, pair<float, float> q1, pair<float, float> p2, pair<float, float> q2)
{
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);
	if ((o1 != o2 && o3 != o4) ||
		(o1 == 0 && OnSegment(p1, p2, q1)) ||
		(o2 == 0 && OnSegment(p1, q2, q1)) ||
		(o3 == 0 && OnSegment(p2, p1, q2)) ||
		(o4 == 0 && OnSegment(p2, q1, q2)))
	{
		return true;
	}
	return false; 
}

bool Map::IsInside(vector<pair<float, float>> polygon, int n, pair<float, float> p)
{
	if (n < 3)
	{
		return false;
	}
	extreme.second = p.second;
	int count = 0, i = 0, next;
	do
	{
		next = (i + 1) % n;
		if (DoIntersect(polygon[i], polygon[next], p, extreme))
		{
			if (orientation(polygon[i], p, polygon[next]) == 0)
			{
				return OnSegment(polygon[i], p, polygon[next]);
			}
			count++;
		}
		i = next;
	} while (i != 0);
	return count & 1;
}