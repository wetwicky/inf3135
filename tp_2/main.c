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
#include "parameter.h"
#include "trim.h"

void obtainFirstTokens(char* lineBuffer, char** nomRecette, char** nomCategory){
  *nomRecette = strtok (lineBuffer, "[");
  trim(lineBuffer);
  *nomCategory = strtok (NULL, "[]");
}

void obtainNextCategoryToken(char** nomCategory){
  *nomCategory = strtok (NULL, "[]");
}

void insertNewValue(category_t** headOfCategory, recette_t** recipyToAdd, category_t** categoryToAdd, char* nomRecette, char* nomCategory){
  createNewRecipy (recipyToAdd, nomRecette);
  createNewCategory (categoryToAdd, recipyToAdd, nomCategory);
  insertInCategoryList (headOfCategory, categoryToAdd);
}

void
parsingAllInformation (category_t** headOfCategory, FILE* dataBank)
{
  recette_t *recipyToAdd = NULL;
  category_t *categoryToAdd = NULL;
  char lineBuffer[120] = {0};
  char *nomRecette = NULL;
  char *nomCategory = NULL;
  while (!feof (dataBank))
    {
      fgets (lineBuffer, 120, dataBank);
      obtainFirstTokens(lineBuffer, &nomRecette, &nomCategory);
      insertNewValue(headOfCategory, &recipyToAdd, &categoryToAdd, nomRecette, nomCategory);
      while (nomCategory != NULL)
        {
          obtainNextCategoryToken(&nomCategory);
          if (!(nomCategory == NULL || strcmp (nomCategory, " ") == 0 || strcmp (nomCategory, "\r\n") == 0))
            {
              insertNewValue(headOfCategory, &recipyToAdd, &categoryToAdd, nomRecette, nomCategory);
            }
        }
    }
}

int
main (int argc, char** argv)
{
  FILE *dataBank = NULL;
  category_t *headOfCategory = NULL;
  
  validationNombreDeParametre (argc, argv[0]);
  ouvertureFichier (&dataBank, argv[1], "r");
  parsingAllInformation (&headOfCategory, dataBank);
  research (headOfCategory);
  releaseCategoryAllocation (&headOfCategory);
  fclose (dataBank);
  return (EXIT_SUCCESS);
}

