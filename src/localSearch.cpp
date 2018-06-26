#include "localSearch.h"

using namespace std;

LocalSearch::LocalSearch(string monInstance, CostFunction* myCost, MoveMaster* myMove):Heuristique(monInstance, myCost){
    k = 0;
    registreCoutParFenetre = vector<int>(n);
    getMove = myMove;
}

void LocalSearch::initRegistre(){
    for (int i=0;i<n;i++){
        registreCoutParFenetre[i] = cost(solutionActuelle[i]);
    }
}

void LocalSearch::takeBestFind(){
    Heuristique::takeBestFind();
    initRegistre();
}

void LocalSearch::substitution(const int &i, const int &j, const FenetreAvecVolet &fenetreIApres, const FenetreAvecVolet &fenetreJApres){
    if (i==j) return;
    int a = cost(fenetreIApres);
    int b = cost(fenetreJApres);
    if (getMove->accepterSaut(a, b, registreCoutParFenetre[i], registreCoutParFenetre[j])){
        solutionActuelle[i] = fenetreIApres;
        solutionActuelle[j] = fenetreJApres;
        registreCoutParFenetre[i] = a;
        registreCoutParFenetre[j] = b;
    }
}

void LocalSearch::substitutionGauche(const int &i, const int &j){
    FenetreAvecVolet fenetreIApres(i, solutionActuelle[j].indexVoletGauche, solutionActuelle[i].indexVoletDroit);
    FenetreAvecVolet fenetreJApres(j, solutionActuelle[i].indexVoletGauche, solutionActuelle[j].indexVoletDroit);
    return substitution(i, j, fenetreIApres, fenetreJApres);
}

void LocalSearch::substitutionDroite(const int &i, const int &j){
    FenetreAvecVolet fenetreIApres(i, solutionActuelle[i].indexVoletGauche, solutionActuelle[j].indexVoletDroit);
    FenetreAvecVolet fenetreJApres(j, solutionActuelle[j].indexVoletGauche, solutionActuelle[i].indexVoletDroit);
    substitution(i, j, fenetreIApres, fenetreJApres);
}

void LocalSearch::saut(){
    int i, j;
    (*getMove)(i, j);
    if (rand()%2)
        substitutionGauche(i, j);
    else
        substitutionDroite(i, j);
}

void LocalSearch::run(const unsigned long long &max_iter){
    initRegistre();
    getMove->init(registreCoutParFenetre);
    for (;k < max_iter;k++){
        saut();
        if (k%10000000==0) {
            display();
            if (computeCost->change())
                initRegistre();
            sauvegarder();
            testIntegriteSolution();
            getMove->testIntegrite(registreCoutParFenetre);
        }
    }
}

bool LocalSearch::testIntegriteSolution(){
    bool result = Heuristique::testIntegriteSolution();
    for (vector< FenetreAvecVolet>::iterator it = solutionActuelle.begin(); it!= solutionActuelle.end(); ++it){
        if (cost(*it)!=registreCoutParFenetre[it->indexFenetre]){
            cerr << "Heuristique::testIntegriteSolution : registreNbRabotParFenetre mal tenu" << endl;
            result = false;
        }
    }
    return result;
}
