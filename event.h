#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include <stdio.h>
#include "membre.h"
typedef struct
{
    int id;
    char nom[50];
    char type[30];
    int jour;
    int mois;
    int annee;
    int heure_debut_h;
    int heure_debut_m;
    int heure_fin_h;
    int heure_fin_m;
    float prix;
    char salle[30];
    int capacite;
} event;

int ajouter_event(char *filename, event e);
int modifier_event(char *filename, int id, event nouv);
int supprimer_event(char *filename, int id);
event chercher_event(char *filename, int id);
int afficher_event(char *filename);
typedef struct
{
    int id_membre;
    char nom[30];
    char prenom[30];
    char sexe[10];
    int id_event;
    char nom_event[50];
    char type_event[30];
    int jour;
    int mois;
    int annee;
    int heure;
    float prix;
    char salle[30];
} participation;

int ajouter_participation(char *filename, participation p);
/*int supprimer_participation(char *filename, int id_membre, int id_event);
/*participation chercher_participation(char *filename, int id_membre, int id_event);

#endif // EVENT_H_INCLUDED



