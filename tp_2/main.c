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
#include "arrlist.h"
#include "boolean.h"
#include "parameter.h"

void
parsingInformation (char* lineBuffer, char** nomRecette, char** nomCategory, category_t** categoryToAdd, recette_t** recipyToAdd, category_t** headOfCategory, FILE* dataBank)
{
  while (!feof (dataBank))
    {
      fgets (lineBuffer, 120, dataBank);
      (*nomRecette) = strtok (lineBuffer, "[");
      createNewRecipy (&(*recipyToAdd), (*nomRecette));
      (*nomCategory) = strtok (NULL, "[]");
      createNewCategory (&(*categoryToAdd), &(*recipyToAdd), (*nomCategory));
      insertInCategoryList (&(*headOfCategory), &(*categoryToAdd));
      while ((*nomCategory) != NULL)
        {
          (*nomCategory) = strtok (NULL, "[]");
          if (!((*nomCategory) == NULL || strcmp ((*nomCategory), " ") == 0 || strcmp ((*nomCategory), "\r\n") == 0))
            {
              createNewRecipy (&(*recipyToAdd), (*nomRecette));
              createNewCategory (&(*categoryToAdd), &(*recipyToAdd), (*nomCategory));
              insertInCategoryList (&(*headOfCategory), &(*categoryToAdd));
            }
        }
    }
}

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
  parsingInformation (lineBuffer, &nomRecette, &nomCategory, &categoryToAdd, &recipyToAdd, &headOfCategory, dataBank);
  research (headOfCategory);
  releaseCategoryAllocation (&headOfCategory);
  fclose (dataBank);
  return (EXIT_SUCCESS);
}

