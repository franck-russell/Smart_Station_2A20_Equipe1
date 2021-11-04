
#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnection();//etablir la connection
    MainWindow w;
    if(test) //si la connection est etablie
{
    w.show();
    QMessageBox::information(nullptr, QObject::tr("database is open"),
    QObject::tr("connection succeful.\n"
                "Click cancel to exit."), QMessageBox::Cancel);
}

    else{
     QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                            QObject::tr("connection failed.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

   }
    return a.exec();
}


