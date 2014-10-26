#ifndef LAUTA
#define LAUTA

#include <SFML/Graphics.hpp>
#include "nappulat.h"
#include <iostream>
#include "globals.h"
#include "ruutu.h"

class Lauta{

protected:
	Ruutu ruudut[8][8];	
	Nappula mustat[16];
	Nappula valkoiset[16];
	Nappula *valinta;
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
	bool onValinta();
	void liikuta(sf::Vector2i);
	void setValinta(sf::Vector2i);
};

#endif
