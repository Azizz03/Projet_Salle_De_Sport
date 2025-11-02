#ifndef ENTRAINEUR_H_INCLUDED
#define ENTRAINEUR_H_INCLUDED
#include <gtk/gtk.h>
typedef struct{
int id;
char nom[30],prenom[30];
int num;
char email[50],mdp[30];
int age,capacite;
char sexe[30],specialite[100],cour[100],nc[100],centre[50];

int moins,heure;
}entrianeur;

int id,heure,capacite,jour,moins,annee;
char nom[50],prenom[50],cour[50],public_cible[100],sexe[50],equipement[50];
char restriction medicale[50],objectif[50],intensite[50];
void ajouter_entraineur(entraineur E);
void supprimer_entraineur(int id);
void modifier_entraineur(entaineur E);
void afficher_entraineur();
void recherche_entraineur(int id);
