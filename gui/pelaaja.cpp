#include "pelaaja.h"

Pelaaja::Pelaaja(int id, Lauta &l){
	lauta = &l;
	if (id == 0)
		nappulat = lauta->getMustat();
	else nappulat = lauta->getValkoiset();
};

Pelaaja::~Pelaaja(){ //Destruktori

};

void Pelaaja::siirra(int i, int x, int y){
	nappulat[i].setPaikka(x,y);
};

void Pelaaja::poista(int i){ //Poistetaan pelaajalta nappula
	nappulat[i].setPelissa(false);
};
