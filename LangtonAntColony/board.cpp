#include "board.h"
#include "ant.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// construct ant's world
//+ creation of array of flags
//DIRECTIONS: 1 = UP, 2 = DOWN, 3 = LEFT, 4 = RIGHT
Board::Board(int x, int y, int logic, int totalAnts, pthread_mutex_t *mutexT, pthread_cond_t *condAnts)
    :collisionLogic(logic), numberOfAnts(totalAnts)
{
    //1 = extinction; 2 = solely survivor; 3 = add-on logic (inverse logic)
    /*const int collisionLogic = logic;
    const int numberOfAnts = totalAnts;*/
    int rowSize = x;
    int colSize = y;
	
	pthread_mutex_t* mutex = mutexT;
	pthread_cond_t* cond_ants = condAnts;

	int antsBoard[80][80][20] = { 0 };
	bool changeBoard[80][80][20] = { 0 };
	char colourBoard[80][80] = { ' ' };
}

//returns column size
int Board::getColSize()
{
    cout << colSize << endl;
    return colSize;
}

//returns row size
int Board::getRowSize()
{
    return rowSize;
}

//returns the color of a square
//if the square has no color, it will default it to white
char Board::getColor(int x, int y)
{
    char el = colourBoard[x][y];

    //defaults empty space to white
    if (el != ' ' && el != '#')
        return ' ';

    return el;
}

//flips to either white or black depending on what is there
void Board::changeColor(int x, int y)
{
    char current = getColor(x, y);

    //white to black
    if (current == ' ')
        colourBoard[x][y] = '#';

    //black to white
    else
        colourBoard[x][y] = ' ';

}

//using the ants current coords, it will make sure
//it is not out of bounds.  If it is, it will return true
bool Board::isWall(int x, int y)
{

    if (x < 0)
        return true;
    //if x coord exceeds row size
    if (x > rowSize - 1)
        return true;

    if (y < 0)
        return true;
    //if y coord exceeds column size
    if (y > colSize - 1)
        return true;

    return false;
}

//set randomly black/white tiles at board
//set randomly black/white tiles at board
void Board::startupSet()
{
    rand();
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            if (((double)rand() / (RAND_MAX)) > 0.5) {
                colourBoard[i][j] = '#';
            }
        }
    }
}
