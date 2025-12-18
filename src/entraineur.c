#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "entraineur.h"
int coach_connecte_id = -1;
const char filename[] = "entraineur.txt";
const char FILENAME_RES[] = "reservation.txt";


int valider_entraineur(entraineur e) {
    if (e.id <= 0) return 0;
    if (strlen(e.nom) == 0 || strlen(e.prenom) == 0) return 0;
    if (e.salaire <= 0) return 0;
    if (strcmp(e.sexe, "Homme") != 0 && strcmp(e.sexe, "Femme") != 0) return 0;
    if (e.date_inscription.jour < 1 || e.date_inscription.jour > 31) return 0;
    if (e.date_inscription.mois < 1 || e.date_inscription.mois > 12) return 0;
    if (e.date_inscription.annee < 2000 || e.date_inscription.annee > 2100) return 0;
    if (strchr(e.email, '@') == NULL) return 0;
    if (strlen(e.num_tel) < 8) return 0;
    return 1;
}

const char* valider_entraineur_msg(entraineur e)
{
    if (e.id <= 0) 
        return "ID invalide (doit être > 0).";

    if (strlen(e.nom) == 0) 
        return "Le nom est obligatoire.";

    if (strlen(e.prenom) == 0) 
        return "Le prénom est obligatoire.";

    if (e.salaire <= 0) 
        return "Le salaire doit être supérieur à 0.";

    if (strcmp(e.sexe, "Homme") != 0 && strcmp(e.sexe, "Femme") != 0)
        return "Sexe invalide (Homme ou Femme).";

    if (e.date_inscription.jour < 1 || e.date_inscription.jour > 31)
        return "Jour de date d’inscription incorrect.";

    if (e.date_inscription.mois < 1 || e.date_inscription.mois > 12)
        return "Mois de date d’inscription incorrect.";

    if (e.date_inscription.annee < 2000 || e.date_inscription.annee > 2100)
        return "Année de date d’inscription incorrecte.";

    if (strchr(e.email, '@') == NULL)
        return "Email invalide.";

    if (strlen(e.num_tel) < 8)
        return "Numéro de téléphone trop court.";

    return NULL; 
}

// ======================== ENTRAINEUR CRUD =============================

int ajouter(entraineur e) {
    FILE* f = fopen(filename, "a");
    if (!f) return 0;

    fprintf(f, "%d;%s;%s;%s;%.2f;%s;%d;%d;%d;%s;%s;%s;%s\n",
        e.id, e.nom, e.prenom, e.specialite, e.salaire, e.sexe,
        e.date_inscription.jour, e.date_inscription.mois, e.date_inscription.annee,
        e.email, e.num_tel, e.centre, e.ville_pref);

    fclose(f);
    return 1;
  }
  





int supprimer_entraineur(const char *filename, int id) {
    FILE *in = fopen(filename, "r");
    if (!in) return 0;

    FILE *out = fopen("aux.tmp", "w");
    if (!out) { fclose(in); return 0; }

    char line[1024];
    int trouve = 0;
    int processed_any = 0;

    while (fgets(line, sizeof line, in)) {
        
        size_t len = strlen(line);
        while (len && (line[len-1] == '\n' || line[len-1] == '\r')) line[--len] = '\0';

        entraineur e;
        int n = sscanf(line,
            "%d;%63[^;];%63[^;];%63[^;];%f;%15[^;];%d;%d;%d;%127[^;];%31[^;];%63[^;];%63[^;\n]",
            &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
            &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
            e.email, e.num_tel, e.centre, e.ville_pref);

        if (n == 13) {
            processed_any = 1;
            if (e.id == id) {
               
                trouve = 1;
            } else {
                
                fprintf(out, "%d;%s;%s;%s;%.2f;%s;%d;%d;%d;%s;%s;%s;%s\n",
                        e.id, e.nom, e.prenom, e.specialite, e.salaire, e.sexe,
                        e.date_inscription.jour, e.date_inscription.mois, e.date_inscription.annee,
                        e.email, e.num_tel, e.centre, e.ville_pref);
            }
        } else {
            
            fputs(line, out);
            fputc('\n', out);
        }
    }

    fclose(in);
    fclose(out);

    if (trouve) {
        
        if (rename("aux.tmp", filename) != 0) {
            
            remove("aux.tmp");
            return 0;
        }
        return 1;
    } else {
        
        remove("aux.tmp");
        return 0;
    }
}


