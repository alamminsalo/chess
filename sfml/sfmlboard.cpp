#include "sfmlboard.h"

BoardGUI::BoardGUI(){

	if (!bgtex.loadFromFile("../img/chessboard.gif"))
			std::cout << "Error loading background file.\n";
	background.setTexture(&bgtex);
	background.setSize(sf::Vector2f(640,640));

	buttontex.loadFromFile("../img/buttons.png");
	for (int i=0; i<16; i++){
		blackButtons[i].setTexture(&buttontex);
		whiteButtons[i].setTexture(&buttontex);
	}

	font.loadFromFile("./LemonMilk.otf");
	statusText.setFont(font);
	statusText.setCharacterSize(16);
	statusText.setPosition(0,HEIGHT-16);
	statusText.setColor(sf::Color::Blue);

	gameBoard = new Board();
	whiteteam = gameBoard->getTeam(0);
	blackteam = gameBoard->getTeam(1);

	player = NULL;

	setup();
}

BoardGUI::BoardGUI(std::string addr, unsigned short port){
	if (!bgtex.loadFromFile("../img/chessboard.gif"))
			std::cout << "Error loading background file.\n";
	background.setTexture(&bgtex);
	background.setSize(sf::Vector2f(640,640));

	buttontex.loadFromFile("../img/buttons.png");
	for (int i=0; i<16; i++){
		blackButtons[i].setTexture(&buttontex);
		whiteButtons[i].setTexture(&buttontex);
	}

	font.loadFromFile("./LemonMilk.otf");
	statusText.setFont(font);
	statusText.setCharacterSize(16);
	statusText.setPosition(0,HEIGHT-16);
	statusText.setColor(sf::Color::Black);

	gameBoard = new Board();
	whiteteam = gameBoard->getTeam(0);
	blackteam = gameBoard->getTeam(1);

	player = NULL;

	setup();

	host = sf::IpAddress(addr);
	this->port = port;
	connectToServer();

//	sf::Thread thread(&BoardGUI::listenThread,this);
//	thread.launch();
}

void BoardGUI::connectToServer(){
	player = new Player();
	statusText.setString("CONNECTING...");
	if (socket.connect(host,port,sf::seconds(10)) != sf::Socket::Done){
		std::cout<<"Error connecting to server. Closing..\n";
	}
	char buf[8];
	std::size_t bufsize;
	std::string data;
	while(true){
		socket.receive(buf,8,bufsize);
		data = buf;
		std::cout<<data;
		if (data == "black\n"){
			player->team = blackteam;
			for (int i=0; i<16; i++)
				player->buttons[i] = &blackButtons[i];
			std::cout<<"Received: "<<data;
			break;
		}
		else if (data =="white\n"){
			player->team = whiteteam;
			for (int i=0; i<16; i++)
				player->buttons[i] = &whiteButtons[i];
			std::cout<<"Received: "<<data;
			break;
		}
	}
	data.clear();
	statusText.setString("OK");

}

BoardGUI::~BoardGUI(){
}

void BoardGUI::setup(){
	this->create(sf::VideoMode(640,640),"CHESS GAME");
	this->setFramerateLimit(30);
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
	while (this->isOpen()){
		sf::Event event;
		while(this->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				this->close();
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					getInput();
				}
				if (event.mouseButton.button == sf::Mouse::Right)
					gameBoard->deselect();
			}
		}

		manage();

		update();

		clear();

		draw(background);
		draw(statusText);
		for (int y=0; y<8; y++)
			for (int x=0; x<8; x++)
				draw(square[x][y]);
		for (int i=0; i<16; i++){
			draw(blackButtons[i]);
			draw(whiteButtons[i]);
		}

		this->display();

		if (player){
			if (!player->team->hasturn)
				getMoveFromServer();
		}
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

	//DEBUGGING..
	for (int y=0; y<8;y++)
		for (int x=0;x<8;x++)
			if (square[x][y].getGlobalBounds().contains(mpos.x,mpos.y) && gameBoard->getSquare(x,y)->piece){
				Piece *piece = gameBoard->getSquare(x,y)->piece;
				std::cout<<"DEBUG: piece "<<piece->getName()<<", "<<(piece->getTeam() == 0 ? "WHITE" : "BLACK")<<" at "<<piece->getX()<<","<<piece->getY()<<" is "<<(piece->isCaptured() ? "CAPTURED" : "NOT CAPTURED")<<std::endl;
			}

	if (gameBoard->getSelected()){
		int bX = gameBoard->getSelected()->getX();
		int bY = gameBoard->getSelected()->getY();
		for (int y=0; y<8; y++)
			for (int x=0; x<8; x++){
				if (square[x][y].getGlobalBounds().contains(mpos.x,mpos.y)){
					if (player){
						if (gameBoard->moveSelected(x,y) == 0){
							postMoveToServer(bX,bY,x,y);
						}
					}
					else gameBoard->moveSelected(x,y);
				}
			}
	}
	else if (!player){								//LOKAALI PELI
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
	else if (player->team->hasturn){			//TCP_PELI
		for (int i=0; i<16; i++){
			if (player->buttons[i]->getGlobalBounds().contains(mpos.x,mpos.y)){
				gameBoard->select(player->team->piece[i]);
			}
		}
	}
}

void BoardGUI::manage(){
	for (int y=0; y<8; y++)
		for (int x=0; x<8; x++){
			square[x][y].setFillColor(sf::Color::Transparent);
			if (gameBoard->isActiveSquare(x,y)){
				square[x][y].setFillColor(sf::Color::Green);
			}
		}
	switch (gameBoard->getStatus()){
		case STATUS_NOCHECK:
			statusText.setString("");
			break;
		case STATUS_CHECK:
			statusText.setString("CHECK");
			break;
		case STATUS_CHECKMATE:
			statusText.setString("CHECKMATE");
			break;
		case STATUS_STALEMATE:
			statusText.setString("STALEMATE");
			break;
	}
}

void BoardGUI::postMoveToServer(int bx,int by,int x,int y){
	char buf[6] = {(char)(bx+48),(char)(by+48),(char)(x+48),(char)(y+48),'\n'};
	std::cout<<buf<<std::endl;
	socket.send(buf,6);
}

void BoardGUI::getMoveFromServer(){
	statusText.setString("Waiting for opponent's move..");
	int bx,by,x,y;
	char buf[5];
	std::size_t datasize;

	socket.receive(buf,5,datasize);
	std::cout<<buf;

	bx = (int)buf[0]-48;
	by = (int)buf[1]-48;
	x = (int)buf[2]-48;
	y = (int)buf[3]-48;
	
	if (gameBoard->selectPieceAt(bx,by))
		gameBoard->moveSelected(x,y);

	statusText.setString("");
}

void BoardGUI::listenThread(){
	sf::Clock timer;
	while(this->isOpen()){
		if (timer.getElapsedTime().asSeconds() > 1){
			if (!player->team->hasturn)
				getMoveFromServer();
			timer.restart();
		}
	}
}

