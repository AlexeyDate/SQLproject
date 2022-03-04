#ifndef CREATE_DB_H
#define CREATE_DB_H

#include <QDialog>

namespace Ui {
class create_db;
}

class create_db : public QDialog
{
    Q_OBJECT

public:
    explicit create_db(QWidget *parent = nullptr);
    ~create_db();

private slots:
    void on_pushButton_clicked();

private:
    Ui::create_db *ui;
};

#endif // CREATE_DB_H
