#ifndef VOL_H
#define VOL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

using namespace std;

class Vol
{
    QString destination, horaire, suivi;
    int numero;

public:
    Vol();
    Vol (int,QString,QString,QString);

    QString getDestination();
    QString getHoraire();
    QString getSuivi();
    int getNumero();

    void setDestination(QString d);
    void setHoraire(QString h);
    void setSuivi(QString s);
    void setNumero(int numero);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * rechercher(QString numero );
    QSqlQueryModel * trier_par_numero();
    QSqlQueryModel * trier_par_destination();
    QSqlQueryModel * trier_par_horaire();
    QSqlQueryModel * trier_par_suivi();
};

#endif // VOL_H
