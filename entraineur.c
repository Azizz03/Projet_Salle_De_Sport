#include <stdio.h>
#include <string.h>
#include "entraineur.h"
#include <gtk/gtk.h>

// ======== GESTION DES ENTRAÎNEURS ========

int ajouter(char *filename, entraineur e) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%d %s %s %s %.2f %s %d %d %d %s %s %d %s %s\n",
                e.id, e.nom, e.prenom, e.specialite, e.salaire, e.sexe,
                e.date_inscription.jour, e.date_inscription.mois, e.date_inscription.annee,
                e.email, e.num_tel, e.cours_privee, e.centre, e.ville_pref);
        fclose(f);
        return 1;
    }
    return 0;
}

int modifier(char *filename, int id, entraineur nouv) {
    int tr = 0;
    entraineur e;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%d %s %s %s %f %s %d %d %d %s %s %d %s %s",
                      &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
                      &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
                      e.email, e.num_tel, &e.cours_privee, e.centre, e.ville_pref) != EOF) {
            if (e.id == id) {
                fprintf(f2, "%d %s %s %s %.2f %s %d %d %d %s %s %d %s %s\n",
                        nouv.id, nouv.nom, nouv.prenom, nouv.specialite, nouv.salaire, nouv.sexe,
                        nouv.date_inscription.jour, nouv.date_inscription.mois, nouv.date_inscription.annee,
                        nouv.email, nouv.num_tel, nouv.cours_privee, nouv.centre, nouv.ville_pref);
                tr = 1;
            } else {
                fprintf(f2, "%d %s %s %s %.2f %s %d %d %d %s %s %d %s %s\n",
                        e.id, e.nom, e.prenom, e.specialite, e.salaire, e.sexe,
                        e.date_inscription.jour, e.date_inscription.mois, e.date_inscription.annee,
                        e.email, e.num_tel, e.cours_privee, e.centre, e.ville_pref);
            }
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt", filename);
    }
    return tr;
}

int supprimer(char *filename, int id) {
    int tr = 0;
    entraineur e;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%d %s %s %s %f %s %d %d %d %s %s %d %s %s",
                      &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
                      &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
                      e.email, e.num_tel, &e.cours_privee, e.centre, e.ville_pref) != EOF) {
            if (e.id != id) {
                fprintf(f2, "%d %s %s %s %.2f %s %d %d %d %s %s %d %s %s\n",
                        e.id, e.nom, e.prenom, e.specialite, e.salaire, e.sexe,
                        e.date_inscription.jour, e.date_inscription.mois, e.date_inscription.annee,
                        e.email, e.num_tel, e.cours_privee, e.centre, e.ville_pref);
            } else {
                tr = 1;
            }
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt", filename);
    }
    return tr;
}

entraineur chercher(char *filename, int id) {
    entraineur e;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (fscanf(f, "%d %s %s %s %f %s %d %d %d %s %s %d %s %s",
                      &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
                      &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
                      e.email, e.num_tel, &e.cours_privee, e.centre, e.ville_pref) != EOF && tr == 0) {
            if (e.id == id)
                tr = 1;
        }
        fclose(f);
    }
    if (tr == 0)
        e.id = -1;
    return e;
}

// ======== GESTION DES RÉSERVATIONS ========

int ajouter_reservation_cours(char* filename, char* equip_file, reservation_cours r) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return -1;
    }
    fprintf(file, "%d,%d,%s,%s,%s,%d\n",
            r.reservation_id, r.equipment_id, r.coach_name, r.course_name, r.reservation_date, r.reserved_qty);
    fclose(file);
    return 0;
}

int supprimer_reservation_cours(char* filename, int reservation_id) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return -1;
    }
    FILE* temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erreur d'ouverture du fichier temporaire\n");
        fclose(file);
        return -1;
    }
    reservation_cours r;
    int found = 0;
    while (fscanf(file, "%d,%d,%49[^,],%49[^,],%19[^,],%d\n",
                  &r.reservation_id, &r.equipment_id, r.coach_name, r.course_name, r.reservation_date, &r.reserved_qty) != EOF) {
        if (r.reservation_id != reservation_id)
            fprintf(temp, "%d,%d,%s,%s,%s,%d\n", r.reservation_id, r.equipment_id, r.coach_name, r.course_name, r.reservation_date, r.reserved_qty);
        else
            found = 1;
    }
    fclose(file);
    fclose(temp);
    if (found) {
        remove(filename);
        rename("temp.txt", filename);
        return 0;
    } else {
        remove("temp.txt");
        return -1;
    }
}

reservation_cours rechercher_reservation_cours(char* filename, int reservation_id) {
    reservation_cours res = {0};
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return res;
    }
    while (fscanf(file, "%d,%d,%49[^,],%49[^,],%19[^,],%d\n",
                  &res.reservation_id, &res.equipment_id, res.coach_name, res.course_name, res.reservation_date, &res.reserved_qty) != EOF) {
        if (res.reservation_id == reservation_id) {
            fclose(file);
            return res;
        }
    }
    fclose(file);
    return res;
}
