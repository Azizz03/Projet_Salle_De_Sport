#include <stdio.h>
#include <string.h>
#include "ajout_membre.h"

int main()
{
    membre m1= {100, "aziz", "hamadi", "centreA", "aziz.bentekaya@gmail.com", 20, "Decembre", 2003, "trimestriel", 50.2, 5.5, 15.2,"H", 190, "...", "...","...", "+21694273829"};
    membre m2= {100, "Hussein", "Ali", "centreA", "ali.bentekaya@gmail.com", 26, "novembre", 2003, "Annuel", 50.2, 5.5, 15.2,"H", 190, "...", "...", "...", "+21694273829"};
membre m3;
    int x=ajouter_membre("membre.txt", m1);
    
    x=modifier_membre("membre.txt",1,m2 );

    if(x==1)
        printf("\nModification de point avec succés");
    else printf("\nechec Modification");
    x=supprimer_membre("membre.txt",1 );
    if(x==1)
        printf("\nSuppression de point avec succés");
    else printf("\nechec Suppression");

    m3=chercher_membre("membre.txt",100 );
    if(m3.id==-1)
        printf("introuvable");
    return 0;
}
