#ifndef CENTRE_H_INCLUDED
#define CENTRE_H_INCLUDED
#include <gtk/gtk.h>

typedef struct {
int id ;
char nom[50];
char adresse [50];
char ville [50];
int tel;
char email[50];
int nb_salle;
int capacite_max;
char service_diso[50];
char etat[50];
int date_debutS;
int date_debutW;
int date_finS;
int date_finW;
}centre;
void ajouter_centre();
void modifier_centre();
void supprimer_centre();
void afficher_centre();
void supprimer_centre();

#endif
