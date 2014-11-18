#include "sfmlboard.h"

int main(int argc, char *argv[]){
	BoardGUI *gameboard;
	if (argc == 1)
	gameboard = new BoardGUI();
	else {
		if (argc != 3)
			return -1;
		std::cout<<"Connecting to "<<argv[1]<<":"<<argv[2]<<"...\n";
		gameboard = new BoardGUI(argv[1],std::atoi(argv[2]));
	}
	gameboard->run();
	return 0;
};
