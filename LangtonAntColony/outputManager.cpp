#include "outputManager.h"
#include "board.h"
#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;
using std::cout;
using std::endl;

void printCmd(Board *b)
{
	//int variables to hold the ants coordinates and
	//to hold the boards correct row and column sizes
	int rowSize = b->getRowSize();
	int colSize = b->getColSize();

	//each element will be filled with a color received from Board
	//if the index reaches the ants x and y coordinats
	//it will print the ant on the screen
	//if not,it will get a color from Board to print in the followin elements
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			cout << b->getColor(i, j);
		}

		cout << endl;
	}
}

void fileOutput(Board* b)
{
	int rowSize = b->getRowSize();
	int colSize = b->getColSize();

	ofstream myfile;
	myfile.open("antPattern.txt");
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			myfile << b->getColor(i, j);
		}
		cout << endl;
	}
	myfile.close();
}