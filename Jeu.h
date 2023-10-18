#ifndef TESTPROECT_JEU_H
#define TESTPROECT_JEU_H
#include "Carte.h"

class Jeu{
private:
    static Jeu* instance;
    std::vector<Carte*> cartes;
    Jeu();
    ~Jeu();
    Jeu(const Jeu& j) = delete;
    Jeu& operator=(const Jeu& j) = delete;
public:
    static Jeu& getInstance(){
        if(instance == nullptr)
            instance = new Jeu();
        return *instance;
    }
    static void libererInstance(){
        delete instance;
        instance = nullptr;
    }
    Carte& getCarte(int i);

    const std::vector<Carte *> &getCartes() const;
};

#endif //TESTPROECT_JEU_H
