#ifndef ENTRAINEUR_H
#define ENTRAINEUR_H
#include <gtk/gtk.h>
#include <stdio.h>
extern int coach_connecte_id;

typedef struct { 
int jour, mois, annee;
} date;

typedef struct {
    int heure, minutes;
} heure;

typedef struct {
    int id;
    char nom[30];
    char prenom[30];
    char specialite[30];
    float salaire;
    char sexe[10];
    date date_inscription;
    char email[50];
    char num_tel[20];
    char centre[30];
    char ville_pref[30];
} entraineur;

typedef struct {
    int reservation_id;
    int coach_id;
    int cour_id;
    int cours_privee; 
    date date;
    heure heure;
    int capacite ;
} reservation;

enum
{
    ID,
    NOM,
    PRENOM,
    SPECIALITE,
    SALAIRE,
    SEXE,
    JOUR,
    MOIS,
    ANNEE,
    EMAIL,
    TELEPHONE,
    CENTRE,
    VILLE_PREF,
    COLUMNS
};



//entraineur chercher_entraineur(char *filename, int id);


int valider_entraineur(entraineur e);
int ajouter(entraineur e);

int modifier(int id, entraineur nouv);
int supprimer(int id);
entraineur chercher(int id);


int ajouter_reservation(reservation r);
int supprimer_reservation(int reservation_id);
reservation rechercher_reservation(int reservation_id);


void vider(GtkWidget *liste);
void afficher_entraineur(GtkWidget *liste);

#endif


    

