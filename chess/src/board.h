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
	Piece *piece[16];
};

class Board{
protected:
	Team black;
	Team white;
	Square square[8][8];
	Piece *selected;
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
	void switchTurn();
	int getTurn();
	void setCheck(bool);
	bool teamOnCheck(bool);
	void checkPositions();
	void manage();
	Team* getTeam(unsigned short id){ return id == 0 ? &black : &white; };
	Piece* getSelected(){ return selected; };
};

#endif
