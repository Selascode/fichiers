/**
 * \file parseur_terrain.c
 * \brief Implémentation du parseur de flux texte pour terrain
 * \author Sm.MACLEAN & Assistant
 * \version 1.0
 * \date 2025
 */

#include "analyseur_terrain.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * \brief Convertit un caractère de direction en énumération DI_Direction
 * \param c Le caractère ('N', 'E', 'S', 'O')
 * \return La direction correspondante
 */
static DI_Direction AT_charVersDirection(char c) {
    switch(c) {
        case 'N': return N;
        case 'E': return E;
        case 'S': return S;
        case 'O': return O;
        default: return S;  
    }
}

/**
 * \brief Ignore les espaces et tabulations dans le flux
 * \param flux Le flux à traiter
 */
static void AT_ignorerEspaces(FILE* flux) {
    int c;
    while ((c = fgetc(flux)) != EOF && (c == ' ' || c == '\t')) { 

    }
    if (c != EOF) {
        ungetc(c, flux); // Permet de remettre dans le flux de lecture un charactère valide (pas d'espace ou de tab)
    }
}

/**
 * \brief Lit un nombre entier depuis le flux
 * \param flux Le flux d'entrée
 * \param nombre Pointeur vers la variable recevant le nombre
 * \return 1 si succès, 0 sinon
 */
static int AT_lireNombre(FILE* flux, unsigned int* nombre) {
    AT_ignorerEspaces(flux);
    return fscanf(flux, "%u", nombre) == 1; // %u unsigned int 
}

/**
 * \brief Lit un caractère depuis le flux
 * \param flux Le flux d'entrée
 * \param c Pointeur vers la variable recevant le caractère
 * \return 1 si succès, 0 sinon
 */
static int AT_lireCaractere(FILE* flux, char* c) {
    AT_ignorerEspaces(flux);
    int caractere = fgetc(flux);
    if (caractere == EOF) {
        return 0;
    }
    *c = (char)caractere;
    return 1;
}

/**
 * \brief Lit une ligne complète et vérifie si c'est la fin (point)
 * \param flux Le flux d'entrée
 * \param buffer Buffer pour stocker la ligne
 * \param taille Taille du buffer
 * \return 1 si ligne lue, 0 si fin (point trouvé) ou erreur
 */
static int AT_lireLigne(FILE* flux, char* buffer, size_t taille) {
    if (fgets(buffer, taille, flux) == NULL) {
        return 0; 
    }
    
    // Retirer le retour à la ligne
    size_t longueur = strlen(buffer);
    if (longueur > 0 && buffer[longueur-1] == '\n') {
        buffer[longueur-1] = '\0';
    }
    
    // Vérifier si c'est juste un point (fin du flux)
    char* c = buffer;
    while (*c == ' ' || *c == '\t'){ 
        c++;
    } 

    if (*c == '.') {
        return 0; // Fin du flux
    }
    
    return 1;
}


T_Terrain AT_analyseurTerrain(FILE* flux) {
    if (flux == NULL) {
        // Retourner un terrain vide par défaut
        return T_terrain(0);
    }
    
    char buffer[256];
    unsigned int largeur = 0;
    
    // 1. Lecture : largeur du terrain
    if (!AT_lireNombre(flux, &largeur) || largeur == 0) {
        printf("ERREUR : lecture de largeur");
        return T_terrain(0);
    }
    
    // Aller jusqu'à la fin de la ligne 
    fgets(buffer, sizeof(buffer), flux);
    
    // Création du térain 
    T_Terrain terrain = T_terrain(largeur);
    
    // 2. Lecture de positon de départ et de l'orientation initiale 
    unsigned int caseDepart = 0;
    char orientationChar = 'N';
    
    if (!AT_lireNombre(flux, &caseDepart)) {
        printf("ERREUR : lecture lecture de la case de départ");
        T_supprimerTerrain(&terrain);
        return T_terrain(0);
    }
    
    AT_ignorerEspaces(flux);
    if (!AT_lireCaractere(flux, &orientationChar)) {
        printf("ERREUR : lecture lecture de l'orientation de départ");
        T_supprimerTerrain(&terrain);
        return T_terrain(0);
    }
    
    fgets(buffer, sizeof(buffer), flux);
    
    // Convertir le numéro de case en coordonnée
    CO_Coordonnee posDepart = CO_NumeroCaseVersCoordonnee(caseDepart, largeur);
    DI_Direction dirDepart = AT_charVersDirection(orientationChar);
    
    terrain.positionDepart = posDepart;
    terrain.directionDepart = dirDepart;
    
    // 3. Lexcture des chemin et des objectifs 
    while (AT_lireLigne(flux, buffer, sizeof(buffer))) {
        // Ignorer les lignes vides
        char* ptr = buffer;
        while (*ptr == ' ' || *ptr == '\t') {
            ptr++;
        }
        if (*ptr == '\0') continue;
        
        // Chercher un tiret (passage entre cases)
        char* tiret = strchr(buffer, '-'); //strchr : Sert à trouver 'aparition d'une cdc et s'arrete dès qu'elle trouve - 
        
        if (tiret != NULL) {
            // C'est un passage : case1-case2
            unsigned int case1, case2;
            if (sscanf(buffer, "%u-%u", &case1, &case2) == 2) {
                CO_Coordonnee coord1 = CO_NumeroCaseVersCoordonnee(case1, largeur);
                CO_Coordonnee coord2 = CO_NumeroCaseVersCoordonnee(case2, largeur);
                T_ajouterChemin(&terrain, coord1, coord2);
            }
        } else {
            // C'est un objectif  
            unsigned int caseObjectif;
            if (sscanf(buffer, "%u", &caseObjectif) == 1) {
                CO_Coordonnee coordObjectif = CO_NumeroCaseVersCoordonnee(caseObjectif, largeur);
                T_ajouterObjectif(&terrain, coordObjectif);
            }
        }
    }

    return terrain;
}


    