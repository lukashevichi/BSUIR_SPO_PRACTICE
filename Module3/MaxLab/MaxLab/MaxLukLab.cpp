// MaxLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <Windows.h>

#include <list>

struct Node
{
	int id;
	int level;
	Node* father;
	std::list<Node*> childs;
};

void WriteNodeNormal(std::ofstream* fs, Node* node) {
	int fid = -1;
	if (node->father != nullptr) {
		fid = node->father->id;
	}
	*fs << node->id << " " << node->level << " " << fid << "\n";
}

struct MyData
{
	std::ofstream* stream;
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

void Task(void* stream, void* node)
{
	MyData data = { (std::ofstream*)stream, (Node* )node };
	DWORD dwThreadId;
	HANDLE thr = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		WriteNode,       // thread function name
		&data,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadId);   // returns the thread identifier 

	WaitForMultipleObjects(1, &thr, TRUE, INFINITE);
}

typedef void* (__cdecl* CREATETREELL)(const char* name);
typedef void(__cdecl* ACTIONTREEL)(void* treell);
typedef void(__cdecl* TASKTREELL)(void* treell, void (*task)(void* stream, void* node));

CREATETREELL CreateTrell;

ACTIONTREEL GenerateDefault;
ACTIONTREEL Store2File;
ACTIONTREEL LoadFromFile;
ACTIONTREEL View;
TASKTREELL TaskIt;

bool LoadDef(HMODULE mod)
{
	CreateTrell = (CREATETREELL)GetProcAddress(mod, "CreateTreell");
	if (!CreateTrell) {
		return false;
	}

	GenerateDefault = (ACTIONTREEL)GetProcAddress(mod, "GenerateDefault");
	if (!GenerateDefault) {
		return false;
	}
	Store2File = (ACTIONTREEL)GetProcAddress(mod, "Store2File");
	if (!Store2File) {
		return false;
	}
	LoadFromFile = (ACTIONTREEL)GetProcAddress(mod, "LoadFromFile");
	if (!LoadFromFile) {
		return false;
	}
	View = (ACTIONTREEL)GetProcAddress(mod, "View");
	if (!View) {
		return false;
	}
	TaskIt = (TASKTREELL)GetProcAddress(mod, "TaskIt");
	if (!TaskIt) {
		return false;
	}


	return true;
}

int main()
{
	std::cout << "Hello World!\n";

	HMODULE lib = LoadLibrary(L"Treell.dll");
	if (lib) {
		if (LoadDef(lib)) {
			void* trell = CreateTrell("TreeName");
			GenerateDefault(trell);
			Store2File(trell);

			TaskIt(trell, Task);

			LoadFromFile(trell);
			Store2File(trell);
			LoadFromFile(trell);
			View(trell);
		}
	}
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
