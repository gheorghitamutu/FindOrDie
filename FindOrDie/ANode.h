#pragma once
#include <utility>
#include <algorithm> 

class ANode
{
private:
	std::pair<int, int> currentPosition;
	int level;
	int priority;
	int dir = 8;
public:
	ANode(int xp, int yp, int d, int p);
	void operator = (const ANode& N);
	friend bool operator<(const ANode& a, const ANode& b);
	int getxPos() const;
	int getyPos() const;
	int getLevel() const;
	int getPriority() const;
	void updatePriority(const int & xDest, const int & yDest);
	void nextLevel(const int & i);
	const int & estimate(const int & xDest, const int & yDest) const;
	~ANode();
};

