#pragma once
#include "SharedElements.h"
using namespace std;

/*
 * La fonction de cout que doit minimiser des heuristiques
 * comme la descente locale.
 * Les commentaires de convergence concernent LocalSearch
 * avec MoveMaster (une simple descente locale).
 */

class CostFunction{
public:
    virtual int operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const = 0;
    virtual bool change(){return false;}

};

class NbRabots: public CostFunction{
    /*
     * La plus immediate : on minimise le nombre de rabots.
     * Le temps de convergence vers un minimum local est si
     * long que sur l'instance Versailles, il ne serait sans
     * doute pas atteint meme apres plusieurs jours d'execution
     * (donc des centaines de milliards d'iterations).
     * La descente locale est laissee trop libre pour donner
     * les meilleurs solutions en temps raisonnable.
     */
public:
    virtual int operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const;
};

class TailleRabots: public CostFunction{
    /*
     * On minimise la taille des rabots (sommee).
     * Trop eloignee de la problematique du nombre
     * de rabots, elle a toutefois l'avantage de
     * converger en temps raisonnable (qq heures).
     */
    virtual int operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const;
};

class TaillePenaliseeRabots: public CostFunction{
    /*
     * On minimise la taille des rabots, mais
     * on ajoute un cout fixe pour chaque fenetre
     * si le nombre de rabots est non nul.
     * Ci-dessous, la dependance au parametre
     * cout_fixe sur l'instance VersaillesOpt,
     * apres 1 milliard d'iterations.
     * 24, 28 -> 479
     * 34 -> 474
     * 40 -> 479
     * 46 -> 477
     * Regle son compte a Versailles Faisable
     * en environ 100 millions d'iterations (qq secondes).
     */
protected:
    int cout_fixe = 30;
public:
    virtual int operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const;
};

class TaillePenaliseeAlterne: public TaillePenaliseeRabots{
    /*
     * Meme chose qu'avant, sauf qu'on fait varier le cout
     * fixe qu'on ajoute.
     * Amelioration incertaine par rapport a la methode precedente.
     */
    int i = 1;
    int n = 0;
    int n_max_1 = 10;
    int n_max_2 = 10;
    int cout1 = 20;
    int cout2 = 25;
public:
    TaillePenaliseeAlterne(){cout_fixe = cout1;}
    virtual bool change();
};

class TailleLogPenaliseeRabots: public CostFunction{
    /*
     * Produit les meilleures solutions connues sur les
     * instances Opt (dont VersaillesOpt).
     * Ajoute un cout fixe si le nombre de rabots est > 0
     * La taille des rabots est ajoutee en log pour ne pas
     * trop penaliser des tailles de rabots importantes.
     * (n'est pertinent que dans les cas où il n'y a pas de solution faisable)
     * Ci-dessous, la dependance au parametre
     * cout_fixe sur l'instance VersaillesOpt,
     * apres 1 milliard d'iterations.
     * 0  -> ~5000
     * 15 -> 403
     * 30 -> 412 -> 373 (alpha = 1, 30 milliards d'iterations ~3h)
     * 30 -> 409
     * 45 -> 407
     * Le parametre alpha, pris proche de 1, n'a pas d'influence sur les resultats.
     */
protected:
    int cout_fixe = 30;
    int alpha = 1;
public:
    virtual int operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const;
};

class Marge: public CostFunction{
    /*
     * Ne definit pas une cost function pour toutes les solutions
     * Si la fenetre admet des coups de rabot, renvoie -1
     * Cela permet de visualiser les marges restantes sur
     * les fenetres d'une bonne solution issue des algorithmes
     * d'optimisation. Des marges tres petites suggerent que
     * la solution est proche de l'optimum.
     */
public:
    virtual int operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const;
};


class TailleLogMargePenalisee: public Marge{
    /*
     * Cout fixe si le nombre de rabots est > 0
     * La taille des rabots est ajoutee en log
     * La marge est comptee negativement
     * cout_marge = 1   ->
     * cout_marge = 0.2 -> 441
     * Les resulats sont moins bons que quand on
     * ne compte pas la marge, donc cela semble
     * etre une impasse pour l'instant.
     */
protected:
    int cout_fixe = 30;
    float cout_marge = 1;
    int marge(const Fenetre & fenetre, const Volet & gauche, const Volet & droit)const;
    virtual int operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const;
};
