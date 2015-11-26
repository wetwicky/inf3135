/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Michael Vincent
 *
 * Created on 25 novembre 2015, 09:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>

typedef struct
{
    char recette[120];
    void *next;
}recette_t ;

typedef struct
{
    char categorie[120];
    recette_t *recette_t;
    category_t *next;
}category_t ;

void createNewRecipy()
{
    (category_t *)malloc();
}

void validationNombreDeParametre(int nombreDeParametre, char* fichierExecution)
{
    if (nombreDeParametre != 2)
    {
        fprintf(stderr, "Usage: %s [nom_du_fichier_d_entree] [nom_du_fichier_de_sortie]\n",fichierExecution);
        exit(EXIT_FAILURE);
    }
}

FILE* ouvertureFichier(char* cheminFichier, char* droitAcces)
{
    FILE* fichierAOuvrir = fopen(cheminFichier, droitAcces);
    if (!fichierAOuvrir)
    {
        fprintf( stderr, "Erreur: %s\n", strerror(errno) );
        exit(EXIT_FAILURE);
    }
    return fichierAOuvrir;
}

char *substring(char *string, int position, int length) 
{
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
 
   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }
 
   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *(string+position-1);      
      string++;   
   }
 
   *(pointer+c) = '\0';
 
   return pointer;
}

/*
 * 
 */
int main(int argc, char** argv) {
    char lineBuffer[120];
    char line_p = lineBuffer;
    char nomRecette[120];
    char nomCategory[120];
    category_t *pointerForCategory;
    int carac = 0;
    int length = 0;
    int position = 0;
    
    validationNombreDeParametre(argc, argv[0]);
    FILE *dataBank = ouvertureFichier(argv[1], "r");
    while(!feof(dataBank))
    {
        fgets(lineBuffer, 120, dataBank);
        while(line_p != '[')
        {
            length++;
            line_p++;
        }
        nomRecette = substring(lineBuffer, 0, length-1);
        
        position = length;
        length = 0;
        while(line_p != ']')
        {
            length++;
            line_p++;
        }
        nomCategory = substring(lineBuffer, position+1, length-1);
    }
    rewind(dataBank);
    fclose(dataBank);
    return (EXIT_SUCCESS);
}

