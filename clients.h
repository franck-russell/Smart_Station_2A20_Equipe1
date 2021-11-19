#ifndef CLIENTS_H
#define CLIENTS_H
#include<QString>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QTableView>
class clients
{
public:
    clients();
    clients(int CIN,QString NOM,QString PRENOM,QString DATE_DE_NAISSANCE,QString NATIONALITE,int NUMERO_TELEPHONE,QString ADRESSE_MAIL);
    int getcin();
    QString getnom();
    QString getprenom();
    QString getdat();
    QString getnationalite();
    int getnum();
    QString getadresse();
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setdat(QString);
    void setnationalite(QString);
    void setnum(int);
    void setadresse(QString);

    //fonctionalité de base

bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(int);

bool modifier(int,QString,QString,QString,QString,int,QString);
//recherche et tri
//QSqlQueryModel * rechercher(QString);
  QSqlQueryModel * tri_CIN();
   QSqlQueryModel * tri_NUM();
    QSqlQueryModel * tri_MAIL();
 // QSqlQueryModel *Find_client();

void clearTable(QTableView * table);


void rechercher(QTableView *table, int x);


  bool controlSaisiecin(int , QString );
  bool controlSaisienom(QString,QString);
  bool controlsaisieprenom(QString,QString);
  bool controlsaisieDate(QString );
  bool controlSaisienationalite (QString,QString);
  bool controlSaisienum(int , QString );
  bool controlsaisieMail(QString );

private:
    int CIN,NUMERO_TELEPHONE;
    QString NOM,PRENOM,DATE_DE_NAISSANCE,NATIONALITE,ADRESSE_MAIL;



};
#endif // CLIENTS_H
