// Pr1.cpp
// Author Maksim Lukashevich
// Android developer    
// Student of the Belarusian State University of Informatics and Radioelectronics
// Groups number 89065012
// 
// Topic: Processand Thread Management.
// In all variants, it is necessary to write three functions that will be called
// from the main() function.Provide for the handling of exceptions at the input stages
// and data outputand during computations

#include <iostream>
#include <windows.h>
#include <malloc.h>

using namespace std;

// The first function gets the dimension of the  array, 
// creates a dynamic array and returns a pointer to the beginning 
// of the created array.
// MxN array
int** createArray(int m, const int n) {

    int** p_array = (int**)malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        p_array[i] = (int*)malloc(n * sizeof(int));
    }

    return p_array;
}
// The second one gets the address of the array 
// and its dimension and solves one of the tasks listed below.
// It is necessary to divide each line element by the largest line element.
void mainTask(int** p_array, int m, int n) {

    int* p_max = new int[m];

    // Finding the maximum values
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j == 0)
                p_max[i] = p_array[i][j];
            else if (p_max[i] < p_array[i][j])
                p_max[i] = p_array[i][j];
        }
    }
    // Divide by maximum values
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (p_max[i] == 0) { 
                throw 13; 
            }
            else {
                p_array[i][j] = p_array[i][j] / p_max[i];
            }
        }
    }

}

// The third function gets the address of the arrayand 
// its dimensionsand frees the memory occupied by the array.
void clearingArray(int** p_array, int m, int n) {

    for (int i = 0; i < m; i++) {
        free(p_array[i]);
    }

    free (p_array);

}

// Function for handling input. 
// We listen to the input until there is a correct expression.
int safetyCinWithMessage(string message){

    while(true){

        int variable;
        cout << message;
        cin >> variable;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Incorect value! Please try again!\n";
        }
        else {
            cin.ignore(32767, '\n');
            return variable;
        }
    }
}

int main()
{

    while (true) {

        //Create size variables
        int m, n;

        //Input terminal data
        cout << "Welcome to IPR1!\nPlease input array size M and N :\n";

        m = safetyCinWithMessage("Input M : ");

        n = safetyCinWithMessage("Input N : ");

        //Create array - Task1
        int** p_array = createArray(m, n);

        cout << "Now enter each element of the array!";

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << "\nInput [" << i << "][" << j << "] :";
                p_array[i][j] = safetyCinWithMessage("");
            }
        }

        cout << "As a result:\n";

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << "[" << p_array[i][j] << "] ";
            }
            cout << "\n";
        }

        cout << "Now task number 2 will be completed...\n";

        //Performing work on the array - Task2 
        try {

            mainTask(p_array, m, n);

            cout << "Task number 2 finished!\n";

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    cout << "[" << p_array[i][j] << "] ";
                }
                cout << "\n";
            }

            cout << "Now we are cleaning data...\n";

            //Clearing the memory occupied by the array - Task3
            clearingArray(p_array, m, n);

            cout << "All is ok.The end.\n";

            return 0;

        }
        catch (int i) {
            cout << "An error occurred while solving the problem:" << "\n";
            if (i == 13) {
                cout << "Division by zero\nThere was a situation in which the maximum value of the variable in the string turned out to be zero. You should try to enter values in such a way as to avoid this." << "\n";
            }
            cout << "Try to avoid this error when reusing\n";
            for (i = 0; i < 3; i++) {
                cout << "Let's try again in " << i << " seconds\n";
                Sleep(i * 1000);
            }
        }

    }

}