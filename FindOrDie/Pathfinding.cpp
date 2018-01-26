#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
}

Pathfinding::~Pathfinding()
{
}

std::pair<std::string, std::pair<std::pair<int,int>, std::pair<int,int>>> Pathfinding::FindPath(
	std::pair<int, int> map_dimensions, std::vector<std::vector<int>> map, std::vector<int>& dx, std::vector<int>& dy, int & dir, 
	const int & x_start, const int & y_start, const int & x_finish, const int & y_finish)
{
	std::vector<std::vector<int>> closed_nodes_map; // map of closed (tried-out) nodes
	std::vector<std::vector<int>> open_nodes_map; // map of open (not-yet-tried) nodes
	std::vector<std::vector<int>> dir_map; // map of directions
	/*	closed_nodes_map.resize(map.size());
		open_nodes_map.resize(map.size());
		dir_map.resize(map.size());
		for (auto& elem1 : closed_nodes_map)
		{
			elem1.resize(map[0].size());
			for (auto& elem2 : elem1)
			{
				elem2 = 0;
			}
		}
		for (auto& elem1 : open_nodes_map)
		{
			elem1.resize(map[0].size());
			for (auto& elem2 : elem1)
			{
				elem2 = 0;
			}
		}
		for (auto& elem1 : dir_map)
		{
			elem1.resize(map[0].size());
			for (auto& elem2 : elem1)
			{
				elem2 = 0;
			}
		}*/

	for (int y = 0; y < map_dimensions.second; y++)
	{
		closed_nodes_map.emplace_back(std::vector<int>(map_dimensions.first, 0));
		open_nodes_map.emplace_back(std::vector<int>(map_dimensions.first, 0));
		dir_map.emplace_back(std::vector<int>(map_dimensions.first, 0));
	}

	std::priority_queue<ANode> pq[2];
	int pqi = 0;
	ANode* n0;
	ANode* m0;
	int i, j, x = map_dimensions.second - 1, y = map_dimensions.first - 1, xdx, ydy;
	char c;
	n0 = new ANode(x_start, y_start, 0, 0);
	n0->UpdatePriority(x_finish, y_finish);
	pq[pqi].push(*n0);
	open_nodes_map[x - 1][y - 1] = n0->GetPriority();
	delete n0;
	while (!pq[pqi].empty())
	{
		n0 = new ANode(pq[pqi].top().GetXPos(), pq[pqi].top().GetYPos(), pq[pqi].top().GetLevel(), pq[pqi].top().GetPriority());
		x = n0->GetXPos();
		y = n0->GetYPos();
		pq[pqi].pop();
		open_nodes_map[x][y] = 0;
		closed_nodes_map[x][y] = 1;
		if (x == x_finish && y == y_finish)
		{
			std::string path = "";
			while (!(x == x_start && y == y_start))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}
			delete n0;
			while (!pq[pqi].empty())
			{
				pq[pqi].pop();
			}
		//	showStuff(path, { xStart, yStart }, mapDimensions, dx, dy, map);
			return { path,{{x_start, y_start},{x_finish,y_finish}} };
		}
		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i];
			ydy = y + dy[i];

			if (!(xdx<0 || xdx>map_dimensions.second - 1 || ydy<0 || ydy>map_dimensions.first - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				m0 = new ANode(xdx, ydy, n0->GetLevel(), n0->GetPriority());
				m0->NextLevel(i);
				m0->UpdatePriority(x_finish, y_finish);
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->GetPriority();
					pq[pqi].push(*m0);
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][ydy] > m0->GetPriority())
				{
					open_nodes_map[xdx][ydy] = m0->GetPriority();
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
					while (!(pq[pqi].top().GetXPos() == xdx &&
						pq[pqi].top().GetYPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop();
					if (pq[pqi].size() > pq[1 - pqi].size())
					{
						pqi = 1 - pqi;
					}
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0);
				}
				else
				{
					delete m0;
				}
			}
		}
		delete n0;
	}
	std::cout << "No route." << std::endl;
	return { "",{ { x_start, y_start },{ x_finish,y_finish } } };
}

void Pathfinding::show_stuff(std::string path, std::pair<int, int> start_location, std::pair<int, int> map_dimensions, std::vector<int>& dx, std::vector<int>& dy, std::vector<std::vector<int>> map)
{
	clock_t start = clock();
	std::string route = path;
	clock_t end = clock();
	if (route == "")
	{
		std::cout << "An empty route generated!" << std::endl;
	}
	double time_elapsed = double(end - start);
	std::cout << "Time to calculate the route (ms): " << time_elapsed << std::endl;
	std::cout << "Route:" << std::endl;
	std::cout << route << std::endl << std::endl;
	if (route.length()>0)
	{
		int j;
		char c;
		int x = start_location.first;
		int y = start_location.second;
		map[x][y] = 2;
		for (int i = 0; i<route.length(); i++)
		{
			c = route.at(i);
			j = atoi(&c);
			x = x + dx[j];
			y = y + dy[j];
			map[x][y] = 3;
		}
		map[x][y] = 4;

		// display the map with the route

		for (auto& elem1 : map)
		{
			for (auto& elem2 : elem1)
			{
				if (elem2 == 0)
					std::cout << " ";
				else if (elem2 == 1)
					std::cout << "*"; //obstacle
				else if (elem2 == 2)
					std::cout << "S"; //start
				else if (elem2 == 3)
					std::cout << "|"; //route
				else if (elem2 == 4)
					std::cout << "F"; //finish
			}
			std::cout << std::endl;
		}
	}
}

