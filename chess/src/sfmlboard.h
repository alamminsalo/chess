#ifndef SFMLBOARD_H
#define SFMLBOARD_H

#define WIDTH 640
#define HEIGHT 640

#include <SFML/Graphics.hpp>
#include "board.h"

class BoardGUI: public sf::RenderWindow{
	protected:
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

		void setup();
		void run();
		void update();
		void getInput();
		void manage();

	public:
		BoardGUI();
		~BoardGUI();
};

#endif
