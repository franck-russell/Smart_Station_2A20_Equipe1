#include "mainwindow.h"
#include "chat.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;

    bool test=c.createconnection();

    MainWindow w;
    chat c1,c2;
    if (test)
    {
        w.show();

        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);
    }

    else
    {
        QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);
    }
    return a.exec();
}
