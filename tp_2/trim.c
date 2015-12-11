#include <assert.h>
#include <ctype.h>
#include <string.h>

void trim(char* stringBuffer)
{
  char* iterateur;
  char* debut;
  assert(stringBuffer != NULL);

  debut = stringBuffer;
  iterateur = stringBuffer;
  while (isspace(*iterateur) && *iterateur != '\0')
    iterateur++;
  while (*(iterateur - 1) != '\0')
  {
    *debut = *iterateur;
    iterateur++;
    debut++;
  }
  iterateur = stringBuffer + strlen(stringBuffer) - 1;
  while (iterateur > stringBuffer && isspace(*iterateur))
    iterateur--;
  *(iterateur + 1) = '\0';
}