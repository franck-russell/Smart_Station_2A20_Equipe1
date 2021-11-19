#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("test-bd");
    db.setUserName("SYSTEM");
    db.setPassword("26112001");

    if(db.open()) test=true;

    return test;
}

void Connection::closeconnection(){db.close();}
