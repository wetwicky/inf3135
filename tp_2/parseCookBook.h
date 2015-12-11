/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   parseCookBook.h
 * Author: michael
 *
 * Created on 11 décembre 2015, 14:34
 */

#ifndef PARSECOOKBOOK_H
#define PARSECOOKBOOK_H

void obtainFirstTokens(char* lineBuffer, char** nomRecette, char** nomCategory);

void obtainNextCategoryToken(char** nomCategory);

void insertNewValue(category_t** headOfCategory, recette_t** recipyToAdd, category_t** categoryToAdd, char* nomRecette, char* nomCategory);

void parsingAllInformation (category_t** headOfCategory, FILE* dataBank);


#endif /* PARSECOOKBOOK_H */

