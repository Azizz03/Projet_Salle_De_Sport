#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <gtk/gtk.h>

typedef struct {
    char nom[30];
    char type[40];
    char date[40];
    int heure;
    int minute;
    int annee;
    char mois[40];
    float prix;
    char salle[50];
} evenement;

void afficher_evenement();
void supprimer_evenement(char nom[]);
void modifier_evenement(evenement newE);
void ajouter_evenement(evenement e);
void rechercher_evenement(char nom[]);

#endif
