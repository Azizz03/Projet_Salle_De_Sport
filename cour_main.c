#include <stdio.h>
#include "cour.h"

int main()
{
    cour c1 = {1, 10, 20, "Yoga", "Collectif", "Lundi", "Amina", "Adultes", "Moyenne", "Aucune", "Souplesse", "Tapis"};
    cour c2 = {2, 14, 15, "Muscu", "Individuel", "Mardi", "Ali", "Hommes", "Forte", "Cœur", "Force", "Haltères"};
    cour c3;

    int x = ajouter("cours.txt", c1);
    if (x) printf("\nAjout réussi"); else printf("\nErreur ajout");

    x = modifier("cours.txt", 1, c2);
    if (x) printf("\nModification réussie"); else printf("\nErreur modification");

    x = supprimer("cours.txt", 2);
    if (x) printf("\nSuppression réussie"); else printf("\nErreur suppression");

    c3 = chercher("cours.txt", 1);
    if (c3.id != -1)
        printf("\nCours trouvé : %s (%s - %s)", c3.nom_c, c3.type_c, c3.jour_c);
    else
        printf("\nCours introuvable");

    sinscrire("cours.txt", 1, "M001");
    reserver("cours.txt", 1, "C002");

    printf("\nInscription et réservation enregistrées.\n");
    return 0;
}
