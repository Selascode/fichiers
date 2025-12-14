/**
 * \file terrain.h
 * \brief TAD Terrain
 * \author J. Emond
 * \version 1.1
 * \date 2025
*/

#ifndef __TERRAIN__
#define __TERRAIN__

#include <stdbool.h>
#include <assert.h>
#include <graphe.h>
#include "direction.h"
#include "coordonnee.h"
#include "TableHachageEnsemble.h"
   

/* -------------------------------------------------------------------------- */
/*                            PARTIE PRIVÉE                                   */
/* -------------------------------------------------------------------------- */

/**
 * \struct T_Terrain
 * \brief 
 */
typedef struct T_Terrain {
    unsigned int taille;           /**< Taille du terrain (largeur/hauteur) */
    G_Graphe chemins;              /**< Graphe non-orienté*/
    CO_Coordonnee positionDepart;
    DI_Direction directionDepart;    
    THE_Ensemble positionsObjectifs;    /**< Ensemble de Coordonnée*/
} T_Terrain;

/* -------------------------------------------------------------------------- */
/*                            PARTIE PUBLIQUE                                 */
/* -------------------------------------------------------------------------- */

/**
 * \brief Création d'un terrain vide.
 * \param h taille du terrain à initialiser
 * \return Le terrain vide
 */
T_Terrain T_terrain(unsigned int h);

/**
 * \brief Savoir si un chemin existe entre les coordonnées adjacentes a et b
 * \param t le terrain dont on obtient les positions
 * \param a la coordonnée a
 * \param b la coordonnée b
 * \return booléen indiquant si un chemin existe
 */
bool T_cheminExiste(T_Terrain t, CO_Coordonnee a, CO_Coordonnee b);

/**
 * \brief Savoir si une coordonnée correspond à celle d'un des objectifs
 * \param t le terrain dont on obtient les positions
 * \param c la coordonnée
 * \return booléen indiquant si c'est une coordonnée d'objectif
 */
bool T_estUnObjectif(T_Terrain t, CO_Coordonnee c);

/**
 * \brief Obtenir la taille du terrain
 * \param t le terrain dont on obtient la taille
 * \return La taille du terrain
 */
unsigned int T_obtenirTaille(T_Terrain t);

/**
 * \brief Obtenir la position de départ du robot
 * \param t le terrain dont on obtient la position
 * \return La position de départ du robot
 */
CO_Coordonnee T_obtenirPositionDepart(T_Terrain t);

/**
 * \brief Obtenir la direction de départ du robot
 * \param t le terrain dont on obtient la direction
 * \return La direction de départ du robot
 */
DI_Direction T_obtenirDirectionDepart(T_Terrain t);

/**
 * \brief Obtenir les positions des objectifs sur le terrain
 * \param t le terrain dont on obtient les positions
 * \return Ensemble contenant les positions des objectifs
 */
THE_Ensemble T_obtenirObjectifs(T_Terrain t);

/**
 * \brief Ajouter un objectif dans le terrain.
 * \param t terrain à modifier
 * \param c la coordonnée de l'objectif à ajouter
 */
void T_ajouterObjectif(T_Terrain* t, CO_Coordonnee c);

/**
 * \brief Ajouter dans le terrain un chemin entre un point A et un point B (adjacents).
 * \param t terrain à modifier
 * \param coordA la coordonnée du point A
 * \param coordA la coordonnée du point B
 */
void T_ajouterChemin(T_Terrain* terrain, CO_Coordonnee coordA, CO_Coordonnee coordB);

/**
 * \brief Fixer un objectif dans le terrain.
 * \param t terrain à modifier\param t terrain à modifier
 * \param t terrain à modifier\param c la coordonnée de l'objectif à fixer
 */
void T_supprimerTerrain(T_Terrain* ch);

#endif
