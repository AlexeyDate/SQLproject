#include "create_db.h"
#include "ui_create_db.h"
#include <QMessageBox>
#include <string>
#include <cstring>

create_db::create_db(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_db)
{
    ui->setupUi(this);
}

create_db::~create_db()
{
    delete ui;
}

void create_db::on_pushButton_clicked()
{
    QString name = ui->name->text();
    std::string conf = "createdb -h localhost -p 5432 -U postgres " + name.toStdString();
    int n = conf.length();
    char char_conf[n + 1];
    strcpy(char_conf, conf.c_str());

    int val = std::system(char_conf) % 255;

    if (!val)
        QMessageBox::information(this, " ", "База данных создана");

    else
       QMessageBox::warning(this, " ", "Ошибка при создании базы данных. Возможно она уже существует");
    hide();
}
