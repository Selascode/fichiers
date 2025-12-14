#include <stdio.h>
#include <stdlib.h>

// puts ajoute automatiquement un caratère de fin de ligne
// fputs ecrit simplement  pour des CDC
// fputc ajoute des caractère
//fprintf 

// Lecture depuis un flux de texte 

int main(void){

    char buf[250]; 
    FILE *f = fopen("map.txt", "r"); 

    if (f == NULL){
        fputs("Le fichier n'a pas pu etre ouvert \n",stderr); 
        return EXIT_FAILURE;
    }
    while (fgets(buf,sizeof buf,f) != )
    {
        if (fgets(buf,sizeof buf,f) != NULL){
            printf("%s\n", buf); 
        }
    }
    
    

    if (fclose(f) == EOF){
        printf("Erreur lors de la lecture du flux"); 
        return EXIT_FAILURE;
    }
    return 0; 
}