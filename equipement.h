#include <stdio.h>

typedef struct
{
    char id[20];
    char nom[50];
    char centre[50];
    char type[50];
    char etat[20];
    int quantite;

} Equipement;

void ajouter_equipement(Equipement e);
void modifier_equipement(Equipement e);
void supprimer_equipement(char id[]);
Equipement rechercher_equipement(char id[]);
void afficher_equipements();
