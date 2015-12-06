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
  char recherche[120] = {0};
  char *rechercheCategory = NULL;
  char *rechercheKeyWord = NULL;
  char *rechercheOtherWord = NULL;
  char *nomRecette = NULL;
  char *nomCategory = NULL;
  category_t *categoryToAdd = NULL;
  recette_t *recipyToAdd = NULL;
  category_t *headOfCategory = NULL;
  FILE *dataBank = NULL;

  validationNombreDeParametre (argc, argv[0]);
  ouvertureFichier (&dataBank, argv[1], "r");
  while (!feof (dataBank))
    {
      fgets (lineBuffer, 120, dataBank);
      nomRecette = strtok (lineBuffer, "[");
      createNewRecipy (&recipyToAdd, nomRecette);
      nomCategory = strtok (NULL, "[]");
      createNewCategory (&categoryToAdd, &recipyToAdd, nomCategory);
      insertInCategoryList (&headOfCategory, &categoryToAdd);
      while (nomCategory != NULL)
        {
          nomCategory = strtok (NULL, "[]");
          if (!(nomCategory == NULL || strcmp (nomCategory, " ") == 0 || strcmp (nomCategory, "\r\n") == 0))
            {
              createNewRecipy (&recipyToAdd, nomRecette);
              createNewCategory (&categoryToAdd, &recipyToAdd, nomCategory);
              insertInCategoryList (&headOfCategory, &categoryToAdd);
              
            }
        }
    }
  printf ("Entrez votre critère de recherche : ");
  scanf ("%s", recherche);

  if (recherche == NULL)
    {
      fprintf (stderr, "La valeur de recherche n'est pas valide.\n");
      exit (EXIT_FAILURE);
    }
  else
    {
      rechercheCategory = strtok (recherche, " ");
      rechercheKeyWord = strtok (NULL, " \r\n");
      if (rechercheKeyWord == NULL)
        {
          findCategory (headOfCategory, rechercheCategory);
        }
      else
        {
          rechercheOtherWord = strtok (NULL, " \r\n");
          if (rechercheOtherWord == NULL)
            {
              selectRecipyByKeyWordInACategory (headOfCategory, rechercheKeyWord);
            }
          else
            {
              printf ("Recherche invalide.");
            }
        }
    }
  releaseCategoryAllocation (&headOfCategory);
  //rewind(dataBank);
  fclose (dataBank);
  return (EXIT_SUCCESS);
}

