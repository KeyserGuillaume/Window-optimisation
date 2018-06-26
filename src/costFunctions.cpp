#include "costFunctions.h"

int NbRabots::operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const{
    int result = 0;
    //bloque en haut à gauche
    if (gauche.hauteurGondSommet > fenetre.hauteurGondSommetGauche ||  \
            gauche.hauteurInterGonds + gauche.hauteurGondSommet > fenetre.hauteurInterGondsGauche + fenetre.hauteurGondSommetGauche){
        ++result;
    }

    //bloque en bas à gauche
    if (gauche.hauteurTotale - gauche.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche && \
            gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche){
        ++result;
    }

    //bloque en haut à droit
    if (droit.hauteurGondSommet > fenetre.hauteurGondSommetDroite ||  \
            droit.hauteurInterGonds + droit.hauteurGondSommet > fenetre.hauteurInterGondsDroite + fenetre.hauteurGondSommetDroite ){
        ++result;
    }

    //bloque en bas à droit
    if (droit.hauteurTotale - droit.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite && \
            droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite){
        ++result;
    }
    // bloque au centre
    if (gauche.largeur + droit.largeur > fenetre.largeurTotale)
    {
        ++result;
    }
    return result;
}

int TailleRabots::operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const{
    int result = 0;
    //bloque en haut à gauche
    if (gauche.hauteurGondSommet > fenetre.hauteurGondSommetGauche ||  \
            gauche.hauteurInterGonds + gauche.hauteurGondSommet > fenetre.hauteurInterGondsGauche + fenetre.hauteurGondSommetGauche){
        result += max(gauche.hauteurGondSommet - fenetre.hauteurGondSommetGauche,
                      gauche.hauteurInterGonds + gauche.hauteurGondSommet - fenetre.hauteurInterGondsGauche - fenetre.hauteurGondSommetGauche);
    }

    //bloque en bas à gauche
    if (gauche.hauteurTotale - gauche.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche && \
            gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche){
        result += min(gauche.hauteurTotale - gauche.hauteurGondSommet - (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche),
                     gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds
                     - (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche));
    }

    //bloque en haut à droit
    if (droit.hauteurGondSommet > fenetre.hauteurGondSommetDroite ||  \
            droit.hauteurInterGonds + droit.hauteurGondSommet > fenetre.hauteurInterGondsDroite + fenetre.hauteurGondSommetDroite ){
        result += max(droit.hauteurGondSommet - fenetre.hauteurGondSommetDroite,
                      droit.hauteurInterGonds + droit.hauteurGondSommet - fenetre.hauteurInterGondsDroite - fenetre.hauteurGondSommetDroite);
    }

    //bloque en bas à droit
    if (droit.hauteurTotale - droit.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite && \
            droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite){
        result += min(droit.hauteurTotale - droit.hauteurGondSommet - (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite),
                     droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds
                     - (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite));
    }
    // bloque au centre
    if (gauche.largeur + droit.largeur > fenetre.largeurTotale)
    {
        result += gauche.largeur + droit.largeur - fenetre.largeurTotale;
    }
    return result;
}

