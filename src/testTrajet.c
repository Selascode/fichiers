#include <stdio.h>
#include <stdlib.h>
#include "trajet.h"
#include "chemin.h"
#include "analyseur_terrain.h"
#include "terrain.h"   // Nécessaire pour T_obtenirPositionDepart, T_obtenirTaille
#include "coordonnee.h" // Nécessaire pour CO_Coordonnee, CO_abscisse, etc.

int main (int argc, char ** argv){

    // 1. Sécurité : Vérifier qu'un fichier est bien passé en argument
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier_terrain.txt>\n", argv[0]);
        return 1;
    }

    // 2. Chargement du terrain
    T_Terrain t = AT_analyseurTerrain(argv[1]);
    
    // 3. Définition des points de départ et d'arrivée
    CO_Coordonnee depart = T_obtenirPositionDepart(t);
    
    // Attention : Assurez-vous que T_obtenirTaille renvoie bien la largeur 
    // ou que CO_NumeroCaseVersCoordonnee accepte le type retourné.
    // Souvent, la conversion numéro -> coord demande la largeur (int).
    // Exemple supposé : int largeur = T_obtenirLargeur(t);
    CO_Coordonnee fin = CO_NumeroCaseVersCoordonnee(13, T_obtenirTaille(t)); 

    // 4. Calcul du chemin
    CH_Chemin cheminObtenu = TR_plusCourtChemin(t, depart, fin); 
    
    unsigned int x, y; 
    unsigned int longueurChemin = CH_longueurChemin(cheminObtenu); 

    // 5. Vérification si un chemin a été trouvé
    if (longueurChemin == 0) {
        printf("Aucun chemin trouvé ou destination inaccessible (Obstacle/Hors map).\n");
    } else {
        printf("Chemin trouvé ! Longueur : %u étapes.\n", longueurChemin);
        printf("Le chemin le plus court est le suivant :\n"); 

        // 6. Défilement et affichage
        // On boucle tant que i <= longueurChemin car on dépile/défile
        for(unsigned int i = 1; i <= longueurChemin; i++){
            // On passe l'adresse (&) car la fonction va modifier la structure (retirer un élément)
            CO_Coordonnee coordoneeActuelle = CH_defilerEtape(&cheminObtenu);
            
            x = CO_abscisse(coordoneeActuelle);
            y = CO_ordonnee(coordoneeActuelle);
            
            printf("Etape %u : (X = %u, Y = %u)\n", i, x, y); 
        }
    }

    return 0;
}