/**
 * \file trajet.c
 * \brief Implémentation des fonctions de calcul de trajet
 * \author Youssef Hajbi
 * \version 1.1 (Ajout Algo Voyageur de Commerce)
 */

#include "trajet.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h> /* Pour INT_MAX */

/* -------------------------------------------------------------------------- */
/* FONCTIONS PRIVÉES                                                          */
/* -------------------------------------------------------------------------- */

/**
 * \brief Vide le chemin 'segment' et ajoute ses étapes à 'cheminPrincipal'.
 */
static void TR_ajouterSegment(CH_Chemin* cheminPrincipal, CH_Chemin* segment) {
    while (longueurChemin(segment) > 0) {
        CO_Coordonnee etape = defilerEtape(segment);
        enfilerEtape(cheminPrincipal, &etape);
    }
}

/* -------------------------------------------------------------------------- */
/* FONCTIONS PUBLIQUES                                                        */
/* -------------------------------------------------------------------------- */

 

static float distanceManhattan(CO_Coordonnee a, CO_Coordonnee b) {
    int dx = abs((int)CO_abscisse(a) - (int)CO_abscisse(b));
    int dy = abs((int)CO_ordonnee(a) - (int)CO_ordonnee(b));
    return (float)(dx + dy);
}

/**
 * \brief Trouve la coordonnée avec le plus petit f dans aVisiter
 */
static CO_Coordonnee extraireMinF(LCL_Liste* aVisiter, THD_Dictionnaire coutF) {
    if (LCL_estVide(*aVisiter)) {
        return CO_coordonnee(UINT_MAX, UINT_MAX);
    }
    
    unsigned int longueur = LCL_longueur(*aVisiter);
    unsigned int indiceMin = 0;
    float fMin = INFINITY;
    
    // Trouver l'indice avec le plus petit f
    for (unsigned int i = 0; i < longueur; i++) {
        CO_Coordonnee* coord = (CO_Coordonnee*)LCL_element(*aVisiter, i);
        if (coord != NULL) {
            float* pf = (float*)THD_valeur(coutF, coord);
            if (pf != NULL && *pf < fMin) {
                fMin = *pf;
                indiceMin = i;
            }
            free(pf);
        }
        free(coord);
    }
    
    // Extraire cette coordonnée
    CO_Coordonnee* coordMin = (CO_Coordonnee*)LCL_element(*aVisiter, indiceMin);
    CO_Coordonnee result = *coordMin;
    free(coordMin);
    LCL_supprimer(aVisiter, indiceMin);
    
    return result;
}

/**
 * \brief Reconstruit le chemin depuis l'arrivée
 */
static void TR_reconstruireChemin(CH_Chemin* leChemin, THD_Dictionnaire parents, CO_Coordonnee depart, CO_Coordonnee arrivee) {
    LCL_Liste pile = LCL_liste(CO_copier, CO_liberer);
    CO_Coordonnee courant = arrivee;
    
    // Remonter du but au départ
    while (!CO_sontEgales(courant, depart)) {
        LCL_inserer(&pile, &courant, 0);
        
        CO_Coordonnee* parent = (CO_Coordonnee*)THD_valeur(parents, &courant);
        if (parent == NULL) break;
        
        courant = *parent;
        free(parent);
    }
    
    // Ajouter le départ
    LCL_inserer(&pile, &depart, 0);
    
    // Dépiler dans le chemin
    unsigned int longueur = LCL_longueur(pile);
    for (unsigned int i = 0; i < longueur; i++) {
        CO_Coordonnee* coord = (CO_Coordonnee*)LCL_element(pile, i);
        if (coord != NULL) {
            CH_enfilerEtape(leChemin, coord);
            free(coord);
        }
    }
    
    LCL_vider(&pile);
}


/**
 * \brief Algorithme A* utilisant le graphe du terrain
 */
