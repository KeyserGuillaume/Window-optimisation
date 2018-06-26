#pragma once
#include "SharedElements.h"
#include "heuristique.h"
using namespace std;

/*
 * Ces classes generent des choix de voisinage a explorer
 * sous la forme d'indices de volets a permuter.
 * Un objectif a ete de tenir compte du nombre de rabots
 * de chaque fenetre pour suggerer les indices de volets a
 * permuter, mais des dificultes dans l'implementation
 * et des avancees dans des directions plus importantes
 * ont mis fin a cela et l'implementation est inachevee.
 *
 * La recherche locale (LocalSearch) pourrait devenir un recuit simule
 * en construisant une sous-classe de moveMaster et en changeant
 * la methode accepter_saut.
 */

class MoveMaster{
protected:
    int n;
public:
    MoveMaster(){}
    virtual void init(const vector<int> &registreCoutParFenetre){n = registreCoutParFenetre.size();}
    virtual void operator()(int& i, int& j){
        i = rand()%n;
        j = rand()%n;
    }
    virtual bool testIntegrite(const vector<int> &registreCoutParFenetre){return true;}
    virtual bool accepterSaut(const int & cost_i_apres, const int & cost_j_apres, const int & cost_i_avant, const int & cost_j_avant){
        return cost_i_apres + cost_j_apres - (cost_i_avant + cost_j_avant) <= 0;
    }
};

struct priorite{
    bool operator()(const pair<int,int> &p1, const pair<int,int> &p2){
        return p1.second < p2.second;
    }
};

class CustomQueue{
public:
    int n;
    priority_queue<pair<int,int>, vector<pair<int,int> >, priorite> queue;
    // stocke les paires (indexFenetre, cout)
    vector<bool> isPriority;
    CustomQueue(){}
    CustomQueue(const vector<int> &registreCoutParFenetre);
    pair<int, int> pop();
    void update(const int &i, const int &j, const int & cost_i_apres, const int & cost_j_apres, const int & cost_i_avant, const int & cost_j_avant);
    bool testIntegrite(const vector<int> &registreCoutParFenetre);
};

class MoveMasterWithPriority: public MoveMaster{
    /*
     * i est tire parmi les fenetres prioritaires
     * j est tire au hasard parmi ttes les fenetres
     * si j est ds les fenetres prioritaires, il faut
     * mettre a jour la queue de priorite
     */
    int last_i;
    int last_j;
    CustomQueue fenetresPrioritaires;
public:
    virtual void init(const vector<int> &registreCoutParFenetre){
        n = registreCoutParFenetre.size();
        fenetresPrioritaires = CustomQueue(registreCoutParFenetre);
    }
    virtual void operator()(int& i, int& j){
        i = fenetresPrioritaires.pop().first;
        j = rand()%n;
//        while(fenetresPrioritaires.isPriority[j])
//            j = rand()%n;
        //cout << i << " " << j << endl;
        last_i = i;
        last_j = j;
    }
    virtual bool testIntegrite(const vector<int> &registreCoutParFenetre){return fenetresPrioritaires.testIntegrite(registreCoutParFenetre);}
    virtual bool accepterSaut(const int & cost_i_apres, const int & cost_j_apres, const int & cost_i_avant, const int & cost_j_avant){
        fenetresPrioritaires.update(last_i, last_j, cost_i_apres, cost_j_apres, cost_i_avant, cost_j_avant);
        return cost_i_apres + cost_j_apres - (cost_i_avant + cost_j_avant) <=0;
    }
};
