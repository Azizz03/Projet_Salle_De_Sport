#include <stdio.h>
#include "event.h"
#include "membre.h"
int main()
{
    // --- TEST ÉVÉNEMENTS ---
    event e1 = {1, "YogaMatinal", "Sport", 10, 11, 2025, 7, 30, 8, 30, 12.00, "SalleZen"};
    event e2 = {2, "ZumbaParty", "CoursCollectif", 12, 11, 2025, 18, 0, 19, 0, 8.00, "SalleDance"};

    ajouter_event("events.txt", e1);
    ajouter_event("events.txt", e2);

    printf("Deux événements ajoutés.\n");


    int x = ajouter_event("events.txt", e1);
    if (x == 1)
        printf("Ajout avec succès\n");
    else
        printf("Échec ajout\n");

    x = modifier_event("events.txt", 1, e2);
    if (x == 1)
        printf("Modification avec succès\n");
    else
        printf("Échec modification\n");

    x = supprimer_event("events.txt", 1);
    if (x == 1)
        printf("Suppression avec succès\n");
    else
        printf("Échec suppression\n");

    e3 = chercher_event("events.txt", 1);
    if (e3.id == -1)
        printf("Événement introuvable\n");
    else
        printf("Événement trouvé : %s - %s\n", e3.nom, e3.type);

    return 0;
    // --- TEST PARTICIPATIONS ---
    participation p1 = {101, "Ali", "Ben", "Homme", 1, "YogaMatinal", "Sport", 10, 11, 2025, 7, 12.00, "SalleZen"};
    participation p2 = {102, "Sara", "Kefi", "Femme", 2, "ZumbaParty", "CoursCollectif", 12, 11, 2025, 18, 8.00, "SalleDance"};

    ajouter_participation("participations.txt", p1);
    ajouter_participation("participations.txt", p2);

    printf("Participations ajoutées.\n");

    // --- RECHERCHE ---
    participation p3 = chercher_participation("participations.txt", 101, 1);
    if (p3.id_membre != -1)
        printf("Participation trouvée : %s %s à %s (%s)\n", p3.nom, p3.prenom, p3.nom_event, p3.salle);
    else
        printf("Participation introuvable.\n");

    // --- SUPPRESSION ---
    int x = supprimer_participation("participations.txt", 102, 2);
    if (x == 1)
        printf("Participation supprimée.\n");
    else
        printf("Aucune participation supprimée.\n");

    return 0;
}
