#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h> 
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

/*
 * Ce fichier et le fichier SharedElements.cpp sont fournis par Axel Parmentier,
 * a la modification pres que la structure std::map a ete remplacee par la structure
 * std::vector pour accelerer les calculs.
 */

class Volet{
public:
	int index;
	int hauteurTotale;
	int hauteurGondSommet;
	int hauteurInterGonds;
	int largeur;

	int getIndex(){return index;}
	string classDescription(){
		return "index, hauteurTotale, hauteurGondSommet, hauteurInterGonds, largeur, ";
	}
	string toString(){
		stringstream result;
		result << index << ", ";
		result << hauteurTotale << ", ";
		result << hauteurGondSommet << ", ";
		result << hauteurInterGonds << ", ";
		result << largeur << ", ";
		return result.str();
	}
	Volet(){}
	Volet(string description){
		stringstream read(description);
		read >> index;
		read >> hauteurTotale;
		read >> hauteurGondSommet;
		read >> hauteurInterGonds;
		read >> largeur;	
	}
    inline int distanceL2(const Volet &v){return pow(hauteurTotale-v.hauteurTotale, 2)+pow(hauteurGondSommet - v.hauteurGondSommet, 2)
                +pow(hauteurInterGonds - v.hauteurInterGonds, 2) + pow(largeur - v.largeur, 2);
    }
};


class Fenetre
{
public:
	int index;
	int hauteurTotale;
	int largeurTotale;
	int hauteurInterGondsGauche;
	int hauteurGondSommetGauche;
	int hauteurInterGondsDroite;
	int hauteurGondSommetDroite;

	int getIndex(){return index;}
	string classDescription(){
		stringstream result;
		result << "index, ";
		result << "hauteurTotale, ";
		result << "largeurTotale, ";
		result << "hauteurInterGondsGauche, ";
		result << "hauteurGondSommetGauche, ";
		result << "hauteurInterGondsDroite, ";
		result << "hauteurGondSommetDroite, ";
		return result.str();
	}
	string toString(){
		stringstream result;
		result << index << ", ";
		result << hauteurTotale << ", ";
		result << largeurTotale << ", ";
		result << hauteurInterGondsGauche << ", ";
		result << hauteurGondSommetGauche << ", ";
		result << hauteurInterGondsDroite << ", ";
		result << hauteurGondSommetDroite << ", ";
		return result.str();
	}
	Fenetre(){}
	Fenetre(string description){
		stringstream read(description);
		read >> index;
		read >> hauteurTotale;
		read >> largeurTotale;
		read >> hauteurInterGondsGauche;
		read >> hauteurGondSommetGauche;
		read >> hauteurInterGondsDroite;
		read >> hauteurGondSommetDroite;		
	}
};

class FenetreAvecVolet
{
public:
	int indexFenetre;
	int indexVoletGauche;
	int indexVoletDroit;

	int getIndex(){return indexFenetre;}

	string classDescription(){
		stringstream result;
		result << "indexFenetre, ";
		result << "indexVoletGauche, ";
		result << "indexVoletDroit, ";
		return result.str();
	}
	string toString(){
		stringstream result;
		result << indexFenetre << ", ";
		result << indexVoletGauche << ", ";
		result << indexVoletDroit << ", ";
		return result.str();
	}
	FenetreAvecVolet(){}
    FenetreAvecVolet(int fen, int volG, int volD){indexFenetre=fen;indexVoletDroit=volD;indexVoletGauche=volG;}
	FenetreAvecVolet(string description){
		stringstream read(description);
		read >> indexFenetre;
		read >> indexVoletGauche;
		read >> indexVoletDroit;
	}
};

void removeOneSubstring(string& s, string const & p);

// void removeOneSubstring(string& s, string const & p) { 
//   string::size_type n = p.length();
//   for (string::size_type i = s.find(p);
//       i != string::npos;
//       i = s.find(p))
//       s.erase(i, n);
// }


template <typename Element>
void readCsvToMap(vector<Element> & readMap, string filename){
	ifstream read(filename.c_str());
    if (!read.is_open()) {cout << "pb with opening file " << filename << endl; throw;}
	string line;
	getline(read, line); // nbElements
	getline(read, line); // Description line
	while (getline(read, line)){
		removeOneSubstring(line, ",");

		Element elem(line);
        readMap.push_back(elem);
	}
}

template <typename Element>
void printMapToCsv(vector<Element> printedMap, string filename){
	ofstream write(filename.c_str());
	if (!write.is_open())
	{
        cout << "pb with opening file" << endl; throw;
	}
	write << "nbElements: " << printedMap.size() << endl;
    write << printedMap.begin()->classDescription() << endl;
    for (typename vector<Element>::iterator it = printedMap.begin(); it!= printedMap.end(); ++it){
        write << it->toString() << endl;
	}
}

