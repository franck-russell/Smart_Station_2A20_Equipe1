#ifndef AVIONS_H
#define AVIONS_H
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>



class Avions
{
public:
    Avions();
    Avions(int,int,QString,QString);
    int getidentifiant();
    int getcapacite();
    QString gettype();
    QString getetat();
    void setidentifiant(int);
    void setcapacite(int);
    void settype(QString);
    void setetat(QString);
    void clearTable(QTableView *table);
    void rechercher(QTableView *table, int x);
    bool ajouter();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(int identifiant);
    QSqlQueryModel* afficher_ID();
    QSqlQueryModel* tri_capacite();
    QSqlQueryModel* tri_etat();
    QSqlQueryModel* tri_type();
private:
    int identifiant;
    int capacite;
    QString type;
    QString etat;
};

#endif // AVIONS_H
