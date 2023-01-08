#include "ant.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "board.h"
#include <random>

//Ant::Ant(void* board)
//{
//	Board* datas = (Board*)board;
//	data = datas;
//	direction = 1;
//
//	alive = true;
//	inverse = false;
//
//	xcoord = genCoord(data->getRowSize());
//	ycoord = genCoord(data->getColSize());
//
//	pthread_mutex_lock(data->mutex);
//	int antID = data->getAntId();
//	data->incrementAntId();
//	pthread_mutex_unlock(data->mutex);
//
//	logicMove();
//
//}

void* logicMove(void* board)
{
    //DEBUG
    
	Board* data = (Board*)board;
	int direction = 1;
	int antID = 0;
	bool alive = true;
	bool inverse = false;

	int xcoord = genCoord(data->getRowSize());
	int ycoord = genCoord(data->getColSize());

	pthread_mutex_lock(data->mutex);
	antID = data->getAntId();
	data->incrementAntId();
	pthread_mutex_unlock(data->mutex);

    while (alive)
    {
		int x = xcoord;
		int y = ycoord;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//inverse logic is off
		if (!inverse)
		{
			
			//if the space is white
			if (data->getColor(x, y) == ' ')
			{
				//turns right to face right
				if (direction == 1)
					direction = 4;
				//turns right to face left
				else if (direction == 2)
					direction = 3;
				//turns right to face up
				else if (direction == 3)
					direction = 1;
				//turns right to face down
				else if (direction == 4)
					direction = 2;
			}

			//if the space is black
			else
			{
				//turns left to face left
				if (direction == 1) {
					direction = 3;
				}
				//turns left to face right
				else if (direction == 2) {
					direction = 4;
				}
				//turns left to face down
				else if (direction == 3) {
					direction = 2;
				}
				//turns left to face up
				else if (direction == 4) {
					direction = 1;
				}
			}
		}
		//invere logic is on
		else
		{
			//if the space is white
			if (data->getColor(x, y) == '#')
			{
				//turns right to face right
				if (direction == 1)
					direction = 4;
				//turns right to face left
				else if (direction == 2)
					direction = 3;
				//turns right to face up
				else if (direction == 3)
					direction = 1;
				//turns right to face down
				else if (direction == 4)
					direction = 2;
			}

			//if the space is black
			else
			{
				//turns left to face left
				if (direction == 1) {
					direction = 3;
				}
				//turns left to face right
				else if (direction == 2) {
					direction = 4;
				}
				//turns left to face down
				else if (direction == 3) {
					direction = 2;
				}
				//turns left to face up
				else if (direction == 4) {
					direction = 1;
				}
			}
		}


		//uses current coords to change the squares color
		pthread_mutex_lock(data->mutex);
		data->changeColor(xcoord, ycoord);
		if (data->getNumOfAnts() > 1)
		{
			data->setChange(x, y, antID);
		}
		pthread_mutex_unlock(data->mutex);

		//if facing up, move up 1
		if (direction == 1)
			xcoord = x - 1;
		//if facing down, move down 1
		if (direction == 2)
			xcoord = x + 1;
		//if facing left, move left 1
		if (direction == 3)
			ycoord = y - 1;
		//if facing right, move right 1
		if (direction == 4)
			ycoord = y + 1;



		//if the ants current coords are out of bounds
		if (data->isWall(xcoord, ycoord))
		{
			//put it back on the board and move it down 1
			//change its direction to down
			if (direction == 1)
			{
				xcoord += 2;
				direction = 2;
			}

			//place it back on board and move it up 1
			//change direction to up
			else if (direction == 2)
			{
				xcoord -= 2;
				direction = 1;
			}

			//place it back on board and move it right 1
			//change diretion to right
			else if (direction == 3)
			{
				ycoord += 2;
				direction = 4;
			}

			//place it back on board and move left 1
			//change direction to left
			else if (direction == 4)
			{
				ycoord -= 2;
				direction = 3;
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (data->getChange(xcoord, ycoord, antID))
        {
            switch (data->getLogic())
            {
                //extinction of all ants
            case 1:
                alive = false;

                pthread_mutex_lock(data->mutex);
                data->setChange(xcoord, ycoord, antID);
                data->placeAnt(false, xcoord, ycoord, antID);
                pthread_mutex_unlock(data->mutex);
                break;

                //solely survivor
            case 2:
                alive = false;

                pthread_mutex_lock(data->mutex);
                data->placeAnt(false, xcoord, ycoord, antID);
                pthread_mutex_unlock(data->mutex);
                break;

                //half change 
            case 3:
                inverse = true;
                break;

            default:
                break;
            }
        }

        //ant has cleard round
        pthread_cond_broadcast(data->cond_ants);
    }

    
}

int genCoord(int max) {
    int min = 0;
    srand(time(NULL));
    return min + rand() % ((max + 1) - min);
}

//void moveAnt(int x, int y)
//{
//	//inverse logic is off
//	if (!inverse)
//	{
//
//		//if the space is white
//		if (data->getColor(x, y) == ' ')
//		{
//			//turns right to face right
//			if (direction == 1)
//				direction = 4;
//			//turns right to face left
//			else if (direction == 2)
//				direction = 3;
//			//turns right to face up
//			else if (direction == 3)
//				direction = 1;
//			//turns right to face down
//			else if (direction == 4)
//				direction = 2;
//		}
//
//		//if the space is black
//		else
//		{
//			//turns left to face left
//			if (direction == 1) {
//				direction = 3;
//			}
//			//turns left to face right
//			else if (direction == 2) {
//				direction = 4;
//			}
//			//turns left to face down
//			else if (direction == 3) {
//				direction = 2;
//			}
//			//turns left to face up
//			else if (direction == 4) {
//				direction = 1;
//			}
//		}
//	}
//	//invere logic is on
//	else
//	{
//		//if the space is white
//		if (data->getColor(x, y) == '#')
//		{
//			//turns right to face right
//			if (direction == 1)
//				direction = 4;
//			//turns right to face left
//			else if (direction == 2)
//				direction = 3;
//			//turns right to face up
//			else if (direction == 3)
//				direction = 1;
//			//turns right to face down
//			else if (direction == 4)
//				direction = 2;
//		}
//
//		//if the space is black
//		else
//		{
//			//turns left to face left
//			if (direction == 1) {
//				direction = 3;
//			}
//			//turns left to face right
//			else if (direction == 2) {
//				direction = 4;
//			}
//			//turns left to face down
//			else if (direction == 3) {
//				direction = 2;
//			}
//			//turns left to face up
//			else if (direction == 4) {
//				direction = 1;
//			}
//		}
//	}
//
//
//
//	//uses current coords to change the squares color
//	pthread_mutex_lock(data->mutex);
//	data->changeColor(xcoord, ycoord);
//	pthread_mutex_unlock(data->mutex);
//
//	//if facing up, move up 1
//	if (direction == 1)
//		xcoord = x - 1;
//	//if facing down, move down 1
//	if (direction == 2)
//		xcoord = x + 1;
//	//if facing left, move left 1
//	if (direction == 3)
//		ycoord = y - 1;
//	//if facing right, move right 1
//	if (direction == 4)
//		ycoord = y + 1;
//
//
//
//	//if the ants current coords are out of bounds
//	if (data->isWall(xcoord, ycoord))
//	{
//		//put it back on the board and move it down 1
//		//change its direction to down
//		if (direction == 1)
//		{
//			xcoord += 2;
//			direction = 2;
//		}
//
//		//place it back on board and move it up 1
//		//change direction to up
//		else if (direction == 2)
//		{
//			xcoord -= 2;
//			direction = 1;
//		}
//
//		//place it back on board and move it right 1
//		//change diretion to right
//		else if (direction == 3)
//		{
//			ycoord += 2;
//			direction = 4;
//		}
//
//		//place it back on board and move left 1
//		//change direction to left
//		else if (direction == 4)
//		{
//			ycoord -= 2;
//			direction = 3;
//		}
//	}
//}