#ifndef ARRLIST_H
#define ARRLIST_H

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

/*
 Allocate memory for a new recipy
 */
int createNewRecipy (recette_t **pointerForRecipy, char* nomRecette);

/*
 Allocate memory for a new category
 */
int createNewCategory (category_t **pointerForCategory, recette_t **pointerForRecipy, char* nomCategory);

/*
 Put a recipy in an arrayList
 */
int insertInRecipyList (recette_t **recipyToAdd, category_t **categoryOfRecipy);

int insertInCategoryList (category_t **headOfCategory, category_t **categoryToAdd);

/*
 Print out all the recipies from a category.
 */
int printAllRecipyOfACategory (category_t * theCategory);

/*
 Print out the recipies containing the keyword.
 */
int selectRecipyByKeyWordInACategory (category_t* headOfCategory, char* keyWord);

int findCategory (category_t *headOfCategory, char* categorywanted);

int releaseRecipyAllocation(recette_t **headOfRecipy);

int releaseCategoryAllocation(category_t ** headOfCategory);

#endif /* ARRLIST_H */

