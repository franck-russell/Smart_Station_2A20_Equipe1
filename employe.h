#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>

using namespace std;

class Employe
{
    int matricule;
    QString nom;
    QString prenom;
    QString datenaissance;
    QString poste;
    int salaire;
public:

    //Constructeurs
    Employe();
    Employe(int, QString, QString, QString, QString, int);

    //Getters
    QString getnom();
    QString getprenom();
    QString getposte();
    QString getdatenaissance();
    int getmatricule();
    int getsalaire();

    //Setters
    void setnom(QString n);
    void setprenom(QString p);
    void setposte(QString po);
    void setdatenaissance(QString d);
    void setmatricule(int m);
    void setsalaire(int s);

    //Fonctionalités de base relatives à l'entité Employe
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * afficher_id();
    QSqlQueryModel * tri_matricule();
    QSqlQueryModel * tri_salaire();
    QSqlQueryModel * tri_poste();
    void clearTable(QTableView * table);
    void rechercher(QTableView *table, int x);
    bool nettoyer();
};

#endif // EMPLOYE_H
