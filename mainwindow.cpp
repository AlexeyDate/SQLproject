#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connect_db.h"
#include "create_db.h"
#include "check_connect.h"
#include <QPixmap>
#include <QPalette>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap background("./image/background.jpg");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    connect_db window;
    window.setModal(true);
    window.setWindowTitle("удаление базы данных");
    window.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    check_connect con_window;
    con_window.setModal(true);
    con_window.setWindowTitle("Подключение к базе данных");
    con_window.exec();
}


void MainWindow::on_pushButton_4_clicked()
{
    create_db create_window;
    create_window.setModal(true);
    create_window.setWindowTitle("Создание базы данных");
    create_window.exec();
}

void MainWindow::on_action_triggered()
{
    system("shutdown now");
}

void MainWindow::on_action_2_triggered()
{
    system("reboot");
}

void MainWindow::on_action_3_triggered()
{
    close();
}
