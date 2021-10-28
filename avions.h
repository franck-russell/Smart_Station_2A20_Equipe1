#ifndef AVIONS_H
#define AVIONS_H

#include <QString>

class Avions
{
public:
    Avions();
    Avions(int,int,QString,QString);
    int getid();
    int getcapacite();
    QString gettype();
    QString getetat();
    void setid(int);
    void setcapacite(int);
    void settype(QString);
    void setetat(QString);
private:
    int id, capacite;
    QString type, etat;
};

#endif // AVIONS_H
