#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include <string>

extern std::string nameNewColumn;
extern int set_text;
extern bool check_error;
extern std::string findvalue;
extern std::string findbox;

namespace Ui {
class table;
}

class table : public QDialog
{
    Q_OBJECT

public:
    explicit table(QWidget *parent = nullptr);
    ~table();

private slots:
    void edit();
    void save_table();
    void update_table();
    void addLine_table();
    void addColumn_table();
    void del_table();
    void findvalue_table();
    void delRow_table();

private:
    Ui::table *ui;
};

#endif // SET_TABLE_H
