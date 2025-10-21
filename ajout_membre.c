#include "ajout_membre.h"

int ajouter_membre(membre m){
FILE *f=fopen("membre.txt","a");
if(f!=NULL){
fprintf(f,"id=%s nom=%s prenom=%s jour=%d mois=%sannee=%d type_abo=%s poids=%f masse_muscu=%fmasse_graisseuse=%fsexe=%s taille=%d programme=%s objectif=%s descr_maladie=%s",m.id,m.nom,m.prenom,m.jour,m.mois,m.annee,m.type_abonnement,m.poids,m.masse_musculaire,m.masse_graisseuse,m.sexe,m.taille,m.programme,m.objectif,m.descr_maladie);
fclose(f);

int modifier_membre(membre *m){
FILE *f=fopen("membre.txt","r");
FILE *f1=fopen("membre_modif.txt","w");
membre membre_modif;
if((f==NULL)||(f1==NULL)
return;
while(fscanf

