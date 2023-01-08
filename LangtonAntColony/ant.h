#pragma once
class Ant
{
private:
	//Board* board;
	int xcoord, ycoord, direction;

public:
	Ant();
	int getRow();
	int getCol();
	void moveAnt(int, int);
};

