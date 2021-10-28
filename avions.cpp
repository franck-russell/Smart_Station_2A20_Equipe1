#include "avions.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>

Avions::Avions()
{
id=0; capacite=0; type=""; etat="";
}

Avions::Avions(int id,int capacite,QString type,QString etat)
{this->id=id; this->capacite=capacite; this->type=type; this->etat=etat;}
int Avions::getid(){return id;}
int Avions::getcapacite(){return capacite;}
QString Avions::gettype(){return type;}
QString Avions::getetat(){return etat;}
void Avions::setid(int id){this->id=id;}
void Avions::setcapacite(int capacite){this->capacite=capacite;}
void Avions::settype(QString type){this->type=type;}
void Avions::setetat(QString etat){this->etat=etat;}
bool Avions::ajouter()
{
    bool test=false;

    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("INSERT INTO avions (id, capacite, type, etat) "
                  "VALUES (:id, :forename, :surname)");
    query.bindValue(":id",res );
    query.bindValue(":capacite", "capacite");
    query.bindValue(":type", "type");
    query.bindValue(":etat", "etat");
    return query.exec();
    return test;
}

QSqlQueryModel* Avions::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("select * from avions");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("capacite"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
return model;
}





