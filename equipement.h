#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <gtk/gtk.h>
#include <stdio.h>

typedef struct
{
    char id[20];
    char nom[50];
    char centre[50];
    char categorie[30];
    int quantite;
    char etat[50];
    char salle[50];
    char couleur[50];
} Equipement;

void ajouter_equipement(Equipement e);
void afficher_equipement(GtkWidget *liste);
void supprimer_equipement(Equipement e);
int modifier_equipement(Equipement e);

void afficher_equipement_filtre(GtkWidget *p_treeview, const gchar *terme_recherche);
// void vider(GtkWidget *liste); 
int verifier_unicite_id_equipement(const char *id_a_verifier);

int reserver_equipement(const char *id_equipement, int quantite_reservee, const char *id_coach);
void remplir_type_equipement(GtkWidget *combo_type, const char *categorie_choisie);

#endif /* EQUIPEMENT_H */