int modifier(int id, entraineur nouv) {
    entraineur e;
    int tr = 0;

    FILE* f = fopen(filename, "r");
    FILE* f2 = fopen("nouv.txt", "w");

    if (!f || !f2) return 0;

    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%f;%[^;];%d;%d;%d;%[^;];%[^;];%[^;];%[^;\n]\n",
        &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
        &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
        e.email, e.num_tel, e.centre, e.ville_pref) != EOF) {

        if (e.id == id) {
            fprintf(f2, "%d;%s;%s;%s;%.2f;%s;%d;%d;%d;%s;%s;%s;%s\n",
                nouv.id, nouv.nom, nouv.prenom, nouv.specialite, nouv.salaire, nouv.sexe,
                nouv.date_inscription.jour, nouv.date_inscription.mois, nouv.date_inscription.annee,
                nouv.email, nouv.num_tel, nouv.centre, nouv.ville_pref);
            tr = 1;
        }
        else {
            fprintf(f2, "%d;%s;%s;%s;%.2f;%s;%d;%d;%d;%s;%s;%s;%s\n",
                e.id, e.nom, e.prenom, e.specialite, e.salaire, e.sexe,
                e.date_inscription.jour, e.date_inscription.mois, e.date_inscription.annee,
                e.email, e.num_tel, e.centre, e.ville_pref);
        }
    }

    fclose(f);
    fclose(f2);

    remove(filename);
    rename("nouv.txt", filename);

    return tr;
}

int supprimer(int id) {
    entraineur e;
    int tr = 0;

    FILE* f = fopen(filename, "r");
    FILE* f2 = fopen("nouv.txt", "w");

    if (!f || !f2) return 0;

    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%f;%[^;];%d;%d;%d;%[^;];%[^;];%[^;];%[^;\n]\n",
        &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
        &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
        e.email, e.num_tel, e.centre, e.ville_pref) != EOF) {

        if (e.id != id)
            fprintf(f2, "%d;%s;%s;%s;%.2f;%s;%d;%d;%d;%s;%s;%s;%s\n",
                e.id, e.nom, e.prenom, e.specialite, e.salaire, e.sexe,
                e.date_inscription.jour, e.date_inscription.mois, e.date_inscription.annee,
                e.email, e.num_tel, e.centre, e.ville_pref);
        else
            tr = 1;
    }

    fclose(f);
    fclose(f2);

    remove(filename);
    rename("nouv.txt", filename);

    return tr;
}



/*entraineur chercher(int id) {
    entraineur e;
    e.id = -1;

    FILE* f = fopen("entraineur.txt", "r");
    if (!f) return e;

    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%f;%[^;];%d;%d;%d;%[^;];%[^;];%[^;];%[^;\n]\n",
        &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
        &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
        e.email, e.num_tel, e.centre, e.ville_pref) != EOF) {
        if (e.id == id) break;
    }

    fclose(f);
    return e;
}*/


entraineur chercher(int id) {
    entraineur e;
    e.id = -1; // not found default

    FILE *f = fopen("entraineur.txt", "r");
    if (!f) {
        // optionally log perror("fopen");
        return e;
    }

    char line[512]; // ensure large enough for a full record
    while (fgets(line, sizeof(line), f)) {
        // Remove trailing newline (optional)
        size_t len = strlen(line);
        if (len && (line[len-1] == '\n' || line[len-1] == '\r')) {
            line[len-1] = '\0';
        }

        entraineur tmp; // parse into a temp
        // Use width limits to avoid overflow. Note: %63[^;] reads up to 63 chars + null
        int n = sscanf(line,
            "%d;%63[^;];%63[^;];%63[^;];%f;%15[^;];%d;%d;%d;%127[^;];%31[^;];%63[^;];%63[^;\n]",
            &tmp.id, tmp.nom, tmp.prenom, tmp.specialite, &tmp.salaire, tmp.sexe,
            &tmp.date_inscription.jour, &tmp.date_inscription.mois, &tmp.date_inscription.annee,
            tmp.email, tmp.num_tel, tmp.centre, tmp.ville_pref);

        // Expect 13 fields
        if (n == 13) {
            if (tmp.id == id) {
                e = tmp; // copy and stop
                break;
            }
        } else {
            // Malformed line; skip it. You can log or handle as needed.
            // fprintf(stderr, "Malformed record (got %d fields): %s\n", n, line);
        }
    }

    fclose(f);
    return e;
}


// ======================== RESERVATIONS =============================

