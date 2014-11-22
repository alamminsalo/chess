#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool gameRunning;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resetSize();


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

    void startGame();

private:
    Ui::MainWindow *ui;
    GameView *gameview;
};

#endif // MAINWINDOW_H
