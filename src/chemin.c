#include "chemin.h"
#include <assert.h>
#include <stddef.h>

CH_Chemin CH_chemin(){
    CH_Chemin ch;
    ch.etapes = LCF_file(NULL, NULL);
    ch.longueur = 0;
    return ch;
}

void CH_enfilerEtape(CH_Chemin* ch, CO_Coordonnee* etape){
    LCF_enfiler(&ch->etapes, etape);
    ch->longueur = ch->longueur + 1;
}

CO_Coordonnee CH_defilerEtape(CH_Chemin* ch){
    assert(ch->longueur > 0);
    CO_Coordonnee c;
    c = *(CO_Coordonnee*)LCF_defiler(&ch->etapes);
    ch->longueur = ch->longueur - 1;
    return c;
}

unsigned int CH_longueurChemin(CH_Chemin ch){
    return ch.longueur;
}

void CH_supprimerChemin(CH_Chemin* ch){
    LCF_vider(&ch->etapes);
}