int TaillePenaliseeRabots::operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const{
    int result = 0;
    //bloque en haut à gauche
    if (gauche.hauteurGondSommet > fenetre.hauteurGondSommetGauche ||  \
            gauche.hauteurInterGonds + gauche.hauteurGondSommet > fenetre.hauteurInterGondsGauche + fenetre.hauteurGondSommetGauche){
        result += max(gauche.hauteurGondSommet - fenetre.hauteurGondSommetGauche,
                      gauche.hauteurInterGonds + gauche.hauteurGondSommet - fenetre.hauteurInterGondsGauche - fenetre.hauteurGondSommetGauche);
        result += cout_fixe;
    }

    //bloque en bas à gauche
    if (gauche.hauteurTotale - gauche.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche && \
            gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche){
        result += min(gauche.hauteurTotale - gauche.hauteurGondSommet - (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche),
                     gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds
                     - (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche));
        result += cout_fixe;
    }

    //bloque en haut à droit
    if (droit.hauteurGondSommet > fenetre.hauteurGondSommetDroite ||  \
            droit.hauteurInterGonds + droit.hauteurGondSommet > fenetre.hauteurInterGondsDroite + fenetre.hauteurGondSommetDroite ){
        result += max(droit.hauteurGondSommet - fenetre.hauteurGondSommetDroite,
                      droit.hauteurInterGonds + droit.hauteurGondSommet - fenetre.hauteurInterGondsDroite - fenetre.hauteurGondSommetDroite);
        result += cout_fixe;
    }

    //bloque en bas à droit
    if (droit.hauteurTotale - droit.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite && \
            droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite){
        result += min(droit.hauteurTotale - droit.hauteurGondSommet - (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite),
                     droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds
                     - (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite));
        result += cout_fixe;
    }
    // bloque au centre
    if (gauche.largeur + droit.largeur > fenetre.largeurTotale)
    {
        result += gauche.largeur + droit.largeur - fenetre.largeurTotale;
        result += cout_fixe;
    }
    return result;
}

bool TaillePenaliseeAlterne::change(){
    if (i==1){
        if (n < n_max_1){
            n++;
            return false;
        }
        else{
            i = 2;
            n = 0;
            cout_fixe = cout2;
            return true;
        }
    }
    if (i==2){
        if (n < n_max_2){
            n++;
            return false;
        }
        else{
            i = 1;
            n = 0;
            cout_fixe = cout1;
            return true;
        }
    }
}

int TailleLogPenaliseeRabots::operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const{
    int result = 0;
    //bloque en haut à gauche
    if (gauche.hauteurGondSommet > fenetre.hauteurGondSommetGauche ||  \
            gauche.hauteurInterGonds + gauche.hauteurGondSommet > fenetre.hauteurInterGondsGauche + fenetre.hauteurGondSommetGauche){
        result += (int)(alpha*log(max(gauche.hauteurGondSommet - fenetre.hauteurGondSommetGauche,
                      gauche.hauteurInterGonds + gauche.hauteurGondSommet - fenetre.hauteurInterGondsGauche - fenetre.hauteurGondSommetGauche)));
        result += cout_fixe;
    }

    //bloque en bas à gauche
    if (gauche.hauteurTotale - gauche.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche && \
            gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche){
        result += (int)(alpha*log(min(gauche.hauteurTotale - gauche.hauteurGondSommet - (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche),
                     gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds
                     - (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche))));
        result += cout_fixe;
    }

    //bloque en haut à droit
    if (droit.hauteurGondSommet > fenetre.hauteurGondSommetDroite ||  \
            droit.hauteurInterGonds + droit.hauteurGondSommet > fenetre.hauteurInterGondsDroite + fenetre.hauteurGondSommetDroite ){
        result += (int)(alpha*log(max(droit.hauteurGondSommet - fenetre.hauteurGondSommetDroite,
                      droit.hauteurInterGonds + droit.hauteurGondSommet - fenetre.hauteurInterGondsDroite - fenetre.hauteurGondSommetDroite)));
        result += cout_fixe;
    }

    //bloque en bas à droit
    if (droit.hauteurTotale - droit.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite && \
            droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite){
        result += (int)(alpha*log(min(droit.hauteurTotale - droit.hauteurGondSommet - (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite),
                     droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds
                     - (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite))));
        result += cout_fixe;
    }
    // bloque au centre
    if (gauche.largeur + droit.largeur > fenetre.largeurTotale)
    {
        result += (int)(alpha*log(gauche.largeur + droit.largeur - fenetre.largeurTotale));
        result += cout_fixe;
    }
    return result;
}

