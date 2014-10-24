#ifndef LAUTA
#define LAUTA

#include <SFML/Graphics.hpp>
#include "nappulat.h"
#include <iostream>
#include "globals.h"

class Lauta{

protected:
	sf::Vector2f ruudut[8][8];
	Nappula mustat[16];
	Nappula valkoiset[16];
	bool pelikaynnissa;
	sf::Texture taustatex;
	sf::Texture nappulatex;
	sf::RectangleShape tausta;
public:
	Lauta();
	~Lauta();
	void piirra(sf::RenderWindow&);
	Nappula* getMustat();
	Nappula* getValkoiset();
	bool kaynnissa();
};

#endif
