#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <Qgraphicsview>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWidget main;
    main.show();
    return a.exec();
}
