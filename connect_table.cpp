#include "connect_table.h"
#include "ui_connect_table.h"
#include "check_connect.h"
#include "table.h"
#include <pqxx/pqxx>
#include <string>
#include <QMessageBox>

std::string name_table;

connect_table::connect_table(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connect_table)
{
    ui->setupUi(this);
}

connect_table::~connect_table()
{
    delete ui;
}

void connect_table::on_pushButton_clicked()
{
    QString name = ui->name->text();
    name_table = name.toStdString();
    pqxx::connection conn("host=localhost port=5432 user=postgres dbname= " + name_server);
    pqxx::work query(conn);
    pqxx::result res;

    try
    {
        res = query.exec("SELECT * FROM " + name_table);
        conn.disconnect();
        hide();

        table table_window;
        table_window.setModal(true);
        table_window.setWindowTitle("Данные из таблицы");
        table_window.exec();
    }

    catch (const std::exception&)
    {
        QMessageBox::warning(this, " ", "Таблицы не существует");
        conn.disconnect();
        hide();
    }
}
