#pragma once

#include <string>
#include <functional>
#include "Node.h"
#include <unordered_map>

using namespace std;

class Tree
{
	string name;
	Node* root;
	Node* current;

	function<void(ofstream&, Node*)> task;
	function<void(ofstream*, Node*)> task2;
	int lastId;
	unordered_map<int, Node*> fastAcces;

public:

	void SetLabTask(function<void(ofstream&, Node*)> task);
	void SetLabTask2(function<void(ofstream*, Node*)> task2);

	Tree(string name);
	Node* Add4Current();

	void SetCurrent(Node* node);

	void Print();

	void View();

	void GenerateDefault();

	void Store2File();

	void LoadFromFile();
};

