#include "moveMaster.h"
using namespace std;

CustomQueue::CustomQueue(const vector<int> &registreCoutParFenetre){
    n = registreCoutParFenetre.size();
    isPriority = vector<bool>(n, false);
    for (int i=0; i<n; i++){
        if (registreCoutParFenetre[i] > 0){
            isPriority[i] = true;
            queue.push(pair<int, int> (i, registreCoutParFenetre[i]));
        }
    }
    cout << "taille de la queue : " <<  queue.size() << endl;
}

pair<int, int> CustomQueue::pop(){
    pair<int, int> p = queue.top();
    queue.pop();
    return p;
}

void CustomQueue::update(const int &i, const int &j, const int & cost_i_apres, const int & cost_j_apres, const int & cost_i_avant, const int & cost_j_avant){
    //cout << "update" << " "<< i << " " << j << " " << cost_j_avant << " " << cost_j_apres << endl;
    if (isPriority[j] && cost_j_avant != cost_j_apres){
        // we want to remove j from the queue but since it's bothersome we make a new one
        priority_queue<pair<int,int>, vector<pair<int,int> >, priorite> new_queue;
        pair<int, int> p;
        while(!queue.empty()){
            p = queue.top();
            queue.pop();
            if (p.first != j)
                new_queue.push(p);
        }
        queue = new_queue;
        if (cost_j_apres > 0)
            // j has to be pushed again
            queue.push(pair<int, int> (j, cost_j_apres));
        else
            isPriority[j] = false;
    }
    else if (!isPriority[j] && cost_j_apres > 0){
        isPriority[j] = true;
        queue.push(pair<int, int> (j, cost_j_apres));
    }
    if (cost_i_apres > 0)
        queue.push(pair<int, int>(i, cost_i_apres));
    else
        isPriority[i] = false;
}

bool CustomQueue::testIntegrite(const vector<int> &registreCoutParFenetre){
    pair<int, int> p;
    bool result = true;
    while(!queue.empty()){
        p = queue.top();
        //cerr << queue.size() << endl;
        queue.pop();
        if (p.second != registreCoutParFenetre[p.first]){
            cerr << "moveMaster.h:testIntegrite:: queue de priorite erronee." << p.first << " " << p.second << " " << registreCoutParFenetre[p.first] << endl;
            result = false;
        }
        if (!isPriority[p.first]){
            cerr << "moveMaster.h:testIntegrite:: registre de priorite non coherent." << p.first << " " << p.second << " " << registreCoutParFenetre[p.first] << endl;
            result = false;
        }
    }
    for (int i=0; i<n; i++){
        if (registreCoutParFenetre[i] > 0){
            isPriority[i] = true;
            queue.push(pair<int, int> (i, registreCoutParFenetre[i]));
        }
    }
    return result;
}
