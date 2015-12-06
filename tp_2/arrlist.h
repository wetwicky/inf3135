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
 * Allocate memory for a new recipy
 * 
 * @param:  recette_t **pointerForRecipy
 *          char* nomRecette
 * 
 * @return: int for success
 */
int createNewRecipy (recette_t **pointerForRecipy, char* nomRecette);

/*
 * Allocate memory for a new category
 * 
 * @param:  category_t **pointerForCategory
 *          recette_t **pointerForRecipy
 *          char* nomCategory
 * 
 * @return: int for success
 */
int createNewCategory (category_t **pointerForCategory, recette_t **pointerForRecipy, char* nomCategory);

/*
 * Put a recipy in an arrayList
 * 
 * @param:  recette_t **recipyToAdd
 *          category_t **categoryOfRecipy
 * 
 * @return: int for success
 */
int insertInRecipyList (recette_t **recipyToAdd, category_t **categoryOfRecipy);

/*
 * Put a category in an arrayList
 * 
 * @param:  category_t **headOfCategory
 *          category_t **categoryToAdd
 * 
 * @return: int for success
 */
int insertInCategoryList (category_t **headOfCategory, category_t **categoryToAdd);

/*
 * Print out all the recipies from a category.
 * 
 * @param:  category_t * theCategory
 * 
 * @return: int for success
 * 
 */
int printAllRecipyOfACategory (category_t * theCategory);

/*
 * Print out the recipies containing the keyword.
 * 
 * @param:  category_t* headOfCategory
 *          char* keyWord
 * 
 * @return: int for success
 */
int selectRecipyByKeyWordInACategory (category_t* headOfCategory, char* keyWord);

/*
 find a categoy that is the same as the category wanted.
 * 
 * @param:  category_t *headOfCategory
 *          char* categorywanted
 *          category_t **returnedCategory
 * 
 * @return: int for success
 */
int findCategory (category_t *headOfCategory, char* categorywanted, category_t **returnedCategory);

/*
 * release all recipy allocations.
 * 
 * @param:  recette_t **headOfRecipy
 * 
 * @return: int for success
 */
int releaseRecipyAllocation(recette_t **headOfRecipy);

/*
 * release all category allocations.
 * 
 * @param:  category_t ** headOfCategory
 * 
 * @return: int for success
 */
int releaseCategoryAllocation(category_t ** headOfCategory);

#endif /* ARRLIST_H */

