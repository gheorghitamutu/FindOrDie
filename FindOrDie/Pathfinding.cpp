#include "Pathfinding.h"



Pathfinding::Pathfinding()
{
}

pair<string, pair<pair<int,int>,pair<int,int>>> Pathfinding::pathFind(pair<int, int> mapDimensions, vector<vector<int>> map, vector<int>& dx, vector<int>& dy, int & dir, const int & xStart, const int & yStart, const int & xFinish, const int & yFinish)
{
		vector<vector<int>> closed_nodes_map; // map of closed (tried-out) nodes
		vector<vector<int>> open_nodes_map; // map of open (not-yet-tried) nodes
		vector<vector<int>> dir_map; // map of directions
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

		for (int y = 0; y < mapDimensions.second; y++)
		{
			closed_nodes_map.emplace_back(vector<int>(mapDimensions.first, 0));
			open_nodes_map.emplace_back(vector<int>(mapDimensions.first, 0));
			dir_map.emplace_back(vector<int>(mapDimensions.first, 0));
		}

		priority_queue<ANode> pq[2];
		int pqi = 0;
		ANode* n0;
		ANode* m0;
		int i, j, x = mapDimensions.second - 1, y = mapDimensions.first - 1, xdx, ydy;
		char c;
		n0 = new ANode(xStart, yStart, 0, 0);
		n0->updatePriority(xFinish, yFinish);
		pq[pqi].push(*n0);
		open_nodes_map[x - 1][y - 1] = n0->getPriority();
		delete n0;
		while (!pq[pqi].empty())
		{
			n0 = new ANode(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(), pq[pqi].top().getLevel(), pq[pqi].top().getPriority());
			x = n0->getxPos();
			y = n0->getyPos();
			pq[pqi].pop();
			open_nodes_map[x][y] = 0;
			closed_nodes_map[x][y] = 1;
			if (x == xFinish && y == yFinish)
			{
				string path = "";
				while (!(x == xStart && y == yStart))
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
				return { path,{{xStart, yStart},{xFinish,yFinish}} };
			}
			for (i = 0; i<dir; i++)
			{
				xdx = x + dx[i];
				ydy = y + dy[i];

				if (!(xdx<0 || xdx>mapDimensions.second - 1 || ydy<0 || ydy>mapDimensions.first - 1 || map[xdx][ydy] == 1
					|| closed_nodes_map[xdx][ydy] == 1))
				{
					m0 = new ANode(xdx, ydy, n0->getLevel(), n0->getPriority());
					m0->nextLevel(i);
					m0->updatePriority(xFinish, yFinish);
					if (open_nodes_map[xdx][ydy] == 0)
					{
						open_nodes_map[xdx][ydy] = m0->getPriority();
						pq[pqi].push(*m0);
						dir_map[xdx][ydy] = (i + dir / 2) % dir;
					}
					else if (open_nodes_map[xdx][ydy] > m0->getPriority())
					{
						open_nodes_map[xdx][ydy] = m0->getPriority();
						dir_map[xdx][ydy] = (i + dir / 2) % dir;
						while (!(pq[pqi].top().getxPos() == xdx &&
							pq[pqi].top().getyPos() == ydy))
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
		return { "",{ { xStart, yStart },{ xFinish,yFinish } } };
}

void Pathfinding::showStuff(string path, pair<int, int> startLocation, pair<int, int> mapDimensions, vector<int>& dx, vector<int>& dy, vector<vector<int>> map)
{
	clock_t start = clock();
	string route = path;
	clock_t end = clock();
	if (route == "")
	{
		std::cout << "An empty route generated!" << std::endl;
	}
	double time_elapsed = double(end - start);
	std::cout << "Time to calculate the route (ms): " << time_elapsed << std::endl;
	std::cout << "Route:" << endl;
	std::cout << route << std::endl << endl;
	if (route.length()>0)
	{
		int j;
		char c;
		int x = startLocation.first;
		int y = startLocation.second;
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
					cout << " ";
				else if (elem2 == 1)
					cout << "*"; //obstacle
				else if (elem2 == 2)
					cout << "S"; //start
				else if (elem2 == 3)
					cout << "|"; //route
				else if (elem2 == 4)
					cout << "F"; //finish
			}
			cout << endl;
		}
	}
}


Pathfinding::~Pathfinding()
{
}

