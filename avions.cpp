#include "avions.h"

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
