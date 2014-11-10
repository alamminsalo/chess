#include "piece.h"

Piece::Piece(){
	type = NOTYPE;
	position_first = new Position();
	position = position_first;
	team = true;
	captured = false;
}

Piece::~Piece(){
	Position *pDel = position_first;
	while (pDel){
		position_first = position_first->next;
		delete pDel;
		pDel = position_first;
	}	
	pDel = position_first = position = NULL;
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
	if (board->getSquare(x,y)->piece)
		board->getSquare(x,y)->piece->setCaptured(true);
	board->getSquare(position->x,position->y)->piece = NULL;
	position->next = new Position();
	position = position->next;
	position->x = x; 
	position->y = y;
	position->turn = board->getTurn();
	board->getSquare(position->x,position->y)->piece = this;
	board->deselect();
	board->switchTurn();
}

void Pawn::setActive(){
	std::cout<<"Setting active pawn...\n";
	int dir;
	int moves = 1;
	dir = board->getTurn() % 2 == 0 ? -1 : 1;
	if (!hasMoved) moves++;

	for (int i=0, y=position->y; i < moves; i++,y+=dir)
		if (!board->getSquare(position->x,y)->piece)
			board->getSquare(position->x,y)->active = true;	
	int x = position->x -1;
	int y = position->y +dir;
	Square *sqr;
	if (x >= 0){
		sqr = board->getSquare(x,y);
		if (sqr->piece)
		   if (sqr->piece->getTeam() != this->team){
			  sqr->active = true;
			  if (sqr->piece->isKing())
				  board->setCheck(!this->team);
		   }
	}
	x = position->x +1;
	if (x <= 7){
		sqr = board->getSquare(x,y);
		if (sqr->piece)
		   if (sqr->piece->getTeam() != this->team){
			  sqr->active = true;
			  if (sqr->piece->isKing())
				  board->setCheck(!this->team);
		   }
	}
}
Pawn::Pawn(){
	type = PAWN;
	hasMoved = false;
	std::cout<<"Created Pawn!\n";
}

Bishop::Bishop(){
	type = BISHOP;
	std::cout<<"Created Bishop!\n";
}
Rook::Rook(){
	type = ROOK;
	std::cout<<"Created rook!\n";
}
Knight::Knight(){
	type = KNIGHT;
	std::cout<<"Created knight!\n";
}
Queen::Queen(){
	type = QUEEN;
	std::cout<<"Created queen!\n";
}
King::King(){
	type = KING;
	std::cout<<"Created king!\n";
}

void Bishop::setActive(){
	
}

void Knight::setActive(){

}

void Rook::setActive(){

}

void Queen::setActive(){

}

void King::setActive(){

}
