#ifndef ENTRAINEUR_H_INCLUDED
#define ENTRAINEUR_H_INCLUDED
#include <stdio.h>
typedef struct {
    int id;
    char nom[30];
    char prenom[30];
    char specialite[30];
    float salaire;
    char sexe[10];
    char date_inscription[15];
    char email[50];
    char num_tel[20];
    char cours_privee[5];
    char centre[30];
} entraineur;

int ajouter(char *filename, entraineur e);
int modifier(char *filename, int id, entraineur nouv);
int supprimer(char *filename, int id);
entraineur chercher(char *filename, int id);

#endif
