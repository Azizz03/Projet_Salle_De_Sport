#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "centre.h"

int ajouter_centre(char *filename, centre c) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%d %s %s %s %d %s %d %d %s %s %d %d %d %d\n",
                c.id, c.nom, c.adresse, c.ville, c.tel,
                c.email, c.nb_salle, c.capacite_max, c.service_diso,c.etat,
                c.date_debutS,c.date_debutW, c.date_finS,c.date_finW);
        fclose(f);
        return 1;
    }
    return 0;
}
int modifier_centre(char *filename, int id, centre new) {
    centre c;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if (f == NULL || aux == NULL)
        return 0;

    while (fscanf(f, "%d %s %s %s %d %s %d %d %s %s %d %d %d %d",
		&c.id, c.nom,c.adresse,c.ville,&c.tel,
                c.email,&c.nb_salle,&c.capacite_max,c.service_diso,c.etat,
                &c.date_debutS,&c.date_debutW,&c.date_finS,&c.date_finW) != EOF) {
        if (c.id == id) {
            fprintf(aux, "%d %s %s %s %d %s %d %d %s %s %d %d %d %d\n",
                c.id,new.nom,new.adresse,new.ville,new.tel,
                new.email,new.nb_salle,new.capacite_max,new.service_diso,new.etat,
                new.date_debutS,new.date_debutW,new.date_finS,new.date_finW);
            trouve = 1;
        } else {
            fprintf(aux, "%d %s %s %s %d %s %d %d %s %s %d %d %d %d\n",
                    c.id, c.nom, c.adresse, c.ville, c.tel,
                c.email, c.nb_salle, c.capacite_max, c.service_diso,c.etat,
                c.date_debutS,c.date_debutW, c.date_finS,c.date_finW);
        }
    }
    if (!trouve) {
   	printf("Erreur : Aucun centre trouvé avec l'ID %d.\n", id);
    }


    fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);
    return trouve;
}
int supprimer_centre(char *filename, int id) {
    centre c;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if (f == NULL || aux == NULL)
        return 0;

    while (fscanf(f, "%d %s %s %s %d %s %d %d %s %s %d %d %d %d",
                  &c.id, c.nom,c.adresse,c.ville,&c.tel,
                c.email,&c.nb_salle,&c.capacite_max,c.service_diso,c.etat,
                &c.date_debutS,&c.date_debutW,&c.date_finS,&c.date_finW) != EOF) {
        if (c.id != id) {
            fprintf(aux, "%d %s %s %s %d %s %d %d %s %s %d %d %d %d\n",
                    c.id, c.nom, c.adresse, c.ville, c.tel,
                c.email, c.nb_salle, c.capacite_max, c.service_diso,c.etat,
                c.date_debutS,c.date_debutW, c.date_finS,c.date_finW);
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
centre chercher_centre(char *filename, int id) {
    centre c;
    centre vide = {0};
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return vide;

    while (fscanf(f, "%d %s %s %s %d %s %d %d %s %s %d %d %d %d",
                  &c.id, c.nom,c.adresse,c.ville,&c.tel,
                c.email,&c.nb_salle,&c.capacite_max,c.service_diso,c.etat,
                &c.date_debutS,&c.date_debutW,&c.date_finS,&c.date_finW) != EOF) {
        if (c.id == id) {
            fclose(f);
            return c;
        }
    }

    fclose(f);
    return vide;
}

void afficher_centre(char *filename) {
    centre c;
    FILE *f = fopen(filename, "r");
    
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier!\n");
        return ;
    }
    
    while (fscanf(f, "%d %s %s %s %d %s %d %d %s %s %d %d %d %d",
                  &c.id, c.nom,c.adresse,c.ville,&c.tel,
                c.email,&c.nb_salle,&c.capacite_max,c.service_diso,c.etat,
                &c.date_debutS,&c.date_debutW,&c.date_finS,&c.date_finW) != EOF) {
	printf("ID du Centre: %d\n", c.id);
	printf("Nom: %s\n", c.nom);
	printf("Adresse: %s\n", c.adresse);
	printf("Ville: %s\n", c.ville);
	printf("Téléphone: %d\n", c.tel);
	printf("Email: %s\n", c.email);
	printf("Nombre de salles: %d\n", c.nb_salle);
	printf("Capacité maximale: %d\n", c.capacite_max);
	printf("Service disponible: %s\n", c.service_diso);
	printf("État: %s\n", c.etat);
	printf("Date de début du service de la semaine (S): %d\n", c.date_debutS);
	printf("Date de début du service de weekend(W): %d\n", c.date_debutW);
	printf("Date de fin du service de la semaine(S): %d\n", c.date_finS);
	printf("Date de fin du service du weekend(W): %d\n", c.date_finW);
    }
 
    fclose(f);
}

