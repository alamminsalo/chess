#ifndef PIECE_H
#define PIECE_H

#include "board.h"

class Board;

struct Position{
	int x, y;
	Position *next;
};


class Piece{
protected:
	Board *board;
	Position *position_first;
	Position *position;
	bool team;
	bool captured;

public:
	Piece();
	virtual ~Piece();
	void setup(int x, int y,Board*);
	void move(int,int);
	void setBlackTeam(){ team = false; };
	bool getTeam(){ return team; }; 
	void setCaptured(bool b){ captured = b; };
	bool isCaptured(){ return captured; };
	int getX(){return position->x;};
	int getY(){return position->y;};
	virtual bool isKing(){ return false; };
	virtual void setActive();	
};

class Pawn: public Piece{
	bool hasMoved;	
public:
	Pawn();
	~Pawn(){};
	void setActive();	
	bool isKing(){ return false; };
};

class Rook: public Piece{
public:
	Rook();
	~Rook(){};
	void setActive();
	bool isKing(){ return false; };
};

class Bishop: public Piece{
public:
	Bishop();
	~Bishop(){};
	void setActive();
	bool isKing(){ return false; };
};

class Knight: public Piece{
public:
	Knight();
	~Knight(){};
	void setActive();
	bool isKing(){ return false; };
};

class Queen: public Piece{
public:
	Queen();
	~Queen(){};
	void setActive();
	bool isKing(){ return false; };
};

class King: public Piece{
public:
	King();
	~King(){};
	void setActive();
	bool isKing(){ return true; };
};

#endif
