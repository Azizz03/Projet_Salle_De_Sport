#include "equipement.h"
#include <stdio.h>
#include <string.h>

void ajouter_equipement(Equipement e) {
    FILE *f = fopen("equipements.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s %s %s %s %d %s %s %s\n",
                e.id, e.nom, e.centre, e.categorie,
                e.quantite, e.etat, e.salle, e.couleur);
        fclose(f);
    }
}

void supprimer_equipement(char id[]) {
    Equipement e;
    FILE *f = fopen("equipements.txt", "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %d %s %s %s",
                      e.id, e.nom, e.centre, e.categorie,
                      &e.quantite, e.etat, e.salle, e.couleur) != EOF) {
            if (strcmp(e.id, id) != 0) {
                fprintf(f2, "%s %s %s %s %d %s %s %s\n",
                        e.id, e.nom, e.centre, e.categorie,
                        e.quantite, e.etat, e.salle, e.couleur);
            }
        }
        fclose(f);
        fclose(f2);
        remove("equipements.txt");
        rename("temp.txt", "equipements.txt");
    }
}

void modifier_equipement(Equipement e_modif) {
    Equipement e;
    FILE *f = fopen("equipements.txt", "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %d %s %s %s",
                      e.id, e.nom, e.centre, e.categorie,
                      &e.quantite, e.etat, e.salle, e.couleur) != EOF) {
            if (strcmp(e.id, e_modif.id) == 0) {
                // Équipement trouvé → on le remplace
                fprintf(f2, "%s %s %s %s %d %s %s %s\n",
                        e_modif.id, e_modif.nom, e_modif.centre,
                        e_modif.categorie, e_modif.quantite,
                        e_modif.etat, e_modif.salle, e_modif.couleur);
            } else {
                // Sinon on garde la ligne originale
                fprintf(f2, "%s %s %s %s %d %s %s %s\n",
                        e.id, e.nom, e.centre, e.categorie,
                        e.quantite, e.etat, e.salle, e.couleur);
            }
        }
        fclose(f);
        fclose(f2);
        remove("equipements.txt");
        rename("temp.txt", "equipements.txt");
    }
}

Equipement rechercher_equipement(char id[]) {
    Equipement e, e_vide = {"", "", "", "", 0, "", "", ""};
    FILE *f = fopen("equipements.txt", "r");

    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %d %s %s %s",
                      e.id, e.nom, e.centre, e.categorie,
                      &e.quantite, e.etat, e.salle, e.couleur) != EOF) {
            if (strcmp(e.id, id) == 0) {
                fclose(f);
                return e;
            }
        }
        fclose(f);
    }
    return e_vide; 
}


