#ifndef PARSECOOKBOOK_H
#define PARSECOOKBOOK_H

/*
 * obtains substrings from a buffer respecting
 * the format for recipy and category
 * 
 * @param:  char* lineBuffer
 *          char** nomRecette
 *          char** nomCategory
 */
void obtainFirstTokens(char* lineBuffer, char** nomRecette, char** nomCategory);

/*
 * obtain a substring from a buffer respecting
 * the format for category. this method is used
 * when their is more than one category
 * 
 * @param:  char* lineBuffer
 *          char** nomCategory
 */
void obtainNextCategoryToken(char** nomCategory);

/*
 * create new structure containing
 * the recipy inside a category placed in the array
 * 
 * @param:  category_t** headOfCategory
 *          recette_t** recipyToAdd
 *          category_t** categoryToAdd
 *          char* nomRecette
 *          char* nomCategory
 */
void insertNewValue(category_t** headOfCategory, recette_t** recipyToAdd, category_t** categoryToAdd, char* nomRecette, char* nomCategory);

/*
 * this method is use to coordinate the process to create
 * all the structure containing the category and recipy
 * 
 * @param:  category_t** headOfCategory
 *          recette_t** recipyToAdd
 *          category_t** categoryToAdd
 *          char* nomRecette
 *          char* nomCategory
 */
void parsingAllInformation (category_t** headOfCategory, FILE* dataBank);


#endif /* PARSECOOKBOOK_H */

