#include "piece.h"

Piece::Piece(){
	type = NOTYPE;
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

void Piece::revert(){
	std::cout<<"Reverting..\n";
	move(pos_back->x,pos_back->y);
//	std::cout<<"Starting from "<<tmp_ptr->x<<","<<tmp_ptr->y<<std::endl;
//	while (tmp_ptr->next != position){
//		std::cout<<"Found next position on list->\n";
//		tmp_ptr = tmp_ptr->next;
//	}
//	board->getSquare(tmp_ptr->x,tmp_ptr->y)->piece = this;
//	board->getSquare(tmp_ptr->next->x,tmp_ptr->next->y)->piece = NULL;
//	delete tmp_ptr->next;
//	tmp_ptr->next = NULL;
//	position = tmp_ptr;
	std::cout<<"Done reverting.\n";
}

void Piece::setup(int x, int y, Board *b){
	position_first = new Position();
	position_first->x = x;
	position_first->y = y;	
	position = position_first;
	board = b;
	board->getSquare(x,y)->piece = this;
}

void Piece::move(int x,int y){
	if (board->getSquare(x,y)->piece)
		board->getSquare(x,y)->piece->setCaptured(true);
	board->getSquare(position->x,position->y)->piece = NULL;
	pos_back = position;
	position->next = new Position();
	position = position->next;
	position->x = x; 
	position->y = y;
	position->turn = board->getTurn();
	board->getSquare(position->x,position->y)->piece = this;
	std::cout<<"piece at: "<<position_first->x<<","<<position_first->y<<"\n";
//	board->deselect();
//	board->switchTurn();
}

void Pawn::setActive(){
	int x = position->x;
	int y = position->y;
	Square *tmpsqr;
	int moves = position_first->next ? 1 : 2;
	for (int i=0; i<moves; i++){
		y += team == WHITE ? -1 : 1;
		if ((x>-1 && y>-1) && (x<8 && y<8)){
			tmpsqr = board->getSquare(x,y);
			tmpsqr->active = true;
			if (tmpsqr->piece){
				if (tmpsqr->piece->getTeam() == this->getTeam())
					tmpsqr->active = false;
			}
		}
	}
	y = position->y;
	y += team == WHITE ? -1 : 1;
	x--;
	if ((x>-1 && y>-1) && (x<8 && y<8)){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
		}
		else tmpsqr->active = false;
	}
	x+=2;
	if ((x>-1 && y>-1) && (x<8 && y<8)){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
		}
		else tmpsqr->active = false;
	}
}
Pawn::Pawn(){
	type = PAWN;
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
