#pragma once
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include "SharedElements.h"
#include "costFunctions.h"
using namespace std;
typedef vector<Fenetre> MapFenetres;
typedef vector <Volet> MapVolets;
typedef vector<FenetreAvecVolet> MapSolutions;

/*
 * Base commune des algorithmes d'optimisation
 */

class Heuristique{
protected:
    // Donnees du probleme, ce dont on a besoin a minima
    int n;
    MapFenetres fenetres;
    MapVolets gauches;
    MapVolets droits;
    string instance;

    // Etat de la solution courante
    MapSolutions solutionActuelle;

    // Etat de la meilleure solution courante
    MapSolutions meilleureSolution;
    int meilleurePerformance;

    // fonction de cout elementaire
    CostFunction* computeCost;

    // repartir de la meilleure solution
    virtual void takeBestFind();

    // calculer la fonction objectif elementaire d'une fenetre
    int cost(const FenetreAvecVolet & solution);
    // calculer le nombre de rabots de la solution
    int totalCost(MapSolutions solution);
    int totalCost(const CostFunction* myCost, MapSolutions solution);

    void init();

public:
    Heuristique(string monInstance, CostFunction* myCost);
    Heuristique(string monInstance);
    void setCost(CostFunction* myCost){computeCost = myCost;}

    virtual bool testIntegriteSolution();

    void sauvegarder();

    void stats();
    void stats(CostFunction *myCost);

    virtual void display(){
        NbRabots NR;
        cout << meilleurePerformance << " " << totalCost(&NR, solutionActuelle) << endl;
    }
    virtual void display(const CostFunction* myCost){
    cout << totalCost(myCost, meilleureSolution) << " " << totalCost(myCost, solutionActuelle) << endl;
    }

};
