#include <iostream>
#include "Carte.h"
#include "Jeueur.h"
#include "Controleur.h"

using namespace std;
int main() {
    Controleur con;
    con.rearrange();
    con.process();

    return 0;
}
