#include "nappulat.h"

Nappula::Nappula(){
	pelissa = true;
};

Nappula::~Nappula(){

};

bool Nappula::onPelissa(){
	return pelissa;
};

void Nappula::setSize(int x, int y){
	sf::RectangleShape::setSize(sf::Vector2f(x,y));
};

sf::Vector2i Nappula::getKoordinaatti(){
	return koordinaatti;
};

void Nappula::setKoordinaatti(int x, int y){
	koordinaatti.x = x;
	koordinaatti.y = y;
};

int Nappula::getId(){
	return id;
};

Sotilas::Sotilas(){
	id = 1;
};
Sotilas::~Sotilas(){};

Lahetti::Lahetti(){
	id = 2;
};
Lahetti::~Lahetti(){};

Ratsu::Ratsu(){
	id = 3;
};
Ratsu::~Ratsu(){};

Torni::Torni(){
	id = 4;
};
Torni::~Torni(){};

Kuningatar::Kuningatar(){
	id = 5;
};
Kuningatar::~Kuningatar(){};

Kuningas::Kuningas(){
	id = 6;
};
Kuningas::~Kuningas(){};