int ajouter_reservation(reservation r) {
    FILE* f = fopen(FILENAME_RES, "a");
    if (!f) return 0;

    fprintf(f, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
        r.reservation_id, r.coach_id, r.cour_id, r.cours_privee,
        r.date.annee, r.date.mois, r.date.jour,
        r.heure.heure, r.heure.minutes,r.capacite);

    fclose(f);
    return 1;
}

int supprimer_reservation(int reservation_id) {
    reservation r;
    int tr = 0;

    FILE* f = fopen(FILENAME_RES, "r");
    FILE* f2 = fopen("temp_res.txt", "w");
    if (!f || !f2) return 0;

    while (fscanf(f, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
        &r.reservation_id, &r.coach_id, &r.cour_id, &r.cours_privee,
        &r.date.annee, &r.date.mois, &r.date.jour,
        &r.heure.heure, &r.heure.minutes,r.capacite) != EOF) {

        if (r.reservation_id != reservation_id)
            fprintf(f2, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
                r.reservation_id, r.coach_id, r.cour_id, r.cours_privee,
                r.date.annee, r.date.mois, r.date.jour,
                r.heure.heure, r.heure.minutes,r.capacite);
        else
            tr = 1;
    }

    fclose(f);
    fclose(f2);
    remove(FILENAME_RES);
    rename("temp_res.txt", FILENAME_RES);

    return tr;
}



reservation rechercher_reservation(int reservation_id) {
    reservation r;
    r.reservation_id = -1;

    FILE* f = fopen(FILENAME_RES, "r");
    if (!f) return r;

    while (fscanf(f, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
        &r.reservation_id, &r.coach_id, &r.cour_id, &r.cours_privee,
        &r.date.annee, &r.date.mois, &r.date.jour,
        &r.heure.heure, &r.heure.minutes,&r.capacite) != EOF) {
        if (r.reservation_id == reservation_id)
            break;
    }

    fclose(f);
    return r;
}




void vider(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    int id;
    char nom[30];
    char prenom[30];
    char specialite[30];
    float salaire;
    char sexe[10];                 
    date date_inscription;
    char email[50];
    char num_tel[20];
    char centre[30];
    char ville_pref[30];

    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));

    if (store == NULL)
    {
       
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

     
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", NOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

      
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", PRENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

     
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Spécialité", renderer, "text", SPECIALITE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

       
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Salaire", renderer, "text", SALAIRE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", SEXE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

       
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", JOUR, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

       
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", MOIS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

       
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Année", renderer, "text", ANNEE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

       
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", EMAIL, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

       
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", TELEPHONE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

       
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Centre", renderer, "text", CENTRE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Ville préférée", renderer, "text", VILLE_PREF, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

   
    store = gtk_list_store_new(COLUMNS,
                               G_TYPE_INT,     // id
                               G_TYPE_STRING,  // nom
                               G_TYPE_STRING,  // prenom
                               G_TYPE_STRING,  // specialite
                               G_TYPE_FLOAT,   // salaire
                               G_TYPE_STRING,  // sexe
                               G_TYPE_INT,     // jour
                               G_TYPE_INT,  // mois
                               G_TYPE_INT,     // annee
                               G_TYPE_STRING,  // email
                               G_TYPE_STRING,  // tel
                               G_TYPE_STRING,  // centre
                               G_TYPE_STRING   // ville
                               );

    gtk_list_store_append(store, &iter);
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
}


/*

void afficher_entraineur(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f;

    
    if (liste == NULL)
        return;

    
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

   

    if (store == NULL)
    {
      
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prenom", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Specialite", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Salaire", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Annee", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Tel", renderer, "text", 10, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Centre", renderer, "text", 11, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Ville", renderer, "text", 12, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        
        store = gtk_list_store_new(COLUMNS,
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING,
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING,
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING, 
                                  G_TYPE_STRING 
        );

    }
    else
    {
       
        gtk_list_store_clear(store);
    }


    f = fopen("entraineur.txt", "r");
    if (f == NULL)
    {
        
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        return;
    }

    entraineur e;
    
    while (fscanf(f, "%d;%29[^;];%29[^;];%29[^;];%f;%19[^;];%d;%d;%d;%49[^;];%19[^;];%29[^;];%29[^;]\n",
                  &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
                  &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
                  e.email, e.num_tel, e.centre, e.ville_pref) == 13)
    {
        char id_str[16], salaire_str[32], jour_str[8], mois_str[8], annee_str[8];

        sprintf(id_str, "%d", e.id);
    
        sprintf(salaire_str, "%.2f", e.salaire);
        sprintf(jour_str, "%d", e.date_inscription.jour);
        sprintf(mois_str, "%d", e.date_inscription.mois);
        sprintf(annee_str, "%d", e.date_inscription.annee);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           ID, id_str,
                           NOM, e.nom,
                           PRENOM, e.prenom,
                           SPECIALITE, e.specialite,
                           SALAIRE, salaire_str,
                           SEXE, e.sexe,
                           JOUR, jour_str,
                           MOIS, mois_str,
                           ANNEE, annee_str,
                           EMAIL, e.email,
                           TELEPHONE, e.num_tel,
                           CENTRE, e.centre,
                           VILLE_PREF, e.ville_pref,
                           -1);
    }

    fclose(f);


    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));

   
        g_object_unref(store);
} */



