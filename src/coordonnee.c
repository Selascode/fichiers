#include "coordonnee.h"
#include <errno.h>
#include <assert.h>
#include <stdlib.h>

CO_Coordonnee CO_coordonnee(unsigned int x, unsigned int y){
	CO_Coordonnee c;
	c.x = x;
	c.y = y;
	return c;
}

unsigned int CO_abscisse(CO_Coordonnee coord){
    return coord.x;
}

unsigned int CO_ordonnee(CO_Coordonnee coord){
    return coord.y;
}

CO_Coordonnee CO_obtenirCoordonneeDirection(CO_Coordonnee coord,
				 DI_Direction direction){
	CO_Coordonnee newcoord;
	switch (direction)
{
	case O : newcoord.x = CO_abscisse(coord) -1; newcoord.y = CO_ordonnee(coord); break;
	case E : newcoord.x = CO_abscisse(coord) +1; newcoord.y = CO_ordonnee(coord); break;
	case S : newcoord.x = CO_abscisse(coord); newcoord.y = CO_ordonnee(coord) +1; break;
	case N : newcoord.x = CO_abscisse(coord); newcoord.y = CO_ordonnee(coord) -1; break;
}
	return newcoord;
}

CO_Coordonnee CO_NumeroCaseVersCoordonnee(unsigned int numero, unsigned int largeur){
	assert(numero>0);
	CO_Coordonnee c;
	c.x = (numero-1)%largeur;
	c.y = (numero-1)/largeur;
	return c;
}

unsigned int CO_CoordonneeVersNumeroCase(CO_Coordonnee c, unsigned int largeur){
	return CO_ordonnee(c)*largeur + CO_abscisse(c) + 1;
}

// CORRECTION CRITIQUE : ET logique au lieu de OU
bool CO_sontEgales(CO_Coordonnee coord1, CO_Coordonnee coord2){
    return CO_abscisse(coord1)==CO_abscisse(coord2) && CO_ordonnee(coord1)==CO_ordonnee(coord2);
}


void* CO_copier(void* pcoord){
    CO_Coordonnee* pnewcoord;
	pnewcoord = (CO_Coordonnee*) malloc(sizeof(CO_Coordonnee));
	pnewcoord->x = CO_abscisse(*(CO_Coordonnee*)pcoord);
	pnewcoord->y = CO_ordonnee(*(CO_Coordonnee*)pcoord);
	return pnewcoord;
}

void CO_liberer(void* pcoord){
    free(pcoord);
}


int CO_comparer(void* pcoord1,void* pcoord2){
	return CO_sontEgales(*(CO_Coordonnee*)pcoord1, *(CO_Coordonnee*)pcoord2) ? 0 : 1;
}