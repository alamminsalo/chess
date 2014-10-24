#include <SFML/Graphics.hpp>
#include <iostream>
#include "lauta.h"
#include "globals.h"
#include "pelaaja.h"

sf::RenderWindow window;
Lauta *lauta;
Pelaaja *pelaaja1;
Pelaaja *pelaaja2;

int main()
{
    window.create(sf::VideoMode(gl::WIDTH,gl::HEIGHT), "chess!");

	lauta = new Lauta();
	pelaaja1 = new Pelaaja(0,*lauta);
	pelaaja2 = new Pelaaja(1,*lauta);	

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		lauta->piirra(window);
        window.display();
    }
	delete [] lauta;

    return 0;
}
