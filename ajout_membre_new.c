#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membre.h"

int ajouter_membre(char *filename, membre m) {
    FILE *f = fopen(filename, "a");
    if(f != NULL) {
        fprintf(f, "%d %s %s %s %s %d %s %d %s %.2f %.2f %.2f %s %d %s %s %s %s\n",
                m.id, m.nom, m.prenom, m.centre, m.email,
                m.jour, m.mois, m.annee, m.type_abonnement,
                m.poids, m.masse_musculaire, m.masse_graisseuse,
                m.sexe, m.taille, m.programme, m.objectif,
                m.descr_maladie, m.num_tel);
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

    while (fscanf(f, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %s",
                  &m.id, m.nom, m.prenom, m.centre, m.email,
                  &m.jour, m.mois, &m.annee, m.type_abonnement,
                  &m.poids, &m.masse_musculaire, &m.masse_graisseuse,
                  m.sexe, &m.taille, m.programme, m.objectif,
                  m.descr_maladie, m.num_tel) != EOF) {
        if (m.id == id) {
            fprintf(aux, "%d %s %s %s %s %d %s %d %s %.2f %.2f %.2f %s %d %s %s %s %s\n",
                    nouv.id, nouv.nom, nouv.prenom, nouv.centre, nouv.email,
                    nouv.jour, nouv.mois, nouv.annee, nouv.type_abonnement,
                    nouv.poids, nouv.masse_musculaire, nouv.masse_graisseuse,
                    nouv.sexe, nouv.taille, nouv.programme, nouv.objectif,
                    nouv.descr_maladie, nouv.num_tel);
            trouve = 1;
        } else {
            fprintf(aux, "%d %s %s %s %s %d %s %d %s %.2f %.2f %.2f %s %d %s %s %s %s\n",
                    m.id, m.nom, m.prenom, m.centre, m.email,
                    m.jour, m.mois, m.annee, m.type_abonnement,
                    m.poids, m.masse_musculaire, m.masse_graisseuse,
                    m.sexe, m.taille, m.programme, m.objectif,
                    m.descr_maladie, m.num_tel);
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

    while (fscanf(f, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %s",
                  &m.id, m.nom, m.prenom, m.centre, m.email,
                  &m.jour, m.mois, &m.annee, m.type_abonnement,
                  &m.poids, &m.masse_musculaire, &m.masse_graisseuse,
                  m.sexe, &m.taille, m.programme, m.objectif,
                  m.descr_maladie, m.num_tel) != EOF) {
        if (m.id != id) {
            fprintf(aux, "%d %s %s %s %s %d %s %d %s %.2f %.2f %.2f %s %d %s %s %s %s\n",
                    m.id, m.nom, m.prenom, m.centre, m.email,
                    m.jour, m.mois, m.annee, m.type_abonnement,
                    m.poids, m.masse_musculaire, m.masse_graisseuse,
                    m.sexe, m.taille, m.programme, m.objectif,
                    m.descr_maladie, m.num_tel);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);
    return trouve;
}

membre chercher_membre(char *filename, int id) {
    membre m;
    membre vide = {-1};
    
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return vide;

    while (fscanf(f, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %s",
                  &m.id, m.nom, m.prenom, m.centre, m.email,
                  &m.jour, m.mois, &m.annee, m.type_abonnement,
                  &m.poids, &m.masse_musculaire, &m.masse_graisseuse,
                  m.sexe, &m.taille, m.programme, m.objectif,
                  m.descr_maladie, m.num_tel) != EOF) {
        if (m.id == id) {
            fclose(f);
            return m;
        }
    }

    fclose(f);
    return vide;
}

void afficher_membre(char *filename) {
    membre m;
    FILE *f = fopen(filename, "r");
    
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier!\n");
        return;
    }
    
    printf("\n=== LISTE DES MEMBRES ===\n");
    while (fscanf(f, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %s",
                  &m.id, m.nom, m.prenom, m.centre, m.email,
                  &m.jour, m.mois, &m.annee, m.type_abonnement,
                  &m.poids, &m.masse_musculaire, &m.masse_graisseuse,
                  m.sexe, &m.taille, m.programme, m.objectif,
                  m.descr_maladie, m.num_tel) != EOF) {
        printf("ID: %d\n", m.id);
        printf("Nom: %s\n", m.nom);
        printf("Prenom: %s\n", m.prenom);
        printf("Centre: %s\n", m.centre);
        printf("Email: %s\n", m.email);
        printf("Date de naissance: %d %s %d\n", m.jour, m.mois, m.annee);
        printf("Type abonnement: %s\n", m.type_abonnement);
        printf("Poids: %.2f kg\n", m.poids);
        printf("Masse musculaire: %.2f kg\n", m.masse_musculaire);
        printf("Masse graisseuse: %.2f kg\n", m.masse_graisseuse);
        printf("Sexe: %s\n", m.sexe);
        printf("Taille: %d cm\n", m.taille);
        printf("Programme: %s\n", m.programme);
        printf("Objectif: %s\n", m.objectif);
        printf("Maladies: %s\n", m.descr_maladie);
        printf("Telephone: %s\n", m.num_tel);
        printf("---------------------------\n");
    }
    
    fclose(f);
}
