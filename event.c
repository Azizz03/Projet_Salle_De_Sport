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
        fprintf(f, "%d %s %s %d %d %d %d %d %d %d %.2f %s\n",
                e.id, e.nom, e.type, e.jour, e.mois, e.annee,
                e.heure_debut_h, e.heure_debut_m, e.heure_fin_h, e.heure_fin_m,
                e.prix, e.salle);
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
        while (fscanf(f, "%d %s %s %d %d %d %d %d %d %d %f %s\n",
                      &e.id, e.nom, e.type, &e.jour, &e.mois, &e.annee,
                      &e.heure_debut_h, &e.heure_debut_m, &e.heure_fin_h, &e.heure_fin_m,
                      &e.prix, e.salle) != EOF)
        {
            if (e.id == id)
            {
                fprintf(f2, "%d %s %s %d %d %d %d %d %d %d %.2f %s\n",
                        nouv.id, nouv.nom, nouv.type, nouv.jour, nouv.mois, nouv.annee,
                        nouv.heure_debut_h, nouv.heure_debut_m, nouv.heure_fin_h, nouv.heure_fin_m,
                        nouv.prix, nouv.salle);
                tr = 1;
            }
            else
            {
                fprintf(f2, "%d %s %s %d %d %d %d %d %d %d %.2f %s\n",
                        e.id, e.nom, e.type, e.jour, e.mois, e.annee,
                        e.heure_debut_h, e.heure_debut_m, e.heure_fin_h, e.heure_fin_m,
                        e.prix, e.salle);
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
        while (fscanf(f, "%d %s %s %d %d %d %d %d %d %d %f %s\n",
                      &e.id, e.nom, e.type, &e.jour, &e.mois, &e.annee,
                      &e.heure_debut_h, &e.heure_debut_m, &e.heure_fin_h, &e.heure_fin_m,
                      &e.prix, e.salle) != EOF)
        {
            if (e.id == id)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %d %d %d %d %d %d %d %.2f %s\n",
                        e.id, e.nom, e.type, e.jour, e.mois, e.annee,
                        e.heure_debut_h, e.heure_debut_m, e.heure_fin_h, e.heure_fin_m,
                        e.prix, e.salle);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

event chercher_event(char *filename, int id)
{
    event e;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL)
    {
        while (fscanf(f, "%d %s %s %d %d %d %d %d %d %d %f %s\n",
                      &e.id, e.nom, e.type, &e.jour, &e.mois, &e.annee,
                      &e.heure_debut_h, &e.heure_debut_m, &e.heure_fin_h, &e.heure_fin_m,
                      &e.prix, e.salle) != EOF)
        {
            if (e.id == id)
            {
                tr = 1;
                break;
            }
        }
        fclose(f);
    }
    if (!tr)
        e.id = -1;
    return e;
}

/////////////////////////////
// GESTION DES PARTICIPATIONS
/////////////////////////////

int ajouter_participation(char *filename, participation p)
{
    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%d %s %s %s %d %s %s %d %d %d %d %.2f %s\n",
                p.id_membre, p.nom, p.prenom, p.sexe,
                p.id_event, p.nom_event, p.type_event,
                p.jour, p.mois, p.annee, p.heure, p.prix, p.salle);
        fclose(f);
        return 1;
    }
    return 0;
}

int supprimer_participation(char *filename, int id_membre, int id_event)
{
    int tr = 0;
    participation p;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %s %d %s %s %d %d %d %d %f %s\n",
                      &p.id_membre, p.nom, p.prenom, p.sexe,
                      &p.id_event, p.nom_event, p.type_event,
                      &p.jour, &p.mois, &p.annee, &p.heure, &p.prix, p.salle) != EOF)
        {
            if (p.id_membre == id_membre && p.id_event == id_event)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %s %d %s %s %d %d %d %d %.2f %s\n",
                        p.id_membre, p.nom, p.prenom, p.sexe,
                        p.id_event, p.nom_event, p.type_event,
                        p.jour, p.mois, p.annee, p.heure, p.prix, p.salle);
        }
    }

    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

participation chercher_participation(char *filename, int id_membre, int id_event)
{
    participation p;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL)
    {
        while (fscanf(f, "%d %s %s %s %d %s %s %d %d %d %d %f %s\n",
                      &p.id_membre, p.nom, p.prenom, p.sexe,
                      &p.id_event, p.nom_event, p.type_event,
                      &p.jour, &p.mois, &p.annee, &p.heure, &p.prix, p.salle) != EOF)
        {
            if (p.id_membre == id_membre && p.id_event == id_event)
            {
                tr = 1;
                break;
            }
        }
        fclose(f);
    }
    if (!tr)
        p.id_membre = -1;
    return p;
}
