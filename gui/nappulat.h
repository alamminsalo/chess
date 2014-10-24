#ifndef NAPPULAT
#define NAPPULAT

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Nappula : public sf::RectangleShape{
protected:
	int x,y;
	bool pelissa;
	int tyyppi;

public:
	Nappula();
	~Nappula();
	virtual void liiku();
	void setPaikka( int x,int y);
	int getTyyppi();
	bool onPelissa();
	void setPelissa(bool b){ pelissa = b; };
	void setSize(int,int);
};


class Sotilas : public Nappula{
public:
	Sotilas();
	~Sotilas();
};

class Lahetti : public Nappula{
public:
	Lahetti();
	~Lahetti();
};

class Ratsu : public Nappula{
public:
	Ratsu();
	~Ratsu();
};

class Torni : public Nappula{
public:
	Torni();
	~Torni();
};

class Kuningatar : public Nappula{
public:
	Kuningatar();
	~Kuningatar();
};

class Kuningas : public Nappula{
public:
	Kuningas();
	~Kuningas();
};

#endif
