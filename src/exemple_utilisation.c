/**
 * \file exemple_utilisation.c
 * \brief Exemple d'utilisation du parseur de terrain
 */

#include <stdio.h>
#include <stdlib.h>
#include "analyseur_terrain.h"


int main(int argc, char* argv[]) {
    FILE* fichier = NULL;
    
    // Ouvrir le fichier passé en argument ou utiliser stdin
    if (argc > 1) {
        fichier = fopen(argv[1], "r");
        if (fichier == NULL) {
            fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", argv[1]);
            return 1;
        }
    } else {
        fichier = stdin;
        printf("Entrez la description du terrain (terminez par un point) :\n");
    }
    
    // Parser le terrain
    T_Terrain terrain = AT_parserTerrain(fichier);
    
    if (fichier != stdin) {
        fclose(fichier);
    }
    
    // Afficher les informations du terrain
    printf("\n=== Terrain parsé ===\n");
    printf("Taille : %u x %u\n", T_obtenirTaille(terrain), T_obtenirTaille(terrain));
    
    CO_Coordonnee posDepart = T_obtenirPositionDepart(terrain);
    printf("Position de départ : (%u, %u)\n", 
           CO_abscisse(posDepart), CO_ordonnee(posDepart));
    
    DI_Direction dirDepart = T_obtenirDirectionDepart(terrain);
    const char* directions[] = {"Nord", "Est", "Sud", "Ouest"};
    printf("Direction de départ : %s\n", directions[dirDepart]);
    
    printf("\nVérification de quelques chemins...\n");
    // Exemple : vérifier si certains chemins existent
    // (Vous pouvez ajouter vos propres tests ici)
    
    // Nettoyer
    T_supprimerTerrain(&terrain);
    
    return 0;
}
