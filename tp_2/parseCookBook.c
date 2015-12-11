#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrlist.h"
#include "trim.h"

void
obtainFirstTokens (char* lineBuffer, char** nomRecette, char** nomCategory)
{
  *nomRecette = strtok (lineBuffer, "[");
  trim (lineBuffer);
  *nomCategory = strtok (NULL, "[]");
}

void
obtainNextCategoryToken (char** nomCategory)
{
  *nomCategory = strtok (NULL, "[]");
}

void
insertNewValue (category_t** headOfCategory, recette_t** recipyToAdd, category_t** categoryToAdd, char* nomRecette, char* nomCategory)
{
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
      if (fgets (lineBuffer, 120, dataBank) != NULL)
        {
          obtainFirstTokens (lineBuffer, &nomRecette, &nomCategory);
          insertNewValue (headOfCategory, &recipyToAdd, &categoryToAdd, nomRecette, nomCategory);
          while (nomCategory != NULL)
            {
              obtainNextCategoryToken (&nomCategory);
              if (!(nomCategory == NULL || strcmp (nomCategory, " ") == 0 || strcmp (nomCategory, "\r\n") == 0))
                {
                  insertNewValue (headOfCategory, &recipyToAdd, &categoryToAdd, nomRecette, nomCategory);
                }
            }
        }
    }
}

