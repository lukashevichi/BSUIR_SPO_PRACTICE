#include "pch.h"

#include "Tree.h"
#include "Treell.h"

void* CreateTreell(const char* name) {
	Tree* tree = new Tree(name);
	return tree;
}

void GenerateDefault(void* treell)
{
	Tree* tree = (Tree *)treell;
	tree->GenerateDefault();
}

void LoadFromFile(void* treell)
{
	Tree* tree = (Tree*)treell;
	tree->LoadFromFile();
}

void Store2File(void* treell)
{
	Tree* tree = (Tree*)treell;
	tree->Store2File();
}

void View(void* treell)
{
	Tree* tree = (Tree*)treell;
	tree->View();
}

void TaskIt(void* treell, void (*task)(void* stream, void* node))
{
	Tree* tree = (Tree*)treell;
	tree->SetLabTask2(task);
}