#include "columnadd.h"
#include "ui_columnadd.h"
#include "table.h"
#include <iostream>
#include <QMessageBox>

ColumnAdd::ColumnAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColumnAdd)
{
    ui->setupUi(this);
}

ColumnAdd::~ColumnAdd()
{
    delete ui;
}

void ColumnAdd::on_pushButton_2_clicked()
{
    QString name = ui->name->text();
    nameNewColumn = name.toStdString();

    if (ui->text->isChecked() && !nameNewColumn.empty())
    {
        set_text = 1;
        hide();
        check_error = false;
    }

    if (ui->numb->isChecked() && !nameNewColumn.empty())
    {
        set_text = 0;
        hide();
        check_error = false;
    }

    if (set_text == -1 || nameNewColumn.empty())
    {
        QMessageBox::warning(this, " ", "Не выбраны параметры");
        check_error = true;
    }
}
