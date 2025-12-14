/**
 * \file analyseyr_terrain.h
 * \brief analyseur de flux texte pour la construction de terrain
 * \author S.MACLEAN & Assistant
 * \version 1.0
 * \date 2025
 */

#ifndef __ANALYSEUR_TERRAIN__
#define __ANALYSEUR_TERRAIN__

#include <stdio.h>
#include "terrain.h"

/**
 * \brief Parse un flux texte et construit un terrain
 * \param flux Le flux d'entrée à parser
 * \return Le terrain construit à partir du flux
 * 
 * Format attendu :
 * - Ligne 1 : largeur l (la ville a l² cases numérotées de 1 à l²)
 * - Ligne 2 : numero_case orientation (N/E/S/O)
 * - Lignes suivantes : case1-case2 (passages entre cases)
 * - Lignes finales : numero_case (objectifs)
 * - Fin : . (point)
 */
T_Terrain AT_parserTerrain(FILE* flux);

#endif