/**
 * \file coordonnee.h
 * \brief TAD Coordonnée (Gestion de la position x,y)
 * \author Youssef Hajbi
 * \version 1.0
 * \date 09/12
 */

#ifndef __COORDONNEES__
#define __COORDONNEES__

#include <stdbool.h>
#include "direction.h"

/* -------------------------------------------------------------------------- */
/* PARTIE PRIVÉE                                                              */
/* -------------------------------------------------------------------------- */

/**
 * \struct Coordonnee
 * \brief Représente une position dans la grille (origine haut-gauche).
 */
typedef struct {
    int x; /**< Colonne  */
    int y; /**< Ligne  */
} CO_Coordonnee;

/* -------------------------------------------------------------------------- */
/* PARTIE PUBLIQUE                                                            */
/* -------------------------------------------------------------------------- */

/**
 * \brief Crée une coordonnee.
 * \param x l'abcisse de la coordonnee.
 * \param y l'ordonnee de la coordonnee .
 * \return La nouvelle coordonnée
 */
CO_Coordonnee CO_coordonnee(unsigned int x, unsigned int y);

/**
 * \brief renvoie l'abcisse de la coordonnee
 * \param coord la coordonnee dont on veut l'abcisse.
 * \return L'abcisse
 */
unsigned int CO_abscisse(CO_Coordonnee coord);

/**
 * \brief renvoie l'ordonnee de la coordonnee
 * \param coord la coordonnee dont on veut l'ordonnee.
 * \return L'ordonnee
 */
unsigned int CO_ordonnee(CO_Coordonnee coord);

/**
 * \brief Donne la coordonnee suivante dans une direction
 * \param coord la coordonnee de départ
 * \param direction la direction du déplacement
 * \return La coordonnee d'arrive
 */
CO_Coordonnee CO_obtenirCoordonneeDirection(CO_Coordonnee coord,
				 DI_Direction direction);

/**
 * \brief Donne si deux coordonnees sont les memes
 * \param coord1 La première coordonnee
 * \param coord2 La deuxième coordonnee
 * \return Si les coordonnees sont égales
 */
bool CO_sontEgales(CO_Coordonnee coord1, CO_Coordonnee coord2);

/**
 * \brief Convertit un numéro de case en (x,y).
 * \param numero Le numéro de la case .
 * \param largeur La largeur de la grille .
 * \return La coordonnée correspondante.
 */
CO_Coordonnee CO_NumeroCaseVersCoordonnee(unsigned int numero, unsigned int largeur);

/**
 * \brief Convertit une coordonnée (x,y) en numéro de case.
 * \param c La coordonnée.
 * \param largeur La largeur de la grille.
 * \return Le numéro de la case .
 */
unsigned int CO_CoordonneeVersNumeroCase(CO_Coordonnee c, unsigned int largeur);

/**
 * \brief Copie un pointeur vers une coordonnée.
 * \param pcoord Le pointeur à copier.
 * \return La copie de pcoord
 */
void* CO_copier(void* pcoord);

/**
 * \brief Libère un pointeur vers une coordonnée.
 * \param pcoord Le pointeur a libéré.
 */
void CO_liberer(void* pcoord);

/**
 * \brief Libère un pointeur vers une coordonnée.
 * \param pcoord Le pointeur a libéré.
 */
int CO_comparer(void* pcoord1,void* pcoord );

#endif