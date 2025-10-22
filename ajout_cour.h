#ifndef COUR_H_INCLUDED
#define COUR_H_INCLUDED
#include<stdio.h>
typedef struct
{
   int id,heure_c,capacite ;
   char nom_c[20],type_c[20],jour_c[20],coach[20],public_cible[20],intensite[20];
   char restrictions_medicales[100],objectif[20];
   char type_equipement[20];
}cour;
void ajouter_cour(cour c);
void supprimer_cour(cour id);
void modifier_cour(cour c);
cour  afficher_cour();
cour recherche_entraineur(int id);
#endif

