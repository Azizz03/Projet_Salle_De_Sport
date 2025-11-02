#include "equipement.h"
#include <string.h>

int ajouter_equipement(FILE *f, Equipement e) {
    if (f == NULL)
        return 0;

    fprintf(f, "%s %s %s %s %d %s %s %s\n",
            e.id, e.nom, e.centre, e.categorie,
            e.quantite, e.etat, e.salle, e.couleur);
    return 1;
}


int modifier_equipement(FILE *f, Equipement e) {
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL)
        return 0;

    Equipement ex;
    int trouve = 0;
    while (fscanf(f, "%s %s %s %s %d %s %s %s",
                  ex.id, ex.nom, ex.centre, ex.categorie,
                  &ex.quantite, ex.etat, ex.salle, ex.couleur) != EOF) {

        if (strcmp(ex.id, e.id) == 0) {
            fprintf(temp, "%s %s %s %s %d %s %s %s\n",
                    e.id, e.nom, e.centre, e.categorie,
                    e.quantite, e.etat, e.salle, e.couleur);
            trouve = 1;
        } else {
            fprintf(temp, "%s %s %s %s %d %s %s %s\n",
                    ex.id, ex.nom, ex.centre, ex.categorie,
                    ex.quantite, ex.etat, ex.salle, ex.couleur);
        }
    }

    fclose(f);
    fclose(temp);
    remove("equipements.txt");
    rename("temp.txt", "equipements.txt");
    return trouve;
}


int supprimer_equipement(FILE *f, const char *id) {
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL)
        return 0;

    Equipement e;
    int supprime = 0;
    while (fscanf(f, "%s %s %s %s %d %s %s %s",
                  e.id, e.nom, e.centre, e.categorie,
                  &e.quantite, e.etat, e.salle, e.couleur) != EOF) {

        if (strcmp(e.id, id) != 0)
            fprintf(temp, "%s %s %s %s %d %s %s %s\n",
                    e.id, e.nom, e.centre, e.categorie,
                    e.quantite, e.etat, e.salle, e.couleur);
        else
            supprime = 1;
    }

    fclose(f);
    fclose(temp);
    remove("equipements.txt");
    rename("temp.txt", "equipements.txt");
    return supprime;
}

int rechercher_equipement(FILE *f, const char *id, Equipement *e) {
    if (f == NULL)
        return 0;

    while (fscanf(f, "%s %s %s %s %d %s %s %s",
                  e->id, e->nom, e->centre, e->categorie,
                  &e->quantite, e->etat, e->salle, e->couleur) != EOF) {

        if (strcmp(e->id, id) == 0)
            return 1;
    }
    return 0;
}

