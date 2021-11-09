#ifndef AVIONS_H
#define AVIONS_H
#include <QSqlQueryModel>
#include <QString>


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
    bool ajouter();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(int identifiant);
    QSqlQueryModel* afficher_ID();
private:
    int identifiant;
    int capacite;
    QString type;
    QString etat;
};

#endif // AVIONS_H
