#ifndef PIECE_H
#define PIECE_H

#include "board.h"

struct Position{
	int x, y;
	Position *next;
};

class Board;

class Piece{
protected:
	Board *board;
	Position *position_first;
	Position *position;

public:
	Piece();
	~Piece();
	void setup(int x, int y,Board*);
	void move(int,int);
	virtual void setActive();	
};

class Pawn: public Piece{
	
public:
	Pawn(){};
	~Pawn(){};
	void setActive();	
};

class Rook: public Piece{
	public:
		Rook(){};
		~Rook(){};
		void setActive();
};

class Bishop: public Piece{
	public:
		Bishop(){};
		~Bishop(){};
		void setActive();
};

class Knight: public Piece{
	public:
		Knight(){};
		~Knight(){};
		void setActive();
};

class Queen: public Piece{
	public:
		Queen(){};
		~Queen(){};
		void setActive();
};

class King: public Piece{
	public:
		King(){};
		~King(){};
		void setActive();
};

#endif
