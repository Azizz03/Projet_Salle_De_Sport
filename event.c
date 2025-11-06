#include "event.h"
#include <stdio.h>
#include <string.h>

//////////////////////
// GESTION ÉVÉNEMENTS
//////////////////////

int ajouter_event(char *filename, event e)
{
    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%d %s %s %d %d %d %d %d %d %d %.2f %s %d\n",
                e.id, e.nom, e.type, e.jour, e.mois, e.annee,
                e.heure_debut_h, e.heure_debut_m, e.heure_fin_h, e.heure_fin_m,
                e.prix, e.salle, e.capacite);
        fclose(f);
        return 1;
    }
    return 0;
}

int modifier_event(char *filename, int id, event nouv)
{
    int tr = 0;
    event e;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %d %d %d %d %d %d %d %f %s %d\n",
                      &e.id, e.nom, e.type, &e.jour, &e.mois, &e.annee,
                      &e.heure_debut_h, &e.heure_debut_m, &e.heure_fin_h, &e.heure_fin_m,
                      &e.prix, e.salle, &e.capacite) != EOF)
        {
            if (e.id == id)
            {
                fprintf(f2, "%d %s %s %d %d %d %d %d %d %d %.2f %s %d\n",
                        nouv.id, nouv.nom, nouv.type, nouv.jour, nouv.mois, nouv.annee,
                        nouv.heure_debut_h, nouv.heure_debut_m, nouv.heure_fin_h, nouv.heure_fin_m,
                        nouv.prix, nouv.salle, nouv.capacite);
                tr = 1;
            }
            else
            {
                fprintf(f2, "%d %s %s %d %d %d %d %d %d %d %.2f %s %d\n",
                        e.id, e.nom, e.type, e.jour, e.mois, e.annee,
                        e.heure_debut_h, e.heure_debut_m, e.heure_fin_h, e.heure_fin_m,
                        e.prix, e.salle, e.capacite);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

int supprimer_event(char *filename, int id)
{
    int tr = 0;
    event e;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %d %d %d %d %d %d %d %f %s %d\n",
                      &e.id, e.nom, e.type, &e.jour, &e.mois, &e.annee,
                      &e.heure_debut_h, &e.heure_debut_m, &e.heure_fin_h, &e.heure_fin_m,
                      &e.prix, e.salle, &e.capacite) != EOF)
        {
            if (e.id == id){
                tr = 1;
            else
                fprintf(f2, "%d %s %s %d %d %d %d %d %d %d %.2f %s %d\n ",
                        e.id, e.nom, e.type, e.jour, e.mois, e.annee,
                        e.heure_debut_h, e.heure_debut_m, e.heure_fin_h, e.heure_fin_m,
                        e.prix, e.salle, e.capacite);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}
}
event chercher_event(char *filename, int id)
{
    event e;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL)
    {
        while (fscanf(f, "%d %s %s %d %d %d %d %d %d %d %f %s %d\n",
                      &e.id, e.nom, e.type, &e.jour, &e.mois, &e.annee,
                      &e.heure_debut_h, &e.heure_debut_m, &e.heure_fin_h, &e.heure_fin_m,
                      &e.prix, e.salle, &e.capacite) != EOF)
        {
            if (e.id == id)
            {
                tr = 1;
                break;
            }
        }
        fclose(f);
    }
    if (!tr){
        e.id = -1;
    return e;}
}
int afficher_event(char *filename)
{
    FILE *f = fopen(filename, "r");
    event e;
    int trouve = 0;

    if (f == NULL)
    {
        printf(" Erreur : impossible d’ouvrir le fichier %s pour lecture.\n", filename);
        return 0;
    }

    printf(" Liste des événements enregistrés :\n");
    printf("------------------------------------------------------------\n");

    while (fscanf(f, "%d %s %s %d %d %d %d %d %d %d %f %s %d",
                  &e.id, e.nom, e.type,s
                  &e.jour, &e.mois, &e.annee,
                  &e.heure_debut_h, &e.heure_debut_m,
                  &e.heure_fin_h, &e.heure_fin_m,
                  &e.prix, e.salle, &e.capacite) != EOF)
    {
        trouve = 1;
        printf("ID : %d\n", e.id);
        printf("Nom : %s\n", e.nom);
        printf("Type : %s\n", e.type);
        printf("Date : %02d/%02d/%04d\n", e.jour, e.mois, e.annee);
        printf("Heure : %02d:%02d - %02d:%02d\n",
               e.heure_debut_h, e.heure_debut_m,
               e.heure_fin_h, e.heure_fin_m);
        printf("Salle : %s\n", e.salle);
        printf("Prix : %.2f DT\n", e.prix);
        printf("Capacité : %d places\n", e.capacite);
        printf("------------------------------------------------------------\n");
    }

    fclose(f);

    if (!trouve)
    {
        printf("  Aucun événement trouvé dans le fichier %s.\n", filename);
        return 0;
    }

    return 1;
}

/////////////////////////////
// GESTION DES PARTICIPATIONS
/////////////////////////////

int ajouter_participation(char *filename, participation p)
{
    static int CAPACITE_MAX = 50;

    if (CAPACITE_MAX <= 0)
    {
        printf("  L'événement est complet. Impossible d'ajouter la participation.\n");
        return 0;
    }

    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%d %s %s %s %d %s %s %d %d %d %d %.2f %s %d \n ,
                p.id, p.nom, p.prenom, p.sexe,
                e.id, e.nom, e.type,
                p.jour, p.mois, p.annee, p.heure, p.prix, p.salle, p.capacite);

        fclose(f);

        CAPACITE_MAX--; // une place en moins après ajout réussi
        printf(" Participation ajoutée. Places restantes : %d\n", CAPACITE_MAX);

        return 1;
    }

    printf(" Erreur lors de l’ouverture du fichier.\n");
    return 0;
}


/*int supprimer_participation(char *filename, int id_membre, int id_event)
{
    int tr = 0;
    participation p;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %s %d %s %s %d %d %d %d %f %s %d\n",
                      &p.id, p.nom, p.prenom, p.sexe,
                      &p.id, p.nom, p.type,
                      &p.jour, &p.mois, &p.annee, &p.heure, &p.prix, p.salle , p.capacite) != EOF)
        {
            if (p.id == id && p.id == id)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %s %d %s %s %d %d %d %d %.2f %s %d\n",
                        p.id, p.nom, p.prenom, p.sexe,
                        p.id, p.nom, p.type,
                        p.jour, p.mois, p.annee, p.heure, p.prix, p.salle, p.capacite);
        }
    }

    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
*/}

/*participation chercher_participation(char *filename, int id_membre, int id_event)
{
    participation p;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL)
    {
        while (fscanf(f, "%d %s %s %s %d %s %s %d %d %d %d %f %s\n %d",
                      &p.id, p.nom, p.prenom, p.sexe,
                      &p.id, p.nom, p.type,
                      &p.jour, &p.mois, &p.annee, &p.heure, &p.prix, p.salle, p.capacite) != EOF)
        {
            if (p.id == id_membre && p.id == id)
            {
                tr = 1;
                break;
            }
        }
        fclose(f);
   */ }
    if (!tr)
        p.id_membre = -1;
    return p;
}


