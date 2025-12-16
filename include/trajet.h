/**
 * \file trajet.h
 * \brief Module de calcul de trajet .
 * \author Youssef Hajbi
 * \version 1.0
 * \date 09/12
 */

#ifndef __TRAJET__
#define __TRAJET__

#include "coordonnee.h"
#include "direction.h"
#include "chemin.h"
#include "terrain.h"  
#include "ListeChaineeFile.h"

/* -------------------------------------------------------------------------- */
/* PARTIE PUBLIQUE                                                            */
/* -------------------------------------------------------------------------- */

/**
 * \brief  le calcul global du parcours.
 * \param terrain Le terrain.
 * \param depart La coordonnée de départ.
 * \param objectifs La liste des points de passage obligatoires.
 * \param nbObjectifs Le nombre de points à visiter.
 * \return Le chemin complet passant par tous les points.
 */
CH_Chemin TR_obtenirParcours(T_Terrain terrain, CO_Coordonnee depart, CO_Coordonnee objectifs[], int nbObjectifs);

/**
 * \brief Trouve le plus court chemin entre deux points précis.
 * \param terrain Le terrain.
 * \param depart Point de départ.
 * \param arrivee Point d'arrivée.
 * \return Le chemin élémentaire entre ces deux points.
 */
CH_Chemin TR_plusCourtChemin(T_Terrain terrain, CO_Coordonnee depart, CO_Coordonnee arrivee);

/**
 * \brief Détermine l'ordre optimal des points de passage (Voyageur de commerce).
 * \param depart Point de départ.
 * \param objectifs Ensemble des coordonnées à visiter.
 * \param nbObjectifs Nombre d'objectifs.
 * \return Le chemin complet ordonné.
 */
CH_Chemin TR_meilleurParcours(CO_Coordonnee depart, CO_Coordonnee objectifs[], int nbObjectifs);

/**
 * \brief Convertit un chemin géométrique en une file d'instructions (AV, TG, TD).
 * \param chemin Le chemin calculé.
 * \param dirInitiale La direction initiale du robot.
 * \return La file d'instructions pour le robot.
 */
LCF_ListeChaineeFile TR_conversionCheminInstr(CH_Chemin chemin, DI_Direction dirInitiale) ; 

#endif
