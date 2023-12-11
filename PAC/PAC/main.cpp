#include "mainwindow.h"
#include<QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("QMainWindow {background: 'black';}");
    w.show();
    return a.exec();
}
