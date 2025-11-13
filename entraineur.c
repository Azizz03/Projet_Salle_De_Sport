#include <stdio.h>
#include <string.h>
#include "entraineur.h"

// ======== VALIDATION ========

int valider_entraineur(entraineur e) {
    if (e.id <= 0) return 0;
    if (strlen(e.nom) == 0 || strlen(e.prenom) == 0) return 0;
    if (e.salaire <= 0) return 0;
    if (strcmp(e.sexe, "Homme") != 0 && strcmp(e.sexe, "Femme") != 0) return 0;
    if (e.date_inscription.jour < 1 || e.date_inscription.jour > 31) return 0;
    if (e.date_inscription.mois < 1 || e.date_inscription.mois > 12) return 0;
    if (e.date_inscription.annee < 2000 || e.date_inscription.annee > 2100) return 0;
    if (strchr(e.email, '@') == NULL) return 0;
    if (strlen(e.num_tel) < 8) return 0;
    return 1;
}

// ======== GESTION DES ENTRAÎNEURS ========

int ajouter(const char *filename, entraineur e) {
    if (!valider_entraineur(e)) {
        printf("❌ Données invalides, ajout annulé.\n");
        return 0;
    }
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

int modifier(const char *filename, int id, entraineur nouv) {
    if (!valider_entraineur(nouv)) {
        printf("❌ Données invalides pour la modification.\n");
        return 0;
    }
    int tr = 0;
    entraineur e;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp.txt", "w");
    if (f && f2) {
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
        rename("temp.txt", filename);
    }
    return tr;
}

int supprimer(const char *filename, int id) {
    int tr = 0;
    entraineur e;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp.txt", "w");
    if (f && f2) {
        while (fscanf(f, "%d %s %s %s %f %s %d %d %d %s %s %d %s %s",
                      &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
                      &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
                      e.email, e.num_tel, &e.cours_privee, e.centre, e.ville_pref) != EOF) {
            if (e.id != id)
                fprintf(f2, "%d %s %s %s %.2f %s %d %d %d %s %s %d %s %s\n",
                        e.id, e.nom, e.prenom, e.specialite, e.salaire, e.sexe,
                        e.date_inscription.jour, e.date_inscription.mois, e.date_inscription.annee,
                        e.email, e.num_tel, e.cours_privee, e.centre, e.ville_pref);
            else
                tr = 1;
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("temp.txt", filename);
    }
    return tr;
}

entraineur chercher(const char *filename, int id) {
    entraineur e;
    e.id = -1;
    FILE *f = fopen(filename, "r");
    if (f) {
        while (fscanf(f, "%d %s %s %s %f %s %d %d %d %s %s %d %s %s",
                      &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
                      &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
                      e.email, e.num_tel, &e.cours_privee, e.centre, e.ville_pref) != EOF) {
            if (e.id == id) break;
        }
        fclose(f);
    }
    return e;
}
// 🔹 GESTION DES RÉSERVATIONS
// =============================

int ajouter_reservation(const char *filename, reservation r) {
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir %s\n", filename);
        return 0;
    }
    fprintf(f, "%d,%d,%s,%s,%s,%d\n", 
            r.reservation_id, r.equipment_id, r.coach_id, r.cour_id, r.reservation_date, r.reserved_qty);
    fclose(f);
    return 1;
}

int supprimer_reservation(const char *filename, int reservation_id) {
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp_res.txt", "w");
    int tr = 0;
    reservation r;
    if (f && f2) {
        while (fscanf(f, "%d,%d,%49[^,],%49[^,],%19[^,],%d\n",
                      &r.reservation_id, &r.equipment_id, r.coach_id, r.cour_id, r.reservation_date, &r.reserved_qty) != EOF) {
            if (r.reservation_id != reservation_id)
                fprintf(f2, "%d,%d,%s,%s,%s,%d\n",
                        r.reservation_id, r.equipment_id, r.coach_id, r.cour_id, r.reservation_date, r.reserved_qty);
            else
                tr = 1;
        }
        fclose(f);
        fclose(f2);
        remove(filename);
        rename("temp_res.txt", filename);
    } else {
        printf("Erreur ouverture fichier pour suppression.\n");
    }
    return tr;
}

reservation rechercher_reservation(const char *filename, int reservation_id) {
    reservation r;
    r.reservation_id = -1;
    FILE *f = fopen(filename, "r");
    if (f) {
        while (fscanf(f, "%d,%d,%49[^,],%49[^,],%19[^,],%d\n",
                      &r.reservation_id, &r.equipment_id, r.coach_id, r.cour_id, r.reservation_date, &r.reserved_qty) != EOF) {
            if (r.reservation_id == reservation_id)
                break;
        }
        fclose(f);
    }
    return r;
}
