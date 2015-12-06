=======
#UTILITE
=======
Ce logiciel permet de chercher des recette trié par categorie. la recherche peux se faire
par categorie ou bien par categorie avec un mot clé. Un mot clé est une suite de caractere
alphabétique qui peuvent apparaitre dans le nom d'une recette qui se trouve dans la categorie
le logiciel a ete redige en langage C dans le cadre du cours INF3135 de Jacques Bergers pour
la session d'automne 2015.
=============
#MODE D'EMPLOI DU MAKEFILE
=============
  les principales cible peuvent etre executé directement, et elles sont:
  
     compile                  compile .c file into .o
     clean                    remove compile files
     link                     create executable from all .o specified
     all                      build 
     help                     print help mesage

=============
#PROCEDURE D'EXECUTION
=============
##etape 1
-------
pour compiler, vous devez saisir la ligne suivante, cela vous donnera un executable
```c
make link
```

##etape 2
-------
pour utiliser le fichier executable, vous devez avoir  1 fichier ayant les recettes dans un
format:<nom de la recette> <[categorie1]> [<[categorie2]>]...
Si tel est le cas,
```c
./executable <nom du fichier des donnees>
```
*ce qui donne avec le parametre:*

```c
./executable fichierDesDonnees.txt
```
##etape 3
-------
en appuyant sur `Enter` vous venez d'executer le fichier avec le parametre nécessaire.
Vous pouvez ensuite rechercher :

votre/vos recette(s) en écrivant (une categorie) 
ex: <nomDeLaCategorie>

  ou  

la/les recette(s) ayant le mot clé saisie (une categorie et un mot clé) 
ex: <nomDeLaCategorie> <motClé>

Pour quitter, simplement saisir le mot mot <quit> et appuyer sur <enter> lorsque 
la phrase <Entrez votre critère de recherche («quit» pour terminer): > apparait.


