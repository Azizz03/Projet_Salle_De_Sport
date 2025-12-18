#include <string.h>
#include <stdlib.h>
#include "ajout_cour.h"
#include<gtk/gtk.h>

#include <stdio.h>
StatCentre tab[10];
int nb_centres = 0;
void vider_cours(GtkWidget *treeview)
{
    GtkListStore *store;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    gtk_list_store_clear(store);
}

int ajouter_cour(const char *filename, cour c)
{
    FILE *f = fopen(filename, "a");
    if(f != NULL)
    {
        fprintf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d\n",
                c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
                c.intensite, c.restrictions_medicales, c.objectif,
                c.capacite, c.type_equipement, c.salle, c.centre,
                c.duree, c.jour, c.mois, c.annee);
        fclose(f);
        return 1;
    }
    return 0;
}

int supprimer_cour(const char *filename, int id)
{
    cour c;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if(f == NULL || aux == NULL)
        return 0;

    while(fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
                 &c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
                 c.intensite, c.restrictions_medicales, c.objectif,
                 &c.capacite, c.type_equipement, c.salle, c.centre,
                 c.duree, &c.jour, &c.mois, &c.annee) != EOF)
    {
        if(c.id != id)
        {
            fprintf(aux, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d\n",
                    c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
                    c.intensite, c.restrictions_medicales, c.objectif,
                    c.capacite, c.type_equipement, c.salle, c.centre,
                    c.duree, c.jour, c.mois, c.annee);
        }
        else
            trouve = 1;
    }

    fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);

    return trouve;
}

int modifier_cour(const char *filename, int id, cour nouv)
{
    cour c;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if(f == NULL || aux == NULL)
        return 0;

    while(fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
                 &c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
                 c.intensite, c.restrictions_medicales, c.objectif,
                 &c.capacite, c.type_equipement, c.salle, c.centre,
                 c.duree, &c.jour, &c.mois, &c.annee) != EOF)
    {
        if(c.id == id)
        {
            fprintf(aux,"%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d\n",
                    nouv.id, nouv.nom_c, nouv.type_c, nouv.coach,
                    nouv.public_cible, nouv.intensite,
                    nouv.restrictions_medicales, nouv.objectif,
                    nouv.capacite, nouv.type_equipement,
                    nouv.salle, nouv.centre, nouv.duree,
                    nouv.jour, nouv.mois, nouv.annee);
            trouve = 1;
        }
        else
        {
            fprintf(aux,"%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d\n",
                    c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
                    c.intensite, c.restrictions_medicales, c.objectif,
                    c.capacite, c.type_equipement, c.salle, c.centre,
                    c.duree, c.jour, c.mois, c.annee);
        }
    }

    fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);

    return trouve;
}

cour chercher_cour(const char *filename, int id)
{
    cour c;
    cour vide;
    vide.id = -1;

    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return vide;

    while(fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
                 &c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
                 c.intensite, c.restrictions_medicales, c.objectif,
                 &c.capacite, c.type_equipement, c.salle, c.centre,
                 c.duree, &c.jour, &c.mois, &c.annee) != EOF)
    {
        if(c.id == id)
        {
            fclose(f);
            return c;
        }
    }
    fclose(f);
    return vide;
}

