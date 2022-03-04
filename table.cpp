#include "table.h"
#include "ui_table.h"
#include "connect_table.h"
#include "check_connect.h"
#include <pqxx/pqxx>
#include <string>
#include <cstring>
#include <QMenuBar>
#include <QMessageBox>
#include <vector>
#include <QTabWidget>
#include "columnadd.h"
#include "findcondition.h"
#include <iostream>

bool table_edit = false;
bool check_error;
int count_addedLines = 0;
int count_addedColumns = 0;
int ROW, COL;
int set_text; //text

std::string nameNewColumn;
std::string findvalue;
std::string findbox;
std::vector<std::string> vec_header;

table::table(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::table)
{  
    ui->setupUi(this);
    vec_header.clear();

    QMenu *menu;
    QAction *edit_OnOff;
    QAction *save;
    QAction *update;
    QAction *addLine;
    QAction *addColumn;
    QAction *del;
    QAction *find;
    QAction *delRow;
    QMenuBar *menuBar = new QMenuBar(this);

    del = new QAction("Удалить таблицу");
    find = new QAction("Поиск значения по заданному полю", this);
    edit_OnOff = new QAction("Включить/отключить режим редактирования ячеек", this);
    save = new QAction("Сохранить изменения", this);
    update = new QAction("Обновить таблицу", this);
    addLine = new QAction("Добавить строку", this);
    addColumn = new QAction("Добавить колонку", this);
    delRow = new QAction("Удалить строку по заданному значению поля", this);

    menu = menuBar->addMenu("Действия");  
    menu->addAction(save);
    menu->addAction(find);
    menu->addAction(update);
    menu->addAction(addLine);
    menu->addAction(addColumn);
    menu->addAction(edit_OnOff);
    menu->addAction(delRow);
    menu->addAction(del);

    update_table();
    connect( edit_OnOff, SIGNAL(triggered()), this, SLOT(edit()));
    connect( save, SIGNAL(triggered()), this, SLOT(save_table()));
    connect( update, SIGNAL(triggered()), this, SLOT(update_table()));
    connect( addLine, SIGNAL(triggered()), this, SLOT(addLine_table()));
    connect( addColumn, SIGNAL(triggered()), this, SLOT(addColumn_table()));
    connect( del, SIGNAL(triggered()), this, SLOT(del_table()));
    connect( find, SIGNAL(triggered()), this, SLOT(findvalue_table()));
    connect( delRow, SIGNAL(triggered()), this, SLOT(delRow_table()));

    ui->tableWidget->setEditTriggers (QAbstractItemView :: NoEditTriggers);
}

table::~table()
{
    delete ui;
}

void table::edit()
{
    if (table_edit)
    {
        ui->tableWidget->setEditTriggers(QAbstractItemView :: NoEditTriggers);
        table_edit = false;
    }

    else if (!table_edit)
    {
        ui->tableWidget->setEditTriggers(QAbstractItemView :: AllEditTriggers);
        table_edit = true;
    }
}

void table::save_table()
{
    pqxx::connection conn_dynamic("host=localhost port=5432 user=postgres dbname= " + name_server);
    pqxx::work query(conn_dynamic);
    pqxx::result last_data;

    try
    {
        for (int i = ROW - count_addedLines; i < ROW; i++)
        {
            std::string values = " (";
            for (int j = 0; j < COL; j++)
            {
                values += "'";
                values += ui->tableWidget->item(i, j)->text().toStdString();
                values += "'";
                if (j != COL - 1)
                    values += ", ";
            }

            values += ")";

            query.exec("INSERT INTO " + name_table + " VALUES" + values);
        }
        query.commit();
        conn_dynamic.disconnect();

        pqxx::connection conn_dynamic("host=localhost port=5432 user=postgres dbname= " + name_server);
        pqxx::work query_after(conn_dynamic);
        last_data = query_after.exec("SELECT * FROM " + name_table);

        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                std::string value = ui->tableWidget->item(i, j)->text().toStdString();
                std::string get_value;

                if (value.empty())
                    value = "null";

                if (last_data[i][j].size())
                    get_value = last_data[i][j].as<std::string>();
                else
                    get_value = "null";


                    if (get_value != value)
                    {
                       std::string condition = " WHERE ";

                       for (int k = 0; k < COL; k++)
                       {
                            ui->tableWidget->item(i, j)->text().toStdString();

                            if (k > 0)
                                condition += " AND ";

                            condition += vec_header[k];

                            if (last_data[i][k].size() > 0)
                                condition += " = '" + last_data[i][k].as<std::string>() + "'";
                            else
                                condition += " IS NULL";
                       }

                       if (value != "null")
                          // std::cout << "UPDATE " + name_table + " SET " + vec_header[j] + " = '" + value + "'" + condition << std::endl;
                          query_after.exec("UPDATE " + name_table + " SET " + vec_header[j] + " = '" + value + "'" + condition);
                       else
                          // std::cout << "UPDATE " + name_table + " SET " + vec_header[j] + " = null" + condition << std::endl;
                          query_after.exec("UPDATE " + name_table + " SET " + vec_header[j] + " = null" + condition);
                    }
            }
        }

        count_addedLines = 0;
        query_after.commit();
    }

    catch(const std::exception&)
    {
        QMessageBox::warning(this, " ", "Некорректно введены данные");
    }

    conn_dynamic.disconnect();
}

