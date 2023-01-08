#pragma once
class Ant
{
private:
	//Board* board;
	int xcoord, 
		ycoord,
		direction, 
		logic;

public:
	Ant();
	int getRow();
	int getCol();
	void moveAnt(int, int);
	void antMove();
};

