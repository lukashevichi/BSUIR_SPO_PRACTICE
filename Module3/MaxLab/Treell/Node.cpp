#include "pch.h"

#include "Node.h"

Node::Node(Node* father, int id, int level)
{
	this->father = father;
	this->id = id;
	this->level = level;
}

void Node::Append(Node* child)
{
	childs.push_back(child);
}

std::list<Node*> Node::AccesChilds()
{
	return childs;
}

int Node::Level()
{
	return level;
}

int Node::Id()
{
	return id;
}

Node* Node::Father()
{
	return father;
}


