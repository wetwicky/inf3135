#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "boolean.h"
#include "assert.h"

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

int
createNewRecipy (recette_t **pointerForRecipy, char* nomRecette)
{
  *pointerForRecipy = (recette_t *) malloc (sizeof (recette_t));
  assert(pointerForRecipy != NULL && "Erreur d'allocation de memoire");
  (*pointerForRecipy)->recipyName = nomRecette;
  return EXIT_SUCCESS;
}

int
createNewCategory (category_t **pointerForCategory, recette_t **pointerForRecipy, char* nomCategory)
{
  *pointerForCategory = (category_t *) malloc (sizeof (category_t));
  assert(pointerForCategory!= NULL && "Erreur d'allocation de memoire");
  (*pointerForCategory)->categorieName = nomCategory;
  (*pointerForCategory)->recette_t = *pointerForRecipy;
  return EXIT_SUCCESS;
}

int
insertInCategoryList (category_t **headOfCategory, category_t **categoryToAdd)
{
  boolean estAjoute = FAUX;
  category_t *pointeur = *headOfCategory;
  int valueOfCmp = 0;
  if (*categoryToAdd == NULL)
    {
      fprintf (stderr, "le pointeur vers la liste de categorie que vous voulez n'existe pas.\n");
      exit (EXIT_FAILURE);
    }
  else
    {
      if (*headOfCategory == NULL)
        {
          *headOfCategory = *categoryToAdd;
        }
      else
        {
          valueOfCmp = strcasecmp ((*categoryToAdd)->categorieName, pointeur->categorieName);
          if (valueOfCmp == 0)
            {//cas où la categorie existe déja
              insertInRecipyList ((*categoryToAdd)->recette_t, pointeur);
              free (*categoryToAdd);
              estAjoute = VRAI;
            }
          else if (valueOfCmp < 0)
            {// nouvelle tête
              (*categoryToAdd)->next = pointeur;
              estAjoute = VRAI;
            }
          else
            {
              while (estAjoute == FAUX && pointeur->next != NULL)
                {
                  valueOfCmp = strcasecmp ((*categoryToAdd)->categorieName, pointeur->next->categorieName);
                  if (valueOfCmp == 0)
                    {//cas identique
                      free (*categoryToAdd);
                      estAjoute = VRAI;
                    }
                  else if (valueOfCmp < 0)
                    {//entre deux
                      (*categoryToAdd)->next = pointeur;
                      estAjoute = VRAI;
                    }
                  else
                    {
                      pointeur = pointeur->next;
                    }
                }
              if (valueOfCmp > 0 && pointeur->next == NULL)
                {//en dernier
                  pointeur->next = *categoryToAdd;
                  estAjoute = VRAI;
                }
            }
        }
    }

  return EXIT_SUCCESS;
}

int
insertInRecipyList (recette_t **recipyToAdd, category_t **categoryOfRecipy)
{
  boolean estAjoute = FAUX;
  recette_t *pointeur;
  int valueOfcmp;
  
  if (*recipyToAdd == NULL || *categoryOfRecipy == NULL)
    {
      fprintf (stderr, "un des pointeurs passes en parametre n'existe pas.\n");
      exit (EXIT_FAILURE);
    }
  else
    {
      pointeur = (*categoryOfRecipy)->recette_t;
      valueOfcmp = strcasecmp ((*recipyToAdd)->recipyName, (*categoryOfRecipy)->recette_t->recipyName);
      if (valueOfcmp == 0)
        { //recette deja presente
          fprintf (stderr, "la recette %s possede des doublons.\n", (*recipyToAdd)->recipyName);
          exit (EXIT_FAILURE);
        }
      else if (valueOfcmp < 0)
        {
          (*recipyToAdd)->next = pointeur;
          (*categoryOfRecipy)->recette_t = *recipyToAdd;
          estAjoute = VRAI;
        }
      else
        {
          while (estAjoute == FAUX && pointeur->next != NULL)
            {
              valueOfcmp = strcasecmp ((*recipyToAdd)->recipyName, pointeur->next->recipyName);
              if (valueOfcmp == 0)
                { //recette deja presente
                  fprintf (stderr, "la recette %s possede des doublons.\n", (*recipyToAdd)->recipyName);
                  exit (EXIT_FAILURE);
                }
              else if (valueOfcmp < 0)
                {
                  recette_t *tmp = pointeur->next;
                  pointeur->next = *recipyToAdd;
                  (*recipyToAdd)->next = tmp;
                  (*categoryOfRecipy)->recette_t = *recipyToAdd;
                  estAjoute = VRAI;
                }
              else
                {
                  pointeur = pointeur->next;
                }
            }
          if (valueOfcmp > 0 && pointeur->next == NULL)
            {
              pointeur->next = *recipyToAdd;
              estAjoute = VRAI;
            }
        }
    }
  return EXIT_SUCCESS;
}

int
findCategory (category_t *pointeurToReturn, category_t* headOfCategory, char* categorywanted)
{
  pointeurToReturn = headOfCategory;
  boolean finded = FAUX;
  if (pointeurToReturn == NULL)
    {
      fprintf (stderr, "le pointeur vers la liste de recette que vous voulez n'existe pas.\n");
      exit (EXIT_FAILURE);
    }
  else
    {
      while (finded == FAUX && pointeurToReturn != NULL)
        {
          if (pointeurToReturn->categorieName == categorywanted)
            {
              finded = VRAI;
            }
          else
            {
              pointeurToReturn = pointeurToReturn->next;
            }
        }
    }
  return EXIT_SUCCESS;
}

int
printAllRecipyOfACategory (category_t * theCategory)
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

int
selectRecipyByKeyWordInACategory (category_t* headOfCategory, char* keyWord)
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
  return EXIT_SUCCESS;
}

int releaseRecipyAllocation(recette_t **headOfRecipy)
{
  if(*headOfRecipy == NULL)
    {
      fprintf (stderr, "le pointeur vers la liste de recette que vous voulez n'existe pas.\n");
      exit (EXIT_FAILURE);
    }
  else
    {
      if((*headOfRecipy)->next == NULL) 
        {
          printf("recette libere = %s", (*headOfRecipy)->recipyName);
          free(*headOfRecipy);
        }
      else
        {
          releaseRecipyAllocation (&(*headOfRecipy)->next);
          printf("recette libere = %s", (*headOfRecipy)->recipyName);
          free(*headOfRecipy);
        }
    }
  return EXIT_SUCCESS;
}

int releaseCategoryAllocation(category_t ** headOfCategory)
{
  if(*headOfCategory == NULL)
    {
      fprintf (stderr, "le pointeur vers la liste de recette que vous voulez n'existe pas.\n");
      exit (EXIT_FAILURE);
    }
  else
    {
      if((*headOfCategory)->next == NULL) 
        {
          releaseRecipyAllocation (&(*headOfCategory)->recette_t);
          printf("category libere = %s", (*headOfCategory)->categorieName);
          free(*headOfCategory);
        }
      else
        {
          releaseCategoryAllocation (&(*headOfCategory)->next);
          releaseRecipyAllocation (&(*headOfCategory)->recette_t);
          printf("category libere = %s", (*headOfCategory)->categorieName);
          free(*headOfCategory);
        }
    }
}

