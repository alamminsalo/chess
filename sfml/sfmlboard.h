#ifndef SFMLBOARD_H
#define SFMLBOARD_H

#define WIDTH 640
#define HEIGHT 640

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../logic/src/board.h"

struct Player{
	Team *team;
	sf::RectangleShape *buttons[16];	
};

class BoardGUI: public sf::RenderWindow{
	protected:
		sf::TcpSocket socket;
		sf::IpAddress host;
		unsigned short port;

		Team *blackteam;
		Team *whiteteam;

		sf::Text statusText;
		sf::Font font;

		Board *gameBoard;

		sf::Texture buttontex;
		sf::RectangleShape blackButtons[16];
		sf::RectangleShape whiteButtons[16];

		sf::Texture bgtex;
		sf::RectangleShape background;

		sf::RectangleShape square[8][8];

		Player *player;

		void setup();
		void update();
		void getInput();
		void manage();
		bool socketOn;
		void connectToServer();
		void getMoveFromServer();
		void postMoveToServer(int,int,int,int);
		void listenThread();

	public:
		BoardGUI();
		BoardGUI(std::string,unsigned short);
		~BoardGUI();
		void run();
};

#endif

