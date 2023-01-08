#pragma once
#include <pthread.h>
#include <unistd.h>

class Board {
private:
	const int numberOfAnts;
	//1 = extinction; 2 = solely survivor; 3 = add-on logic (inverse logic)
	const int collisionLogic;
	pthread_mutex_t* mutex;
	pthread_cond_t* cond_ants;

	int antsBoard[80][80][20];
	bool changeBoard[80][80][20];
	char colourBoard[80][80];

	int rowSize;
	int colSize;

public:
	Board(int x, int y, int logic, int totalAnts, pthread_mutex_t* mutex, pthread_cond_t* condAnts);
	//Board(int, int, int, int, pthread_mutex_t&, pthread_cond_t&);
    int getColSize();
    int getRowSize();
    void startupSet();
    char getColor(int, int);
    void changeColor(int, int);
    bool isWall(int, int);
	int getLogic();
	int getNumOfAnts();
	bool getChange(int, int, int);
	void setChange(int, int, int);

};