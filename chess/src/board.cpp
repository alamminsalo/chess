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
		piece->setActive();		
		selected = piece;
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
	if (selected)
		selected->clearActiveList();
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

	 if (black.hasturn) std::cout<<"Black has turn.\n";
	 if (white.hasturn) std::cout<<"White has turn.\n";
 }

bool Board::teamOnCheck(){
	if (white.oncheck || black.oncheck) return true;
	return false;
}

void Board::setCheck(unsigned short team){
	if (team == 0)
		white.oncheck = true;
	else black.oncheck = true;
}

void Board::checkPositions(){
	black.oncheck = white.oncheck = false;
	int x, y;
	for (int i=0; i<16; i++){
		if (!black.piece[i]->isCaptured()){
			select(black.piece[i]);
			x = white.piece[15]->getX();
			y = white.piece[15]->getY();
			if (square[x][y].active){
				white.oncheck = true;
				std::cout<<"White on check!\n";
			}
		}
		if (!white.piece[i]->isCaptured()){
			select(white.piece[i]);
			x = black.piece[15]->getX();
			y = black.piece[15]->getY();
			if (square[x][y].active){
				black.oncheck = true;
				std::cout<<"Black on check!\n";
			}
		}
	//	if (!getInactiveTeam()->piece[i]->isCaptured()){
	//		select(getInactiveTeam()->piece[i]);
	//		if (square[getActiveTeam()->piece[15]->getX()][getActiveTeam()->piece[15]->getY()].active){
	//			getActiveTeam()->oncheck = true;
	//			return;
	//		}
	//	}
	}
}

int Board::moveSelected(int x, int y){
	Piece *pc = square[x][y].piece ? square[x][y].piece : NULL;

	selected->move(x,y);
	Piece *tmp_sel = selected;

	checkPositions();
	if (getActiveTeam()->oncheck){
		std::cout<<"ERROR: Move puts this team on check.\n";	
		tmp_sel->revert();
		if (pc){
			square[x][y].piece = pc;
			square[x][y].piece->setCaptured(false);
		}
		deselect();
		return -1;
	}
	else{
		switchTurn();
		//if (evaluateMate() == 1){
		//	std::cout<<"CHECKMATE\nGAME OVER.\n";
		//}
		deselect();
	}
	return 0;
}

int Board::evaluateMate(){
	for (int i=0; i<16; i++){
		select(getActiveTeam()->piece[i]);
		Position *pos = selected->getActiveBegin();
		//std::cout<<"Evaluating legal moves for piece "<<i<<"...";
		//std::cout<<selected->getName()<<std::endl;
		std::cout<<"Simulating piece["<<i<<"]: "<<selected->getName()<<" at "<<selected->getX()<<","<<selected->getY()<<std::endl;
		while (pos){
			int x = pos->x; 
			int y = pos->y;
			Piece *pc = square[x][y].piece ? square[x][y].piece : NULL;
			selected->move(x,y);
			Piece *tmp_sel = selected;
			checkPositions();
			tmp_sel->revert();
			if (pc){
				square[x][y].piece = pc;
				square[x][y].piece->setCaptured(false);
			}
			if (!getActiveTeam()->oncheck){
				std::cout<<"\tFound possible move.\n";
				return 0;
			}
			else std::cout<<"\t...\n";
			pos = pos->next;
		}
		std::cout<<"Next piece:\n";
	}	
	return 1;
}

