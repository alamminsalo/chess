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
	Square *tmpsqr;
	for (int y=position->y-1, x=position->x-1; x>-1 && y>-1; x--,y--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			break;
		}
	}
	for (int y=position->y+1, x=position->x+1; x<8 && y<8; x++,y++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			break;
		}
	}
	for (int y=position->y-1, x=position->x+1; x<8 && y>-1; x++, y--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			break;
		}
	}
	for (int y=position->y+1, x=position->x-1; y<8 && x>-1; x--,y++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			break;
		}
	}
}

void Knight::setActive(){
	Square *tmpsqr;
	int x, y;
	for (int i=0; i<8; i++){
		x = position->x;
		y = position->y;
		switch(i){
			case 0:
				x++; y-=2;
				break;
			case 1:
				x+=2; y--;
				break;
			case 2:
				x+=2; y++;
				break;
			case 3:
				x++; y+=2;
				break;
			case 4:
				x--; y+=2;
				break;
			case 5:
				x-=2; y++;
				break;
			case 6:
				x-=2; y--;
				break;
			case 7:
				x--; y-=2;
				break;
		}
		if ((x>-1 && y>-1) && (x<8 && y<8)){
			tmpsqr = board->getSquare(x,y);
			tmpsqr->active = true;
			if (tmpsqr->piece){
				if (tmpsqr->piece->getTeam() == this->getTeam())
					tmpsqr->active = false;
			}
		}
	}
}

void Rook::setActive(){
	Square *tmpsqr;
	for (int y=position->y, x=position->x-1; x>-1; x--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			break;
		}
	}
	for (int y=position->y, x=position->x+1; x<8; x++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			break;
		}
	}
	for (int y=position->y-1, x=position->x; y>-1; y--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			break;
		}
	}
	for (int y=position->y+1, x=position->x; y<8; y++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			break;
		}
	}
}

void Queen::setActive(){
	Rook::setActive();
	Bishop::setActive();	
}

void King::setActive(){
	int x = position->x;
	int y = position->y;
	Square *tmpsqr;
	for (int i=0; i<8; i++){
		switch(i){
			case 0:case 6: case 7:
				y--;
				break;
			case 1:
				x++;
				break;
			case 2: case 3:
				y++;
				break;
			case 4: case 5:
				x--;
		}
		if ((x>-1 && y>-1) && (x<8 && y<8)){
			tmpsqr = board->getSquare(x,y);
			tmpsqr->active = true;
			if (tmpsqr->piece){
				if (tmpsqr->piece->getTeam() == this->getTeam())
					tmpsqr->active = false;
			}
		}
	}
}
