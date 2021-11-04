#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    db=QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("test-bd");
    db.setUserName("system");
    db.setPassword("allemagne20");

    if (db.open()) test=true;

    return test;
}

void Connection::closeconnection(){db.close();}
