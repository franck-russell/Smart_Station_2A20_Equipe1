#include "mainwindow.h"
#include "emplacement.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Emplacement w;
    w.show();
    return a.exec();
}
