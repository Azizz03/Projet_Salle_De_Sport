#include <stdio.h>
#include "ajout_cour.h"
#include "entraineur.h"
#include "membre.h"
#include <string.h>



int main()
{
    cour c1 = {1, 10, 20, "Yoga", "Collectif", "Lundi", "Amina", "Adultes", "Moyenne", "Aucune", "Souplesse", "Tapis"};
    cour c2 = {2, 14, 15, "Muscu", "Individuel", "Mardi", "Ali", "Hommes", "Forte", "Cœur", "Force", "Haltères"};
    cour c3;
int choix 
    do
        { do {
        }while(choix<0 || choix >6);
         switch(choix){
             case ajout :

    int x = ajouter("cours.txt", c1);
    if (x) printf("\nAjout réussi"); else printf("\nErreur ajout");
           case modif :
    x = modifier("cours.txt", 1, c2);
    if (x) printf("\nModification réussie"); else printf("\nErreur modification");
             case suprim :
    x = supprimer("cours.txt", 2);
    if (x) printf("\nSuppression réussie"); else printf("\nErreur suppression");
             case chercher :
    c3 = chercher("cours.txt", 1);
    if (c3.id != -1)
        printf("\nCours trouvé : %s (%s - %s)", c3.nom_c, c3.type_c, c3.jour_c);
    else
        printf("\nCours introuvable");
             case sinscrire :
    sinscrire("cours.txt", 1, "M001");
     printf("\nInscription  enregistrées.\n");
             case reserver:
    reserver("cours.txt", 1, "C002");

    printf("\n réservation enregistrées.\n");
         }
    return 0;
}
