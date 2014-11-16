#include "sfmlboard.h"

BoardGUI::BoardGUI(){
	this->create(sf::VideoMode(640,640),"CHESS GAME");

	if (!bgtex.loadFromFile("../img/chessboard.gif"))
			std::cout << "Error loading background file.\n";
	background.setTexture(&bgtex);
	background.setSize(sf::Vector2f(640,640));

	buttontex.loadFromFile("../img/buttons.png");
	for (int i=0; i<16; i++){
		blackButtons[i].setTexture(&buttontex);
		whiteButtons[i].setTexture(&buttontex);
	}

	gameBoard = new Board();
	whiteteam = gameBoard->getTeam(0);
	blackteam = gameBoard->getTeam(1);

	setup();

	run();
}

BoardGUI::~BoardGUI(){
}

void BoardGUI::setup(){
	for (int y=0; y<8; y++)
		for (int x=0; x<8; x++){
			square[x][y].setFillColor(sf::Color::Transparent);
			square[x][y].setSize(sf::Vector2f(WIDTH/8,HEIGHT/8));
			square[x][y].setOrigin(WIDTH/8/2,HEIGHT/8/2);
			square[x][y].setPosition((WIDTH/8/2)+x*(WIDTH/8),(HEIGHT/8/2)+y*(HEIGHT/8));
		}
	std::cout<<"Created squares!\n";
	for (int i=0; i<16; i++){
		switch (blackteam->piece[i]->getType()){
			case PAWN:
				blackButtons[i].setTextureRect(sf::IntRect(0,0,57,90));
				break;
			case KNIGHT:
				blackButtons[i].setTextureRect(sf::IntRect(127,0,82,90));
				break;
			case BISHOP:
				blackButtons[i].setTextureRect(sf::IntRect(209,0,85,90));
				break;
			case ROOK:
				blackButtons[i].setTextureRect(sf::IntRect(58,0,69,90));
				break;
			case QUEEN:
				blackButtons[i].setTextureRect(sf::IntRect(295,0,93,90));
				break;
			case KING:
				blackButtons[i].setTextureRect(sf::IntRect(390,0,80,90));
				break;
		}
		switch (whiteteam->piece[i]->getType()){
			case PAWN:
				whiteButtons[i].setTextureRect(sf::IntRect(0,90,57,90));
				break;
			case KNIGHT:
				whiteButtons[i].setTextureRect(sf::IntRect(127,90,82,90));
				break;
			case BISHOP:
				whiteButtons[i].setTextureRect(sf::IntRect(209,90,85,90));
				break;
			case ROOK:
				whiteButtons[i].setTextureRect(sf::IntRect(58,90,69,90));
				break;
			case QUEEN:
				whiteButtons[i].setTextureRect(sf::IntRect(295,90,93,90));
				break;
			case KING:
				whiteButtons[i].setTextureRect(sf::IntRect(390,90,80,90));
				break;
		}
		blackButtons[i].setSize(sf::Vector2f(blackButtons[i].getTextureRect().width,blackButtons[i].getTextureRect().height));
		blackButtons[i].setOrigin(blackButtons[i].getSize().x/2,blackButtons[i].getSize().y/2);
		whiteButtons[i].setSize(sf::Vector2f(whiteButtons[i].getTextureRect().width,whiteButtons[i].getTextureRect().height));
		whiteButtons[i].setOrigin(whiteButtons[i].getSize().x/2,whiteButtons[i].getSize().y/2);
		blackButtons[i].setScale(0.6,0.6);
		whiteButtons[i].setScale(0.6,0.6);
	}			
}

void BoardGUI::run(){
	sf::Event event;
	while (this->isOpen()){

		while(this->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				this->close();
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left)
					getInput();
				if (event.mouseButton.button == sf::Mouse::Right)
					gameBoard->deselect();
			}
		}

		manage();

		update();

		this->clear();

		draw(background);
		for (int y=0; y<8; y++)
			for (int x=0; x<8; x++)
				draw(square[x][y]);
		for (int i=0; i<16; i++){
			draw(blackButtons[i]);
			draw(whiteButtons[i]);
		}

		this->display();
	}
}

void BoardGUI::update(){
	for (int i=0; i<16; i++){
		if (!blackteam->piece[i]->isCaptured()){
			blackButtons[i].setPosition(square[blackteam->piece[i]->getX()][blackteam->piece[i]->getY()].getPosition());
		}
		else blackButtons[i].setPosition(-999,-999);
		if (!whiteteam->piece[i]->isCaptured()){
			whiteButtons[i].setPosition(square[whiteteam->piece[i]->getX()][whiteteam->piece[i]->getY()].getPosition());
		}
		else whiteButtons[i].setPosition(-999,-999);
	}
}

void BoardGUI::getInput(){
	sf::Vector2i mpos = sf::Mouse::getPosition(*this);
	if (gameBoard->getSelected()){
		for (int y=0; y<8; y++)
			for (int x=0; x<8; x++){
				if (gameBoard->isActiveSquare(x,y) && square[x][y].getGlobalBounds().contains(mpos.x,mpos.y)){
					gameBoard->moveSelected(x,y);
					gameBoard->checkPositions();
				}
			}
	}
	else{
		if (gameBoard->getTeam(0)->hasturn){		//Valkoisen vuoro siirtää
			for (int i=0; i<16; i++){
				if (whiteButtons[i].getGlobalBounds().contains(mpos.x,mpos.y)){
					gameBoard->select(whiteteam->piece[i]);
					break;
				}
			}
		}
		else if (gameBoard->getTeam(1)->hasturn){	//Mustan vuoro
			for (int i=0; i<16; i++){
				if (blackButtons[i].getGlobalBounds().contains(mpos.x,mpos.y)){
					gameBoard->select(blackteam->piece[i]);
					break;
				}
			}
		}
	}
}

void BoardGUI::manage(){
	for (int y=0; y<8; y++)
		for (int x=0; x<8; x++){
			square[x][y].setFillColor(sf::Color::Transparent);
			if (gameBoard->isActiveSquare(x,y))
				square[x][y].setFillColor(sf::Color::Green);
		}
}
