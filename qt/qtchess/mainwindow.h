#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_main_connect_clicked();

    void on_main_local_clicked();

    void on_main_settings_clicked();

    void on_connect_back_clicked();

    void on_settings_back_clicked();

    void on_settings_ok_clicked();

    void on_pushButton_clicked();

    void on_main_search_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
