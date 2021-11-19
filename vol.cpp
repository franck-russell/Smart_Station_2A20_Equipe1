#include "vol.h"

using namespace std;

Vol::Vol()
{
    numero=0;
    destination="";
    horaire="";
    suivi="";
}

Vol::Vol(int numero,QString destination,QString horaire,QString suivi)
{
    this->numero=numero;
    this->destination=destination;
    this->horaire=horaire;
    this->suivi=suivi;
}


QString Vol::getDestination()
{
    return destination;
}
QString Vol::getHoraire()
{
    return horaire;
}

QString Vol::getSuivi()
{
    return suivi;
}

int Vol::getNumero()
{
    return numero;
}


void Vol::setDestination(QString d)
{
    destination=d;
}

void Vol::setHoraire(QString h)
{
    horaire=h;
}

void Vol::setSuivi(QString s)
{
    suivi=s;
}

void Vol::setNumero(int num)
{
    numero=num;
}


bool Vol::ajouter()
{
    QSqlQuery query;

    QString numero_string = QString::number(numero);

    query.prepare("INSERT INTO VOL (numero, destination, horaire, suivi)"
                  "values (:numero, :destination, :horaire, :suivi)");

    query.bindValue(":numero",numero_string);
    query.bindValue(":destination",destination);
    query.bindValue(":horaire",horaire);
    query.bindValue(":suivi",suivi);

    return query.exec();
}

QSqlQueryModel * Vol::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from vol");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Numero"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Destination"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Horaire"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Suivi"));

    return model;
}

bool Vol::supprimer(int numero)
{
    QSqlQuery query;

    QString numero_string = QString::number(numero);

    query.prepare("Delete from VOL where NUMERO= :numero");
    query.bindValue(":numero",numero_string);

    return query.exec();
}

bool Vol::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE VOL SET destination=:destination, horaire=:horaire, suivi=:suivi WHERE NUMERO=:numero ");
    query.bindValue(":destination", destination);
    query.bindValue(":horaire", horaire);
    query.bindValue(":suivi", suivi);

    query.bindValue(":numero",numero);

    return query.exec();
}

QSqlQueryModel * Vol::rechercher(QString numero )
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM VOL WHERE numero LIKE '%"+numero+"%' ");

    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("numero"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("destination"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("suivi"));

    return model ;
}

QSqlQueryModel * Vol::trier_par_numero()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM VOL ORDER BY numero ;");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("numero"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("destination"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("suivi"));

    return model ;
}

QSqlQueryModel * Vol::trier_par_destination()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM VOL ORDER BY destination ;");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("numero"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("destination"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("suivi"));

    return model ;
}

QSqlQueryModel * Vol::trier_par_horaire()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM VOL ORDER BY horaire ;");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("numero"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("destination"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("suivi"));

    return model ;
}

QSqlQueryModel * Vol::trier_par_suivi()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM VOL ORDER BY suivi ;");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("numero"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("destination"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("horaire"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("suivi"));

    return model ;
}
