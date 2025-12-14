/**
 * \file exemple_utilisation.c
 * \brief Exemple d'utilisation du parseur de terrain
 */

#include <stdio.h>
#include <stdlib.h>
#include "analyseur_terrain.h"


int main(int argc, char* argv[]) {
    FILE* fichier = NULL;
    
    if (argc > 1) {
        printf("Ouverture du fichier : %s\n", argv[1]);
        fichier = fopen(argv[1], "r");
        if (fichier == NULL) {
            fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", argv[1]);
            return 1;
        }
    } else {
        fichier = stdin;
        printf("Entrez la description du terrain (terminez par un point) :\n");
    }
    
    // Analyser le terrain
    printf("Analyse  du terrain...\n");
    T_Terrain terrain = AT_parserTerrain(fichier);
    
    if (fichier != stdin) {
        fclose(fichier);
    }
    
    // Afficher les informations du terrain
    printf("\n=== Terrain parsé ===\n");
    printf("Taille : %u x %u\n", T_obtenirTaille(terrain), T_obtenirTaille(terrain));
    
    CO_Coordonnee posDepart = T_obtenirPositionDepart(terrain);
    printf("Position de départ : case %u soit (%u, %u)\n",
           CO_CoordonneeVersNumeroCase(posDepart, T_obtenirTaille(terrain)),
           CO_abscisse(posDepart), CO_ordonnee(posDepart));
    
    DI_Direction dirDepart = T_obtenirDirectionDepart(terrain);
    const char* directions[] = {"Nord", "Est", "Sud", "Ouest"};
    printf("Direction de départ : %s\n", directions[dirDepart]);
    
    // Afficher les objectifs
    printf("\nObjectifs :\n");
    LCL_Liste listeObjectifs = THE_elements(T_obtenirObjectifs(terrain));
    unsigned int nbObjectifs = LCL_longueur(listeObjectifs);
    printf("Nombre d'objectifs : %u\n", nbObjectifs);
    
    for (unsigned int i = 0; i < nbObjectifs; i++) {
        CO_Coordonnee* pCoord = (CO_Coordonnee*)LCL_element(listeObjectifs, i);
        if (pCoord != NULL) {
            printf("  - Case %u : (%u, %u)\n",
                   CO_CoordonneeVersNumeroCase(*pCoord, T_obtenirTaille(terrain)),
                   CO_abscisse(*pCoord), CO_ordonnee(*pCoord));
            free(pCoord);
        }
    }
    LCL_vider(&listeObjectifs);
    
    // Vérifier quelques chemins
    printf("\nVérification de quelques chemins...\n");
    CO_Coordonnee c1 = CO_NumeroCaseVersCoordonnee(1, T_obtenirTaille(terrain));
    CO_Coordonnee c2 = CO_NumeroCaseVersCoordonnee(2, T_obtenirTaille(terrain));
    printf("Chemin entre case 1 et case 2 : %s\n", 
           T_cheminExiste(terrain, c1, c2) ? "OUI" : "NON");
    
    CO_Coordonnee c6 = CO_NumeroCaseVersCoordonnee(6, T_obtenirTaille(terrain));
    CO_Coordonnee c11 = CO_NumeroCaseVersCoordonnee(11, T_obtenirTaille(terrain));
    printf("Chemin entre case 6 et case 11 : %s\n", 
           T_cheminExiste(terrain, c6, c11) ? "OUI" : "NON");
    
    // Nettoyer
    T_supprimerTerrain(&terrain);
    
    printf("\nTerminé avec succès !\n");
    return 0;
}