#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>
#include "Tree.h"

void Tree::SetLabTask(function<void(ofstream&, Node*)> task)
{
	this->task = task;
}

Tree::Tree(string name)
{
	task = nullptr;
	this->name = name;
	root = new Node(nullptr, 0, 0);
	current = root;
	lastId = 0;
	fastAcces[0] = root;
	printf("%s name = %s\r\n", __FUNCSIG__, name.c_str());
}

Node *Tree::Add4Current()
{
	Node* child = new Node(current, ++lastId, current->Level() + 1);
	fastAcces[lastId] = child;
	current->Append(child);
	return child;
}

void Tree::SetCurrent(Node* node)
{
	current = node; 
}

void Tree::Print()
{
	for (const auto& t : fastAcces) {
		if (t.second->Father()) {
			printf("N[%d, %d, %d] ", t.second->Id(), t.second->Father()->Id(), t.second->Level());
		}
		else
		{
			printf("N[%d, %s, %d] ", t.second->Id(), "null", t.second->Level());
		}
	}
}

void Tree::View()
{
	std::unordered_map<int, std::unordered_map<int, Node*>> levels;
	for (const auto& t : fastAcces) {
		levels[t.second->Level()][t.first] = t.second;
	}

	for (const auto& l : levels) {
		for (const auto& t : l.second) {
			if (t.second->Father()) {
				printf("N[%d, %d, %d] ", t.second->Id(), t.second->Father()->Id(), t.second->Level());
			}
			else
			{
				printf("N[%d, %s, %d] ", t.second->Id(), "null", t.second->Level());
			}
		}
		printf("\r\n");
	}
}

void Tree::GenerateDefault()
{
	Node* left = Add4Current();
	Node* right = Add4Current();
	SetCurrent(left);
	Add4Current();
	Add4Current();
	Add4Current();
	SetCurrent(right);
	Add4Current();
}

void Tree::Store2File()
{
	ofstream myfile;
	myfile.open(name + "_tree.txt");
	myfile.clear();

	for (const auto& t : fastAcces) {
		if (task != nullptr) {
			task(myfile, t.second);
			continue;
		}

		int fid = -1;
		if (t.second->Father() != nullptr) {
			fid = t.second->Father()->Id();
		}

		myfile << t.second->Id() << " " << t.second->Level() << " " << fid << "\n";
	}

	myfile.close();
} 

void Tree::LoadFromFile()
{
	ifstream myfile;
	string line;
	fastAcces.clear();
	fastAcces[0] = root;
	myfile.open(name + "_tree.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			stringstream ss;
			ss << line;
			int id, level, fid;
			ss >> id;
			ss >> level;
			ss >> fid;

			if (id == 0) {
				continue; // skip root
			}

			fastAcces[id] = new Node(fastAcces[fid], id, level);
			fastAcces[fid]->Append(fastAcces[id]);
		}

		myfile.close();
	}

	myfile.close();
}
