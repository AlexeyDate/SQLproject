#ifndef ALL_TABLES_H
#define ALL_TABLES_H

#include <QDialog>

namespace Ui {
class all_tables;
}

class all_tables : public QDialog
{
    Q_OBJECT

public:
    explicit all_tables(QWidget *parent = nullptr);
    ~all_tables();

private:
    Ui::all_tables *ui;
};

#endif // ALL_TABLES_H
