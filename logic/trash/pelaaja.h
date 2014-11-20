#ifndef PELAAJA
#define PELAAJA

#include "lauta.h"
#include "nappulat.h"

class Pelaaja{

protected:
	Lauta *lauta;
	Nappula *nappulat;

public:
	Pelaaja(int,Lauta&);
	~Pelaaja();
	void siirra(int,int,int);
	void poista(int);
};

#endif
