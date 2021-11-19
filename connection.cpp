#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");//inserer le nom de la source de données ODBC
db.setUserName("oumaima");//inserer nom de l'utilisateur
db.setPassword("oumaima");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
test=true;





    return  test;
}
void connection::closeconnect(){db.close();}
