#pragma once
#include <list>
class Node
{
	int id;
	int level;
	Node* father;
	std::list<Node*> childs;
public:
	Node(Node *father, int id, int level);
	void Append(Node* child);
	std::list<Node*> AccesChilds();
	int Level();
	int Id();
	Node *Father();
};

