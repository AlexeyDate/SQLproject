#ifndef FUNC_H
#define FUNC_H

#include <QDialog>

namespace Ui {
class func;
}

class func : public QDialog
{
    Q_OBJECT

public:
    explicit func(QWidget *parent = nullptr);
    ~func();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::func *ui;
};

#endif // FUNC_H
