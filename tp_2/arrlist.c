#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "boolean.h"

typedef struct recette_s
{
  char *recipyName;
  struct recette_s *next;
} recette_t;

typedef struct category_s
{
  char *categorieName;
  recette_t *recette_t;
  struct category_s *next;
} category_t;

recette_t*
createNewRecipy (char* nomRecette)
{
  recette_t *nouvelleRecette = (recette_t *) malloc (sizeof (recette_t));
  nouvelleRecette->recipyName = nomRecette;
  return nouvelleRecette;
}

category_t*
createNewCategory (char *nomCategory, recette_t *firstRecipy)
{
  category_t *nouvelleCategorie = (category_t *) malloc (sizeof (category_t));
  nouvelleCategorie->categorieName = nomCategory;
  nouvelleCategorie->recette_t = firstRecipy;
  return nouvelleCategorie;
}

int
insertInCategoryList (category_t *headOfCategory, category_t *categoryToAdd)
{
  boolean estAjoute = FAUX;
  category_t *pointeur = headOfCategory = NULL;
  int valueOfStrcmp = 0;

  if (headOfCategory == NULL)
    {
      headOfCategory = categoryToAdd;
    }
  else
    {
      valueOfStrcmp = strcasecmp (categoryToAdd->categorieName, pointeur->categorieName);
      if (valueOfStrcmp == 0)
        {//cas où la categorie existe déja
          insertInRecipyList (categoryToAdd->recette_t, pointeur);
          free (categoryToAdd);
          estAjoute = VRAI;
        }
      else if (valueOfStrcmp < 0)
        {// nouvelle tête
          categoryToAdd->next = pointeur;
          estAjoute = VRAI;
        }
      else if (valueOfStrcmp > 0 && pointeur->next == NULL)
        {//2e position
          pointeur->next = categoryToAdd;
          estAjoute = VRAI;
        }
      else//avec plusieur valeurs
        {
          while (estAjoute == FAUX && pointeur->next != NULL)
            {
              valueOfStrcmp = strcasecmp (categoryToAdd->categorieName, pointeur->next->categorieName);
              if (valueOfStrcmp == 0)
                {//cas identique
                  free (categoryToAdd);
                  estAjoute = VRAI;
                }
              else if (valueOfStrcmp < 0)
                {//entre deux
                  categoryToAdd->next = pointeur;
                  estAjoute = VRAI;
                }
              else if (valueOfStrcmp > 0 && pointeur->next == NULL)
                {//en dernier
                  pointeur->next = categoryToAdd;
                  estAjoute = VRAI;
                }
              pointeur = pointeur->next;
            }
        }
    }
  return EXIT_SUCCESS;
}

int
insertInRecipyList (recette_t *recipyToAdd, category_t *categoryOfRecipy)
{
  boolean estAjoute = FAUX;
  recette_t *pointeur = categoryOfRecipy->recette_t;
  char *nomRecette = recipyToAdd->recipyName;
  int valueOfStrcmp = strcasecmp (nomRecette, categoryOfRecipy->recette_t->recipyName);
  if (valueOfStrcmp == 0)
    {
      estAjoute = VRAI;
    }
  else if (valueOfStrcmp < 0)
    {
      recipyToAdd->next = pointeur;
      categoryOfRecipy->recette_t = recipyToAdd;
      estAjoute = VRAI;
    }
  else if (valueOfStrcmp > 0 && pointeur->next == NULL)
    {
      pointeur->next = recipyToAdd;
      estAjoute = VRAI;
    }
  else
    {
      while (estAjoute == FAUX && categoryOfRecipy->recette_t->next != NULL)
        {

        }
    }

  category_t * findCategory (category_t* headOfCategory, char* categorywanted)
  {
    category_t* pointeur = headOfCategory;
    boolean finded = FAUX;
    while (finded == FAUX && pointeur != NULL)
      {
        if (pointeur->categorieName == categorywanted)
          {
            finded = VRAI;
          }
        else
          {
            pointeur = pointeur->next;
          }
      }
    return pointeur;
  }

  int printAllRecipyOfACategory (category_t * theCategory)
  {
    recette_t* pointeur = theCategory->recette_t;
    if (pointeur == NULL)
      {
        fprintf (stderr, "le pointeur vers la liste de recette que vous voulez n'existe pas.\n");
        exit (EXIT_FAILURE);
      }
    else
      {
        while (pointeur != NULL)
          {
            fprintf (stdout, "%s", pointeur->recipyName);
            pointeur = pointeur->next;
          }
      }
    return EXIT_SUCCESS;
  }

  int SelectRecipyByKeyWordInACategory (category_t* headOfCategory, char* keyWord)
  {
    recette_t* pointeur = headOfCategory->recette_t;
    if (pointeur == NULL)
      {
        fprintf (stderr, "le pointeur vers la liste de recette que vous voulez n'existe pas.\n");
        exit (EXIT_FAILURE);
      }
    else
      {
        while (pointeur != NULL)
          {
            if (strstr (pointeur->recipyName, keyWord) != NULL)
              {
                fprintf (stdout, "%s\n", pointeur->recipyName);
              }
            pointeur = pointeur->next;
          }
      }
  }
  return EXIT_SUCCESS;
}