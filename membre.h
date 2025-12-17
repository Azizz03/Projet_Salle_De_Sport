#ifndef MEMBRE_H_INCLUDED
#define MEMBRE_H_INCLUDED
#include <gtk/gtk.h>


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
    char objectif[40];
    char descr_maladie[100];
    char num_tel[20];
    int duree_prog;
    int maladie;
    
    
} membre;
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

/* Réservation coach : même logique que reservationSalle */
typedef struct {
    int id_membre;
    char nom_membre[30];
    char prenom_membre[30];
    char centre[40];
    char salle[30];

    char coach[60];       /* "Nom Prenom" */
    char specialite[30];
    char sexe[10];        /* "Homme" / "Femme" / "Indiff" (ou "" selon ton choix) */
    int nbre_seance;
    Date date;
    int hd, md;           /* heure/min début */
    int hf, mf;           /* heure/min fin */
} reservationCoach;
enum {
    ID,
    NOM,
    PRENOM,
    CENTRE,
    EMAIL,
    JOUR,
    MOIS,
    ANNEE,
    TYPE_ABONNEMENT,
    POIDS,    
    MASSE_MUSCU,
    MASSE_GRAISS,
    SEXE,   
    TAILLE,
    OBJECTIF,
    DESC_MALADIE,
    TELEPHONE,
    DUREE_PROG,
    MALADIE,   
    COLUMNS
};


int ajouter_membre(char *filename, membre m);
int supprimer_membre(char *filename, int id);
int modifier_membre(char *filename, int id, membre nouv);
membre chercher_membre(char *filename, int id);
void afficher_membre(char *filename);

void afficher_membres_treeview(GtkWidget *liste);
void vider(GtkWidget *liste);
int tableau_reservations_coach(reservationCoach tab[], int max, char fichier[100]);

int verifier_reservation_coach(reservationCoach tab[], int n,
                               char coach[60], char centre[40],
                               Date d,
                               int hd, int md, int hf, int mf);

int tableau_coachs_disponibles(char noms[][60], int max,
                               char specialite[30], char sexe[10],
                               char centre[40],
                               Date d,
                               int hd, int md, int hf, int mf,
                               char f_coachs[100], char f_reserve[100]);

void reserver_coach(reservationCoach r, char f_reserve[100]);

int compter_homme_femme(char fichier[100], int *nb_h, int *nb_f);




#endif
