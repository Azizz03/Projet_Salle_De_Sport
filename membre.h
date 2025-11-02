#ifndef MEMBRE_H_INCLUDED
#define MEMBRE_H_INCLUDED

typedef struct {
    int id;
    char nom[30];
    char prenom[30];
    char centre[40];
    char email[30];
    int jour;
    char mois[30];
    int annee;
    char type_abonnement[40];
    float poids;
    float masse_musculaire;
    float masse_graisseuse;
    char sexe[20];
    int taille;
    char programme[20];
    char objectif[40];
    char descr_maladie[100];
    char num_tel[20];
} membre;

int ajouter_membre(char *filename, membre m);
int supprimer_membre(char *filename, int id);
int modifier_membre(char *filename, int id, membre nouv);
membre chercher_membre(char *filename, int id);
void afficher_membre(char *filename);

#endif
