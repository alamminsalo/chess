#include <SFML/Graphics.hpp>
#include <iostream>
#include "lauta.h"
#include "globals.h"
#include "classes/board.h"

sf::RenderWindow window;
Lauta *lauta;

int main()
{
    window.create(sf::VideoMode(gl::WIDTH,gl::HEIGHT), "chess!");
	window.setFramerateLimit(15);

	lauta = new Lauta();


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button== sf::Mouse::Left){
					if (lauta->onValinta())
						lauta->liikuta(sf::Mouse::getPosition(window));
					else lauta->setValinta(sf::Mouse::getPosition(window));
				}
        }
        window.clear();
		lauta->piirra(window);
        window.display();
    }
	delete lauta;

    return 0;
}
