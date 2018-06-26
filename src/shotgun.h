#include "heuristique.h"
using namespace std;

/*
 * Les fenetres choisissent leur volet en respectant
 * le principe "premier arrive, premier servi".
 * Chaque fenetre minimise d'abord son nombre de rabots,
 * puis maximise la taille des rabots
 */

class Shotgun: public Heuristique{
    //int marge(const Fenetre & fenetre, const Volet & gauche, const Volet & droit)const;
    TaillePenaliseeRabots TR;
public:
    Shotgun(string monInstance);

    void run();

    virtual void display(){
        NbRabots NR;
        cout << totalCost(&NR, solutionActuelle) << endl;
    }
    virtual void display(const CostFunction* myCost){
    cout << "Nb final de coups de rabot  " << totalCost(myCost, solutionActuelle) << endl;
    }
};

