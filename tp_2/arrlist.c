#include <stdlib.h>
#include <stdio.h>


typedef struct recette_s
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