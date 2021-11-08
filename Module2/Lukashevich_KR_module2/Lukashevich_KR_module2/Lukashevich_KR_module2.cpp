// Lukashevich_KR_module2.cpp : 
// Processes and threads.
// In all variants of tasks Writing a program that uses OS system objects for
// synchronization of threads of different processes
// 
// Option number 3  
// 
// The function of writing a tree node to a file (WriteNode ()) is executed in the secondary thread. While creating
// the thread is passed a pointer to a variable of type Node* .
// The thread should write the new node to the file if the node address has changed.
// The main thread in a loop adds nodes to the tree(new nodes are added from left to right).Front
// by adding a new node, the thread is paused, and at the end of the addition it is started.By using
// programs from the 4th work check the correctness of the tree written in the file.
// 
// Функция записи узла дерева в файл (WriteNode()) выполняется во вторичном потоке. При создании 
//потоку передается указатель на переменную типа Node* .
//Поток должен записать новый узел в файл если адрес узла изменился.
//Главный поток в цикле добавляет узлы в дерево(новые узлы добавляются слева на право).Перед
//добавлением нового узла поток приостанавливается, а в конце добавления запускается.С помощью
//программы из 4 - й работы проверить правильность записанного в файл дерева.
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}