CPP = main.cpp sfmlboard.cpp board.cpp piece.cpp
OBJECTS = main.o sfmlboard.o board.o piece.o
LIBS = -lsfml-window -lsfml-system -lsfml-graphics -lsfml-network

sfml-app: $(OBJECTS)
	clang++ $(OBJECTS) -o sfml-app $(LIBS)

main.o  planet.o ship.o: 
	clang++ -c -Wall $(CPP) -std=gnu++11

clean:
	rm *.o sfml-app 
