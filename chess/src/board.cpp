#include "board.h"

Board::Board(){
	black.oncheck = false;
	white.oncheck = false;
	black.hasturn = false;
	white.hasturn = true;
	std::cout<<"Created board.\n";
	selected = NULL;
	reset();	
}

Board::~Board(){
	for (int i=0; i<16; i++){
		delete black.piece[i];
		delete white.piece[i];
	}
	std::cout<<"Deleted board.\n";
}

void Board::reset(){
	status = STATUS_NOCHECK;
	for (int y=0; y < 8; y++)
		for (int x=0; x < 8; x++){
			square[x][y].active = false;	
			square[x][y].piece = NULL;
		}
	setupTeamsDefault();
	std::cout<<"Set up teams.\n";
	std::cout<<"White has turn\n";
}

void Board::setupTeamsDefault(){
	int order[8] = {0,7,1,6,2,5,3,4};
	for (int i=0; i<16; i++){
		if (i<8){
			black.piece[i] = new Pawn();
			black.piece[i]->setup(order[i%8],1,this);
			white.piece[i] = new Pawn();
			white.piece[i]->setup(order[i%8],6,this);
		}	
		else switch(i){
			case 8: case 9:
				black.piece[i] = new Rook();
				black.piece[i]->setup(order[i%8],0,this);
				white.piece[i] = new Rook();
				white.piece[i]->setup(order[i%8],7,this);
				break;
			case 10: case 11:
				black.piece[i] = new Knight();
				black.piece[i]->setup(order[i%8],0,this);
				white.piece[i] = new Knight();
				white.piece[i]->setup(order[i%8],7,this);
				break;
			case 12: case 13:
				black.piece[i] = new Bishop();
				black.piece[i]->setup(order[i%8],0,this);
				white.piece[i] = new Bishop();
				white.piece[i]->setup(order[i%8],7,this);
				break;
			case 14:
				black.piece[i] = new Queen();
				black.piece[i]->setup(order[i%8],0,this);
				white.piece[i] = new Queen();
				white.piece[i]->setup(order[i%8],7,this);
				break;
			case 15:
				black.piece[i] = new King();
				black.piece[i]->setup(order[i%8],0,this);
				white.piece[i] = new King();
				white.piece[i]->setup(order[i%8],7,this);
		}
		white.piece[i]->setTeam(0);
		black.piece[i]->setTeam(1);
	}
}

void Board::select(Piece *piece){
	if (piece != selected){
		deselect();
		selected = piece;
		piece->setActive();		
	}
}

bool Board::selectPieceAt(int x, int y){
	if (square[x][y].piece){	
		select(square[x][y].piece);
		return true;
	}
	return false;
}

void Board::deselect(){
	selected = NULL;
	for (int y=0; y < 8; y++)
		for (int x=0; x < 8; x++)
			square[x][y].active = false;
}

Square* Board::getSquare(int x, int y){
	return &square[x][y];
}

bool Board::isActiveSquare(int x, int y){
	return square[x][y].active;
}

int Board::getTurn(){
	return turns;
}
 void Board::switchTurn(){
	turns++;
	black.hasturn = !black.hasturn;
	white.hasturn = !white.hasturn;

	switch (evaluateMate()){
		case 1:
			status = STATUS_CHECKMATE;
			std::cout<<"Checkmate!\n";
			break;
		case 2:
			status = STATUS_STALEMATE;
			std::cout<<"Stalemate!\n";
			break;
		default:
			if (teamOnCheck())
				status = STATUS_CHECK;
			else status = STATUS_NOCHECK;
			if (black.hasturn) std::cout<<"Black has turn.\n";
			else std::cout<<"White has turn.\n";
	}
 }

bool Board::teamOnCheck(){
	return (white.oncheck || black.oncheck) ? true : false;
}

void Board::checkForMate(){
	getActiveTeam()->oncheck = false;	
	for (int i=0; i<16; i++){
		if (getInactiveTeam()->piece[i])
			if (!getInactiveTeam()->piece[i]->isCaptured())
				getInactiveTeam()->piece[i]->setActive();
	}
	if (square[getActiveTeam()->piece[15]->getX()][getActiveTeam()->piece[15]->getY()].active){
		getActiveTeam()->oncheck = true;
	}
	deselect();
}

int Board::simulateMove(Piece *simulated,int x,int y){
	std::cout<<"Simulation: "<<simulated->getName()<<" TO ["<<x<<","<<y<<"]\n";
	deselect();
	Piece *pc = square[x][y].piece;

	simulated->move(x,y);

	checkForMate();
	std::cout<<"\t";
	simulated->revert();
	if (pc){
		square[x][y].piece = pc;
		square[x][y].piece->setCaptured(false);
	}
	std::cout<<"\t";
	if (getActiveTeam()->oncheck){
		std::cout<<"Move not legal\n";
		return -1;
	}
	std::cout<<"Move is legal\n";
	return 0;
}

int Board::moveSelected(int x, int y){
	Piece *tmp_sel = selected;
	if (simulateMove(selected,x,y) == 0){
		tmp_sel->move(x,y);
		switchTurn();
	}
	else {
		std::cout<<"Error: Move puts this team on check.\n";
		return -1;
	}
	return 0;
}

int Board::evaluateMate(){
	checkForMate();
	bool teamoncheck = getActiveTeam()->oncheck;
	Position *pos, *root;
	for (int i=0; i<16; i++){
		if (!getActiveTeam()->piece[i]->isCaptured()){
			root = pos = getActiveList(getActiveTeam()->piece[i]); 
			while (pos){
				if (simulateMove(getActiveTeam()->piece[i],pos->x,pos->y) == 0){
					getActiveTeam()->oncheck = teamoncheck;
					return 0;
				}
				if (!pos->next)
					break;
				pos = pos->next;
			}
			std::cout<<"Arrived to end of list\n";
			deleteActiveList(pos);
			//getActiveTeam()->piece[i]->clearActiveList();
		}
	}	
	getActiveTeam()->oncheck = teamoncheck;
	return teamoncheck ? 1 : 2;
}

Position* Board::getActiveList(Piece *pc){
	select(pc);
	Position *head = NULL;
	Position *tail;
	std::cout<<pc->getName()<<":";

	for (int y=0; y<8; y++){
		for (int x=0; x<8; x++){
			if (square[x][y].active){
				if (!head){
					head = new Position;
					head->x = x;
					head->y = y;
					head->next = NULL;
					tail = head;
				}
				else{
					tail->next = new Position;
					tail->next->x = x;
					tail->next->y = y;
					tail = tail->next;
					tail->next = NULL;
				}
				std::cout<<" -> ["<<x<<","<<y<<"]";
			}
		}
	}
	Position *tmp = head;
	while (tmp){
		std::cout<<"lap";
		if (tmp->next)
			tmp = tmp->next;
		else break;
	}
	if (!head)
		std::cout<<"No possible moves";
	std::cout<<std::endl;
	return head;
}

void Board::deleteActiveList(Position *root){
	Position *tmp;
	while(root){
		tmp = root;	
		root = root->next;
		delete tmp;
	}	
	std::cout<<"Deleted linked list!\n";
}

