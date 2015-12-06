/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   parameter.h
 * Author: michael
 *
 * Created on 6 décembre 2015, 14:35
 */

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

