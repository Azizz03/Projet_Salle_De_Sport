#include <stdio.h>
#include "entraineur.h"

int main() {
    entraineur e1 = {1, "Ali", "Ben", "Fitness", 1200.50, "Homme", "01/01/2024",
                     "ali@gmail.com", "20202020", "Oui", "CentreA"};
    entraineur e2 = {2, "Sara", "Khemiri", "Yoga", 1000.00, "Femme", "05/02/2024",
                     "sara@gmail.com", "98989898", "Non", "CentreB"};
    entraineur e3;

    int x = ajouter("entraineurs.txt", e1);
    x = ajouter("entraineurs.txt", e2);

    if (x == 1)
        printf("\nAjout effectué avec succès !");
    else
        printf("\nÉchec dajout !");

    x = modifier("entraineurs.txt", 1, e2);
    if (x == 1)
        printf("\nModification réussie !");
    else
        printf("\nÉchec de modification !");

    x = supprimer("entraineurs.txt", 2);
    if (x == 1)
        printf("\nSuppression réussie !");
    else
        printf("\nÉchec de suppression !");

    e3 = chercher("entraineurs.txt", 1);
    if (e3.id == -1)
        printf("\nIntrouvable !");
    else
        printf("\nEntraîneur trouvé : %s %s, Spécialité : %s", e3.nom, e3.prenom, e3.specialite);

    return 0;
}
