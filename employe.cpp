#include "employe.h"

using namespace std;

//Constructeurs
Employe::Employe()
{
    matricule=0;
    salaire=0;
    nom="";
    prenom="";
    datenaissance="";
    poste="";
}

Employe::Employe(int matricule, QString nom, QString prenom, QString datenaissance, QString poste, int salaire)
{
    this->matricule=matricule;
    this->salaire=salaire;
    this->nom=nom;
    this->prenom=prenom;
    this->poste=poste;
    this->datenaissance=datenaissance;
}

//Getters
QString Employe::getnom()
{
    return nom;
}

QString Employe::getprenom()
{
    return prenom;
}

QString Employe::getposte()
{
    return poste;
}

QString Employe::getdatenaissance()
{
    return datenaissance;
}

int Employe::getmatricule()
{
    return matricule;
}

int Employe::getsalaire()
{
    return salaire;
}

//Setters
void Employe::setnom(QString n)
{
    nom=n;
}

void Employe::setprenom(QString p)
{
    prenom=p;
}

void Employe::setposte(QString po)
{
    poste=po;
}

void Employe::setdatenaissance(QString d)
{
    datenaissance=d;
}

void Employe::setmatricule(int m)
{
    matricule=m;
}

void Employe::setsalaire(int s)
{
    salaire=s;
}

//Fonctionalités de base relatives à l'entité Employe
bool Employe::ajouter()
{
    QSqlQuery query;

    QString id_string = QString::number(matricule);
    QString salaire_string = QString::number(salaire);

    query.prepare("INSERT INTO EMPLOYE (matricule, nom, prenom, datenaissance, poste, salaire)"
                  "values (:matricule, :nom, :prenom, :datenaissance, :poste, :salaire)");

    //Création des variables liées
    query.bindValue(":matricule",matricule);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":datenaissance", datenaissance);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);

    return query.exec();
}

QSqlQueryModel * Employe::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from EMPLOYE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date de naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Poste"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Salaire"));

    return model;
}

bool Employe::supprimer(int matricule)
{
    QSqlQuery query;
    QString id_string = QString::number(matricule);
    QString salaire_string = QString::number(salaire);


    query.prepare("Delete from EMPLOYE where MATRICULE= :matricule");
    query.bindValue(":matricule",id_string);

    return query.exec();
}

bool Employe::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE EMPLOYE SET nom = :nom, prenom = :prenom, datenaissance = :datenaissance, poste = :poste, salaire = :salaire WHERE matricule = :matricule");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":datenaissance", datenaissance);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":matricule", matricule);

    return query.exec();
}

QSqlQueryModel* Employe ::afficher_id()
   {
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select matricule from EMPLOYE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
    return model;

   }

QSqlQueryModel * Employe::tri_matricule()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from EMPLOYE order by matricule ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date de naissance"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Poste"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Salaire"));
    return model;
}

QSqlQueryModel * Employe::tri_salaire()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from EMPLOYE order by salaire ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date de naissance"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Poste"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Salaire"));
    return model;
}

QSqlQueryModel * Employe::tri_poste()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from EMPLOYE order by poste ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Matricule"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date de naissance"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Poste"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Salaire"));
    return model;
}

void Employe::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}

void Employe::rechercher(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from EMPLOYE WHERE regexp_like(matricule, :matricule)");
   query->bindValue(":matricule",x);

   if(x==0)
   {
       query->prepare("select * from EMLPOYE;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}

bool Employe::nettoyer()
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE;");
    return query.exec();
}
