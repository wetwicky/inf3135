#ifndef ARRLIST_H
#define ARRLIST_H
typedef struct recette_s {} recette_t;
typedef struct category_s {} category_t;
/*
 Allocate memory for a new recipy
 */
recette_t* createNewRecipy ();

/*
 Allocate memory for a new category
 */
category_t* createNewCategory (category_t*, recette_t*, char*);

/*
 Put a recipy in an arrayList
 */
void insertInRecipyList(recette_t*, category_t*);

/*
 Print out all the recipies from a category.
 */
int printAllRecipyOfACategory (category_t * theCategory);

/*
 Print out the recipies containing the keyword.
 */
int printRecipiesByKeyWordInACategory (category_t* headOfCategory, char* keyWord);

#endif /* ARRLIST_H */

