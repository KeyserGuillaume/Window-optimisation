#include "heuristique.h"
#include "moveMaster.h"
using namespace std;

/*
 * On parcourt le voisinage defini par les substitutions
 * de volets pour faire evoluer la solution
 */

class LocalSearch: public Heuristique{
    // nombre d'iterations effectuees
    unsigned long long k;
    vector<int> registreCoutParFenetre;
    MoveMaster* getMove;

    // mouvements
    void substitution(const int &i, const int &j, const FenetreAvecVolet &fenetreIApres, const FenetreAvecVolet &fenetreJApres);
    void substitutionGauche(const int &i, const int &j);
    void substitutionDroite(const int &i, const int &j);
    void saut();

    void initRegistre();
    virtual void takeBestFind();
public:
    LocalSearch(string monInstance, CostFunction* myCost, MoveMaster *myGen);

    void run(const unsigned long long & max_iter=1000000);

    virtual void display(){
        cout << k << " ";
        Heuristique::display();
    }
    virtual void display(const CostFunction* myCost){
        cout << k << " ";
        Heuristique::display(myCost);
    }
    virtual bool testIntegriteSolution();
};

