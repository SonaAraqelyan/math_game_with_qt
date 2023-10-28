#include "mainwindow.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(350,650);
    w.setWindowTitle("Math Game");
    w.show();

    return a.exec();
}
