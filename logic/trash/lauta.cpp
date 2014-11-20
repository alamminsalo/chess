#include "lauta.h"

Lauta::Lauta(){
	taustatex.loadFromFile("chessboard.gif");
	tausta.setTexture(&taustatex);
	tausta.setSize(sf::Vector2f(gl::WIDTH,gl::HEIGHT));
	
	nappulatex.loadFromFile("buttons.png");
	int divx = nappulatex.getSize().x / 6;
	int divy = nappulatex.getSize().y / 12;

	float scaleX = (tausta.getSize().x / 8) / divx;
	float scaleY = (tausta.getSize().y / 8) / divy;

	std::cout << scaleX << std::endl;
	std::cout << scaleY << std::endl;

	int my=0, vy=1;

	for (int i=0; i<8; i++){
		for (int ii=0; ii<8; ii++){
			ruudut[ii][i].setPosition(tausta.getSize().x / 8 * ii,tausta.getSize().y / 8 * i);
			ruudut[ii][i].setSize(sf::Vector2f(tausta.getSize().x/8,tausta.getSize().y/8));
		}
	}

	int jarjestys[8] = {0,7,1,6,2,5,3,4};

	for (int x=0,i=0,rivi=1; i<16; i++){
		switch(i){
			case 8: 
				rivi--;
			case 10: 
			case 12: 
			case 14: 
			case 15:
				x++;
		}

		if (x==0){
			mustat[i] = Sotilas();
			valkoiset[i] = Sotilas();
		}
		if (x==1){
			mustat[i] = Torni();
			valkoiset[i] = Torni();
		}
		if (x==2){
			mustat[i] = Ratsu();
			valkoiset[i] = Ratsu();
		}
		if (x==3){
			mustat[i] = Lahetti();
			valkoiset[i] = Lahetti();
		}
		if (x==4){
			mustat[i] = Kuningatar();
			valkoiset[i] = Kuningatar();
		}
		if (x==5){
			mustat[i] = Kuningas();
			valkoiset[i] = Kuningas();
		}

		mustat[i].setTexture(&nappulatex);
		mustat[i].setTextureRect(sf::IntRect(divx*x,divy*my,divx,divy));
		mustat[i].setSize(divx,divy);
		mustat[i].setScale(scaleX,scaleY);

		valkoiset[i].setTexture(&nappulatex);
		valkoiset[i].setTextureRect(sf::IntRect(divx*x,divy*vy,divx,divy));
		valkoiset[i].setSize(divx,divy);
		valkoiset[i].setScale(scaleX,scaleY);

		ruudut[jarjestys[i % 8]][rivi].setNappula(valkoiset[i]);
		ruudut[jarjestys[i % 8]][7-rivi].setNappula(mustat[i]);
	}

//	for (int j=0; j<8; j++){
//		ruudut[j][1].setNappula(valkoiset[j]);
//		ruudut[j][6].setNappula(mustat[j]);
//	}
//	ruudut[0][0].setNappula(valkoiset[12]);
//	ruudut[7][0].setNappula(valkoiset[13]);
	

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
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++)
			ruudut[j][i].piirra(w);
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

void Lauta::liikuta(sf::Vector2i mp){
	for (int y=0; y<8; y++)
		for (int x=0; x<8; x++)
			if (ruudut[x][y].getGlobalBounds().contains(mp.x,mp.y)){
				if (ruudut[x][y].isActive())
					ruudut[x][y].setNappula(*valinta);
				valinta = NULL;
				break;
			}
	// Tänne kaikkien ruutujen aktiivisuuden resettaus
};

void Lauta::setValinta(sf::Vector2i mp){
	for (int y=0; y<8; y++)
		for (int x=0; x<8; x++)
			if (ruudut[x][y].getGlobalBounds().contains(mp.x,mp.y)){
				if (ruudut[x][y].hasNappula()){
					valinta = ruudut[x][y].getNappula();

				}
				break;
			}
	// Tänne logiikka millä asetetaan aktiivisiksi ruudut joihin voidaan liikkua!
	// Esim. if (valinta->getId == 1), niin sotilaslogiikka eli yksi ruutu eteenpäin laudalla 
};

bool Lauta::onValinta(){
	return valinta == NULL ? false : true;
};
