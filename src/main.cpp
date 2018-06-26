#include "heuristique.h"
#include "costFunctions.h"
#include "localSearch.h"
#include "moveMaster.h"
#include "shotgun.h"

#include <map>
#include <vector>
#include <sstream>
#include "SharedElements.h"
using namespace std;

typedef vector<Fenetre> MapFenetres;
typedef vector <Volet> MapVolets;
typedef vector<FenetreAvecVolet> MapSolutions;

//cette fonction cree un premier fichier _solution.csv.
//en fait recuperer le fichier des fenetres ne sert qu'a
//savoir combien de fenetres il y a sans devoir les ouvrir
//un par un
void initSolution(const string &instance){
    MapFenetres fenetres;
    MapSolutions solution;
    cout<<"ready to read path " << "../instances/" << instance << "_fenetres.csv" <<endl;
    readCsvToMap<Fenetre>(fenetres, "../instances/" + instance + "_fenetres.csv");
    for (int i=0; i < fenetres.size(); i++){
        FenetreAvecVolet F(i, i, i);
        solution.push_back(F);
    }
    printMapToCsv<FenetreAvecVolet>(solution, "../nosSolutions/" + instance + "_solutionInitiale.csv");
    cout<<"initialisation successful"<<endl;
}

int main(){
    string tailles[5] = {"petite", "moyenne", "grande", "versailles", "groupe"};

    //string faisable = "Faisable";
    string faisable = "Opt";

    string instance = tailles[2] + faisable;

    initSolution(instance);  // A appeler la premiere fois qu'on travaille sur l'instance

    NbRabots NR;
    TailleRabots TR;
    TailleLogPenaliseeRabots CF;
//    Shotgun S(instance);
//    S.run();
//    S.display(&NR);
//    S.stats(&TR);
//    return 0;

    //Heuristique H(instance, &TR);
    //H.stats();
    MoveMaster MM;
    LocalSearch LS(instance, &CF, &MM);
    LS.stats(&TR);
    LS.run(1000*1000*1000);//*30LL);
    LS.stats(&TR);
    LS.display(&NR);
    return 0;
}
