#include "ajout_cour.h"
#include "entraineur.h"
#include "membre.h"
#include <string.h>

int ajouter(char *filename, cour c)
{
    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%d %s %s %s %s %s %s %s %s %d %s\n",
                c.id, c.nom_c, c.type_c, c.jour_c, c.coach,
                c.public_cible, c.intensite, c.restrictions_medicales,
                c.objectif, c.capacite, c.type_equipement);
        fclose(f);
        return 1;
    }
    return 0;
}

int modifier(char *filename, int id, cour nouv)
{
    int tr = 0;
    cour c;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %s %s %s %s %s %s %d %s\n",
                      &c.id, c.nom_c, c.type_c, c.jour_c, c.coach,
                      c.public_cible, c.intensite, c.restrictions_medicales,
                      c.objectif, &c.capacite, c.type_equipement) != EOF)
        {
            if (c.id == id)
            {
                fprintf(f2, "%d %s %s %s %s %s %s %s %s %d %s\n",
                        nouv.id, nouv.nom_c, nouv.type_c, nouv.jour_c, nouv.coach,
                        nouv.public_cible, nouv.intensite, nouv.restrictions_medicales,
                        nouv.objectif, nouv.capacite, nouv.type_equipement);
                tr = 1;
            }
            else
                fprintf(f2, "%d %s %s %s %s %s %s %s %s %d %s\n",
                        c.id, c.nom_c, c.type_c, c.jour_c, c.coach,
                        c.public_cible, c.intensite, c.restrictions_medicales,
                        c.objectif, c.capacite, c.type_equipement);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("temp.txt", filename);
    return tr;
}

int supprimer(char *filename, int id)
{
    int tr = 0;
    cour c;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("temp.txt", "w");
    if (f != NULL && f2 != NULL)
    {
        while (fscanf(f, "%d %s %s %s %s %s %s %s %s %d %s\n",
                      &c.id, c.nom_c, c.type_c, c.jour_c, c.coach,
                      c.public_cible, c.intensite, c.restrictions_medicales,
                      c.objectif, &c.capacite, c.type_equipement) != EOF)
        {
            if (c.id == id)
                tr = 1;
            else
                fprintf(f2, "%d %s %s %s %s %s %s %s %s %d %s\n",
                        c.id, c.nom_c, c.type_c, c.jour_c, c.coach,
                        c.public_cible, c.intensite, c.restrictions_medicales,
                        c.objectif, c.capacite, c.type_equipement);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("temp.txt", filename);
    return tr;
}

cour chercher(char *filename, int id)
{
    cour c;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL)
    {
        while (fscanf(f, "%d %s %s %s %s %s %s %s %s %d %s\n",
                      &c.id, c.nom_c, c.type_c, c.jour_c, c.coach,
                      c.public_cible, c.intensite, c.restrictions_medicales,
                      c.objectif, &c.capacite, c.type_equipement) != EOF)
        {
            if (c.id == id)
            {
                tr = 1;
                break;
            }
        }
        fclose(f);
    }
    if (tr == 0)
        c.id = -1;
    return c;
}

int sinscrire(char *filename, int id_cour, char id_membre[])
{
    FILE *f = fopen("inscriptions.txt", "a");
    if (f != NULL)
    {
        fprintf(f, "%d %s\n", id_cour, id_membre);
        fclose(f);
        return 1;
    }
    return 0;
}

int reserver(char *filename, int id_cour, char id_coach[])
{
    FILE *f = fopen("reservations.txt", "a");
    if (f != NULL)
    {
        fprintf(f, "%d %s\n", id_cour, id_coach);
        fclose(f);
        return 1;
    }
    return 0;
}
