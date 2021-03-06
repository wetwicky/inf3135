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

typedef struct recette_s
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

recette_t * createNewRecipy(recette_t *pointerForRecipy, char *nomRecette)
{
    boolean estAjoute = false;
    recette_t *nouvelleRecette = pointerForRecipy;
    nouvelleRecette = (recette_t *)malloc(sizeof(recette_t));
    recette_t *pointeur = nouvelleRecette; 
    int actualValue = 0;
    nouvelleRecette = (recette_t *)malloc(sizeof(recette_t));
    nouvelleRecette->recette = nomRecette;
    
    if(pointerForRecipy == NULL)
    {
        nouvelleRecette->next = NULL;
    }
    else
    {
        triCategorie(nomRecette, &estAjoute, &nouvelleRecette, pointeur, &actualValue);
        while (((estAjoute == false) && pointeur->next != NULL))
        {
            triRecette(nomRecette, &estAjoute, &nouvelleRecette, pointeur, &actualValue);
            pointeur = pointeur->next;   
        }
    }
}

void triRecette(char* nomRecette, boolean* estAjoute, recette_t** nouvelleRecette, recette_t* pointeur, int* actualValue){
    (*actualValue) = strcmp(pointeur->recette, nomRecette);
    if((*actualValue) > 0 && (*nouvelleRecette)->next == NULL)
    {
        pointeur->next = (*nouvelleRecette);
        (*estAjoute) = true;
    }
    else if ((*actualValue) < 0 )
    {
        recette_t *temporaire = pointeur->next;
        pointeur->next = (*nouvelleRecette);
        (*nouvelleRecette) = temporaire;
        (*estAjoute) = true;
    }
    else if ((*actualValue) == 0)
    {
        free((*nouvelleRecette));
        (*estAjoute) = true;
    }
}

void triCategorie(char* nomCategory, boolean* estAjoute, category_t** nouvelleCategorie, category_t* pointeur, int* actualValue){
    (*actualValue) = strcmp(pointeur->categorie, nomCategory);
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

 category_t* createNewCategory(category_t *pointerForCategory, recette_t *pointerForRecipy, char *nomCategory)
{
    boolean estAjoute = false;
    category_t *nouvelleCategorie;
    category_t *pointeur = nouvelleCategorie; 
    int actualValue = 0;
    nouvelleCategorie = (category_t *)malloc(sizeof(category_t));
    nouvelleCategorie->categorie = nomCategory;
    nouvelleCategorie->recette_t = pointerForRecipy;
    
    if(pointerForCategory == NULL)
    {
        nouvelleCategorie->next = NULL;
    }
    else
    {
        triCategorie(nomCategory, &estAjoute, &nouvelleCategorie, pointeur, &actualValue);
        while (((estAjoute == false) && pointeur->next != NULL))
        {
            triCategorie(nomCategory, &estAjoute, &nouvelleCategorie, pointeur, &actualValue);
            pointeur = pointeur->next;   
        }
    }
    return nouvelleCategorie;
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

void freeRecursiveRecette(recette_t *ptr)
{
    if (ptr->next != NULL) {
        freeRecursiveRecette(ptr->next);
        free(ptr);
    }
    else
    {
        free(ptr);
    }
}

void freeRecursiveCategory(category_t *ptr)
{
    if (ptr->next != NULL) {
        freeRecursiveCategory(ptr->next);
        freeRecursiveRecette(ptr->recette_t);
        free(ptr);
    }
    else
    {
        freeRecursiveRecette(ptr->recette_t);
        free(ptr);
    }
}

void lengthIncremention(char** carac_p, int* length, char c){
    while(*(*carac_p) != c)
    {
        (*length)++;
        (*carac_p)++;
    }
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
    recette_t *pointerForRecipy = NULL;
    category_t *pointerForCategory = NULL;
    int length = 0;
    int position = 0;
    
    validationNombreDeParametre(argc, argv[0]);
    FILE *dataBank = ouvertureFichier(argv[1], "r");
    fgets(lineBuffer, 120, dataBank);
    while(!feof(dataBank))
    {
        lengthIncremention(&carac_p, &length, '[');
        nomRecette = substring(line_p, 0, length-1);
        pointerForRecipy = createNewRecipy(pointerForRecipy, nomRecette);
        position = length;
        length = 0;
        lengthIncremention(&carac_p, &length, ']');
        nomCategory = substring(line_p, position+1, length-1);
        pointerForCategory = createNewCategory(pointerForCategory, pointerForRecipy, nomCategory);
        carac_p = carac_p + 2;
        position = length;
        length = 0;
        while(*carac_p != '\0')
        {
            pointerForRecipy = createNewRecipy(pointerForRecipy, nomRecette);
            lengthIncremention(&carac_p, &length, ']');
            nomCategory = substring(line_p, position+1, length-1);
            pointerForCategory = createNewCategory(pointerForCategory, pointerForRecipy, nomCategory); 
        }
        fgets(line_p, 120, dataBank);
    }
    //rewind(dataBank);
    freeRecursiveCategory(pointerForCategory);
    fclose(dataBank);
    return (EXIT_SUCCESS);
}

