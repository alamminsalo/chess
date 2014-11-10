g++ -c *.cpp -IC:\SFML-2.1\include

g++ *.o -o sfml-app.exe -LC:\SFML-2.1\lib -lsfml-window -lsfml-graphics -lsfml-system

mkdir chessBuildWin
mkdir chessBuildWin\bin
mkdir chessBuildWin\img

copy ..\img\buttons.png .\chessBuildWin\img\
copy ..\img\chessboard.gif .\chessBuildWin\img\

move sfml-app.exe .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-audio-2.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-window-2.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-graphics-2.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-system-2.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\openal32.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\libsndfile-1.dll .\chessBuildWin\bin

copy C:\SFML-2.1\bin\sfml-window-2.dll .\chessBuildWin\bin

copy C:\MinGW\bin\libgcc_s_dw2-1.dll .\chessBuildWin\bin

copy "C:\MinGW\bin\libstdc++-6.dll" .\chessBuildWin\bin
