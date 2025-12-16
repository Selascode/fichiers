#include "trajet.h"
#include "chemin.h"
#include "analyseur_terrain.h"

int main (int argc, char ** argv){

    T_Terrain t = AT_analyseurTerrain(argv[1]);
    CO_Coordonnee depart =  T_obtenirPositionDepart(t);
    CO_Coordonnee  fin = CO_NumeroCaseVersCoordonnee(13,T_obtenirTaille(t)); 
    CO_Coordonnee coordoneeActuelle; 
    CH_Chemin cheminObtenu = TR_plusCourtChemin(t,depart,fin); 
    unsigned int x, y; 
     
    printf("Le chemin le plus court est le suivant \n"); 
    unsigned int longeurChemin = CH_longueurChemin(cheminObtenu); 

    for(unsigned int i = 1; i <= longeurChemin; i++){
        coordoneeActuelle =  CH_defilerEtape(&cheminObtenu);
        x = CO_abscisse(coordoneeActuelle);
        y = CO_ordonnee(coordoneeActuelle);
        printf("%u , (X = %u,  Y = %u )\n", i , x ,y ); 

    }
} 
    
       