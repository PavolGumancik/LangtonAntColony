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
    :collisionLogic(logic), numberOfAnts(totalAnts), rowSize(x), colSize(y), antId(0)
{  
    //type of logic - decision at collision
    //1 = extinction; 2 = solely survivor; 3 = add-on logic (inverse logic)
    
	pthread_mutex_t* mutex = mutexT;
	pthread_cond_t* cond_ants = condAnts;

	int antsBoard[80][80][20] = { 0 };
	bool changeBoard[80][80][20] = { 0 };
	char colourBoard[80][80] = { ' ' };
}

//returns column size
int Board::getColSize()
{
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

int Board::getLogic()
{
    return Board::collisionLogic;
}

bool Board::getChange(int x, int y, int id)
{
    return changeBoard[x][y][id];
}

int Board::getNumOfAnts()
{
    return Board::numberOfAnts;
}


int Board::getNumOfAntsTile(int xcoord, int ycoord)
{
    int cnt = 0;
    for (int i = 0; i < getNumOfAnts(); i++)
    {
        if (antsBoard[xcoord][ycoord][i] == true) {
            cnt++;
        }
    }
    return cnt;
}

void Board::setChange(int xcoord, int ycoord, int id)
{
    if (collisionLogic == 2)
    {
        changeBoard[xcoord][ycoord][id] = true;
    }
    else if (collisionLogic == 3)
    {
        int cnt = 0;
        int i = 0;
        while (cnt < getNumOfAntsTile(xcoord, ycoord)/2)
        {
            changeBoard[xcoord][ycoord][i] = true;
            i++;
        }
    }
    else
    {
        for (int i = 0; i < getNumOfAnts(); i++)
        {
            if (changeBoard[xcoord][ycoord][i]) {
                changeBoard[xcoord][ycoord][i] = true;
            }
        }
    }
    
}

int Board::getAntId()
{
    return Board::antId;
}

void Board::incrementAntId()
{
    antId++;
}

void Board::placeAnt(bool set, int x, int y, int antId)
{
    if (set)
    {
        antsBoard[x][y][antId] = true;
    }
    else
    {
        antsBoard[x][y][antId] = false;
        changeBoard[x][y][antId] = false;
    }
}