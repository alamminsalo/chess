#include "board.h"

Board::Board(){
	black.piece = new Piece*[16];
	black.oncheck = false;
	white.piece = new Piece*[16];
	white.oncheck = false;
	reset();	
	std::cout<<"Created board.\n";
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
		black.piece[i]->setBlackTeam();
	}
}

void Board::select(Piece *piece){
	piece->setActive();		
}

void Board::deselect(){
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

bool Board::getTeam(){
	return (turns % 2 == 0) ? true : false;
}
 void Board::switchTurn(){
	 turns++;
 }

bool Board::teamOnCheck(bool team){
	return team ? white.oncheck : black.oncheck;	
}

void Board::setCheck(bool b){
	if (b)
		white.oncheck = true;
	else black.oncheck = true;
}

void Board::checkPositions(){
	for (int i=0; i<16; i++){
		std::cout<<"Piece at ["<<white.piece[i]->getX()<<","<<white.piece[i]->getY()<<"]\n";
		std::cout<<"Piece at ["<<black.piece[i]->getX()<<","<<black.piece[i]->getY()<<"]\n";
	}	
}
