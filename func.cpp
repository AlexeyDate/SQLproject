#include "func.h"
#include "ui_func.h"
#include "connect_table.h"
#include "all_tables.h"
#include "check_connect.h"
#include <QPixmap>
#include <QMessageBox>

func::func(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::func)
{
    ui->setupUi(this);
    QPixmap pix(":/image/image.png");
    int w = ui->image->width();
    int h = ui->image->height();

    ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

func::~func()
{
    delete ui;
}

void func::on_pushButton_2_clicked()
{
    connect_table contable;
    contable.setModal(true);
    contable.setWindowTitle("Установка связи с таблицой");
    contable.exec();
}

void func::on_pushButton_3_clicked()
{
    all_tables altable_window;
    altable_window.setModal(true);
    altable_window.setWindowTitle("Отображение имён доступных таблиц");
    altable_window.exec();
}

void func::on_pushButton_4_clicked()
{
    std::string conf = "dropdb -h localhost -p 5432 -U postgres " + name_server;
    int n = conf.length();
    char char_conf[n + 1];
    strcpy(char_conf, conf.c_str());
    int value1 = std::system(char_conf) % 255;

    conf = "createdb -h localhost -p 5432 -U postgres " + name_server;
    n = conf.length();
    strcpy(char_conf, conf.c_str());
    int value2 = std::system(char_conf) % 255;

    if (!value1 & !value2)
        QMessageBox::information(this, " ", "Все таблицы удалены");
    else
       QMessageBox::warning(this, " ", "Ошибка при удалении");
}