void afficher_cours_fichier(char *filename)
{
    cour c;
    FILE *f = fopen(filename, "r");

    if(f == NULL)
    {
        printf("Erreur fichier !\n");
        return;
    }

    printf("\n===== LISTE DES COURS =====\n");

    while(fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
                 &c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
                 c.intensite, c.restrictions_medicales, c.objectif,
                 &c.capacite, c.type_equipement, c.salle, c.centre,
                 c.duree, &c.jour, &c.mois, &c.annee) != EOF)
    {
        printf("ID: %d | Nom: %s | Type: %s | Coach: %s | Intensité: %s\n",
               c.id, c.nom_c, c.type_c, c.coach, c.intensite);
    }

    fclose(f);
}

 int sinscrire(char *filename, reservation r,
              char *salle_out,
              char *intensite_out,
              char *public_out,
              char *objectif_out,
              char *duree_out)
{
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    cour c;
    int inscrit = 0;

    if (!f || !temp)
        return 0;

    while (fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
                  &c.id,
                  c.nom_c,
                  c.type_c,
                  c.coach,
                  c.public_cible,
                  c.intensite,
                  c.restrictions_medicales,
                  c.objectif,
                  &c.capacite,
                  c.type_equipement,
                  c.salle,
                  c.centre,
                  c.duree,
                  &c.jour, &c.mois, &c.annee) != EOF)
    {
        int sexe_ok = 0;

        /* Contrôle sexe */
        if (r.sexe == 1)
        {
            if (!strcmp(c.public_cible, "homme_adulte") ||
                !strcmp(c.public_cible, "adulte_mixte") ||
                !strcmp(c.public_cible, "enfants_garcons") ||
                !strcmp(c.public_cible, "enfants_mixte"))
                sexe_ok = 1;
        }
        else if (r.sexe == 2)
        {
            if (!strcmp(c.public_cible, "femme_adulte") ||
                !strcmp(c.public_cible, "adulte_mixte") ||
                !strcmp(c.public_cible, "enfants_filles") ||
                !strcmp(c.public_cible, "enfants_mixte"))
                sexe_ok = 1;
        }

        if (!inscrit &&
            sexe_ok &&
            strcmp(c.type_c, r.type) == 0 &&
            strcmp(c.centre, r.centre) == 0 &&
            c.jour == r.jour &&
            c.mois == r.mois &&
            c.annee == r.annee &&
            c.capacite > 0)
        {
            c.capacite--;

            strcpy(salle_out, c.salle);
            strcpy(intensite_out, c.intensite);
            strcpy(public_out, c.public_cible);
            strcpy(objectif_out, c.objectif);
            strcpy(duree_out, c.duree);

            inscrit = 1;
        }

        fprintf(temp, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d\n",
                c.id,
                c.nom_c,
                c.type_c,
                c.coach,
                c.public_cible,
                c.intensite,
                c.restrictions_medicales,
                c.objectif,
                c.capacite,
                c.type_equipement,
                c.salle,
                c.centre,
                c.duree,
                c.jour, c.mois, c.annee);
    }

    fclose(f);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    return inscrit;

}


void afficher_cour(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    // Variables séparées (pas de struct)
    int id;
    char nom_c[50];
    char type_c[30];
    char coach[30];
    char public_cible[30];
    char intensite[30];
    char restrictions_medicales[100];
    char objectif[30];
    int capacite;
    char type_equipement[30];
    char salle[20];
    char centre[20];
    char duree[20];
    int jour, mois, annee;

    FILE *f;

    if (liste == NULL)
        return;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL)
    {
        // 1
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COL_ID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 2
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", COL_NOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 3
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", COL_TYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 4
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Coach", renderer, "text", COL_COACH, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 5
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Public", renderer, "text", COL_PUBLIC, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 6
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Intensité", renderer, "text", COL_INTENSITE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 7
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Restriction", renderer, "text", COL_RESTRICTION, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 8
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Objectif", renderer, "text", COL_OBJECTIF, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 9
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", COL_CAPACITE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 10
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Équipement", renderer, "text", COL_EQUIPEMENT, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 11
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Salle", renderer, "text", COL_SALLE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 12
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Centre", renderer, "text", COL_CENTRE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 13
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Durée", renderer, "text", COL_DUREE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 14
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", COL_JOUR, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 15
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", COL_MOIS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 16
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Année", renderer, "text", COL_ANNEE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    // Création du store
    store = gtk_list_store_new(
        COLUMNS,
        G_TYPE_INT,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_INT,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_STRING,
        G_TYPE_INT,
        G_TYPE_INT,
        G_TYPE_INT);

    f = fopen("cour.txt", "r");
    if (!f)
        return;

    while (fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
                  &id, nom_c, type_c, coach, public_cible,
                  intensite, restrictions_medicales, objectif,
                  &capacite, type_equipement, salle, centre,
                  duree, &jour, &mois, &annee) != EOF)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_ID, id,
                           COL_NOM, nom_c,
                           COL_TYPE, type_c,
                           COL_COACH, coach,
                           COL_PUBLIC, public_cible,
                           COL_INTENSITE, intensite,
                           COL_RESTRICTION, restrictions_medicales,
                           COL_OBJECTIF, objectif,
                           COL_CAPACITE, capacite,
                           COL_EQUIPEMENT, type_equipement,
                           COL_SALLE, salle,
                           COL_CENTRE, centre,
                           COL_DUREE, duree,
                           COL_JOUR, jour,
                           COL_MOIS, mois,
                           COL_ANNEE, annee,
                           -1);
    }

    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

