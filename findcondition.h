#ifndef FINDCONDITION_H
#define FINDCONDITION_H

#include <QDialog>

namespace Ui {
class FindCondition;
}

class FindCondition : public QDialog
{
    Q_OBJECT

public:
    explicit FindCondition(QWidget *parent = nullptr);
    ~FindCondition();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FindCondition *ui;
};

#endif // FINDCONDITION_H
