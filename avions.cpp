#include "avions.h"
#include "connection.h"
#include <QSqlQuery>
#include <iostream>
#include <QSql>
#include <QSqlQueryModel>

Avions::Avions()
{
identifiant=0; capacite=0; type=""; etat="";
}

Avions::Avions(int identifiant,int capacite,QString type,QString etat)
{this->identifiant=identifiant; this->capacite=capacite; this->type=type; this->etat=etat;}
int Avions::getidentifiant(){return identifiant;}
int Avions::getcapacite(){return capacite;}
QString Avions::gettype(){return type;}
QString Avions::getetat(){return etat;}
void Avions::setidentifiant(int identifiant){this->identifiant=identifiant;}
void Avions::setcapacite(int capacite){this->capacite=capacite;}
void Avions::settype(QString type){this->type=type;}
void Avions::setetat(QString etat){this->etat=etat;}

bool Avions::ajouter()
{
    bool test=false;

    QSqlQuery query;
    QString res= QString::number(identifiant);
    query.prepare("INSERT INTO AVION (IDENTIFIANT, CAPACITE, TYPE, ETAT) "
                  "VALUES (:identifiant, :capacite, :type, :etat)");
    query.bindValue(":identifiant",res );
    query.bindValue(":capacite", capacite);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    return query.exec();
    return test;
}

bool Avions::modifier()
{
    QSqlQuery query;
    QString res= QString::number(identifiant);
    query.prepare("UPDATE AVION SET  identifiant=:identifiant, capacite=:capacite, type=:type, etat=:etat where identifiant=:identifiant");
    query.bindValue(":identifiant",res );
    query.bindValue(":capacite", capacite);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    return query.exec();

}

bool Avions::supprimer(int identifiant)
{
    QSqlQuery query;
    QString res= QString::number(identifiant);
    query.prepare("Delete from AVION where identifiant=:identifiant");
    query.bindValue(":identifiant",res );

    return query.exec();
}

QSqlQueryModel* Avions::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("select * from AVION");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("capacite"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
return model;
}

QSqlQueryModel * Avions::rechercher(int identifiant)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;

query.prepare("select * from AVION where identifiant=:identifiant");
query.bindValue(":identifiant", identifiant);

query.exec();
model->setQuery(query);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("capacite"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));

return model;

}

QSqlQueryModel* Avions::afficher_ID()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("select identifiant from AVION");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
return model;
}

QSqlQueryModel* Avions::tri_capacite()
{
    QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("select * from AVION order by capacite ASC");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("capacite"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
       return model;
}

QSqlQueryModel* Avions::tri_etat()
{
    QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("select * from AVION order by etat ASC");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("capacite"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
       return model;
}

QSqlQueryModel* Avions::tri_type()
{
    QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("select * from AVION order by type ASC");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("identifiant"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("capacite"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
       return model;
}

void Avions::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}

void Avions::recherche_avancee(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from AVION WHERE regexp_like(identifiant, :identifiant)");
   query->bindValue(":identifiant",x);

   if(x==0)
   {
       query->prepare("select * from AVION;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
