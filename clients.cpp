#include "clients.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include<QString>
#include<QMessageBox>

clients::clients()
{

   CIN=0; NOM=""; PRENOM=""; DATE_DE_NAISSANCE=""; NATIONALITE="" ; NUMERO_TELEPHONE=0; ADRESSE_MAIL="";


}
clients::clients(int CIN,QString NOM,QString PRENOM,QString DATE_DE_NAISSANCE,QString NATIONALITE,int NUMERO_TELEPHONE,QString ADRESSE_MAIL)
{this->CIN=CIN; this->NOM=NOM; this->PRENOM=PRENOM; this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE; this->NATIONALITE=NATIONALITE; this->NUMERO_TELEPHONE=NUMERO_TELEPHONE; this->ADRESSE_MAIL=ADRESSE_MAIL; }
int clients::getcin(){return CIN;}
QString clients::getnom(){return NOM;}
QString clients::getprenom(){return PRENOM;}
QString clients::getdat(){return DATE_DE_NAISSANCE;}
QString clients::getnationalite(){return NATIONALITE ;}
int clients::getnum(){return NUMERO_TELEPHONE;}
QString clients::getadresse(){return ADRESSE_MAIL;}
void clients::setcin(int CIN){this->CIN=CIN;}
void clients::setnom(QString NOM){this->NOM=NOM;}
void clients::setprenom(QString PRENOM){this->PRENOM=PRENOM;}
void clients::setdat(QString DATE_DE_NAISSANCE){this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE;}
void clients::setnationalite(QString NATIONALITE){this->NATIONALITE=NATIONALITE;}
void clients::setnum(int NUMERO_TELEPHONE){this->NUMERO_TELEPHONE=NUMERO_TELEPHONE;}
void clients::setadresse(QString ADRESSE_MAIL){this->ADRESSE_MAIL=ADRESSE_MAIL;}

//les fn
bool clients::ajouter()
{

QSqlQuery query;
QString res= QString::number(CIN);
      query.prepare("INSERT INTO CLIENT (CIN,NOM,PRENOM,DATE_DE_NAISSANCE,NATIONALITE,NUMERO_TELEPHONE,ADRESSE_MAIL)"
                    "VALUES(:CIN,:NOM,:PRENOM,:DATE_DE_NAISSANCE,:NATIONALITE,:NUMERO_TELEPHONE,:ADRESSE_MAIL)");
      query.bindValue(":CIN", res);
      query.bindValue(":NOM", NOM);
      query.bindValue(":PRENOM", PRENOM);
      query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
      query.bindValue(":NATIONALITE", NATIONALITE);
      query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);
      query.bindValue(":ADRESSE_MAIL", ADRESSE_MAIL);

return       query.exec();


}

QSqlQueryModel * clients::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NATIONALITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO_TELEPHONE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_MAIL"));




        return model;
}
bool clients::supprimer(int CIN)
{
  QSqlQuery query;
    QString res= QString::number(CIN);
    query.prepare("Delete from CLIENT where CIN = :res ");
    query.bindValue(":CIN", res);


    return    query.exec();


}


bool clients::modifier(int CIN,QString NOM,QString PRENOM,QString DATE_DE_NAISSANCE,QString NATIONALITE,int NUMERO_TELEPHONE,QString ADRESSE_MAIL)
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET CIN=:CIN,NOM=:NOM,PRENOM=:PRENOM,DATE_DE_NAISSANCE=:DATE_DE_NAISSANCE,NATIONALITE=:NATIONALITE,NUMERO_TELEPHONE=:NUMERO_TELEPHONE,ADRESSE_MAIL=:ADRESSE_MAIL WHERE CIN=:CIN");
   query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
    query.bindValue(":NATIONALITE", NATIONALITE);
    query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);

    query.bindValue(":ADRESSE_MAIL", ADRESSE_MAIL);


    return    query.exec();

}


//tri

