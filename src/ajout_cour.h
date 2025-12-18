#ifndef AJOUT_COUR_H_INCLUDED
#define AJOUT_COUR_H_INCLUDED
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
typedef struct
{
   int id;
   char nom_c[50];
   char type_c[30];
   char coach[30];
   char public_cible[30];
   char intensite[30];
   char restrictions_medicales[100];
   char objectif[30];
   int capacite;
   char type_equipement[30];
   char salle[20];
   char centre[20];
   char duree[20];
   int jour,mois,annee;
} cour;




typedef struct
{
    int sexe;
    int restriction_med;             
    int jour, mois, annee;       
   char type[20];
    char centre[20];
} reservation;


typedef struct
{
    char centre[20];
    int nb;
} StatCentre;

extern StatCentre tab[10];
extern int nb_centres;

enum
{
    COL_ID,
    COL_NOM,
    COL_TYPE,
    COL_COACH,
    COL_PUBLIC,
    COL_INTENSITE,
    COL_RESTRICTION,
    COL_OBJECTIF,
    COL_CAPACITE,
    COL_EQUIPEMENT,
    COL_SALLE,
    COL_CENTRE,
    COL_DUREE,
    COL_JOUR,
    COL_MOIS,
    COL_ANNEE,
    COLUMNS
};



int ajouter_cour(const char *filename, cour c);
int supprimer_cour(const char *filename, int id);
int modifier_cour(const char *filename, int id, cour nouv);
cour chercher_cour(const char *filename, int id);
void afficher_cours_fichier(char *filename);
 int sinscrire(char *filename, reservation r,
              char *salle_out,
              char *intensite_out,
              char *public_out,
              char *objectif_out,
              char *duree_out);
void afficher_cour(GtkWidget *liste);
void vider_cours(GtkWidget *treeview);
int rechercher_cour(char *filename, reservation r, cour *resultat);
int confirmer_reservation(char *filename, int id_cour);
int confirmer_reservation(char *filename, int id_cour);
int sexe_compatible(int sexe, char *public);
void calculer_stats_sexe(const char *filename, int *nb_hommes, int *nb_femmes);
void calculer_stats_centres(const char *filename);
int rechercher_cours_compatibles(char *filename,
                                 reservation r,
                                 cour tab[]);
int id_cour_existe(const char *filename, int id_recherche);
#endif


   







