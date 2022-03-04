#include "findcondition.h"
#include "ui_findcondition.h"
#include "table.h"
#include <QMessageBox>

FindCondition::FindCondition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindCondition)
{
    ui->setupUi(this);
}

FindCondition::~FindCondition()
{
    delete ui;
}

void FindCondition::on_pushButton_clicked()
{
    QString box = ui->namebox->text();
    QString value = ui->namevalue->text();

    findbox = box.toStdString();
    findvalue = value.toStdString();

    if (findbox.empty())
    {
        QMessageBox::warning(this, " ", "Не задано поле");
        check_error = true;
    }

    else if (findvalue.empty())
    {
        QMessageBox::warning(this, " ", "Не задано значение поля");
        check_error = true;
    }
    else
    {
       check_error = false;
       hide();
    }

}
