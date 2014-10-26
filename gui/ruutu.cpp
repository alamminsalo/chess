#include "ruutu.h"

Ruutu::Ruutu(){
	nappula = NULL;
	active = false;
	this->setFillColor(sf::Color::Green);
};

Ruutu::~Ruutu(){

};

bool Ruutu::hasNappula(){
	return nappula == NULL ? false : true;
};

Nappula* Ruutu::getNappula(){
	return nappula;
};

void Ruutu::setNappula(Nappula &n){
	if (hasNappula())
		nappula->setPelissa(false);
	nappula = &n;
	nappula->setPosition(this->getPosition());
};

void Ruutu::setActive(bool b){
	active = b;
};	

bool Ruutu::isActive(){
	return active;
};

void Ruutu::piirra(sf::RenderWindow &w){
	if (active)
		w.draw(*this);
	if (hasNappula())
		w.draw(*nappula);
};

void Ruutu::setKoordinaatti(int x, int y){
	this->koordinaatti.x = x;
	this->koordinaatti.y = y;
};

sf::Vector2i Ruutu::getKoordinaatti(){
	return koordinaatti;
};
