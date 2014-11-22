#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gameRunning = false;

    ui->setupUi(this);
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(closeTriggered()));
    connect(ui->actionDisconnect,SIGNAL(triggered()),SLOT(disconnectTriggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetSize(){
    this->resize(430,387);
}

void MainWindow::on_main_local_clicked()
{
    gameview = new GameView();
    this->connect(gameview,SIGNAL(signalMessage()),this,SLOT(changeStatus()));

    startGame();
    ui->actionDisconnect->setEnabled(false);
}

void MainWindow::on_main_connect_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->connect_page);
}

void MainWindow::on_main_settings_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->settings_page);
}

void MainWindow::on_main_search_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->search_page);
}

void MainWindow::on_connect_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}

void MainWindow::on_settings_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}

void MainWindow::on_settings_ok_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}

void MainWindow::on_search_back_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main_page);
}

void MainWindow::disconnectTriggered()
{
    changeStatus();
    gameRunning = false;
    ui->stackedWidget->setCurrentWidget(ui->connect_page);
    resetSize();
    delete gameview;
    ui->connect_connect->setEnabled(true);
}

void MainWindow::closeTriggered(){
    if (gameRunning){
        delete gameview;
    }
    this->close();
}

void MainWindow::on_connect_connect_clicked()
{
    ui->connect_connect->setEnabled(false);
    QString addr = ui->connect_address->text();
    qint16 port = ui->connect_port->text().toInt();

    gameview = new GameView();

    this->connect(gameview,SIGNAL(connectionSuccess()),this,SLOT(startGame()));
    this->connect(gameview,SIGNAL(connectionError()),this,SLOT(disconnectTriggered()));
    this->connect(gameview,SIGNAL(signalMessage()),this,SLOT(changeStatus()));

    gameview->connectToServer(addr,port);
}

void MainWindow::startGame(){
    gameview->setParent(ui->game_page);
    ui->stackedWidget->setCurrentWidget(ui->game_page);
    int width = gameview->size().width();
    int height = gameview->size().height();
    int windowheight = height + ui->menuBar->size().height() + ui->statusBar->size().height();
    this->resize(width,windowheight);
    ui->centralWidget->resize(width,height);
    ui->stackedWidget->resize(width,height);

    ui->actionDisconnect->setEnabled(true);

    gameRunning = true;
    changeStatus();
}

void MainWindow::changeStatus(){
    ui->statusBar->showMessage(gameview->getStatus(),0);
}
