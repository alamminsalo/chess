#include "gameview.h"

GameView::GameView()
{

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setScene(&scene);

    bgtex.load("img/chessboard.png");
    this->setBackgroundBrush(bgtex.scaled(640,640));
    scene.setSceneRect(0,0,640,640);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setSceneRect(0,0,640,640);
    this->resize(640,640);

    gameBoard = new Board();
    whiteteam = gameBoard->getTeam(0);
    blackteam = gameBoard->getTeam(1);

    player = NULL;
    socket = NULL;

    setup();
}


GameView::~GameView(){
    qDebug()<<"Deleting gameview..\n";
    if (socket){
        qDebug()<<"Deleting socket..\n";
        if (socket->isOpen())
            closeConnection();
        delete socket;
        delete player;
    }
    qDebug()<<"Deleting board..\n";
    delete gameBoard;
}

void GameView::connectToServer(QString addr, qint16 port){
    //changeStatusBarMessage("Connecting..");
    statusstr = "Connecting...";
    emit signalMessage();

    QHostAddress host;
    host.setAddress(addr);
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(socket,SIGNAL(connected()),this,SLOT(initConnection()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(failedConnection()));

    socket->connectToHost(addr,port);
    /*if (socket->waitForConnected(10000)){
        player = new Player;
        char buf[8];
        qint16 datasize;
        std::string data;
        while(true){
            datasize = socket->read(buf,8);
            if (datasize > 0){
                data = buf;
                if (data == "black\n"){
                    player->team = blackteam;
                    for (int i=0; i<16; i++)
                        player->buttons[i] = &blackButtons[i];
                    std::cout<<"Received: "<<data;
                    break;
                }
                else if (data =="white\n"){
                    player->team = whiteteam;
                    for (int i=0; i<16; i++)
                        player->buttons[i] = &whiteButtons[i];
                    std::cout<<"Received: "<<data;
                    break;
                }
            }
        }
        statusstr = "Connected";
        return true;
    }
    return false;*/
}

void GameView::initConnection(){
    statusstr = "Connected - Waiting for opponent";
    emit signalMessage();
    player = new Player;
    char buf[8];
    qint16 datasize;
    std::string data;
    while(true){
        datasize = socket->read(buf,8);
        if (datasize > 0){
            data = buf;
            if (data == "black\n"){
                player->team = blackteam;
                for (int i=0; i<16; i++)
                    player->buttons[i] = &blackButtons[i];
                //std::cout<<"Received: "<<data;
                break;
            }
            else if (data =="white\n"){
                player->team = whiteteam;
                for (int i=0; i<16; i++)
                    player->buttons[i] = &whiteButtons[i];
                //std::cout<<"Received: "<<data;
                break;
            }
        }
    }
    emit connectionSuccess();
}

void GameView::failedConnection(){
    statusstr = "Error connecting to server";
    emit signalMessage();
    emit connectionError();
}

void GameView::setup(){

    this->setMouseTracking(true);

    for (int y=0; y<8; y++)
            for (int x=0; x<8; x++){
                square[x][y].setPen(Qt::NoPen);
                square[x][y].setRect(0,0,HEIGHT/8,WIDTH/8);
                square[x][y].setBrush(QBrush(Qt::transparent));
                scene.addItem(&square[x][y]);
                square[x][y].setPos(x*(WIDTH/8),y*(HEIGHT/8));
            }

    bpctex[0].load("img/bpawn.png");
    bpctex[1].load("img/bknight.png");
    bpctex[2].load("img/bbishop.png");
    bpctex[3].load("img/brook.png");
    bpctex[4].load("img/bqueen.png");
    bpctex[5].load("img/bking.png");

    wpctex[0].load("img/wpawn.png");
    wpctex[1].load("img/wknight.png");
    wpctex[2].load("img/wbishop.png");
    wpctex[3].load("img/wrook.png");
    wpctex[4].load("img/wqueen.png");
    wpctex[5].load("img/wking.png");

    for (int i=0; i<16; i++){
        blackButtons[i].setPen(Qt::NoPen);
        whiteButtons[i].setPen(Qt::NoPen);

        switch (blackteam->piece[i]->getType()){
                    case PAWN:
                        blackButtons[i].setBrush(bpctex[0]);
                        break;
                    case KNIGHT:
                        blackButtons[i].setBrush(bpctex[1]);
                        break;
                    case BISHOP:
                        blackButtons[i].setBrush(bpctex[2]);
                        break;
                    case ROOK:
                        blackButtons[i].setBrush(bpctex[3]);
                        break;
                    case QUEEN:
                        blackButtons[i].setBrush(bpctex[4]);
                        break;
                    case KING:
                        blackButtons[i].setBrush(bpctex[5]);
                        break;
                }
                switch (whiteteam->piece[i]->getType()){
                    case PAWN:
                        whiteButtons[i].setBrush(wpctex[0]);
                        break;
                    case KNIGHT:
                        whiteButtons[i].setBrush(wpctex[1]);
                        break;
                    case BISHOP:
                        whiteButtons[i].setBrush(wpctex[2]);
                        break;
                    case ROOK:
                        whiteButtons[i].setBrush(wpctex[3]);
                        break;
                    case QUEEN:
                        whiteButtons[i].setBrush(wpctex[4]);
                        break;
                    case KING:
                        whiteButtons[i].setBrush(wpctex[5]);
                        break;
                }

        blackButtons[i].setRect(0,0,80,80);
        whiteButtons[i].setRect(0,0,80,80);

        scene.addItem(&blackButtons[i]);
        scene.addItem(&whiteButtons[i]);
    }
    manage();
}

void GameView::run(){

    //manage();
    //update();

    //this->show();

    if (player){
        if (!player->team->hasturn)
            readData();
    }
}
/*
void GameView::changeStatusBarMessage(const char *msg){
    statusstr = msg;
}*/

void GameView::update(){
    for (int i=0; i<16; i++){
        if (!blackteam->piece[i]->isCaptured()){
            blackButtons[i].setPos(square[blackteam->piece[i]->getX()][blackteam->piece[i]->getY()].pos());
        }
        else blackButtons[i].setPos(-999,-999);
        if (!whiteteam->piece[i]->isCaptured()){
            whiteButtons[i].setPos(square[whiteteam->piece[i]->getX()][whiteteam->piece[i]->getY()].pos());
        }
        else whiteButtons[i].setPos(-999,-999);
    }
}

void GameView::manage(){
    for (int y=0; y<8; y++)
        for (int x=0; x<8; x++){
            square[x][y].setBrush(QBrush(Qt::transparent));
            if (gameBoard->isActiveSquare(x,y)){
                square[x][y].setBrush(QBrush(Qt::green));
            }
        }
    switch (gameBoard->getStatus()){
        case STATUS_NOCHECK:
            statusstr = (gameBoard->getActiveTeam() == whiteteam) ? "Turn: WHITE" : "Turn: BLACK";
            break;
        case STATUS_CHECK:
            statusstr = (gameBoard->getActiveTeam() == whiteteam) ? "CHECK - Turn: WHITE" : "CHECK - Turn: BLACK";
            break;
        case STATUS_CHECKMATE:
            statusstr = "CHECKMATE";
            statusstr += " - ";
            statusstr += (gameBoard->getActiveTeam() == whiteteam) ? "Black wins!" : "White wins!";
            break;
        case STATUS_STALEMATE:
            statusstr = "STALEMATE";
            break;
    }
    emit signalMessage();
    update();
}

void GameView::writeData(int bx,int by,int x,int y){
    char buf[6] = {(char)(bx+48),(char)(by+48),(char)(x+48),(char)(y+48),'\n'};

    socket->write(buf,5);
    socket->waitForBytesWritten(1000);
}

void GameView::readData(){
    statusstr = "Waiting for opponent's move..";
    emit signalMessage();

    QString data = socket->readAll();

    if (data == "CLOSE\n"){
        statusstr = "Other player disconnected";
        emit connectionError();
        return;
    }

    int bx = (int)data.toStdString().at(0)-48;
    int by = (int)data.toStdString().at(1)-48;
    int x = (int)data.toStdString().at(2)-48;
    int y = (int)data.toStdString().at(3)-48;

    if (gameBoard->selectPieceAt(bx,by))
        gameBoard->moveSelected(x,y);
    manage();

}

void GameView::closeConnection(){
    socket->close();
}

void GameView::mousePressEvent ( QMouseEvent * event ){
    if (event->button() == Qt::LeftButton){
        for (int y=0; y<8;y++)
            for (int x=0;x<8;x++)
                if ((square[x][y].x() < event->x() && (square[x][y].rect().width()+(square[x][y].x()) > event->x())) && (square[x][y].y() < event->y() && (square[x][y].rect().height()+(square[x][y].y()) > event->y()))){
                    //Piece *piece = gameBoard->getSquare(x,y)->piece;
                    //std::cout<<"DEBUG: piece "<<piece->getName()<<", "<<(piece->getTeam() == 0 ? "WHITE" : "BLACK")<<" at "<<piece->getX()<<","<<piece->getY()<<" is "<<(piece->isCaptured() ? "CAPTURED" : "NOT CAPTURED")<<std::endl;
                    if (player){                    //this means online game
                        if (player->team->hasturn){
                            if (!gameBoard->getSelected())
                                gameBoard->selectPieceAt(x,y);
                            else {
                                int bX = gameBoard->getSelected()->getX();
                                int bY = gameBoard->getSelected()->getY();
                                if (gameBoard->moveSelected(x,y) == 0){
                                    writeData(bX,bY,x,y);
                                }
                                else{
                                    statusstr = "Error: Illegal move";
                                    emit signalMessage();
                                }
                            }
                        }
                        break;
                    }
                    else {                          //this means local game
                        if (!gameBoard->getSelected())
                            gameBoard->selectPieceAt(x,y);
                        else {
                            if (gameBoard->moveSelected(x,y) == -1){
                                statusstr = "Error: Illegal move";
                                emit signalMessage();
                            }
                        }
                        break;
                    }
                }
    }
    else if (event->button() == Qt::RightButton){
        gameBoard->deselect();
    }
    manage();
}
