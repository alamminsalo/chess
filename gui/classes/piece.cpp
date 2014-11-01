#include "piece.h"

Piece::Piece(){
	position_first = new Position();
	position = position_first;
}

void Piece::setActive(){
	Square *sqr;
	for (int y=0; y<8; y++)
		for(int x=0; x<8; x++){
			sqr = board->getSquare(x,y);
			if (!sqr->piece)
				sqr->active = true;
		}
}

void Piece::setup(int x, int y, Board *b){
	position->x = x;
	position->y = y;	
	board = b;
	board->getSquare(x,y)->piece = this;
}

void Piece::move(int x,int y){
	position->next = new Position();
	position = position->next;
	position->x = x; 
	position->y = y;
}

