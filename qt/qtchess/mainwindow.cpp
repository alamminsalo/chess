#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_main_local_clicked()
{

}

void MainWindow::on_main_connect_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_main_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_main_search_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_connect_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_settings_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_settings_ok_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}




