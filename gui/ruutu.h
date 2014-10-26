#ifndef RUUTU
#define RUUTU

#include <SFML/Graphics.hpp>
#include "nappulat.h"

class Ruutu: public sf::RectangleShape{
protected:
	Nappula *nappula;
	sf::Vector2i koordinaatti;
	bool active;
public:
	Ruutu();
	~Ruutu();
	bool hasNappula();
	Nappula* getNappula();
	void setNappula(Nappula&);
	void piirra(sf::RenderWindow &w);
	void setActive(bool);
	bool isActive();
	void setKoordinaatti(int,int);
	sf::Vector2i getKoordinaatti();
};

#endif