void table::update_table()
{
    pqxx::connection conn("host=localhost port=5432 user=postgres dbname= " + name_server);
    pqxx::work query(conn);
    pqxx::result res;

    if (count_addedLines > 0)
    {
        ROW -= count_addedLines;
        count_addedLines = 0;
    }

    res = query.exec("SELECT count(*) FROM " + name_table);
    ROW = res[0][0].as<int>();
    res = query.exec("SELECT count(*) FROM information_schema.columns WHERE table_name = '" + name_table + "'");
    COL = res[0][0].as<int>();

    ui->tableWidget->setRowCount(ROW);
    ui->tableWidget->setColumnCount(COL);

    res = query.exec("SELECT * FROM information_schema.columns WHERE table_name = '" + name_table + "' ORDER BY ordinal_position");

    QStringList header;
    for (int i = 0; i < COL; i++)
    {
        std::string str_header = res[i][3].as<std::string>();
        vec_header.push_back(str_header);
        int n = str_header.length();
        char char_header[n + 1];
        strcpy(char_header, str_header.c_str());

        header<<tr(char_header);
        ui->tableWidget->setHorizontalHeaderLabels(header);
    }

    res = query.exec("SELECT * FROM " + name_table);

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem());

             std::string str_value;

             if (res[i][j].size())
             {
                str_value = res[i][j].as<std::string>();

                int n = str_value.length();
                char char_value[n + 1];
                strcpy(char_value, str_value.c_str());

                ui->tableWidget->item(i,j)->setText(char_value);
             }
        }
    }
    query.commit();
    conn.disconnect();
}

void table::addLine_table()
{
    ROW++;
    ui->tableWidget->setRowCount(ROW);

    for (int j = 0; j < COL; j++)
    {
        ui->tableWidget->setItem(ROW-1, j, new QTableWidgetItem());
        ui->tableWidget->item(ROW-1, j)->setText("NULL");
    }

    count_addedLines++;
}

void table::addColumn_table()
{
    set_text = -1;
    check_error = false;

    ColumnAdd column_window;
    column_window.setModal(true);
    column_window.setWindowTitle("Установка параметров");
    column_window.exec();

    if (!check_error)
    {
        COL++;
        ui->tableWidget->setColumnCount(COL);

        for (int i = 0; i < ROW; i++)
        {
            ui->tableWidget->setItem(i, COL-1, new QTableWidgetItem());
        }

        vec_header.push_back(nameNewColumn);
        int n = vec_header[vec_header.size() - 1].length();
        char char_header[n + 1];
        strcpy(char_header, vec_header[vec_header.size() - 1].c_str());

        QTableWidgetItem *new_head = new QTableWidgetItem();
        new_head->setText(char_header);
        ui->tableWidget->setHorizontalHeaderItem(vec_header.size() - 1, new_head);

        pqxx::connection conn("host=localhost port=5432 user=postgres dbname= " + name_server);
        pqxx::work query(conn);

        if (set_text == 1)
            query.exec("ALTER TABLE " + name_table + " ADD COLUMN " + nameNewColumn + " text");

        if (set_text == 0)
            query.exec("ALTER TABLE " + name_table + " ADD COLUMN " + nameNewColumn + " int");

        query.commit();
        conn.disconnect();
    }
}

void table::del_table()
{
    pqxx::connection conn("host=localhost port=5432 user=postgres dbname= " + name_server);
    pqxx::work query(conn);
    try
    {
        query.exec("DROP TABLE " + name_table + " CASCADE");
        query.commit();
        QMessageBox::information(this, " ", "Таблица удалена");
        hide();
    }

    catch (const std::exception&)
    {
        QMessageBox::warning(this, " ", "Не удалось удалить таблицу");
    }

    conn.disconnect();
}

void table::findvalue_table()
{
    check_error = false;
    findvalue.clear();
    findbox.clear();

    FindCondition findcond_window;
    findcond_window.setModal(true);
    findcond_window.setWindowTitle("Установка параметров поиска");
    findcond_window.exec();


    int count_in = 0;
    if (!check_error)
    {
        for (int i = 0; i < vec_header.size(); i++)
        {
            if (vec_header[i] == findbox)
            {
                for (int j = 0; j < ROW; j++)
                {
                      if (ui->tableWidget->item(j, i)->text().toStdString() == findvalue)
                      {
                          ui->tableWidget->item(j, i)->setSelected(true);
                          count_in++;
                      }
                }
                break;
            }
        }

        if (!count_in && !findvalue.empty() && !findbox.empty())
            QMessageBox::warning(this, " ", "Значение не найдено");
    }
}

void table::delRow_table()
{
    check_error = false;
    findvalue.clear();
    findbox.clear();

    FindCondition findcond_window;
    findcond_window.setModal(true);
    findcond_window.setWindowTitle("Установка параметров удаления");
    findcond_window.exec();

    int count_in = 0;
    if (!check_error)
    {
        for (int i = 0; i < vec_header.size(); i++)
        {
            if (vec_header[i] == findbox)
            {
                for (int j = 0; j < ROW; j++)
                {
                      if (ui->tableWidget->item(j, i)->text().toStdString() == findvalue)
                      {
                          try
                          {
                             count_in++;
                             pqxx::connection conn("host=localhost port=5432 user=postgres dbname= " + name_server);
                             pqxx::work query(conn);
                             query.exec("DELETE FROM " + name_table + " WHERE " + findbox + " = " + findvalue);

                             ui->tableWidget->removeRow(j);
                             ROW--;

                             query.commit();
                             conn.disconnect();

                          }
                          catch(const std::exception&)
                          {
                              QMessageBox::warning(this, " ", "Возникла ошибка при удалении");
                              count_in = 0;
                          }
                      }
                }
                break;
            }
        }

        if (!count_in && !findvalue.empty() && !findbox.empty())
            QMessageBox::warning(this, " ", "Значение для удаления не найдено");
    }
}
