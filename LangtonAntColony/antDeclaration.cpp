#include <iostream>
#include "integerCheck.h"
#include "board.h"
#include "ant.h"
#include"outputManager.h"
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	//int variables to hold the user entered row size
	//column size, the x coord of the ant and
	//the y coord of the ant
	int numberOfAnts, rsize, csize, collisionType;

	cout << "Please enter a positive integer from 2 to 80"
		" - will be used for the row size." << endl;
	//checks for positive integer
	rsize = getUnsignedInt();
	//user has to enter at least 2 rows and at most
	//80 rows
	while (!(isRange(rsize, 80, 2)))
	{
		cout << "Error. Out of range." << endl;
		cout << "Please enter a positive integer from 2 to 80." << endl;
		rsize = getUnsignedInt();
	}

	cout << "Next, please enter a positive integer from 2 to 80"
		" for the colmun size." << endl;
	//checks for positive integer
	csize = getUnsignedInt();
	//the user has to enter at least 2 columns and at most
	//80 columns
	while (!(isRange(csize, 80, 2)))
	{
		cout << "Error. Out of range." << endl;
		cout << "Please enter a positive integer from 2 to 80." << endl;
		csize = getUnsignedInt();
	}

	cout << "Next, please enter a positive integer from 1 to 20"
		" for the number of ants." << endl;
	//checks for positive integer
	numberOfAnts = getUnsignedInt();
	//the user has to enter at least 2 columns and at most
	//80 columns
	while (!(isRange(numberOfAnts, 20, 1)))
	{
		cout << "Error. Out of range." << endl;
		cout << "Please enter a positive integer from 1 to 20." << endl;
		numberOfAnts = getUnsignedInt();
	}

	cout << "Next, please enter a positive integer from 1 to 3"
		" for collision solving. 1 = eradication; 2 = one survivor; 3 = add-on logic." << endl;
	//checks for positive integer
	collisionType = getUnsignedInt();
	//the user has to enter at least 2 columns and at most
	//80 columns
	while (!(isRange(collisionType, 3, 1)))
	{
		cout << "Error. Out of range." << endl;
		cout << "Please enter a positive integer from 1 to 3." << endl;
		collisionType = getUnsignedInt();
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////	THREADING	/////////////////////////////////////////////////////////

	pthread_mutex_t  mutex;
	pthread_cond_t  cond_ants;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_ants, NULL);

	pthread_t ants[numberOfAnts];

	//type to int from unsigned int
	/*int rsize1 = (int)rsize;
	int csize1 = (int)csize;
	int collisionType1 = (int)collisionType;
	int numberOfAnts1 = (int)numberOfAnts;*/

	//DEBUG DELETE
	/*cout << "row: " << rsize1 << endl;
	cout << "Col: " << csize1 << endl;
	cout << "logic: " << collisionType1 << endl;
	cout << "ants: " << numberOfAnts1 << endl;*/

	//remember to free allocated space
	Board boardData = Board((int)rsize, (int)csize, (int)collisionType, (int)numberOfAnts, &mutex, &cond_ants);

	//DEBUG DO NOT FORGET COMMENT
	//cout << "Board has been created:"; cout << endl;
	//printCmd(&boardData);
	/*cout << "Col size: " << boardData.getColSize() << endl;
	cout << "Row size: " << boardData.getRowSize() << endl;
	cout << "Change: " << boardData.getChange(0,0,0) << endl;
	cout << "Logic: " << boardData.getLogic() << endl;
	cout << "Num of ants: " << boardData.getNumOfAnts() << endl;*/
	//DEBUG DO NOT FORGET COMMENT
	boardData.startupSet();
	//cout << "Board has been set!"; cout << endl;
	printCmd(&boardData);
	//cout << "Board has been on std::out!"; cout << endl;


	for (int i = 0; i < numberOfAnts; ++i) {
		pthread_create(&ants[i], NULL, &logicMove, &boardData);
	}

	for (int i = 0; i < numberOfAnts; ++i) {
		pthread_join(ants[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_ants);
	delete &boardData;
}