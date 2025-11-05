#include "equipement.h"
#include <string.h>


int ajouter_equipement(FILE *f, Equipement *e) {
    if (f == NULL || e == NULL) return 0;
    fprintf(f, "%s %s %s %s %d %s %s %s\n",
            e->id, e->nom, e->centre, e->categorie,
            e->quantite, e->etat, e->salle, e->couleur);
    return 1;
}

int modifier_equipement(FILE *f, Equipement *e) {
    if (f == NULL || e == NULL) return 0;
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) return 0;

    Equipement ex;
    int trouve = 0;

    while (fscanf(f, "%19s %49s %49s %49s %d %29s %49s %19s",
                  ex.id, ex.nom, ex.centre, ex.categorie,
                  &ex.quantite, ex.etat, ex.salle, ex.couleur) == 8) {

        if (strcmp(ex.id, e->id) == 0) {
            fprintf(temp, "%s %s %s %s %d %s %s %s\n",
                    e->id, e->nom, e->centre, e->categorie,
                    e->quantite, e->etat, e->salle, e->couleur);
            trouve = 1;
        } else {
            fprintf(temp, "%s %s %s %s %d %s %s %s\n",
                    ex.id, ex.nom, ex.centre, ex.categorie,
                    ex.quantite, ex.etat, ex.salle, ex.couleur);
        }
    }

    fclose(temp);
    return trouve;
}


int supprimer_equipement(FILE *f, const char *id) {
    if (f == NULL || id == NULL) return 0;
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) return 0;

    Equipement ex;
    int supprime = 0;
    while (fscanf(f, "%19s %49s %49s %49s %d %29s %49s %19s",
                  ex.id, ex.nom, ex.centre, ex.categorie,
                  &ex.quantite, ex.etat, ex.salle, ex.couleur) == 8) {

        if (strcmp(ex.id, id) != 0) {
            fprintf(temp, "%s %s %s %s %d %s %s %s\n",
                    ex.id, ex.nom, ex.centre, ex.categorie,
                    ex.quantite, ex.etat, ex.salle, ex.couleur);
        } else {
            supprime = 1;
        }
    }

    fclose(temp);
    return supprime;
}


int rechercher_equipement(FILE *f, const char *id, Equipement *e) {
    if (f == NULL || id == NULL || e == NULL) return 0;
    rewind(f);
    while (fscanf(f, "%19s %49s %49s %49s %d %29s %49s %19s",
                  e->id, e->nom, e->centre, e->categorie,
                  &e->quantite, e->etat, e->salle, e->couleur) == 8) {
        if (strcmp(e->id, id) == 0) {
            return 1;
        }
    }
    return 0;
}

