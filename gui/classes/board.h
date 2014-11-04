#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "piece.h"

class Piece;

struct Square{
	bool active;
	Piece *piece;
};

struct Team{
	bool oncheck;
	Piece **piece;
};

class Board{
protected:
	Team black;
	Team white;
	Square square[8][8];
	int turns;
	void setupTeamsDefault();
public:
	Board();
	~Board();
	void reset();
	void select(Piece*);
	void deselect();
	bool isActiveSquare(int,int);
	Square* getSquare(int,int);
	bool getTeam();
	void switchTurn();
	void setCheck(bool);
	bool teamOnCheck(bool);
	void checkPositions();
};

#endif
