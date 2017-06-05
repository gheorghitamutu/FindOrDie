#include "ANode.h"

ANode::ANode(int xp, int yp, int d, int p)
{
		currentPosition.first = xp;
		currentPosition.second = yp;
		level = d;
		priority = p;
}

void ANode::operator=(const ANode & N)
{
	currentPosition.first = N.currentPosition.first;
	currentPosition.second = N.currentPosition.second;
	level = N.level;
	priority = N.priority;
}

int ANode::getxPos() const
{
	return currentPosition.first;
}

int ANode::getyPos() const
{
	return currentPosition.second;
}

int ANode::getLevel() const
{
	return level;
}

int ANode::getPriority() const
{
	return priority;
}

void ANode::updatePriority(const int & xDest, const int & yDest)
{
	priority = level + estimate(xDest, yDest) * 10;
}

void ANode::nextLevel(const int & i)
{
	level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

const int & ANode::estimate(const int & xDest, const int & yDest) const
{
	return(std::max(xDest - currentPosition.first, yDest - currentPosition.second));
}

ANode::~ANode()
{
}

bool operator<(const ANode & a, const ANode & b)
{
	return a.getPriority() > b.getPriority();
}
