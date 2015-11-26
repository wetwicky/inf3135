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

typedef enum { false, true } boolean;

typedef struct
{
    char *recette;
    struct recette_s *next;
}recette_t ;

typedef struct category_s
{
    char *categorie;
    recette_t *recette_t;
    struct category_s *next;
}category_t ;

recette_t * createNewRecipy()
{
    recette_t *nouvelleRecette;
    nouvelleRecette = (recette_t *)malloc(sizeof(recette_t));
    return nouvelleRecette;
}

void triCategorie(char* category, boolean* estAjoute, category_t** nouvelleCategorie, category_t* pointeur, int* actualValue){
    (*actualValue) = strcmp(pointeur->categorie, category);
    if((*actualValue) > 0 && (*nouvelleCategorie)->next == NULL)
    {
        pointeur->next = (*nouvelleCategorie);
        (*estAjoute) = true;
    }
    else if ((*actualValue) < 0 )
    {
        category_t *temporaire = pointeur->next;
        pointeur->next = (*nouvelleCategorie);
        (*nouvelleCategorie) = temporaire;
        (*estAjoute) = true;
    }
    else if ((*actualValue) == 0)
    {
        free((*nouvelleCategorie));
        (*estAjoute) = true;
    }
}

void createNewCategory(category_t *pointerForCategory, recette_t *pointerForRecipy, char *category)
{
    boolean estAjoute = false;
    category_t *nouvelleCategorie;
    category_t *pointeur = nouvelleCategorie; 
    int actualValue = 0;
    nouvelleCategorie = (category_t *)malloc(sizeof(category_t));
    nouvelleCategorie->categorie = category;
    nouvelleCategorie->recette_t = pointerForRecipy;
    
    if(pointerForCategory == NULL)
    {
        nouvelleCategorie->next = NULL;
    }
    else
    {
        triCategorie(category, &estAjoute, &nouvelleCategorie, pointeur, &actualValue);
        while (((estAjoute == false) && pointeur->next != NULL))
        {
            triCategorie(category, &estAjoute, &nouvelleCategorie, pointeur, &actualValue);
            pointeur = pointeur->next;   
        }
    }
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
   char *pointer = malloc(length+1);;
   int c;
 
   if (pointer == NULL)
   {
      printf("impossibilite d'allouer de la memoire.\n");
      exit(EXIT_FAILURE);
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
    char *line_p = lineBuffer;
    char *carac_p = lineBuffer;
    char *nomRecette;
    char *nomCategory;
    category_t *pointerForCategory = NULL;
    int carac = 0;
    int length = 0;
    int position = 0;
    
    validationNombreDeParametre(argc, argv[0]);
    FILE *dataBank = ouvertureFichier(argv[1], "r");
    while(!feof(dataBank))
    {
        fgets(lineBuffer, 120, dataBank);
        while(*carac_p != '[')
        {
            length++;
            carac_p++;
        }
        nomRecette = substring(line_p, 0, length-1);
        
        position = length;
        length = 0;
        while(*carac_p != ']')
        {
            length++;
            carac_p++;
        }
        nomCategory = substring(line_p, position+1, length-1);
        
    }
    rewind(dataBank);
    fclose(dataBank);
    return (EXIT_SUCCESS);
}
