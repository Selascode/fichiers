#include "terrain.h"
#include <stdlib.h>
#include <assert.h>

/**
 * @brief Crée un terrain vide de taille h x h
 * @param h Taille du terrain
 * @return Le terrain initialisé
 */
T_Terrain T_terrain(unsigned int h) {
    T_Terrain t;
    t.taille = h;
    
    // Création d'un graphe non-orienté, non-étiqueté, non-valué
    t.chemins = G_graphe(false, NULL, NULL, NULL, NULL, NULL, NULL);
    
    // Ajout de tous les sommets (cases du terrain)
    // Les cases sont numérotées de 0 à h*h - 1
    for (unsigned int i = 0; i < h * h; i++) {
        G_ajouterSommet(&t.chemins, i, NULL);
    }
    
    // Position et direction de départ par défaut (0,0) direction Nord
    t.positionDepart = CO_coordonnee(0, 0);
    t.directionDepart = N;
    
    // Création de l'ensemble des objectifs (vide initialement)
    t.positionsObjectifs = THE_ensemble(CO_copier, CO_liberer, CO_comparer, sizeof(CO_Coordonnee));
    
    return t;
}

/**
 * @brief Vérifie si un chemin existe entre deux coordonnées adjacentes
 * @param t Le terrain
 * @param a Première coordonnée
 * @param b Deuxième coordonnée
 * @return true si un chemin existe, false sinon
 */
bool T_cheminExiste(T_Terrain t, CO_Coordonnee a, CO_Coordonnee b) {
    unsigned int caseA = CO_CoordonneeVersNumeroCase(a, t.taille);
    unsigned int caseB = CO_CoordonneeVersNumeroCase(b, t.taille);
    return G_arcPresent(t.chemins, caseA, caseB);
}

/**
 * @brief Vérifie si une coordonnée est un objectif
 * @param t Le terrain
 * @param c La coordonnée à vérifier
 * @return true si c'est un objectif, false sinon
 */
bool T_estUnObjectif(T_Terrain t, CO_Coordonnee c) {
    return THE_estPresent(t.positionsObjectifs, &c);
}

/**
 * @brief Retourne la taille du terrain
 * @param t Le terrain
 * @return La taille du terrain
 */
unsigned int T_obtenirTaille(T_Terrain t) {
    return t.taille;
}

/**
 * @brief Retourne la position de départ du robot
 * @param t Le terrain
 * @return La coordonnée de départ
 */
CO_Coordonnee T_obtenirPositionDepart(T_Terrain t) {
    return t.positionDepart;
}

/**
 * @brief Retourne la direction de départ du robot
 * @param t Le terrain
 * @return La direction de départ
 */
DI_Direction T_obtenirDirectionDepart(T_Terrain t) {
    return t.directionDepart;
}

/**
 * @brief Retourne l'ensemble des objectifs
 * @param t Le terrain
 * @return L'ensemble des positions objectifs
 */
THE_Ensemble T_obtenirObjectifs(T_Terrain t) {
    return t.positionsObjectifs;
}

/**
 * @brief Ajoute un objectif au terrain
 * @param t Pointeur vers le terrain
 * @param c La coordonnée de l'objectif
 */
void T_ajouterObjectif(T_Terrain* t, CO_Coordonnee c) {
    THE_ajouter(&t->positionsObjectifs, &c);
}

/**
 * @brief Ajoute un chemin entre deux coordonnées adjacentes
 * @param terrain Pointeur vers le terrain
 * @param coordA Première coordonnée
 * @param coordB Deuxième coordonnée
 */
void T_ajouterChemin(T_Terrain* terrain, CO_Coordonnee coordA, CO_Coordonnee coordB) {
    unsigned int caseA = CO_CoordonneeVersNumeroCase(coordA, terrain->taille);
    unsigned int caseB = CO_CoordonneeVersNumeroCase(coordB, terrain->taille);
    
    // Ajouter l'arc (le graphe est non-orienté, donc un seul arc suffit)
    G_ajouterArc(&terrain->chemins, caseA, caseB, NULL);
}

/**
 * @brief Libère la mémoire associée au terrain
 * @param t Pointeur vers le terrain à supprimer
 */
void T_supprimerTerrain(T_Terrain* t) {
    // Vider le graphe des chemins
    G_vider(&t->chemins);
    
    // Vider l'ensemble des objectifs
    THE_vider(&t->positionsObjectifs);
}
