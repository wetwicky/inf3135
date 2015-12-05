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
#include "arrlist.h"
#include "boolean.h"

int
validationNombreDeParametre (int nombreDeParametre, char* fichierExecution)
{
  if (nombreDeParametre != 2)
    {
      fprintf (stderr, "Usage: %s [nom_du_fichier_d_entree] [nom_du_fichier_de_sortie]\n", fichierExecution);
      exit (EXIT_FAILURE);
    }
  return EXIT_SUCCESS;
}

int
ouvertureFichier (FILE **fichierAOuvrir, char* cheminFichier, char* droitAcces)
{
  *fichierAOuvrir = fopen (cheminFichier, droitAcces);
  printf ("%p", fichierAOuvrir);
  if (!fichierAOuvrir)
    {
      fprintf (stderr, "Erreur: %s\n", strerror (errno));
      exit (EXIT_FAILURE);
    }
  return EXIT_SUCCESS;
}

/*
 * 
 */
int
main (int argc, char** argv)
{
  char lineBuffer[120] = {0};
  char *nomRecette = NULL;
  char *nomCategory = NULL;
  category_t *categoryToAdd = NULL;
  recette_t *recipyToAdd = NULL;
  category_t *headOfCategory = NULL;
  FILE *dataBank = NULL;

  validationNombreDeParametre (argc, argv[0]);
  ouvertureFichier (&dataBank, argv[1], "r");
  printf ("%s", argv[1]);
  printf ("%p", dataBank);
  while (!feof (dataBank))
    {
      fgets (lineBuffer, 120, dataBank);
      printf ("%s", lineBuffer);
      nomRecette = strtok (lineBuffer, "[");
      printf ("%s", nomRecette);
      createNewRecipy (&recipyToAdd, nomRecette);
      nomCategory = strtok (NULL, "[]");
      printf ("%s", nomCategory);
      createNewCategory (&categoryToAdd, &recipyToAdd, nomCategory); //peut passer un pointeur NULL
      while (nomCategory != NULL)
        {
          nomCategory = strtok (NULL, "[]");
          if(!(nomCategory == NULL || strcmp(nomCategory, " ") == 0 || strcmp(nomCategory, "\r\n") == 0))
            {
              printf ("%s\n", nomCategory);
              createNewCategory (&categoryToAdd, &recipyToAdd, nomCategory); //peut passer un pointeur NULL
              insertInCategoryList (&headOfCategory, &categoryToAdd);
            }
        }
    }
  releaseCategoryAllocation (&headOfCategory);
  //rewind(dataBank);
  fclose (dataBank);
  return (EXIT_SUCCESS);
}

