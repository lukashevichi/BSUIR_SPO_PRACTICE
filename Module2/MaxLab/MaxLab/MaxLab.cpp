// MaxLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <Windows.h>

#include "Tree.h"
#include "MaxLab.h"

void WriteNodeNormal(ofstream& stream, Node* node) {
	int fid = -1;
	if (node->Father() != nullptr) {
		fid = node->Father()->Id();
	}
	stream << node->Id() << " " << node->Level() << " " << fid << "\n";
}

struct MyData
{
	ofstream& stream;
	Node* node;
};


DWORD WINAPI WriteNode(LPVOID lpParam)
{
	static Node* oldNode = nullptr;
	MyData* data = (MyData*)lpParam;
	if (data->node != oldNode) {
		WriteNodeNormal(data->stream, data->node);
	}
	oldNode = data->node;
	return 0;
}


int main()
{
	std::cout << "Hello World!\n";

	Tree tree("HelloWorldTree");

	tree.GenerateDefault();
	tree.Store2File();

	tree.SetLabTask([=](ofstream& stream, Node* node) {

		MyData data = { stream, node };
		DWORD dwThreadId;
		HANDLE thr = CreateThread(
			NULL,                   // default security attributes
			0,                      // use default stack size  
			WriteNode,       // thread function name
			&data,          // argument to thread function 
			0,                      // use default creation flags 
			&dwThreadId);   // returns the thread identifier 

		WaitForMultipleObjects(1, &thr, TRUE, INFINITE);

		});

	tree.LoadFromFile();
	tree.Store2File();
	tree.LoadFromFile();
	tree.View();

	//tree.Store2File();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
