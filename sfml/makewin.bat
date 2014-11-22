del *.o

g++ -c main.cpp sfmlboard.cpp ../logic/src/board.cpp ../logic/src/piece.cpp -IC:\SFML-2.1\include

g++ main.o sfmlboard.o ../logic/src/board.o ../logic/src/piece.o -o sfml-app.exe -LC:\SFML-2.1\lib -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network

mkdir chessBuildWin
mkdir chessBuildWin\bin
mkdir chessBuildWin\img

copy ..\img\buttons.png .\chessBuildWin\img\
copy ..\img\chessboard.gif .\chessBuildWin\img\
copy LemonMilk.otf .\chessBuildWin\bin

move sfml-app.exe .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-audio-2.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-network-2.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-window-2.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-graphics-2.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-system-2.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\openal32.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\libsndfile-1.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-window-2.dll .\chessBuildWin\bin

copy C:\MinGW\bin\libgcc_s_dw2-1.dll .\chessBuildWin\bin

copy "C:\MinGW\bin\libstdc++-6.dll" .\chessBuildWin\bin
