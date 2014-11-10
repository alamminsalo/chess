CPP = main.cpp lauta.cpp pelaaja.cpp nappulat.cpp ruutu.cpp
OBJECTS = main.o lauta.o pelaaja.o nappulat.o ruutu.o
LIBS = -lsfml-window -lsfml-audio -lsfml-system -lsfml-graphics

sfml-app: $(OBJECTS)
	clang++ $(OBJECTS) -o sfml-app $(LIBS)

main.o  planet.o ship.o: 
	clang++ -c -Wall $(CPP) -std=gnu++11

clean:
	rm *.o sfml-app 
