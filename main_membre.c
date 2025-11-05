#include <stdio.h>
#include <string.h>
#include "membre.h"
#include <stdlib.h>

int main() {

    int choix,id,x;
membre m1 = {100, "aziz", "hamadi", "centreA", "aziz.bentekaya@gmail.com", 20, "Decembre", 2003, "trimestriel", 50.2, 5.5, 15.2, "H", 190, "xyz", "bcv", "ert", "+21694273829", 9};
    membre m2 = {1, "Hussein", "Ali", "centreA", "ali.bentekaya@gmail.com", 26, "novembre", 2003, "Annuel", 50.2, 5.5, 15.2, "H", 190, "try", "abc", "wxc", "+21694273829", 8};
membre m3;
do{
printf("Le menu de gestion \n");
printf("1.afficher les membres\n");
printf("2.ajoutez un membre\n");
printf("3.modifier un membre\n");
printf("4.supprimer un membre\n");
printf("5.chercher un membre\n");
printf("6.reserver un coach\n");
printf("0.quitter le programme\n");
printf("saisissez votre choix\n");
scanf("%d",&choix);
switch (choix){
case 1 :afficher_membre("membre.txt");
break;
case 2 :
 x = ajouter_membre("membre.txt", m1);
if(x == 1)
    printf("Ajout de membre avec succes\n");
    else 
        printf("Echec d'ajout\n");
break;

case 3 :

x = modifier_membre("membre.txt", 1, m2);
if(x == 1)
     printf("Modification de membre avec succes\n");
    else 
       printf("Echec modification\n");
break; 
case 4:
scanf("%d",&id);    
x = supprimer_membre("membre.txt", id);
   if(x == 1)
     printf("Suppression de membre avec succes\n");
   else 
        printf("Echec suppression\n");
break;
case 5:   
m3 = chercher_membre("membre.txt", 100);
 if(m3.id == -1)
    printf("Membre introuvable\n");
    else
        printf("Membre trouve: %s %s\n", m3.nom, m3.prenom);
break;
case 0: break;
default :
printf("choix invalide \n");
}
}while(choix!=0);    
    
    return 0;
}
