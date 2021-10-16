#ifndef AVIONS_H
#define AVIONS_H
#include <string>

using namespace std;
class Avions
{
private:
    int id;
    int capacite;
    string etat;
    string type;

public:
    void ajouterAvion();
    void modifierAvion();
    void supprimerAvion();
    void afficherAvion();
    Avions chercherAvion(int id);
    void trierAvion();



};
#endif // AVIONS_H