QSqlQueryModel * clients::tri_CIN()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from CLIENT order by CIN ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_DE_NAISSANCE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("NATIONALITE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUMERO_TELEPHONE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_MAIL"));

    return model;

}
QSqlQueryModel * clients::tri_NUM()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from CLIENT order by NUMERO_TELEPHONE ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_DE_NAISSANCE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("NATIONALITE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUMERO_TELEPHONE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_MAIL"));

    return model;

}

QSqlQueryModel * clients::tri_MAIL()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from CLIENT order by ADRESSE_MAIL ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE_DE_NAISSANCE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("NATIONALITE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUMERO_TELEPHONE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE_MAIL"));

    return model;

}


bool clients::controlsaisieMail(QString saisi){
    int i,test1=0,test2=0;


            for (i=0;i<saisi.length();i++)
            {
     if( saisi[i]=="@")
          test1=1;
     if( saisi[i]==".")
         test2=1;
            }
    if((test1==1)&&(test2==1)){
        return true;
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Email"),
                    QObject::tr("L'adresse Mail non valid.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }


}



bool clients::controlSaisienom(QString saisi,QString type){
    if(saisi.contains(QRegExp("^[A-Za-z ]+$")))
    {
        return true;
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("ID"),
                    QObject::tr("Le %1 contient un Caractére non valid.\n"
                                "Click Cancel to exit.").arg(type), QMessageBox::Cancel);
        return false;
    }


}
bool clients::controlsaisieprenom(QString saisi,QString type){
    if(saisi.contains(QRegExp("^[A-Za-z ]+$")))
    {
        return true;
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("ID"),
                    QObject::tr("Le %1 contient un Caractére non valid.\n"
                                "Click Cancel to exit.").arg(type), QMessageBox::Cancel);
        return false;
    }


}



bool clients::controlSaisiecin(int num,QString numm){

       if(std::to_string(num).length()==8)
               {
         return true;
    }

    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Numéro"),
                    QObject::tr("Le %1 doit avoir 8 chiffre .\n"
                                "Click Cancel to exit.").arg(numm), QMessageBox::Cancel);
        return false;
    }

}
bool clients::controlsaisieDate(QString date)
{
    int i,test1=0,test2=0;
    for (i=0;i<date.length();i++)
    {
        if(date[2]=="/")
            test1=1;
          if(date[5]=="/")
              test2=1;

     }
    if((test1==1)&&(test2==1)&&(date.length()==10))
    {
        return true;
    }
      else {

                QMessageBox::critical(nullptr, QObject::tr("Email"),
                            QObject::tr("Date non valid.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                return false;
           }

}
bool clients::controlSaisienationalite(QString saisi,QString type){
    if(saisi.contains(QRegExp("^[A-Za-z ]+$")))
    {
        return true;
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("ID"),
                    QObject::tr("Le %1 contient un Caractére non valid.\n"
                                "Click Cancel to exit.").arg(type), QMessageBox::Cancel);
        return false;
    }


}


bool clients::controlSaisienum(int num,QString numm){

       if(std::to_string(num).length()==8)
               {
         return true;
    }

    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Numéro"),
                    QObject::tr("Le %1 doit avoir 8 chiffre .\n"
                                "Click Cancel to exit.").arg(numm), QMessageBox::Cancel);
        return false;
    }

}

void clients::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}

void clients::rechercher(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from CLIENT WHERE regexp_like(CIN, :CIN)");
   query->bindValue(":CIN",x);

   if(x==0)
   {
       query->prepare("select * from CLIENT;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}




//find nest7a9ha bech taaytli leli mawjoud f table bch nhoto f fichier (pdf ou excel)
/*QSqlQueryModel * clients::Find_client()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT NOM,PRENOM,DATE_DE_NAISSANCE,NATIONALITE,NUMERO_TELEPHONE,ADRESSE_MAIL FROM CLIENT");

    query.exec();
    model->setQuery(query);
    return model;
}
*/