CH_Chemin TR_plusCourtChemin(T_Terrain terrain, CO_Coordonnee depart, CO_Coordonnee arrivee) {
    CH_Chemin leChemin = CH_chemin();
    
    // Ensemble des coordonnées visitées (liste fermée)
    THE_Ensemble noeudVisites = THE_ensemble(CO_copier, CO_liberer, CO_comparer, sizeof(CO_Coordonnee));
    
    // Liste des coordonnées à visiter (liste ouverte)
    LCL_Liste aVisiter = LCL_liste(CO_copier, CO_liberer);
    
    // Dictionnaires pour stocker g, f et parents
    // On utilise CO_Coordonnee comme clé pour tout
    THD_Dictionnaire coutG = THD_dictionnaire(CO_copier, CO_liberer, CO_comparer, sizeof(CO_Coordonnee),
                                              CLCTS_copierFloat, CLCTS_libererFloat);
    THD_Dictionnaire coutF = THD_dictionnaire(CO_copier, CO_liberer, CO_comparer, sizeof(CO_Coordonnee),
                                              CLCTS_copierFloat, CLCTS_libererFloat);
    THD_Dictionnaire parents = THD_dictionnaire(CO_copier, CO_liberer, CO_comparer, sizeof(CO_Coordonnee),
                                                CO_copier, CO_liberer);
    
    // Initialiser le départ
    float gDepart = 0.0f;
    float heuristique = distanceManhattan(depart, arrivee);
    float fDepart = gDepart + heuristique;
    
    THD_inserer(&coutG, &depart, &gDepart);
    THD_inserer(&coutF, &depart, &fDepart);
    LCL_inserer(&aVisiter, &depart, 0);
    
    // Boucle principale A*
    while (!LCL_estVide(aVisiter)) {
        // Extraire la coordonnée avec le plus petit f
        CO_Coordonnee coordCourante = extraireMinF(&aVisiter, coutF);
        
        // Vérifier si c'est une coordonnée invalide
        if (CO_abscisse(coordCourante) == UINT_MAX) break;
        
        // Si on a atteint l'arrivée
        if (CO_sontEgales(coordCourante, arrivee)) {
            THE_ajouter(&noeudVisites, &coordCourante);
            TR_reconstruireChemin(&leChemin, parents, depart, arrivee);
            break;
        }
        
        // Ajouter à la liste fermée (noeudVisites)
        THE_ajouter(&noeudVisites, &coordCourante);
        
        // Obtenir le coût g actuel
        float* pCoutCourant = (float*)THD_valeur(coutG, &coordCourante);
        float coutCourant = (pCoutCourant != NULL) ? *pCoutCourant : 0.0f;
        if (pCoutCourant != NULL) free(pCoutCourant);
        
        // Convertir la coordonnée en numéro de case pour le graphe
        unsigned int numCaseCourante = CO_CoordonneeVersNumeroCase(coordCourante, T_obtenirTaille(terrain));
        
        // Obtenir les voisins depuis le GRAPHE (G_obtenirSommetsAdjacents)
        // Cette fonction retourne les numéros de cases adjacentes connectées par un arc
        LCL_Liste voisins = G_obtenirSommetsAdjacents(terrain.chemins, numCaseCourante);
        int nb_voisins = LCL_longueur(voisins);
        
        // Parcourir chaque voisin
        for (int voisin = 0; voisin < nb_voisins; voisin++) {
            // Récupérer le numéro de case du voisin
            unsigned int* pNumVoisin = (unsigned int*)LCL_element(voisins, voisin);
            if (pNumVoisin == NULL) continue;
            
            // Convertir le numéro de case en coordonnée
            CO_Coordonnee coordVoisin = CO_NumeroCaseVersCoordonnee(*pNumVoisin, T_obtenirTaille(terrain));
            free(pNumVoisin);
            
            // Vérifier si déjà visité (dans noeudVisites)
            if (THE_estPresent(noeudVisites, &coordVoisin)) {
                continue;
            }
            
            // Calculer le nouveau coût g pour ce voisin
            // Le graphe est non-orienté et non-valué, donc coût = 1 par arc
            float coutVoisin = coutCourant + 1.0f;
            
            // Vérifier si ce voisin est déjà dans aVisiter avec un meilleur coût
            float* pGVoisinActuel = (float*)THD_valeur(coutG, &coordVoisin);
            bool dejaPresent = (pGVoisinActuel != NULL);
            
            if (dejaPresent) {
                // Si le nouveau chemin est moins bon, on ignore
                if (coutVoisin >= *pGVoisinActuel) {
                    free(pGVoisinActuel);
                    continue;
                }
                free(pGVoisinActuel);
            }
            
            // Calculer h(voisin) et f(voisin)
            heuristique = distanceManhattan(coordVoisin, arrivee);
            float f = coutVoisin + heuristique;
            
            // Mettre à jour les dictionnaires
            THD_inserer(&coutG, &coordVoisin, &coutVoisin);
            THD_inserer(&coutF, &coordVoisin, &f);
            THD_inserer(&parents, &coordVoisin, &coordCourante);
            
            // Ajouter à la liste ouverte (aVisiter) si pas déjà présent
            if (!dejaPresent) {
                LCL_inserer(&aVisiter, &coordVoisin, LCL_longueur(aVisiter));
            }
        }
        
        LCL_vider(&voisins);
    }
    
    // Libérations des pointeurs allouées 
    THE_vider(&noeudVisites);
    LCL_vider(&aVisiter);
    THD_vider(&coutG);
    THD_vider(&coutF);
    THD_vider(&parents);
    
    return leChemin;
}

CH_Chemin TR_meilleurParcours(CO_Coordonnee depart, CO_Coordonnee objectifs[], int nbObjectifs) {
    CH_Chemin cheminComplet = chemin();
    CO_Coordonnee positionActuelle = depart;

    int estVisite[4] = {0}; 
    int nbVisites = 0;

    /* Algorithme du Plus Proche Voisin  */
    while (nbVisites < nbObjectifs) {
        int indexPlusProche = -1;
        int distMin = INT_MAX;

        /* 1. Trouver l'objectif non visité le plus proche de la position actuelle */
        for (int i = 0; i < nbObjectifs; i++) {
            if (!estVisite[i]) {
                /* On utilise la distance de Manhattan comme heuristique rapide */
                int d = distanceManhattan(positionActuelle, objectifs[i]);
                if (d < distMin) {
                    distMin = d;
                    indexPlusProche = i;
                }
            }
        }

        /* 2. Si on a trouvé un voisin */
        if (indexPlusProche != -1) {
            /* Calculer le vrai chemin (A*) vers cet objectif */
            CH_Chemin segment = TR_plusCourtChemin(NULL, positionActuelle, objectifs[indexPlusProche]);
            
            /* Ajouter ce segment au chemin final */
            TR_ajouterSegment(&cheminComplet, &segment);

            /* Mettre à jour l'état */
            estVisite[indexPlusProche] = 1;
            nbVisites++;
            positionActuelle = objectifs[indexPlusProche];
        } else {
            /* si on ne trouve plus rien  */
            break;
        }
    }

    return cheminComplet;
}

CH_Chemin TR_obtenirParcours(T_Terrain terrain, CO_Coordonnee depart, CO_Coordonnee objectifs[], int nbObjectifs) {
    return TR_meilleurParcours(depart, objectifs, nbObjectifs);
}

LCF_File TR_conversionCheminInstr(CH_Chemin chemin, Direction dirInitiale) {
    LCF_File instructions;
     instructions = FILE_file(NULL, NULL); 
    return instructions;
}