void afficher_entraineur(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f;
    gboolean store_created = FALSE; 

    if (!liste) return;

    
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (!store)
    {
        
        const char *titles[] = {"ID","Nom","Prenom","Specialite","Salaire","Sexe",
                                "Jour","Mois","Annee","Email","Tel","Centre","Ville"};
        for (int i = 0; i < 13; i++)
        {
            renderer = gtk_cell_renderer_text_new();
            column = gtk_tree_view_column_new_with_attributes(titles[i], renderer, "text", i, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        }

        
        store = gtk_list_store_new(COLUMNS,
                               G_TYPE_INT,     // id
                               G_TYPE_STRING,  // nom
                               G_TYPE_STRING,  // prenom
                               G_TYPE_STRING,  // specialite
                               G_TYPE_FLOAT,   // salaire
                               G_TYPE_STRING,  // sexe
                               G_TYPE_INT,     // jour
                               G_TYPE_INT,  // mois
                               G_TYPE_INT,     // annee
                               G_TYPE_STRING,  // email
                               G_TYPE_STRING,  // tel
                               G_TYPE_STRING,  // centre
                               G_TYPE_STRING   // ville
                               );

        store_created = TRUE;
    }
    else
    {
        gtk_list_store_clear(store);
    }

    
    f = fopen("entraineur.txt", "r");
    if (!f)
    {
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        if (store_created) g_object_unref(store);
        return;
    }

    entraineur e;
    while (fscanf(f, "%d;%29[^;];%29[^;];%29[^;];%f;%19[^;];%d;%d;%d;%49[^;];%19[^;];%29[^;];%29[^\n]\n",
                  &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
                  &e.date_inscription.jour, &e.date_inscription.mois, &e.date_inscription.annee,
                  e.email, e.num_tel, e.centre, e.ville_pref) == 13)
    {
        char id_str[16], salaire_str[32], jour_str[8], mois_str[8], annee_str[8];

        sprintf(id_str, "%d", e.id);
        sprintf(salaire_str, "%.2f", e.salaire);
        sprintf(jour_str, "%d", e.date_inscription.jour);
        sprintf(mois_str, "%d", e.date_inscription.mois);
        sprintf(annee_str, "%d", e.date_inscription.annee);

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, e.id,
                           1, e.nom,
                           2, e.prenom,
                           3, e.specialite,
                           4, e.salaire,
                           5, e.sexe,
                           6, e.date_inscription.jour,
                           7, e.date_inscription.mois,
                           8, e.date_inscription.annee,
                           9, e.email,
                           10, e.num_tel,
                           11, e.centre,
                           12, e.ville_pref,
                           -1);
    }

    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));

    if (store_created) g_object_unref(store);
}


int compter_specialite_entraineur(char fichier[100],
                                  int *nb_deb,
                                  int *nb_int,
                                  int *nb_pro)
{
    FILE *f;
    char ligne[512];
    char *token;
    int col;

    *nb_deb = *nb_int = *nb_pro = 0;

    f = fopen(fichier, "r");
    if (!f)
        return 0;

    while (fgets(ligne, sizeof(ligne), f)) {
        col = 0;
        token = strtok(ligne, ";");

        while (token) {
            col++;

            if (col == 4) {   
                if (strcmp(token, "Débutant") == 0)
                    (*nb_deb)++;
                else if (strcmp(token, "Intermédiaire") == 0)
                    (*nb_int)++;
                else if (strcmp(token, "Professionnel") == 0)
                    (*nb_pro)++;
                break;
            }
            token = strtok(NULL, ";");
        }
    }

    fclose(f);
    return 1;
}

