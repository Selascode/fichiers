/**
 * \file direction.c
 * \brief Implémentation du TAD Direction
 * \author Youssef Hajbi
 * \version 1.0
 * \date 2025
 */

#include "direction.h"

DI_Direction DI_tournerGauche(DI_Direction d) {
    /* * Pour tourner à gauche  :
     * N(0) -> O(3), O(3) -> S(2)...
     */
    return (d + 3) % 4;
}

DI_Direction DI_tournerDroite(DI_Direction d) {
    /* * Pour tourner à droite  :
     * N(0) -> E(1), E(1) -> S(2)...
     */
    return (d + 1) % 4;
}

DI_Direction DI_opposee(DI_Direction d) {
    /* * L'opposé  :
     * N(0) <-> S(2)
     * E(1) <-> O(3)
     */
    return (d + 2) % 4;
}