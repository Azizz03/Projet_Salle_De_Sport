#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <gtk/gtk.h>
#include <stdio.h>

typedef struct {
    char id[20];
    char nom[50];
    char centre[50];
    char categorie[30];
    int quantite;
    char etat[30];
    char salle[50];
    char couleur[20];
} Equipement;


int ajouter_equipement(FILE *f, Equipement e);
int modifier_equipement(FILE *f, Equipement e);
int supprimer_equipement(FILE *f, const char *id);
int rechercher_equipement(FILE *f, const char *id, Equipement *e);

#endif