int Marge::operator ()(const Fenetre & fenetre, const Volet & gauche, const Volet & droit)const{
    int result = 0; int tmp;
    tmp = min( - gauche.hauteurGondSommet + fenetre.hauteurGondSommetGauche,
                   - gauche.hauteurInterGonds - gauche.hauteurGondSommet + fenetre.hauteurInterGondsGauche + fenetre.hauteurGondSommetGauche);
    if (tmp < 0) return -1; else  result += tmp;
    tmp = max(- gauche.hauteurTotale + gauche.hauteurGondSommet + (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche),
                  - gauche.hauteurTotale + gauche.hauteurGondSommet + gauche.hauteurInterGonds
                  + (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche));
    if (tmp < 0) return -1; else  result += tmp;
    tmp = min( - droit.hauteurGondSommet + fenetre.hauteurGondSommetDroite,
                   - droit.hauteurInterGonds - droit.hauteurGondSommet + fenetre.hauteurInterGondsDroite + fenetre.hauteurGondSommetDroite);
    if (tmp < 0) return -1; else  result += tmp;
    tmp = max(-droit.hauteurTotale + droit.hauteurGondSommet + (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite),
                  -droit.hauteurTotale + droit.hauteurGondSommet + droit.hauteurInterGonds
                  + (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite));
    if (tmp < 0) return -1; else  result += tmp;
    tmp = gauche.largeur + droit.largeur - fenetre.largeurTotale;
    if (tmp > 0) return -1; else  result -= tmp;
    return result;
}

int TailleLogMargePenalisee::operator()( const Fenetre & fenetre, const Volet & gauche, const Volet & droit) const{
    int result = 0;
    //bloque en haut à gauche
    if (gauche.hauteurGondSommet > fenetre.hauteurGondSommetGauche ||  \
            gauche.hauteurInterGonds + gauche.hauteurGondSommet > fenetre.hauteurInterGondsGauche + fenetre.hauteurGondSommetGauche){
        result += (int)log(max(gauche.hauteurGondSommet - fenetre.hauteurGondSommetGauche,
                      gauche.hauteurInterGonds + gauche.hauteurGondSommet - fenetre.hauteurInterGondsGauche - fenetre.hauteurGondSommetGauche));
        result += cout_fixe;
    }

    //bloque en bas à gauche
    if (gauche.hauteurTotale - gauche.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche && \
            gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche){
        result += (int)log(min(gauche.hauteurTotale - gauche.hauteurGondSommet - (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche),
                     gauche.hauteurTotale - gauche.hauteurGondSommet - gauche.hauteurInterGonds
                     - (fenetre.hauteurTotale - fenetre.hauteurGondSommetGauche - fenetre.hauteurInterGondsGauche)));
        result += cout_fixe;
    }

    //bloque en haut à droit
    if (droit.hauteurGondSommet > fenetre.hauteurGondSommetDroite ||  \
            droit.hauteurInterGonds + droit.hauteurGondSommet > fenetre.hauteurInterGondsDroite + fenetre.hauteurGondSommetDroite ){
        result += (int)(log(max(droit.hauteurGondSommet - fenetre.hauteurGondSommetDroite,
                      droit.hauteurInterGonds + droit.hauteurGondSommet - fenetre.hauteurInterGondsDroite - fenetre.hauteurGondSommetDroite)));
        result += cout_fixe;
    }

    //bloque en bas à droit
    if (droit.hauteurTotale - droit.hauteurGondSommet > fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite && \
            droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds > \
                fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite){
        result += (int)(log(min(droit.hauteurTotale - droit.hauteurGondSommet - (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite),
                     droit.hauteurTotale - droit.hauteurGondSommet - droit.hauteurInterGonds
                     - (fenetre.hauteurTotale - fenetre.hauteurGondSommetDroite - fenetre.hauteurInterGondsDroite))));
        result += cout_fixe;
    }
    // bloque au centre
    if (gauche.largeur + droit.largeur > fenetre.largeurTotale)
    {
        result += (int)(log(gauche.largeur + droit.largeur - fenetre.largeurTotale));
        result += cout_fixe;
    }
    if (result==0){
        result += (int)(cout_marge * Marge::operator()(fenetre, gauche, droit));
    }
    return result;
}
