#ifndef CHECK_CONNECT_H
#define CHECK_CONNECT_H

#include <QDialog>
#include <string>

extern std::string name_server;

namespace Ui {
class check_connect;
}

class check_connect : public QDialog
{
    Q_OBJECT

public:
    explicit check_connect(QWidget *parent = nullptr);
    ~check_connect();

private slots:
    void on_pushButton_clicked();

private:
    Ui::check_connect *ui;

};

#endif // CHECK_CONNECT_H
