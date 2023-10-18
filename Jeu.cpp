#include "Jeu.h"

Jeu* Jeu::instance = nullptr;

Jeu::Jeu(){
    for(int i = 0;i < 6;i++) {
        cartes.push_back(new Carte("cornfield", 1, "wheat", "all", 1, 0));
        cartes.push_back(new Carte("farm", 1, "cow", "all", 1, 0));
        cartes.push_back(new Carte("bakery", 1, "house", "self", 2, 3));
        cartes.push_back(new Carte("coffeeCar", 2,  "cup", "other", 3, 0));
        cartes.push_back(new Carte("store", 2, "house", "self", 4, 0));
        cartes.push_back(new Carte("forest", 3, "gear", "all", 5, 0));
        cartes.push_back(new Carte("cheeseFactory", 5, "factory", "self", 7, 0));
        cartes.push_back(new Carte("businessCenter", 8, "maison", "once", 6, 0));
        cartes.push_back(new Carte("gym", 6, "factory", "once", 6, 0));
        cartes.push_back(new Carte("bandstand", 7, "factory", "once", 6, 0));
        cartes.push_back(new Carte("furnitureFactory", 3, "maison", "self", 8, 0));
        cartes.push_back(new Carte("mineField", 6, "gear", "all", 9, 0));
        cartes.push_back(new Carte("restaurant", 3, "cup", "other", 9, 10));
        cartes.push_back(new Carte("orchard", 3, "wheat", "all", 10, 0));
        cartes.push_back(new Carte("market", 2, "maison", "self", 11, 12));
    }
    cartes.push_back(new Carte("railwayStation",4,"null","self",0,0));
    cartes.push_back(new Carte("shoppingCenter",10,"null","self",0,0));
    cartes.push_back(new Carte("amusementPark",16,"null","self",0,0));
    cartes.push_back(new Carte("radioStation",22,"null","self",0,0));
    cartes.push_back(new Carte("cornfield",1,"wheat","all",1,0));
    cartes.push_back(new Carte("bakery",1,"house","self",2,3));
}

Jeu::~Jeu(){
    Carte* item = nullptr;
    for(int i = 0;i < cartes.size();i++){
        item= cartes[i];
        delete item;
    }
    std::vector<Carte*> temp;
    cartes.swap(temp);
}

Carte& Jeu::getCarte(int i){
    return *cartes[i];
}

const std::vector<Carte *> &Jeu::getCartes() const {
    return cartes;
}
