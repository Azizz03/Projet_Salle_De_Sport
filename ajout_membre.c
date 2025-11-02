#include "ajout_membre.h"
#include <stdio.h>
int ajouter_membre(char *filename ,membre m){
FILE *f=fopen(filename,"a");
if(f!=NULL){
fprintf(f,"id=%d nom=%s prenom=%s jour=%d mois=%s annee=%d type_abo=%s poids=%f masse_muscu=%f masse_graisseuse=%f sexe=%s taille=%d programme=%s objectif=%s,descr_maladie=%s,numero_tel=%s,email=%s,centre=%s",m.id,m.nom,m.prenom,m.jour,m.mois,m.annee,m.type_abonnement,m.poids,m.masse_musculaire,m.masse_graisseuse,m.sexe,m.taille,m.programme,m.objectif,m.descr_maladie,m.num_tel,m.email,m.centre);
fclose(f);
return 1;
}
else
	return 0;
}

int modifier_membre(char *filename, int id, membre nouv) {
    membre m;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if (f == NULL || aux == NULL)
        return 0;

    while (fscanf(f, "%d %s %s %s %d %s %d %s %s %s %f %f %f %d %s %s %s %s",
                  &m.id,m.nom, m.prenom, m.sexe,
                  &m.jour, m.mois, &m.annee, m.email,m.num_tel,m.type_abonnement,&m.poids,&m.masse_musculaire,&m.masse_graisseuse,&m.taille,m.programme,m.objectif,m.descr_maladie,m.centre)!= EOF) {
        if (m.id == id) {
            fprintf(aux, " %d %s %s %s %d %s %d %s %s %s %f %f %f %s %s %s %d %s\n",
                     m.id,nouv.nom, nouv.prenom, nouv.sexe,
                    nouv.jour, nouv.mois, nouv.annee, nouv.email, nouv.num_tel,nouv.type_abonnement,nouv.poids,nouv.masse_musculaire,nouv.masse_graisseuse,nouv.descr_maladie,nouv.objectif,nouv.programme,nouv.taille,nouv.centre);
            trouve = 1;
        } else {
            fprintf(aux, "%d %s %s %s %d %s %d %s %s %s %f %f %f %s %s %s %d %s\n",
                    m.id, m.nom, m.prenom, m.sexe,
                    m.jour, m.mois, m.annee, m.email, m.num_tel,m.type_abonnement,m.poids,m.masse_musculaire,m.masse_graisseuse,m.descr_maladie,m.objectif,m.programme,m.taille,m.centre);
        }
    }

    fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);
    return trouve;
}

int supprimer_membre(char *filename, int id) {
    membre m;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if (f == NULL || aux == NULL)
        return 0;

    while (fscanf(f, "%d %s %s %s %d %s %d %s %s %s %f %f %f %d %s %s %s %s",
                  &m.id, m.nom, m.prenom, m.sexe,
                  &m.jour, m.mois, &m.annee, m.email, m.num_tel,m.type_abonnement,&m.poids,&m.masse_musculaire,&m.masse_graisseuse,&m.taille,m.programme,m.objectif,m.descr_maladie,m.centre) != EOF) {
        if (m.id != id)
            fprintf(aux, "%d %s %s %s %d %s %d %s %s %s %f %f %f %s %s %s %d %s\n",
                    m.id, m.nom, m.prenom, m.sexe,
                    m.jour, m.mois, m.annee, m.email, m.num_tel,m.type_abonnement,m.poids,m.masse_musculaire,m.masse_graisseuse,m.descr_maladie,m.objectif,m.programme,m.taille,m.centre);
        else
            trouve = 1;
    }

    fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);
    return trouve;
}

membre chercher_membre(char *filename, int id){
    membre m, vide = {0};
    FILE *f = fopen(filename, "r");

    if (f == NULL)
        return vide;

    while (fscanf(f, "%d %s %s %s %d %s %d %s %s %s %f %f %f %d %s %s %s %s",
                  &m.id, m.nom, m.prenom, m.sexe,
                  &m.jour, m.mois, &m.annee, m.email, m.num_tel,m.type_abonnement,&m.poids,&m.masse_musculaire,&m.masse_graisseuse,&m.taille,m.programme,m.objectif,m.descr_maladie,m.centre) != EOF) {
        if (m.id == id) {
            fclose(f);
            return m;
        }
    }

    fclose(f);
    return vide; // si non trouvé
}




