#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

struct Square{
	bool active;
	Piece *piece;
};

struct Team{
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
	void giveTurn(Team*);
	Square* getSquare(int,int);
};

#endif