int rechercher_cour(char *filename, reservation r, cour *resultat)
{

    FILE *f = fopen(filename, "r");
    cour c;

    if (!f) return 0;

    while (fscanf(f,
        "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
        &c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
        c.intensite, c.restrictions_medicales, c.objectif,
        &c.capacite, c.type_equipement, c.salle, c.centre,
        c.duree, &c.jour, &c.mois, &c.annee) != EOF)
    {
        int sexe_ok = 0;

        /* contrôle sexe */
        if (r.sexe == 1 &&
           (!strcmp(c.public_cible,"homme_adulte") ||
            !strcmp(c.public_cible,"adulte_mixte") ||
            !strcmp(c.public_cible,"enfants_garcons") ||
            !strcmp(c.public_cible,"enfants_mixte")))
            sexe_ok = 1;

        if (r.sexe == 2 &&
           (!strcmp(c.public_cible,"femme_adulte") ||
            !strcmp(c.public_cible,"adulte_mixte") ||
            !strcmp(c.public_cible,"enfants_filles") ||
            !strcmp(c.public_cible,"enfants_mixte")))
            sexe_ok = 1;

        if ( sexe_ok &&
             c.capacite > 0 &&
             !strcmp(c.type_c, r.type) &&
             !strcmp(c.centre, r.centre) &&
             c.jour == r.jour &&
             c.mois == r.mois &&
             c.annee == r.annee )
        {
            *resultat = c;
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;


}



/*int confirmer_reservation(char *filename, int id_cour)
{
    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    cour c;

    if (!f || !temp)
        return 0;

    while (fscanf(f,
        "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
        &c.id,
        c.nom_c,
        c.type_c,
        c.coach,
        c.public_cible,
        c.intensite,
        c.restrictions_medicales,
        c.objectif,
        &c.capacite,
        c.type_equipement,
        c.salle,
        c.centre,
        c.duree,
        &c.jour, &c.mois, &c.annee) != EOF)
    {
        if (c.id == id_cour && c.capacite > 0)
            c.capacite--;

        fprintf(temp,
            "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d\n",
            c.id,
            c.nom_c,
            c.type_c,
            c.coach,
            c.public_cible,
            c.intensite,
            c.restrictions_medicales,
            c.objectif,
            c.capacite,
            c.type_equipement,
            c.salle,
            c.centre,
            c.duree,
            c.jour, c.mois, c.annee);
    }

    fclose(f);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    return 1;


}*/ 





int sexe_compatible(int sexe, char *public)
{
    if (sexe == 1) // homme
        return (strcmp(public,"homme_adulte")==0 ||
                strcmp(public,"adulte_mixte")==0 ||
                strcmp(public,"enfants_garcons")==0 ||
                strcmp(public,"enfants_mixte")==0);

    if (sexe == 2) // femme
        return (strcmp(public,"femme_adulte")==0 ||
                strcmp(public,"adulte_mixte")==0 ||
                strcmp(public,"enfants_filles")==0 ||
                strcmp(public,"enfants_mixte")==0);

    return 0;
}

int confirmer_reservation(char *filename, int id_cour)
{

    FILE *f = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    cour c;
    int ok = 0;

    if (!f || !temp) return 0;

    while (fscanf(f,
        "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
        &c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
        c.intensite, c.restrictions_medicales, c.objectif,
        &c.capacite, c.type_equipement, c.salle, c.centre,
        c.duree, &c.jour, &c.mois, &c.annee) != EOF)
    {
        if (c.id == id_cour && c.capacite > 0)
        {
            c.capacite--;
            ok = 1;
        }

        fprintf(temp,
            "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d\n",
            c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
            c.intensite, c.restrictions_medicales, c.objectif,
            c.capacite, c.type_equipement, c.salle, c.centre,
            c.duree, c.jour, c.mois, c.annee);
    }

    fclose(f);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);

    return ok;

}

void calculer_stats_sexe(const char *filename, int *nb_hommes, int *nb_femmes)
{
    FILE *f = fopen(filename, "r");
    cour c;

    *nb_hommes = 0;
    *nb_femmes = 0;

    if (!f) return;

    while (fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
        &c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
        c.intensite, c.restrictions_medicales, c.objectif,
        &c.capacite, c.type_equipement, c.salle, c.centre,
        c.duree, &c.jour, &c.mois, &c.annee) != EOF)
    {
        /* hommes */
        if (!strcmp(c.public_cible,"homme_adulte") ||
            !strcmp(c.public_cible,"adulte_mixte") ||
            !strcmp(c.public_cible,"enfants_garcons") ||
            !strcmp(c.public_cible,"enfants_mixte"))
            (*nb_hommes)++;

        /* femmes */
        if (!strcmp(c.public_cible,"femme_adulte") ||
            !strcmp(c.public_cible,"adulte_mixte") ||
            !strcmp(c.public_cible,"enfants_filles") ||
            !strcmp(c.public_cible,"enfants_mixte"))
            (*nb_femmes)++;
    }

    fclose(f);
}

