#ifndef COLUMNADD_H
#define COLUMNADD_H

#include <QDialog>

namespace Ui {
class ColumnAdd;
}

class ColumnAdd : public QDialog
{
    Q_OBJECT

public:
    explicit ColumnAdd(QWidget *parent = nullptr);
    ~ColumnAdd();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ColumnAdd *ui;
};

#endif // COLUMNADD_H
