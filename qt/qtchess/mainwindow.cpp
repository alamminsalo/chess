#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(closeTriggered()));
    connect(ui->actionDisconnect,SIGNAL(triggered()),SLOT(disconnectTriggered()));
    ui->connect_pass->setEchoMode(QLineEdit::Password);
    loadConfig();
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
    ui->connect_connect->setEnabled(true);
    ui->stackedWidget->setCurrentWidget(ui->connect_page);
    resetSize();
    this->disconnect(gameview,SIGNAL(connectionSuccess()),this,SLOT(startGame()));
    this->disconnect(gameview,SIGNAL(connectionError()),this,SLOT(disconnectTriggered()));
    this->disconnect(gameview,SIGNAL(signalMessage()),this,SLOT(changeStatus()));

    if (gameview)
        delete gameview;
    qDebug()<<"Disconnect ended";
}

void MainWindow::closeTriggered(){
    if (gameview){
        delete gameview;
    }
    this->close();
}

void MainWindow::on_connect_connect_clicked()
{
    QString addr = ui->connect_address->text();
    qint16 port = ui->connect_port->text().toInt();
    QString name = ui->connect_name->text();
    QString pass = ui->connect_pass->text();

    if (name != "" && pass != ""){
        saveConfig();
        ui->connect_connect->setEnabled(false);
        gameview = new GameView();

        this->connect(gameview,SIGNAL(connectionSuccess()),this,SLOT(startGame()));
        this->connect(gameview,SIGNAL(connectionError()),this,SLOT(disconnectTriggered()));
        this->connect(gameview,SIGNAL(signalMessage()),this,SLOT(changeStatus()));

        gameview->connectToServer(addr,port,name,pass);
    }
    else {
        ui->statusBar->showMessage("Please give name and password",0);
    }
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

    changeStatus();
}

void MainWindow::changeStatus(){
    ui->statusBar->showMessage(gameview->getStatus(),0);
}

int MainWindow::loadConfig(){
    QFile file("config.xml");
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Error reading configuration file!";
        return -1;
    }
    QXmlStreamReader xml(&file);
    QString str;
    while (!xml.atEnd()){
        xml.readNext();
        if (xml.name() == "name"){
            str = xml.readElementText();
            str = str == "" ? "Chess Master" : str;
            ui->connect_name->setText(str);
        }
        if (xml.name() == "address"){
            str = xml.readElementText();
            str = str == "" ? "localhost" : str;
            ui->connect_address->setText(str);
        }
        if (xml.name() == "port"){
            str = xml.readElementText();
            str = str == "" ? "3333" : str;
            ui->connect_port->setText(str);
        }
    }
    file.close();

    return 0;
}

int MainWindow::saveConfig(){
    QFile file("config.xml");
    if (!file.open(QIODevice::WriteOnly)){
        qDebug()<<"Error writing configuration file!";
        return -1;
    }
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();

    xml.writeStartElement("config");

    xml.writeTextElement("name",ui->connect_name->text());

    xml.writeStartElement("host");
    xml.writeTextElement("address",ui->connect_address->text());
    xml.writeTextElement("port",ui->connect_port->text());
    xml.writeEndElement();

    xml.writeEndElement();

    file.close();

    return 0;
}
