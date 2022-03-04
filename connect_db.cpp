#include "connect_db.h"
#include "mainwindow.h"
#include "ui_connect_db.h"
#include <QMessageBox>
#include <string>
#include <cstring>

connect_db::connect_db(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connect_db)
{
    ui->setupUi(this);
}

connect_db::~connect_db()
{
    delete ui;
}

void connect_db::on_pushButton_clicked()
{
    QString name = ui->name->text();
    std::string conf = "dropdb -h localhost -p 5432 -U postgres " + name.toStdString();
    int n = conf.length();
    char char_conf[n + 1];
    strcpy(char_conf, conf.c_str());

    int val = std::system(char_conf) % 255;

    if (!val)
        QMessageBox::information(this, " ", "База данных удалена");

    else
       QMessageBox::warning(this, " ", "Ошибка подключения к базе данных");
    hide();
}
