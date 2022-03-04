#include "check_connect.h"
#include "ui_check_connect.h"
#include "func.h"
#include <pqxx/pqxx>
#include <QMessageBox>
#include <string>

std::string name_server;

check_connect::check_connect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::check_connect)
{
    ui->setupUi(this);
}

check_connect::~check_connect()
{
    delete ui;
}

void check_connect::on_pushButton_clicked()
{
    QString name = ui->name->text();
    name_server = name.toStdString();

    try
    {
        pqxx::connection conn("host=localhost port=5432 user=postgres dbname= " + name_server);
        conn.disconnect();

        if (name.size() > 0)
        {
           // QMessageBox::information(this, " ", "Подключение к базе данных установлено");
            hide();
            func func_window;
            func_window.setModal(true);
            func_window.setWindowTitle("Функционал базы данных");
            func_window.exec();
        }

        else
        {
            QMessageBox::warning(this, " ", "Ошибка подключения к базе данных");
            hide();
        }
    }
    catch (const std::exception&)
    {
        QMessageBox::warning(this, " ", "Ошибка подключения к базе данных");
        hide();
    }
}
