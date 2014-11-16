#ifndef PIECE_H
#define PIECE_H

#include "board.h"

#define NOTYPE 0
#define PAWN 1
#define KNIGHT 2
#define ROOK 3
#define BISHOP 4
#define QUEEN 5
#define KING 6

#define WHITE 0
#define BLACK 1

class Board;

struct Position{
	unsigned int turn;
	int x, y;
	Position *next;
};


class Piece{
protected:
	Board *board;
	Position *position_first;
	Position *position, *pos_back;
	bool captured;
	unsigned short team;
	unsigned short type;

public:
	Piece();
	virtual ~Piece();
	void setup(int x, int y,Board*);
	void move(int,int);
	void setTeam(unsigned short s){ team = s; };
	unsigned short getTeam(){ return team; }; 
	void setCaptured(bool b){ captured = b; };
	bool isCaptured(){ return captured; };
	int getX(){return position->x;};
	int getY(){return position->y;};
	virtual bool isKing(){ return false; };
	void revert();
	virtual void setActive();	
	unsigned short getType(){return type;};
};

class Pawn: public Piece{
public:
	Pawn();
	~Pawn(){};
	void setActive();	
};

class Rook: public virtual Piece{
public:
	Rook();
	~Rook(){};
	void setActive();
};

class Bishop: public virtual Piece{
public:
	Bishop();
	~Bishop(){};
	virtual void setActive();
};

class Knight: public Piece{
public:
	Knight();
	~Knight(){};
	virtual void setActive();
};

class Queen: public Rook, public Bishop{
public:
	Queen();
	~Queen(){};
	void setActive();
};

class King: public Piece{
public:
	King();
	~King(){};
	void setActive();
	bool isKing(){ return true; };
};

#endif
