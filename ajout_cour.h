#ifndef COUR_H_INCLUDED
#define COUR_H_INCLUDED
#include <gtk/gtk.h>
#include<stdio.h>
typedef struct
{
   int id,heure_c,capacite ;
   char nom_c[20],type_c[20],jour_c[20],coach[20],public_cible[20],intensite[20];
   char restrictions_medicales[100],objectif[20];
   char type_equipement[20];
}cour;
int ajouter_cour(char *filename,cour c);
int supprimer_cour( char *filename,int id );
void modifier_cour(char *filename ,int id ,cour nouv);
int siscrire(char *filename,int id_cour,char id_membre[]);
int reserver (char*filename ,int id_cour ,char id_coach[]);
cour chercher_cour(char *filename ,int id );
#endif

