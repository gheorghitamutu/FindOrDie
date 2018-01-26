#include "ANode.h"

ANode::ANode(int xp, int yp, int d, int p)
{
		this->current_position.first = xp;
		this->current_position.second = yp;
		this->level = d;
		this->priority = p;
}

ANode::~ANode()
{
}


void ANode::operator=(const ANode & node)
{
	this->current_position.first = node.current_position.first;
	this->current_position.second = node.current_position.second;
	this->level = node.level;
	this->priority = node.priority;
}

int ANode::GetXPos() const
{
	return this->current_position.first;
}

int ANode::GetYPos() const
{
	return this->current_position.second;
}

int ANode::GetLevel() const
{
	return this->level;
}

int ANode::GetPriority() const
{
	return this->priority;
}

void ANode::UpdatePriority(const int & x_dest, const int & y_dest)
{
	this->priority = this->level + Estimate(x_dest, y_dest) * 10;
}

void ANode::NextLevel(const int & i)
{
	this->level += (this->dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

const int & ANode::Estimate(const int & x_dest, const int & y_dest) const
{
	return(std::max(x_dest - this->current_position.first, y_dest - this->current_position.second));
}

bool operator<(const ANode & a, const ANode & b)
{
	return a.GetPriority() > b.GetPriority();
}
