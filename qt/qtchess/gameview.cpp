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

GameView::GameView(QTcpSocket *tcpsocket, QString side): GameView(){
    socket = tcpsocket;
    connect(socket,SIGNAL(readyRead()),this,SLOT(readData()));

    if (side == "BLACK\n"){
        qDebug()<<"Got side BLACK";
        player = new Player;
        player->team = blackteam;
        for (int i=0; i<16; i++)
            player->buttons[i] = &blackButtons[i];
    }
    else if (side =="WHITE\n"){
        qDebug()<<"Got side WHITE";
        player = new Player;
        player->team = whiteteam;
        for (int i=0; i<16; i++)
            player->buttons[i] = &whiteButtons[i];
    }
}


GameView::~GameView(){
    qDebug()<<"Deleting gameview..";
    if (player){
        delete player;
    }
    qDebug()<<"Deleting board..";
    delete gameBoard;
    qDebug()<<"All done.";
}

void GameView::initConnection(){
    message.clear();
    message.append(name);
    message.append('\n');
    socket->write(message);

    message.clear();
    message.append(pass);
    message.append('\n');
    socket->write(message);

    statusstr = "Connected. Waiting for opponent...";
    emit signalMessage();
}

void GameView::failedConnection(){
    statusstr = "Error connecting to server";
    qDebug() << "CONN_FAILED";
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

void GameView::writeData(int bx,int by,int x,int y,std::string piece){
    qDebug()<<"Writing move..";
    char buf[6] = {(char)(bx+48),(char)(by+48),(char)(x+48),(char)(y+48)};
    message.clear();
    message.append(buf);
    message.append('\n');
    socket->write(message);
    //socket->waitForBytesWritten(1000);

    message.clear();
    message.append(piece.c_str());
    message.append('\n');
    socket->write(message);
    //socket->waitForBytesWritten(1000);

    message.clear();
    switch (gameBoard->getStatus()){
        case STATUS_NOCHECK:
            message.append("-");
            break;
        case STATUS_CHECK:
            message.append("CHECK");
            break;
        case STATUS_CHECKMATE:
            message.append("CHECKMATE");
            break;
        case STATUS_STALEMATE:
            message.append("STALEMATE");
            break;
    }
    message.append('\n');
    socket->write(message);
    //socket->waitForBytesWritten(1000);
    qDebug()<<"Wrote move!";
}

void GameView::readData(){
    QString data = socket->readAll();

    if (data == "CLOSE_CL\n"){
        statusstr = "Other player disconnected";
        qDebug()<<"Received CLOSE_CL";
        emit connectionError();
    }
    else if (data == "CLOSE_SV\n"){
        statusstr = "Server disconnected";
        qDebug()<<"Received CLOSE_SV";
        emit connectionError();
    }
    else if (data == "PING\n"){
        qDebug()<<"Received PING";
        socket->write("PONG\n");
    }

    else{
        int bx = (int)data.toStdString().at(0)-48;
        int by = (int)data.toStdString().at(1)-48;
        int x = (int)data.toStdString().at(2)-48;
        int y = (int)data.toStdString().at(3)-48;

        if (gameBoard->selectPieceAt(bx,by))
            gameBoard->moveSelected(x,y);
        manage();
    }
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
                                std::string piecename = gameBoard->getSelected()->getName();
                                if (gameBoard->moveSelected(x,y) == 0){
                                    writeData(bX,bY,x,y,piecename);
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
