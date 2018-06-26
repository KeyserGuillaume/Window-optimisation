#include "heuristique.h"
#include <ctime>
#include <vector>
#include <sstream>
#include "SharedElements.h"
using namespace std;

typedef vector<Fenetre> MapFenetres;
typedef vector <Volet> MapVolets;
typedef vector<FenetreAvecVolet> MapSolutions;


Heuristique::Heuristique(string monInstance, CostFunction *myCost){
    instance = monInstance;
    computeCost = myCost;
    init();
}

Heuristique::Heuristique(string monInstance){
    instance = monInstance;
    init();
}

void Heuristique::init(){
    string fenetresFile = "../instances/" + instance + "_fenetres.csv";
    string gauchesFile = "../instances/" + instance + "_voletsGauches.csv";
    string droitsFile = "../instances/" + instance + "_voletsDroits.csv";
    string solutionsFile = "../nosSolutions/" + instance + "_solutionInitiale.csv";
    readCsvToMap<Volet>(droits, droitsFile);
    readCsvToMap(solutionActuelle, solutionsFile);
    readCsvToMap<Volet>(gauches, gauchesFile);
    readCsvToMap<Fenetre>(fenetres, fenetresFile);
    cout << "ok" << endl;
    n = fenetres.size();
    meilleureSolution = solutionActuelle;
    NbRabots NR;
    meilleurePerformance = totalCost(&NR, meilleureSolution);
    if (testIntegriteSolution())
        cout << "Solution initiale correcte." << endl;
    else
        cerr << "Solution initiale incorrecte !" << endl;
    srand((unsigned int)time(0));              //initialisation du generateur aleatoire
}

//reprend la meilleure solution rencontree
void Heuristique::takeBestFind(){
    solutionActuelle = meilleureSolution;
}

int Heuristique::cost(const FenetreAvecVolet & solution){
    return (*computeCost)(fenetres[solution.indexFenetre], gauches[solution.indexVoletGauche], droits[solution.indexVoletDroit]);
}

int Heuristique::totalCost(MapSolutions solutions){
    int result = 0;
    for (vector< FenetreAvecVolet>::iterator it = solutions.begin(); it!= solutions.end(); ++it){
        result += cost(*it);
    }
    return result;
}

void Heuristique::sauvegarder(){
    NbRabots NR;
    int cost_now = totalCost(&NR, solutionActuelle);
    if (cost_now < meilleurePerformance){
        meilleurePerformance = cost_now;
        meilleureSolution = solutionActuelle;
        printMapToCsv<FenetreAvecVolet>(solutionActuelle, "../nosSolutions/" + instance + "_solution.csv");
    }
}

bool Heuristique::testIntegriteSolution(){
    bool result = true;
    if (gauches.size()!=n){
        cerr << "Heuristique::testIntegriteSolution : le nombre de volets gauches ne correspond pas ! n = " << n << " et il y a " << gauches.size() << " volets gauches" << endl;
        result = false;
    }

    if (droits.size()!=n){
        cerr << "Heuristique::testIntegriteSolution : le nombre de volets droits ne correspond pas ! n = " << n << " et il y a " << droits.size() << " volets droits" << endl;
        result = false;
    }

    if (fenetres.size()!=n){
        cerr << "Heuristique::testIntegriteSolution : le nombre de fenetres ne correspond pas ! n=" << n << "et il y a " << fenetres.size() << "fenetres" << endl;
        result = false;
    }
    // ici il y a une verif a faire a cause d'une repetition dans la maniere d'encoder une solution
    // on suppose que solution[i].indexFenetre = i
    //
    vector< bool> voletsGauchesVisites(n, false);
    vector< bool> voletsDroitsVisites(n, false);
    vector< bool> fenetresVisitees(n, false);
    int count=0;
    for (vector< FenetreAvecVolet>::iterator it = solutionActuelle.begin(); it!= solutionActuelle.end(); ++it){
        voletsGauchesVisites[it->indexVoletGauche] = true;
        voletsDroitsVisites[it->indexVoletDroit] = true;
        fenetresVisitees[it->indexFenetre] = true;
        if (count!=it->indexFenetre){
            cerr<<"Heuristique::testIntegriteSolution : solution actuelle mal indexee; solutionActuelle["<<count<<"] contient la fenetre "<<it->indexFenetre<<endl;
            result = false;
        }
//        if (nbRabotsFenetre(*it)!=registreNbRabotParFenetre[count2]){
//            cerr<<"Heuristique::testIntegriteSolution : registreNbRabotParFenetre mal tenu" << endl;
//            result = false;
//        }
        count++;
    }
    int nbVoletsGauchesPasVisites = 0;
    int nbVoletsDroitsPasVisites = 0;
    int nbFenetresPasVisitees = 0;
    for (vector< bool>::iterator it= voletsGauchesVisites.begin(); it!=voletsGauchesVisites.end();++it){
        if (!*it)
            nbVoletsGauchesPasVisites++;
    }
    for (vector< bool>::iterator it= voletsDroitsVisites.begin(); it!=voletsDroitsVisites.end();++it){
        if (!*it)
            nbVoletsDroitsPasVisites++;
    }
    for (vector< bool>::iterator it= fenetresVisitees.begin(); it!=fenetresVisitees.end();++it){
        if (!*it)
            nbFenetresPasVisitees++;
    }
    if (nbVoletsGauchesPasVisites>0){
        cerr << "Heuristique::testIntegriteSolution : " << nbVoletsGauchesPasVisites << " volets gauches n'ont pas ete assignes de fenetre" << endl;
        result = false;
    }
    if (nbVoletsDroitsPasVisites>0){
        cerr << "Heuristique::testIntegriteSolution : " << nbVoletsDroitsPasVisites << " volets droits n'ont pas ete assignes de fenetre" << endl;
        result = false;
    }
    if (nbFenetresPasVisitees>0){
        cerr << "Heuristique::testIntegriteSolution : " << nbFenetresPasVisitees << " fenetres n'ont pas ete assignes de volets" << endl;
        result = false;
    }
    return result;
}

int nb_chiffres(int i){
    if (i < 2)
        return 1;
    else
        return 1 + int(log(i)/log(10));
}

void Heuristique::stats(){
    map<int, int> count;
    for (vector< FenetreAvecVolet>::iterator it = solutionActuelle.begin(); it!= solutionActuelle.end(); ++it){
        count[cost(*it)]++;
    }
    int max_cost = count.rbegin()->first;
    cout << "  statistiques : histogramme sur le cout par fenetre" << endl;
    for (int i=0; i<max_cost+1; i++)
        cout << i << "       ";
    cout << endl;
    for (int i=0; i<max_cost+1; i++){
        cout << count[i] << string(7-nb_chiffres(count[i])+nb_chiffres(i), ' ');
    }
    cout << endl;
}

void Heuristique::stats(CostFunction* myCost){
    CostFunction* temp = computeCost;
    computeCost = myCost;
    stats();
    computeCost = temp;
}

int Heuristique::totalCost(const CostFunction* myCost, MapSolutions solution){
    /*
     * qd on veut calculer le cout pour une autre fonction objectif
     */
    int result = 0;
    for (vector< FenetreAvecVolet>::iterator it = solution.begin(); it!= solution.end(); ++it){
        result += (*myCost)(fenetres[it->indexFenetre], gauches[it->indexVoletGauche], droits[it->indexVoletDroit]);
    }
    return result;
}
