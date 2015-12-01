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
ouvertureFichier (FILE* fichierAOuvrir, char* cheminFichier, char* droitAcces)
{
  fichierAOuvrir = fopen (cheminFichier, droitAcces);
  if (!fichierAOuvrir)
    {
      fprintf (stderr, "Erreur: %s\n", strerror (errno));
      exit (EXIT_FAILURE);
    }
  return EXIT_SUCCESS;
}

char *
substring (char *string, int position, int length)
{
  char *pointer = malloc (length + 1);
  ;
  int c;

  if (pointer == NULL)
    {
      printf ("impossibilite d'allouer de la memoire.\n");
      exit (EXIT_FAILURE);
    }

  for (c = 0; c < length; c++)
    {
      *(pointer + c) = *(string + position - 1);
      string++;
    }

  *(pointer + c) = '\0';

  return pointer;
}

/*
 * 
 */
int
main (int argc, char** argv)
{
  char lineBuffer[120];
  char *line_p = lineBuffer;
  char *carac_p = lineBuffer;
  char *nomRecette;
  char *nomCategory;
  category_t *pointerForCategory = NULL;
  recette_t *pointerForRecipy = NULL;
  int carac = 0;
  int length = 0;
  int categoryStart = 0;

  validationNombreDeParametre (argc, argv[0]);
  FILE *dataBank = NULL;
  ouvertureFichier (dataBank, argv[1], "r");
  while (!feof (dataBank))
    {
      fgets (lineBuffer, 120, dataBank);
      while (*carac_p != '[')
        {
          length++;
          carac_p++;
        }
      nomRecette = substring (line_p, 0, length - 1);
      pointerForRecipy = createNewRecipy (nomRecette);
      while (carac_p != NULL)
        {
          categoryStart = length + 1;
          length = 0;
          while (*carac_p != ']' && carac_p != NULL)
            {
              length++;
              carac_p++;
            }
          if(*carac_p == ']')
            {
              nomCategory = substring (line_p, categoryStart, length - 1);
              createNewCategory (pointerForCategory, pointerForRecipy, nomCategory); //peut passer un pointeur NULL
            }
        }

    }
  //rewind(dataBank);
  fclose (dataBank);
  return (EXIT_SUCCESS);
}

