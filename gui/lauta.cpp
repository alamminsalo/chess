#include "lauta.h"

Lauta::Lauta(){
	for (int i=0; i<16; i++){
		if (i < 8){
			mustat[i] = Sotilas();
			valkoiset[i] = Sotilas();
			break;
		}	
		if (i < 10){
			mustat[i] = Torni();
			valkoiset[i] = Torni();
			break;
		}
		if (i < 12){
			mustat[i] = Lahetti();
			valkoiset[i] = Lahetti();
		}
		if (i < 14){
			mustat[i] = Ratsu();
			valkoiset[i] = Ratsu();
			break;
		}
		if (i < 15){
			mustat[i] = Kuningatar();
			valkoiset[i] = Kuningatar();
			break;
		}
		if (i < 16){
			mustat[i] = Kuningas();
			valkoiset[i] = Kuningas();
		}
	}
	taustatex.loadFromFile("chessboard.gif");
	tausta.setTexture(&taustatex);
	tausta.setSize(sf::Vector2f(gl::WIDTH,gl::HEIGHT));

	for (int i=0; i<8; i++){
		for (int ii=0; ii<8; ii++){
			ruudut[i][ii] = sf::Vector2f(gl::WIDTH/8*i,gl::HEIGHT/8*ii);
		}
	}
};

Lauta::~Lauta(){
	delete [] &tausta;
	delete [] &taustatex;
	delete [] mustat;
	delete [] valkoiset;
};

void Lauta::piirra(sf::RenderWindow &w){
	w.draw(tausta);
	for (int i=0; i<16; i++){
		if (mustat[i]->onPelissa())
			w.draw(mustat[i]);
		if (valkoiset[i]->onPelissa())
			w.draw(valkoiset[i]);
	}
};

Nappula* Lauta::getMustat(){
	return mustat;
};

Nappula* Lauta::getValkoiset(){
	return valkoiset;
};

bool Lauta::kaynnissa(){
	return pelikaynnissa;
};
