#ifndef PARAMETER_H
#define PARAMETER_H
/*
 * validate the number of parameter passed in argument.
 * 
 * @param:  int nombreDeParametre
 *          char* fichierExecution
 * 
 * @return: int for success
 */
int validationNombreDeParametre (int nombreDeParametre, char* fichierExecution);

/*
 * make sure the name of the string is valid and open acces to the file.
 * 
 * @param:  FILE **fichierAOuvrir
 *          char* cheminFichier
 *          char* droitAcces
 * 
 * @return: int for success
 */
int ouvertureFichier (FILE **fichierAOuvrir, char* cheminFichier, char* droitAcces);

#endif /* PARAMETER_H */

