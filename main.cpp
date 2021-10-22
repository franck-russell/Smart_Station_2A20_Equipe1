#include "mainwindow.h"

#include <QApplication>
//pour git
//pour GestionAvions
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
