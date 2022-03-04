#ifndef CONNECT_TABLE_H
#define CONNECT_TABLE_H

#include <QDialog>
#include <string>

extern std::string name_table;

namespace Ui {
class connect_table;
}

class connect_table : public QDialog
{
    Q_OBJECT

public:
    explicit connect_table(QWidget *parent = nullptr);
    ~connect_table();

private slots:
    void on_pushButton_clicked();

private:
    Ui::connect_table *ui;
};

#endif // CONNECT_TABLE_H
