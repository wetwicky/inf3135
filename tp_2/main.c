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

typedef enum
{
  false, true
} boolean;

typedef struct
{
  char *recette;
  struct recette_s *next;
} recette_t;

typedef struct category_s
{
  char *categorieName;
  recette_t *recette_t;
  struct category_s *next;
} category_t;

recette_t *
createNewRecipy ()
{
  recette_t *nouvelleRecette;
  nouvelleRecette = (recette_t *) malloc (sizeof (recette_t));
  return nouvelleRecette;
}

category_t*
createNewCategory (category_t *headOfCategory, recette_t *pointerForRecipy, char *nomCategory)
{
  boolean estAjoute = false;
  category_t *nouvelleCategorie;
  category_t *pointeur = headOfCategory;
  category_t *precedent;
  int valueOfStrcmp;
  nouvelleCategorie = (category_t *) malloc (sizeof (category_t));
  nouvelleCategorie->categorieName = nomCategory;
  nouvelleCategorie->recette_t = pointerForRecipy;

  if (headOfCategory == NULL)
    {
      nouvelleCategorie->next = NULL;
      headOfCategory = nouvelleCategorie;
    }
  else
    {
      valueOfStrcmp = strcmp (pointeur->categorieName, nomCategory);
      if (valueOfStrcmp == 0)
        {//cas identique
          free (nouvelleCategorie);
          estAjoute = true;
        }
      else if (valueOfStrcmp < 0)
        {//en premier
          nouvelleCategorie->next = pointeur;
          estAjoute = true;
        }
      else if (valueOfStrcmp > 0 && pointeur->next == NULL)
        {//en dernier
          pointeur->next = nouvelleCategorie;
          estAjoute = true;
        }
      else//avec plusieur valeurs
        {
          while(estAjoute == false && pointeur->next != NULL) 
            {
                valueOfStrcmp = strcmp (pointeur->next->categorieName, nomCategory);
                if (valueOfStrcmp == 0)
                  {//cas identique
                    free (nouvelleCategorie);
                    estAjoute = true;
                  }
                else if (valueOfStrcmp < 0)
                  {//entre deux
                    nouvelleCategorie->next = pointeur;
                    estAjoute = true;
                  }
                else if (valueOfStrcmp > 0 && pointeur->next == NULL)
                  {//en dernier
                    pointeur->next = nouvelleCategorie;
                    estAjoute = true;
                  }
                pointeur = pointeur->next;
            }
        }
    }
  return headOfCategory;
}

void
validationNombreDeParametre (int nombreDeParametre, char* fichierExecution)
{
  if (nombreDeParametre != 2)
    {
      fprintf (stderr, "Usage: %s [nom_du_fichier_d_entree] [nom_du_fichier_de_sortie]\n", fichierExecution);
      exit (EXIT_FAILURE);
    }
}

FILE*
ouvertureFichier (char* cheminFichier, char* droitAcces)
{
  FILE* fichierAOuvrir = fopen (cheminFichier, droitAcces);
  if (!fichierAOuvrir)
    {
      fprintf (stderr, "Erreur: %s\n", strerror (errno));
      exit (EXIT_FAILURE);
    }
  return fichierAOuvrir;
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
  FILE *dataBank = ouvertureFichier (argv[1], "r");
  while (!feof (dataBank))
    {
      fgets (lineBuffer, 120, dataBank);
      while (*carac_p != '[')
        {
          length++;
          carac_p++;
        }
      nomRecette = substring (line_p, 0, length - 1);
      pointerForRecipy = createNewRecipy ();
      categoryStart = length + 1;
      length = 0;
      while (*carac_p != ']')
        {
          length++;
          carac_p++;
        }
      nomCategory = substring (line_p, categoryStart, length - 1);
      pointerForCategory = createNewCategory (pointerForCategory, pointerForRecipy, nomCategory); //peut passer un pointeur NULL
    }
  //rewind(dataBank);
  fclose (dataBank);
  return (EXIT_SUCCESS);
}

