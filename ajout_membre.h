#ifndef MEMBRE_H_INCLUDED
#define MEMBRE_H_INCLUDED
#include <gtk/gtk.h>

typedef struct {
int id;
char nom[30];
char prenom[30];
int jour;
char mois[30];
int annee;
char type_abonnement[40];
float poids;
int taille;
char programme[20];
char objectif[40];
char descr_maladie[100];
}Membre;

void ajouter_membre(Membre m );
void supprimer_membre(int id);
void modifier_membre(Membre m);
void afficher_membre();
membre rechercher_membre(int id);





