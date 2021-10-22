#ifndef VOLS_H
#define VOLS_H
#include <string>

using namespace std;

class Vols
{
private:
    int numero;
    string destination;
    string horraire;
    string suivi;
public:
    void AjouterVol();
    void ModifierVol();
    void AfficherVol();
    void SupprimerVol();
};

#endif // VOLS_H
