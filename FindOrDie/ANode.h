#pragma once
#include <utility>
#include <algorithm> 

class ANode
{
private:
	std::pair<int, int> current_position;
	int level;
	int priority;
	int dir = 8;
public:
	ANode(int xp, int yp, int d, int p);
	void operator = (const ANode& node);
	friend bool operator<(const ANode& a, const ANode& b);
	int GetXPos() const;
	int GetYPos() const;
	int GetLevel() const;
	int GetPriority() const;
	void UpdatePriority(const int & x_dest, const int & y_dest);
	void NextLevel(const int & i);
	const int & Estimate(const int & x_dest, const int & y_dest) const;
	~ANode();
};

