#ifndef TESTPROECT_CONTROLEUR_H
#define TESTPROECT_CONTROLEUR_H
#include "Jeueur.h"
#include "BankCarte.h"
//#include "Jeu.h"

class Controleur {
private:
     int JeueurNum;
    std::vector<Jeueur*> J;
    BankCarte bank;
public:
    Controleur();
    ~Controleur();
    Jeueur& getJeueur(std::string name);

    int choseFirst();
    void rearrange();
    void afficherAll();
    bool win(Jeueur j);
    void process();
    void process_dlc();
};


#endif //TESTPROECT_CONTROLEUR_H
