#include "piece.h"

Piece::Piece(){
	type = NOTYPE;
	captured = false;
	pos_active_start = pos_active_tail = pos_active_current = NULL;
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

void Piece::createMovementList(){
	for (int y=0; y<8; y++)
		for (int x=0; x<8; x++){
			if (board->getSquare(x,y)->active){
				if (!pos_active_tail){
					pos_active_start = pos_active_tail = new Position();
				}
				else {
					pos_active_tail->next = new Position();
					pos_active_tail = pos_active_tail->next;
				}
				pos_active_tail->x = x;
				pos_active_tail->y = y;
			}
		}			
	pos_active_current = pos_active_start;
	while (pos_active_current){
		std::cout<<"Active square at "<<pos_active_current->x<<","<<pos_active_current->y<<"\n";
		pos_active_current = pos_active_current->next;
	}
}

void Piece::clearActiveList(){
	pos_active_current = pos_active_start;
	while (pos_active_current){
		pos_active_start = pos_active_current;
		pos_active_current = pos_active_current->next;
		delete pos_active_start;
	}	
	pos_active_start = pos_active_tail = pos_active_current = NULL;
	std::cout<<"Cleared active movement list!\n";
}

void Piece::toActiveList(int x, int y){
	if (!pos_active_tail)
		pos_active_start = pos_active_current = pos_active_tail = new Position();
	else {
		pos_active_tail->next = new Position();
		pos_active_tail = pos_active_tail->next;
	}
	pos_active_tail->x = x;
	pos_active_tail->y = y;
	pos_active_tail->next = NULL;
}

Position* Piece::getActiveBegin(){
	return pos_active_start;
}

void Piece::revert(){
	std::cout<<"Reverting..\n";
	//move(pos_back->x,pos_back->y);

	board->getSquare(pos_back->x,pos_back->y)->piece = this;
	board->getSquare(position->x,position->y)->piece = NULL;

	delete position;
	position = pos_back;
	position->next = NULL;

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
	std::cout<<"::MOVE START.::\n";
	std::cout<<"-->TARGET SQUARE AT "<<x<<", "<<y<<"\n";
	if (board->getSquare(x,y)->piece){
		std::cout<<"-->CAPTURING PIECE..."<<board->getSquare(x,y)->piece->getName()<<"\n";
		board->getSquare(x,y)->piece->setCaptured(true);
		std::cout<<"-->PIECE CAPTURED\n";
	}
	std::cout<<"-->SETTING SELECTED SQUARE NULL\n";
	board->getSquare(position->x,position->y)->piece = NULL;
	pos_back = position;

	std::cout<<"-->CREATING NEW POSITION...";
	position->next = new Position();
	position = position->next;
	position->x = x; 
	position->y = y;
	position->turn = board->getTurn();
	position->next = NULL;
	std::cout<<"DONE.\n";

	std::cout<<"-->SETTING SELECTED SQUARE TO THIS PIECE\n";
	board->getSquare(position->x,position->y)->piece = this;
	std::cout<<"::MOVE END.::\n";
	//std::cout<<"piece at: "<<position->x<<","<<position->y<<"\n";
//	board->deselect();
//	board->switchTurn();
}

void Pawn::setActive(){
	std::cout<<"Selected "<<getName()<<std::endl;
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
				tmpsqr->active = false;
			}
			if (tmpsqr->active) toActiveList(x,y);
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
		if (tmpsqr->active) toActiveList(x,y);
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
		if (tmpsqr->active) toActiveList(x,y);
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
	std::cout<<"Selected "<<getName()<<std::endl;
	Square *tmpsqr;
	for (int y=position->y-1, x=position->x-1; x>-1 && y>-1; x--,y--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			if (tmpsqr->active) toActiveList(x,y);
			break;
		}
	}
	for (int y=position->y+1, x=position->x+1; x<8 && y<8; x++,y++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			if (tmpsqr->active) toActiveList(x,y);
			break;
		}
	}
	for (int y=position->y-1, x=position->x+1; x<8 && y>-1; x++, y--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			if (tmpsqr->active) toActiveList(x,y);
			break;
		}
	}
	for (int y=position->y+1, x=position->x-1; y<8 && x>-1; x--,y++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			if (tmpsqr->active) toActiveList(x,y);
			break;
		}
	}
}

void Knight::setActive(){
	std::cout<<"Selected "<<getName()<<std::endl;
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
			if (tmpsqr->active) toActiveList(x,y);
		}
	}
}

void Rook::setActive(){
	std::cout<<"Selected "<<getName()<<std::endl;
	Square *tmpsqr;
	for (int y=position->y, x=position->x-1; x>-1; x--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			if (tmpsqr->active) toActiveList(x,y);
			break;
		}
	}
	for (int y=position->y, x=position->x+1; x<8; x++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			if (tmpsqr->active) toActiveList(x,y);
			break;
		}
	}
	for (int y=position->y-1, x=position->x; y>-1; y--){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			if (tmpsqr->active) toActiveList(x,y);
			break;
		}
	}
	for (int y=position->y+1, x=position->x; y<8; y++){
		tmpsqr = board->getSquare(x,y);
		tmpsqr->active = true;
		if (tmpsqr->piece){
			if (tmpsqr->piece->getTeam() == this->getTeam())
				tmpsqr->active = false;
			if (tmpsqr->active) toActiveList(x,y);
			break;
		}
	}
}

void Queen::setActive(){
	std::cout<<"Selected "<<getName()<<std::endl;
	Rook::setActive();
	Bishop::setActive();	
}

void King::setActive(){
	std::cout<<"Selected "<<getName()<<std::endl;
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
			if (tmpsqr->active) toActiveList(x,y);
		}
	}
}
