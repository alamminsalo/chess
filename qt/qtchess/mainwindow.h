#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "gameview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTcpSocket socket;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resetSize();
    int loadConfig();
    int saveConfig();
    void startLocalGame();
    void startOnlineGame(QString);

signals:
    void authDone();

private slots:
    void on_main_connect_clicked();

    void on_main_local_clicked();

    void on_main_settings_clicked();

    void on_connect_back_clicked();

    void on_settings_back_clicked();

    void on_settings_ok_clicked();

    void on_main_search_clicked();

    void on_search_back_clicked();

    void on_connect_connect_clicked();

    void changeStatus();

    void closeTriggered();

    void disconnectTriggered();



    void authenticate();
    void connectionFailed();
    void readData();

private:
    Ui::MainWindow *ui;
    GameView *gameview;
};

#endif // MAINWINDOW_H
