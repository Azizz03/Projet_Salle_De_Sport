#ifndef ENTRAINEUR_H_INCLUDED
#define ENTRAINEUR_H_INCLUDED
#include <stdio.h>
typedef struct {
    int jour,mois,annee;
}date; 

typedef struct 
    int id;
    char nom[30];
    char prenom[30];
    char specialite[30];
    float salaire;
    char sexe[10];
    date date_inscription;
    char email[50];
    char num_tel[20];
    int cours_privee;
    char centre[30];
    char ville_pref[30];
} entraineur;
typedef struct {     
    int reservation_id;         
    int equipment_id;          
    char coach_name[50];        
    char course_name[50];       
    char reservation_date[20];  
    int reserved_qty;           
} reservation_cours;

int ajouter(char *filename, entraineur e);
int modifier(char *filename, int id, entraineur nouv);
int supprimer(char *filename, int id);
entraineur chercher(char *filename, int id);

int ajouter_reservation_cours(char* filename, char* equip_file, reservation_cours r) ;
int supprimer_reservation_cours(char* filename, int reservation_id) ;
reservation_cours rechercher_reservation_cours(char* filename, int reservation_id);