void calculer_stats_centres(const char *filename)
{
    FILE *f = fopen(filename, "r");
    cour c;
    int i, found;

    nb_centres = 0;

    if (!f) return;

    while (fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
                  &c.id, c.nom_c, c.type_c, c.coach,
                  c.public_cible, c.intensite,
                  c.restrictions_medicales, c.objectif,
                  &c.capacite, c.type_equipement,
                  c.salle, c.centre, c.duree,
                  &c.jour, &c.mois, &c.annee) != EOF)
    {
        found = 0;
        for (i = 0; i < nb_centres; i++)
        {
            if (strcmp(tab[i].centre, c.centre) == 0)
            {
                tab[i].nb++;
                found = 1;
                break;
            }
        }

        if (!found && nb_centres < 10)
        {
            strcpy(tab[nb_centres].centre, c.centre);
            tab[nb_centres].nb = 1;
            nb_centres++;
        }
    }

    fclose(f);
}


int rechercher_cours_compatibles(char *filename,
                                 reservation r,
                                 cour tab[])
{
    FILE *f;
    cour c;
    int n = 0;
    int sexe_ok;

    f = fopen(filename, "r");
    if (!f) return 0;

    while (fscanf(f,
        "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
        &c.id,
        c.nom_c,
        c.type_c,
        c.coach,
        c.public_cible,
        c.intensite,
        c.restrictions_medicales,
        c.objectif,
        &c.capacite,
        c.type_equipement,
        c.salle,
        c.centre,
        c.duree,
        &c.jour,
        &c.mois,
        &c.annee) != EOF)
    {
        sexe_ok = 0;

        /* === contrôle sexe === */
        if (r.sexe == 1) /* homme */
        {
            if (!strcmp(c.public_cible,"homme_adulte") ||
                !strcmp(c.public_cible,"adulte_mixte") ||
                !strcmp(c.public_cible,"enfants_garcons") ||
                !strcmp(c.public_cible,"enfants_mixte"))
                sexe_ok = 1;
        }
        else if (r.sexe == 2) /* femme */
        {
            if (!strcmp(c.public_cible,"femme_adulte") ||
                !strcmp(c.public_cible,"adulte_mixte") ||
                !strcmp(c.public_cible,"enfants_filles") ||
                !strcmp(c.public_cible,"enfants_mixte"))
                sexe_ok = 1;
        }

        if (sexe_ok &&
            strcmp(c.type_c, r.type) == 0 &&
            strcmp(c.centre, r.centre) == 0 &&
            c.jour == r.jour &&
            c.mois == r.mois &&
            c.annee == r.annee &&
            c.capacite > 0)
        {
            tab[n++] = c;   /* sauvegarde */
        }
    }

    fclose(f);
    return n;
}

int id_cour_existe(const char *filename, int id_recherche)
{
    FILE *f;
    int id;
    char nom_c[50], type_c[30], coach[30], public_cible[30];
    char intensite[30], restrictions_medicales[100], objectif[30];
    int capacite;
    char type_equipement[30], salle[20], centre[20], duree[20];
    int jour, mois, annee;

    f = fopen(filename, "r");
    if (f == NULL)
        return 0;

    while (fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
                  &id, nom_c, type_c, coach, public_cible,
                  intensite, restrictions_medicales, objectif,
                  &capacite, type_equipement, salle, centre,
                  duree, &jour, &mois, &annee) != EOF)
    {
        if (id == id_recherche)
        {
            fclose(f);
            return 1; 
        }
    }

    fclose(f);
    return 0; 
}


