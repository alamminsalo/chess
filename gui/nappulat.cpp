#include "nappulat.h"

Nappula::Nappula(){
	pelissa = true;
};

Nappula::~Nappula(){

};

void Nappula::liiku(){

};

void Nappula::setPaikka(int xpos, int ypos){
	x = xpos; y = ypos;
};

int Nappula::getTyyppi(){
	return tyyppi;
};

bool Nappula::onPelissa(){
	return pelissa;
};

void Nappula::setSize(int x, int y){
	sf::RectangleShape::setSize(sf::Vector2f(x,y));
};

Sotilas::Sotilas(){
	std::cout << "Alustettiin sotilas\n";
	tyyppi = 1;
};
Sotilas::~Sotilas(){};

Lahetti::Lahetti(){
	tyyppi = 2;
};
Lahetti::~Lahetti(){};

Ratsu::Ratsu(){
	tyyppi = 3;
};
Ratsu::~Ratsu(){};

Torni::Torni(){
	tyyppi = 4;
};
Torni::~Torni(){};

Kuningatar::Kuningatar(){
	tyyppi = 5;
};
Kuningatar::~Kuningatar(){};

Kuningas::Kuningas(){
	tyyppi = 6;
};
Kuningas::~Kuningas(){};

