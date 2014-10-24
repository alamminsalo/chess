#include "lauta.h"

Lauta::Lauta(){
	taustatex.loadFromFile("chessboard.gif");
	tausta.setTexture(&taustatex);
	tausta.setSize(sf::Vector2f(gl::WIDTH,gl::HEIGHT));
	
	nappulatex.loadFromFile("chessbuttons.png");
	int divx = nappulatex.getSize().x / 6;
	int divy = nappulatex.getSize().y / 12;

	int x;
	int my=0, vy=1;
	
	for (int i=0; i<8; i++){
		x = 0;
		mustat[i] = Sotilas();
		valkoiset[i] = Sotilas();
		mustat[i].setTexture(&nappulatex);
		mustat[i].setTextureRect(sf::IntRect(divx*x,divy*my,divx,divy));
		mustat[i].setSize(divx,divy);
		valkoiset[i].setTexture(&nappulatex);
		valkoiset[i].setTextureRect(sf::IntRect(divx*x,divy*vy,divx,divy));
		valkoiset[i].setSize(divx,divy);
	}

	for (int i=0; i<8; i++){
		for (int ii=0; ii<8; ii++){
			ruudut[i][ii] = sf::Vector2f(gl::WIDTH/8*i,gl::HEIGHT/8*ii);
		}
	}

	for (int i=0; i<2; i++){
		for (int j=0; j<8; j++)
			mustat[j*(i+1)].setPosition(ruudut[i][j]);
	};

	std::cout << "Laudan alustus valmis\n";
};

Lauta::~Lauta(){
	delete [] &tausta;
	delete [] &taustatex;
	for (int i=0; i<16; i++){
		delete [] &mustat[i];
		delete [] &valkoiset[i];
	}
};

void Lauta::piirra(sf::RenderWindow &w){
	w.draw(tausta);
	for (int i=0; i<16; i++){
		if (mustat[i].onPelissa())
			w.draw(mustat[i]);
		if (valkoiset[i].onPelissa())
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
