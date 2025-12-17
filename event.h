#ifndef EVENT_H
#define EVENT_H
#include <gtk/gtk.h> 
#include <limits.h>

#define EVENT_FILENAME "event.txt"
#ifdef event
#undef event
#endif
typedef struct
{
    int id;
    char nom[50];
    char type[30];
    int jour, mois, annee;
    int heure_debut_h, heure_debut_m;
    int heure_fin_h, heure_fin_m;
    float prix;
    char salle[30];
    int capacite;
} event;

typedef struct
{
    int id_membre;
    char nom[50];
    char prenom[50];
    char sexe[10];
    int id_event;
    char nom_event[50];
    char type_event[50];
    int jour, mois, annee, heure;
    float prix;
    char salle[30];
    int capacite;
    char niveau[100]; 
} participation;



int ajouter_event(char *filename, event e);

int modifier_event(const char *filename, int id, event nouv);
int supprimer_event(const char *filename, int id);
int safe_supprimer_event(const char *filename, int id);
event chercher_event(char *filename, int id);
int afficher_event(char *filename);

int ajouter_participation(char *filename, participation p);

void ajouter(char nom[], char prenom[], char login[], char password[], int role);
int verifier(char login[], char password[]);


void rafraichir_liste_event(GtkWidget *liste, char *nom_fichier);
void afficher_event_treeview(GtkWidget *treeview, char *filename);

#endif
