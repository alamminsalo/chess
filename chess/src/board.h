#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "piece.h"

#define STATUS_NOCHECK 0
#define STATUS_CHECK 1
#define STATUS_CHECKMATE 2
#define STATUS_STALEMATE 3

class Piece;
struct Position;

struct Square{
	bool active;
	Piece *piece;
};

struct Team{
	bool oncheck, hasturn;
	Piece *piece[16];
};

class Board{
protected:
	Team black;
	Team white;
	Square square[8][8];
	Piece *selected;
	int turns;
	int status;
	void setupTeamsDefault();
	Position* getActiveList(Piece*);
	void deleteActiveList(Position*);
public:
	Board();
	~Board();
	void reset();
	void select(Piece*);
	bool selectPieceAt(int,int);
	void deselect();
	bool isActiveSquare(int,int);
	Square* getSquare(int,int);
	void switchTurn();
	int getTurn();
	bool teamOnCheck();
	void checkForMate();
	int simulateMove(Piece*,int x, int y);
	Team* getTeam(unsigned short id){ return id == 0 ? &white : &black; };
	Team* getActiveTeam(){ return white.hasturn ? &white : &black;};
	Team* getInactiveTeam(){ return white.hasturn ? &black : &white;};
	Piece* getSelected(){ return selected; };
	int moveSelected(int,int);
	int evaluateMate();
	int getStatus(){ return status;};
};

#endif
