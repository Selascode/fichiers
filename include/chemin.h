/**
 * \file chemin.h
 * \brief TAD Chemin
 * \author J. Emond
 * \version 1.0
 * \date 2025
*/

#ifndef __CHEMIN__
#define __CHEMIN__

#include "ListeChaineeFile.h"
#include "coordonnee.h"   

/* -------------------------------------------------------------------------- */
/*                            PARTIE PRIVÉE                                   */
/* -------------------------------------------------------------------------- */

/**
 * \struct CH_Chemin
 * \brief Chemin représentant des cases à parcourir
 */
typedef struct {
    LCF_ListeChaineeFile etapes;   /**< File de coordonnées (FIFO)*/
    unsigned int longueur;
} CH_Chemin;

/* -------------------------------------------------------------------------- */
/*                            PARTIE PUBLIQUE                                 */
/* -------------------------------------------------------------------------- */

/**
 * \brief Création d'un chemin vide.
 * \return Le chemin vide.
 */
CH_Chemin CH_chemin();

/**
 * \brief Ajout d'une étape dans le chemin.
 * \param ch chemin auquel ajouter l'étape
 * \param etape étape à ajouter dans le chemin
 */
void CH_enfilerEtape(CH_Chemin* ch, CO_Coordonnee* etape);

/**
 * \brief Retrait de l'étape qui a été ajoutée le plus tôt.
 * \param ch chemin auquel retirer l'étape
 * \return L'étape défilée du chemin
 */
CO_Coordonnee CH_defilerEtape(CH_Chemin* ch);

/**
 * \brief Création d'un chemin vide.
 * \param ch chemin auquel retirer l'étape
 * \return La longueur du chemin
 */
unsigned int CH_longueurChemin(CH_Chemin ch);

/**
 * \brief Suppression d'un chemin.
 * \param ch chemin à supprimer
 */
void CH_supprimerChemin(CH_Chemin* ch);

#endif
