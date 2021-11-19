#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("ines");
    db.setUserName("ines");
    db.setPassword("ines");

    if(db.open()) test=true;

    return test;
}

void Connection::closeconnection(){db.close();}
