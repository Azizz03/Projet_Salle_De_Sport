#include <stdio.h>
#include <string.h>
#include "entraineur.h"

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
