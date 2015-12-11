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

