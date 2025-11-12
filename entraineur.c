#include <stdio.h>
#include <string.h>
#include "entraineur.h"
#include ­<gtk/gtk.h­­>

int ajouter(char *filename, entraineur e) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%d %s %s %s %.2f %s %s %s %s %s %s\n",
                e.id, e.nom, e.prenom, e.specialite, e.salaire,
                e.sexe, e.date_inscription, e.email, e.num_tel,
                e.cours_privee, e.centre);
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
        while (fscanf(f, "%d %s %s %s %f %s %s %s %s %s %s\n",
                      &e.id, e.nom, e.prenom, e.specialite, &e.salaire,
                      e.sexe, e.date_inscription, e.email, e.num_tel,
                      e.cours_privee, e.centre) != EOF) {
            if (e.id == id) {
                fprintf(f2, "%d %s %s %s %.2f %s %s %s %s %s %s\n",
                        e.id, nouv.nom, nouv.prenom, nouv.specialite, nouv.salaire,
                        nouv.sexe, nouv.date_inscription, nouv.email, nouv.num_tel,
                        nouv.cours_privee, nouv.centre);
                tr = 1;
            } else {
                fprintf(f2, "%d %s %s %s %.2f %s %s %s %s %s %s\n",
                        e.id, e.nom, e.prenom, e.specialite, e.salaire,
                        e.sexe, e.date_inscription, e.email, e.num_tel,
                        e.cours_privee, e.centre);
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
        while (fscanf(f, "%d %s %s %s %f %s %s %s %s %s %s\n",
                      &e.id, e.nom, e.prenom, e.specialite, &e.salaire,
                      e.sexe, e.date_inscription, e.email, e.num_tel,
                      e.cours_privee, e.centre) != EOF) {
            if (e.id == id)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %s %.2f %s %s %s %s %s %s\n",
                        e.id, e.nom, e.prenom, e.specialite, e.salaire,
                        e.sexe, e.date_inscription, e.email, e.num_tel,
                        e.cours_privee, e.centre);
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
        while (fscanf(f, "%d %s %s %s %f %s %s %s %s %s %s\n",
                      &e.id, e.nom, e.prenom, e.specialite, &e.salaire,
                      e.sexe, e.date_inscription, e.email, e.num_tel,
                      e.cours_privee, e.centre) != EOF && tr == 0) {
            if (e.id == id)
                tr = 1;
        }
        fclose(f);
    }
    if (tr == 0)
        e.id = -1;
    return e;
}



int ajouter_reservation_cours(char* filename, char* equip_file, reservation_cours r) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return -1; // Retourne une erreur
    }

    // Ajout de la réservation au fichier
    fprintf(file, "%d,%d,%s,%s,%s,%d\n", r.reservation_id, r.equipment_id, r.coach_name, r.course_name, r.reservation_date, r.reserved_qty);

    fclose(file);
    return 0; // Réussi
}

// Fonction pour supprimer une réservation de cours
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
    while (fscanf(file, "%d,%d,%49[^,],%49[^,],%19[^,],%d\n", &r.reservation_id, &r.equipment_id, r.coach_name, r.course_name, r.reservation_date, &r.reserved_qty) != EOF) {
        if (r.reservation_id != reservation_id) {
            fprintf(temp, "%d,%d,%s,%s,%s,%d\n", r.reservation_id, r.equipment_id, r.coach_name, r.course_name, r.reservation_date, r.reserved_qty);
        } else {
            found = 1; // Suppression effectuée
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(filename); // Supprimer l'ancien fichier
        rename("temp.txt", filename); // Renommer le fichier temporaire
        return 0; // Réussi
    } else {
        remove("temp.txt");
        return -1; // Réservation non trouvée
    }
}

// Fonction pour rechercher une réservation de cours
reservation_cours rechercher_reservation_cours(char* filename, int reservation_id) {
    reservation_cours res = {0}; // Initialisation à zéro
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return res; // Retourne une réservation vide en cas d'erreur
    }

    while (fscanf(file, "%d,%d,%49[^,],%49[^,],%19[^,],%d\n", &res.reservation_id, &res.equipment_id, res.coach_name, res.course_name, res.reservation_date, &res.reserved_qty) != EOF) {
        if (res.reservation_id == reservation_id) {
            fclose(file);
            return res; // Retourne la réservation trouvée
        }
    }

    fclose(file);
    return res; // Retourne une réservation vide si non trouvé
}

        fprintf(f, "%d;%s;%s;%s;%s;%s;%d;%c\n", 
                i->i_id, i->nom, i->prenom, i->date_naissance, 
                i->numero_tel, i->specialite, 
                i->nb_heures, i->sexe);
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }

    return *i;
}

