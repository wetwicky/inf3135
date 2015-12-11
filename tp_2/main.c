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
#include "arrlist.h"
#include "parameter.h"
#include "parseCookBook.h"

int
main (int argc, char** argv)
{
  FILE *dataBank = NULL;
  category_t *headOfCategory = NULL;
  
  validationNombreDeParametre (argc, argv[0]);
  ouvertureFichier (&dataBank, argv[1], "r");
  parsingAllInformation (&headOfCategory, dataBank);
  research (headOfCategory);
  releaseCategoryAllocation (&headOfCategory);
  fclose (dataBank);
  return (EXIT_SUCCESS);
}

