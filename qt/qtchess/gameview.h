#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QDebug>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QMouseEvent>
#include <QThread>

#include "../../logic/src/board.h"

#define WIDTH 640
#define HEIGHT 640

struct Player{
    Team *team;
    QGraphicsRectItem *buttons[16];
};

class GameView : public QGraphicsView
{
    Q_OBJECT
    QTcpSocket *socket;
    QThread thread;

    QGraphicsScene scene;
    QPixmap bgtex;

    QPixmap bpctex[6];
    QPixmap wpctex[6];
    QGraphicsRectItem blackButtons[16];
    QGraphicsRectItem whiteButtons[16] ;

    QGraphicsRectItem square[8][8];

    Board *gameBoard;
    QString statusstr;

    Team *blackteam;
    Team *whiteteam;

    Player *player;

    void setup();
    void update();
    void getInput();
    void manage();
    //bool socketOn;

    void listenThread();
    void mousePressEvent ( QMouseEvent * event );


public:
    GameView();
    ~GameView();
    void run();
    QString getStatus(){ return statusstr; }
    void connectToServer(QString,qint16);
    void closeConnection();

signals:
    void signalMessage();
    void connectionSuccess();
    void connectionError();

public slots:
    void readData();
    void writeData(int,int,int,int);
    void initConnection();
    void failedConnection();
};

#endif // GAMEVIEW_H
