#include "piece.h"

Piece::Piece(){
	type = NOTYPE;
	captured = false;
}

Piece::~Piece(){
	Position *pDel;
	while (position_root){
		pDel = position_root;
		position_root = position_root->next;
		delete pDel;
	}	
}

void Piece::revert(){
    board->getSquare(position->x,position->y)->piece = NULL;

	Position *pos_back = position_root;
	while (pos_back->next != position)
		pos_back = pos_back->next;
	board->getSquare(pos_back->x,pos_back->y)->piece = this;

	delete position;
	position = pos_back;
	position->next = NULL;

	std::cout<<"Reverted move\n";
}

void Piece::setup(int x, int y, Board *b){
	position = new Position;
	position->x = x;
	position->y = y;	
	position_root = position;

    position->next = NULL;

	board = b;
	board->getSquare(x,y)->piece = this;
}

void Piece::addPosition(int x,int y){
	position->next = new Position;
	position = position->next;
	position->x = x; 
	position->y = y;
	position->turn = board->getTurn();
	position->next = NULL;
}

void Piece::addActive(int x, int y){
	if (!active_root){
		active_root = new Position;
		active = active_root;	
	}
	else{
		active->next = new Position;
		active = active->next;
	}
	active->x = x;
	active->y = y;
	active->next = NULL;
	std::cout<<"Added active!\n";

	Position *tmp = active_root;
	while (tmp){
		std::cout<<"next\n";
		if(tmp->next)
			tmp = tmp->next;
		else break;
	}
}

void Piece::clearActiveList(){
	Position *tmp;
	while (active_root){
		tmp = active_root;
		active_root = active_root->next;
		delete tmp;
	}
	std::cout<<"Cleared active list\n";
}

Position* Piece::getActivePositionRoot(){
	return active_root;
}

void Piece::move(int x,int y){
	if (board->getSquare(x,y)->piece){
		board->getSquare(x,y)->piece->setCaptured(true);
	}
	board->getSquare(position->x,position->y)->piece = NULL;
	board->getSquare(x,y)->piece = this;
	addPosition(x,y);
}

void Pawn::setActive(){
	int x = position->x;
	int y = position->y;
	Square *tmpsqr;
    int moves = (position_root->next) ? 1 : 2;
	for (int i=0; i<moves; i++){
		y += team == WHITE ? -1 : 1;
		if ((x>-1 && y>-1) && (x<8 && y<8)){
			tmpsqr = board->getSquare(x,y);
			tmpsqr->active = true;
			if (tmpsqr->piece){
				tmpsqr->active = false;
			}
			//if (tmpsqr->active) addActive(x,y);
		}
	}
	y = position->y;
	y += team == WHITE ? -1 : 1;
	x--;
	if ((x>-1 && y>-1) && (x<8 && y<8)){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = false;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() != this->getTeam()){
				tmpsqr->active = true;
			}
			//if (tmpsqr->active) addActive(x,y);
		}
	}
	x+=2;
	if ((x>-1 && y>-1) && (x<8 && y<8)){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = false;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() != this->getTeam())
				tmpsqr->active = true;
			//if (tmpsqr->active) addActive(x,y);
		}
	}
}
Pawn::Pawn(){
	type = PAWN;
}

Bishop::Bishop(){
	type = BISHOP;
}
Rook::Rook(){
	type = ROOK;
}
Knight::Knight(){
	type = KNIGHT;
}
Queen::Queen(){
	type = QUEEN;
}
King::King(){
	type = KING;
}

void Bishop::setActive(){
	//std::cout<<"Selected "<<getName()<<std::endl;
	Square *tmpsqr;
	for (int y=position->y-1, x=position->x-1; x>-1 && y>-1; x--,y--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			//if (tmpsqr->active) addActive(x,y);
			break;
		}
	}
	for (int y=position->y+1, x=position->x+1; x<8 && y<8; x++,y++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			//if (tmpsqr->active) addActive(x,y);
			break;
		}
	}
	for (int y=position->y-1, x=position->x+1; x<8 && y>-1; x++, y--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			//if (tmpsqr->active) addActive(x,y);
			break;
		}
	}
	for (int y=position->y+1, x=position->x-1; y<8 && x>-1; x--,y++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			//if (tmpsqr->active) addActive(x,y);
			break;
		}
	}
}

void Knight::setActive(){
	//std::cout<<"Selected "<<getName()<<std::endl;
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
				//if (tmpsqr->active) addActive(x,y);
			}
		}
	}
}

void Rook::setActive(){
	//std::cout<<"Selected "<<getName()<<std::endl;
	Square *tmpsqr;
	for (int y=position->y, x=position->x-1; x>-1; x--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			//if (tmpsqr->active) addActive(x,y);
			break;
		}
	}
	for (int y=position->y, x=position->x+1; x<8; x++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			//if (tmpsqr->active) addActive(x,y);
			break;
		}
	}
	for (int y=position->y-1, x=position->x; y>-1; y--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			//if (tmpsqr->active) addActive(x,y);
			break;
		}
	}
	for (int y=position->y+1, x=position->x; y<8; y++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			//if (tmpsqr->active) addActive(x,y);
			break;
		}
	}
}

void Queen::setActive(){
	//std::cout<<"Selected "<<getName()<<std::endl;
	Rook::setActive();
	Bishop::setActive();	
}

void King::setActive(){
	//std::cout<<"Selected "<<getName()<<std::endl;
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
				//if (tmpsqr->active) addActive(x,y);
			}
		}
	}
}
