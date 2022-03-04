#include "all_tables.h"
#include "ui_all_tables.h"
#include "check_connect.h"
#include <pqxx/pqxx>
#include <string>

all_tables::all_tables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::all_tables)
{
    int ROW;

    pqxx::connection conn("host=localhost port=5432 user=postgres dbname= " + name_server);
    pqxx::work query(conn);
    pqxx::result res;

    res = query.exec("SELECT count(*) table_name FROM information_schema.tables WHERE table_type = 'BASE TABLE' AND table_schema NOT IN ('pg_catalog', 'information_schema')");
    ROW = res[0][0].as<int>();

    ui->setupUi(this);
    ui->tableWidget->setRowCount(ROW);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setEditTriggers (QAbstractItemView :: NoEditTriggers);

    QStringList header;
    header<<tr("table_name");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    res = query.exec("SELECT table_name FROM information_schema.tables WHERE table_type = 'BASE TABLE' AND table_schema NOT IN ('pg_catalog', 'information_schema')");

   for (int i = 0; i < ROW; i++)
   {
       ui->tableWidget->setItem(i, 0, new QTableWidgetItem());

       std::string str_value = res[i][0].as<std::string>();
       int n = str_value.length();
       char char_value[n + 1];
       strcpy(char_value, str_value.c_str());

       ui->tableWidget->item(i,0)->setText(char_value);
    }
}

all_tables::~all_tables()
{
    delete ui;
}
