#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int
validationNombreDeParametre (int nombreDeParametre, char* fichierExecution)
{
  if (nombreDeParametre != 2)
    {
      fprintf (stderr, "Usage: %s [nom_du_fichier_d_entree] [nom_du_fichier_de_sortie]\n", fichierExecution);
      exit (EXIT_FAILURE);
    }
  return EXIT_SUCCESS;
}

int
ouvertureFichier (FILE **fichierAOuvrir, char* cheminFichier, char* droitAcces)
{
  *fichierAOuvrir = fopen (cheminFichier, droitAcces);
  if (!fichierAOuvrir)
    {
      fprintf (stderr, "Erreur: %s\n", strerror (errno));
      exit (EXIT_FAILURE);
    }
  return EXIT_SUCCESS;
}
