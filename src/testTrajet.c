#include <stdio.h>
#include <stdlib.h>
#include "trajet.h"
#include "chemin.h"
#include "analyseur_terrain.h"
#include "terrain.h"   
#include "coordonnee.h"

int main (int argc, char ** argv){

    // 1. Sécurité : Vérifier l'argument
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier_terrain.txt>\n", argv[0]);
        return 1;
    }

    // 2. CORRECTION : Ouverture du fichier
    FILE* fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Chargement du terrain avec le FLUX fichier
    T_Terrain t = AT_analyseurTerrain(fichier);
    
    // Fermeture du fichier une fois lu
    fclose(fichier);

    // Vérification que le terrain est valide (taille > 0)
    if (T_obtenirTaille(t) == 0) {
        fprintf(stderr, "Erreur: Terrain invalide ou vide (Taille = 0).\n");
        return 1;
    }
    
    // 3. Définition des points
    CO_Coordonnee depart = T_obtenirPositionDepart(t);
    
    // Attention: S'assurer que la case 13 existe pour ce terrain
    // Pour être robuste, on peut vérifier que 13 < largeur*hauteur
    CO_Coordonnee fin = CO_NumeroCaseVersCoordonnee(13, T_obtenirTaille(t)); 

    printf("Calcul du chemin de (%u, %u) vers (%u, %u)...\n", 
           CO_abscisse(depart), CO_ordonnee(depart), 
           CO_abscisse(fin), CO_ordonnee(fin));

    // 4. Calcul du chemin
    CH_Chemin cheminObtenu = TR_plusCourtChemin(t, depart, fin); 
    
    unsigned int x, y; 
    unsigned int longueurChemin = CH_longueurChemin(cheminObtenu); 

    // 5. Affichage
    if (longueurChemin == 0) {
        // Note: Si départ == arrivée, la longueur est 0 mais c'est un succès.
        if (CO_abscisse(depart) == CO_abscisse(fin) && CO_ordonnee(depart) == CO_ordonnee(fin)) {
            printf("Départ et arrivée sont identiques.\n");
        } else {
            printf("Aucun chemin trouvé ou destination inaccessible.\n");
        }
    } else {
        printf("Chemin trouvé ! Longueur : %u étapes.\n", longueurChemin);
        printf("Le chemin le plus court est le suivant :\n"); 

        for(unsigned int i = 1; i <= longueurChemin; i++){
            CO_Coordonnee coordoneeActuelle = CH_defilerEtape(&cheminObtenu);
            x = CO_abscisse(coordoneeActuelle);
            y = CO_ordonnee(coordoneeActuelle);
            printf("Etape %u : (X = %u, Y = %u)\n", i, x, y); 
        }
    }
    
    // Penser à libérer le terrain si une fonction existe (ex: T_libererTerrain(&t))
    return 0;
}