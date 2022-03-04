#include "mainwindow.h"
#include "table.h"
#include <QApplication>
#include <QtWidgets>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("DataBase editor version 1.0");
    w.resize(800, 600);

    QDesktopWidget widget;
    QRect screenGeometry = widget.screenGeometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    w.move((width - w.width()) / 2.0,
                    (height - w.height()) / 2.0);

    w.show();
    return a.exec();
}
