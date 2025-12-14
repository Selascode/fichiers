/**
 * \file direction.h
 * \brief TAD DI_Direction (Points cardinaux et orientation)
 * \author [Ton Nom]
 * \version 1.0
 * \date 2025
 */

#ifndef __DIRECTION__
#define __DIRECTION__

/* -------------------------------------------------------------------------- */
/* PARTIE PRIVÉE                                   */
/* -------------------------------------------------------------------------- */

/**
 * \enum DI_Direction
 * \brief DI_Directions possibles pour le déplacement du robot.
 */
typedef enum {
    N = 0, /**< DI_Direction Nord  */
    E,      /**< DI_Direction Est  */
    S,      /**< DI_Direction Sud  */
    O     /**< DI_Direction Ouest  */
} DI_Direction;

/* -------------------------------------------------------------------------- */
/* PARTIE PUBLIQUE                                 */
/* -------------------------------------------------------------------------- */

/**
 * \brief Effectue une rotation de 90 degrés vers la gauche .
 * Correspond à l'ordre 'TG'.
 * \param d La direction actuelle.
 * \return La nouvelle direction après rotation.
 */
DI_Direction DI_tournerGauche(DI_Direction d);

/**
 * \brief Effectue une rotation de 90 degrés vers la droite .
 * Correspond à l'ordre 'TD'.
 * \param d La direction actuelle.
 * \return La nouvelle direction après rotation.
 */
DI_Direction DI_tournerDroite(DI_Direction d);

/**
 * \brief Donne la direction opposée .
 * \param d La direction actuelle.
 * \return La direction opposée.
 */
DI_Direction DI_opposee(DI_Direction d);

#endif