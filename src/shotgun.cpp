#include "shotgun.h"

using namespace std;

Shotgun::Shotgun(string monInstance):Heuristique(monInstance){
    TR = TaillePenaliseeRabots();
    setCost(&TR);
}

void Shotgun::run(){
    /*
     * On tient une liste des volets gauche et droit candidats.
     * Pour chaque fenetre, on prend la paire de volets de plus petite marge positive.
     * Si aucune paire de volets n'a de marge positive, on prend la paire qui donne
     * un cout maximal (en taille des rabots) parmi celles qui donnent un nb de rabots
     * minimal.
     * Les volets choisis sont retires des volets candidats.
     * On itere jusqu'a ce qu'il n'y ait plus de fenetres.
     */
    vector<int> candidatsG(n);
    vector<int> candidatsD(n);
    NbRabots NR;
    Marge compute_marge;
    for (int i=0; i<n; i++){
        candidatsG[i] = i;
        candidatsD[i] = i;
    }
    for (int i=0; i<n; i++){
        cout << i << endl;
        int min_marge = INFINITY;
        int m;
        int min_g = -1;
        int min_d = -1;
        for (auto itg=candidatsG.begin(); itg!=candidatsG.end(); itg++){
            for (auto itd=candidatsD.begin(); itd!=candidatsD.end(); itd++){
                m = compute_marge(fenetres[i], gauches[*itg], droits[*itd]);
                if (m >= 0 && m < min_marge){
                    min_marge = m;
                    min_g = *itg;
                    min_d = *itd;
                }
            }
        }
        if (min_d == -1){ // cas ou on a pas de solution sans coup de rabot
            // on repere les fenetres avec le moins de coups de rabot
            vector<vector<pair<int, int>>> groupes_paires_volets(6);
            int min_rabots = 7;
            for (auto itg=candidatsG.begin(); itg!=candidatsG.end(); itg++){
                for (auto itd=candidatsD.begin(); itd!=candidatsD.end(); itd++){
                    int nb_rabots = NR(fenetres[i], gauches[*itg], droits[*itd]);
                    if (nb_rabots <= min_rabots){
                        groupes_paires_volets[nb_rabots].push_back(pair<int, int>(*itg, *itd));
                        min_rabots = nb_rabots;
                    }
                }
            }
            // on choisit la paire de volets de taille de rabot maximal
            int max_cost = 0;
            int cost;
            for (auto it=groupes_paires_volets[min_rabots].begin(); it!=groupes_paires_volets[min_rabots].end(); it++){
                cost = (*computeCost)(fenetres[i], gauches[it->first], droits[it->second]);
                if (cost > max_cost){
                    max_cost = cost;
                    min_g = it->first;
                    min_d = it->second;
                }
            }
        }
        //candidatsG.erase(candidatsG.begin() + min_g);
        for (auto itg = candidatsG.begin(); itg != candidatsG.end(); itg++){
            if (*itg == min_g){
                candidatsG.erase(itg);
                break;
            }
        }
        //candidatsD.erase(candidatsD.begin() + min_d);
        solutionActuelle[i] = FenetreAvecVolet(i, min_g, min_d);
        for (auto itd = candidatsD.begin(); itd != candidatsD.end(); itd++){
            if (*itd == min_d){
                candidatsD.erase(itd);
                break;
            }
        }
    }
    testIntegriteSolution();
    sauvegarder();
}
