#include <gtk/gtk.h>
#include "equipement.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // Indispensable pour l'horodatage

enum {
    ID,
    NOM,
    CENTRE,
    CATEGORIE,
    QUANTITE,
    ETAT,
    SALLE,
    COULEUR,
    COLUMNS
};

void ajouter_equipement(Equipement e)
{
    if (verifier_unicite_id_equipement(e.id) == 0)
    {
        g_print("ERREUR: Echec de l'ajout. L'ID %s existe déjà !\n", e.id);
        
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                     GTK_DIALOG_MODAL,
                                                     GTK_MESSAGE_ERROR,
                                                     GTK_BUTTONS_OK,
                                                     "ERREUR: Echec de l'Ajout. L'ID %s existe déjà.", e.id);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return; 
    }
    
    FILE *f = fopen("equipements.txt", "a"); 
    if (f != NULL)
    {
        fprintf(f, "%s;%s;%s;%s;%d;%s;%s;%s\n",
                e.id, e.nom, e.centre, e.categorie, e.quantite, e.etat, e.salle, e.couleur);
        fclose(f);
        g_print("SUCCES: Équipement ID %s ajouté avec succès !\n", e.id);
    }
    else
    {
        g_print("Erreur: Impossible d'ouvrir le fichier equipements.txt.\n");
    }
}

void afficher_equipement(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	char id[50], nom[50], centre[50], categorie[50], etat[50], salle[50], couleur[50];
	int quantite;	
	FILE *f;
    
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    
	if(store == NULL)
	{
    	renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ID, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", NOM, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Centre", renderer, "text", CENTRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Catégorie", renderer, "text", CATEGORIE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Quantité", renderer, "text", QUANTITE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text", ETAT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Salle", renderer, "text", SALLE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Couleur", renderer, "text", COULEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	}

	store = gtk_list_store_new(COLUMNS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
		
	f = fopen("equipements.txt","r");	
	if(f == NULL)
	{
        f = fopen("equipements.txt","a+");
        if (f != NULL) {
            fclose(f);
        }
        gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
		g_object_unref (store);
		return;
	}

	while(fscanf(f, "%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^\n]\n",
                 id, nom, centre, categorie, &quantite, etat, salle, couleur) == 8)
	{
		gtk_list_store_append (store,&iter);	
		gtk_list_store_set (store,&iter,
                            ID, id,
                            NOM, nom,
                            CENTRE, centre,
                            CATEGORIE, categorie,
                            QUANTITE, quantite,
                            ETAT, etat,
                            SALLE, salle,
                            COULEUR, couleur, -1); 
	}
	
	fclose(f);
    
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);
}

void supprimer_equipement(Equipement e)
{
    char id[50], nom[50], centre[50], categorie[50], etat[50], salle[50], couleur[50];
    int quantite;
    
    FILE *f, *g;
    f = fopen("equipements.txt","r");
    g = fopen("dump.txt","w");
    
    if(f==NULL || g==NULL)
    {
        return;
    }
    else{
        while(fscanf(f, "%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^\n]\n", 
                     id, nom, centre, categorie, &quantite, etat, salle, couleur) == 8)
        {
            if(strcmp(e.id, id) != 0 ||
               strcmp(e.nom, nom) != 0 ||
               strcmp(e.centre, centre) != 0 ||
               strcmp(e.categorie, categorie) != 0 ||
               e.quantite != quantite || 
               strcmp(e.etat, etat) != 0 ||
               strcmp(e.salle, salle) != 0 ||
               strcmp(e.couleur, couleur) != 0)
            {
                fprintf(g,"%s;%s;%s;%s;%d;%s;%s;%s\n",
                        id, nom, centre, categorie, quantite, etat, salle, couleur);
            }
        }
        
        fclose(f);
        fclose(g);
        remove("equipements.txt");
        rename("dump.txt","equipements.txt");
    }
}

void vider(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store;
	
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    
	if (store == NULL)
	{
        renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ID, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", NOM, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Centre", renderer, "text", CENTRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Catégorie", renderer, "text", CATEGORIE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Quantité", renderer, "text", QUANTITE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Etat", renderer, "text", ETAT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Salle", renderer, "text", SALLE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("Couleur", renderer, "text", COULEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
	}
    
	store = gtk_list_store_new(COLUMNS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store); 
}

int modifier_equipement(Equipement e)
{
    FILE *f, *g;
    char id[50], nom[50], centre[50], categorie[50], etat[50], salle[50], couleur[50];
    int quantite;
    int trouve = 0;

    f = fopen("equipements.txt", "r");
    g = fopen("dump.txt", "w");

    if (f == NULL || g == NULL) {
        if (f) fclose(f);
        if (g) fclose(g);
        return 0;
    }

    while (fscanf(f, "%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^\n]\n",
                  id, nom, centre, categorie, &quantite, etat, salle, couleur) == 8) {
        
        if (strcmp(e.id, id) == 0) {
            fprintf(g, "%s;%s;%s;%s;%d;%s;%s;%s\n",
                    e.id, e.nom, e.centre, e.categorie, e.quantite, e.etat, e.salle, e.couleur);
            trouve = 1;
        } else {
            fprintf(g, "%s;%s;%s;%s;%d;%s;%s;%s\n",
                    id, nom, centre, categorie, quantite, etat, salle, couleur);
        }
    }

    fclose(f);
    fclose(g);

    if (trouve) {
        remove("equipements.txt");
        rename("dump.txt", "equipements.txt");
        return 1; 
    } else {
        remove("dump.txt"); 
        return 0; 
    }
}
void afficher_equipement_filtre(GtkWidget *p_treeview, const gchar *terme_recherche)
{
    GtkListStore *store;
    GtkTreeIter iter;
    Equipement e;
    FILE *f;
    int resultats_trouves = 0;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(p_treeview)));
    if (store == NULL) return; 
    gtk_list_store_clear(store);

    if (terme_recherche == NULL || terme_recherche[0] == '\0') {
        return; 
    }

    f = fopen("equipements.txt", "r");
    if (f == NULL) return;

    while(fscanf(f, "%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^\n]\n",
                 e.id, 
                 e.nom, 
                 e.centre, 
                 e.categorie, 
                 &e.quantite, 
                 e.etat, 
                 e.salle, 
                 e.couleur) != EOF)
    {
        if (strcmp(e.id, terme_recherche) == 0 ||
            strstr(e.nom, terme_recherche) != NULL)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, e.id,
                               1, e.nom,
                               2, e.centre,
                               3, e.categorie,
                               4, e.quantite,
                               5, e.etat,
                               6, e.salle,
                               7, e.couleur,
                               -1);
            
            resultats_trouves++; 
        }
    }

    fclose(f);
    if (resultats_trouves == 0) {
        g_print("INFO: Aucun équipement trouvé pour la recherche : '%s'\n", terme_recherche);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                     GTK_DIALOG_MODAL,
                                                     GTK_MESSAGE_INFO,
                                                     GTK_BUTTONS_OK,
                                                     "Aucun équipement ne correspond à l'ID '%s'.", terme_recherche);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void remplir_type_equipement(GtkWidget *combo_type, const char *categorie_choisie)
{
    GtkListStore *store;
    GtkTreeIter iter;
    Equipement e;
    FILE *f;
    
    store = gtk_list_store_new(1, G_TYPE_STRING);
    gtk_combo_box_set_model(GTK_COMBO_BOX(combo_type), GTK_TREE_MODEL(store));
    
    if (categorie_choisie == NULL || categorie_choisie[0] == '\0') {
        g_object_unref(store);
        return;
    }

    f = fopen("equipements.txt", "r");
    if (f == NULL) {
        g_object_unref(store);
        return;
    }
    
    while(fscanf(f, "%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^\n]\n",
                 e.id, e.nom, e.centre, e.categorie, &e.quantite, e.etat, e.salle, e.couleur) != EOF)
    {
        if (strcmp(e.categorie, categorie_choisie) == 0)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, e.nom, -1);
        }
    }

    fclose(f);
    
    g_object_unref(store); 
}


int reserver_equipement(const char *id_equipement, int quantite_reservee, const char *id_coach)
{
    Equipement e;
    FILE *f_in, *f_out;
    int trouve = 0;
    int reservation_succes = 0;

    f_in = fopen("equipements.txt", "r");
    f_out = fopen("temp.txt", "w");

    if (f_in == NULL || f_out == NULL) {
        g_print("Impossible d'ouvrir les fichiers pour la réservation.\n");
        if (f_in) fclose(f_in);
        if (f_out) fclose(f_out);
        return 0;
    }

    while(fscanf(f_in, "%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^\n]\n",
                 e.id, e.nom, e.centre, e.categorie, &e.quantite, e.etat, e.salle, e.couleur) != EOF)
    {
        if (strcmp(e.id, id_equipement) == 0)
        {
            trouve = 1;

            if (strcmp(e.etat, "Disponible") == 0)
            {
                if (e.quantite >= quantite_reservee)
                {
                    e.quantite -= quantite_reservee;
                    reservation_succes = 1;

                    if (e.quantite == 0) {
                         strncpy(e.etat, "Réservé", sizeof(e.etat) - 1);
                         e.etat[sizeof(e.etat) - 1] = '\0';
                    }
                } else {
                    g_print("Echec réservation: Stock insuffisant pour l'équipement %s (Stock: %d, Demandé: %d)\n", 
                            e.id, e.quantite, quantite_reservee);
                }
            } else {
                g_print("Echec réservation: L'équipement %s n'est pas disponible (Etat : %s).\n", 
                        e.id, e.etat);
            }
        }
        
        fprintf(f_out, "%s;%s;%s;%s;%d;%s;%s;%s\n",
                e.id, e.nom, e.centre, e.categorie, e.quantite, e.etat, e.salle, e.couleur);
    }

    fclose(f_in);
    fclose(f_out);

    remove("equipements.txt");
    rename("temp.txt", "equipements.txt");

    if (reservation_succes) {
        FILE *f_log = fopen("reservations.txt", "a");
        if (f_log != NULL) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            char date_str[30];

            sprintf(date_str, "%02d/%02d/%d %02d:%02d", 
        			tm.tm_mday,         // Jour
        			tm.tm_mon + 1,      // Mois
        			tm.tm_year + 1900,  // Année (depuis 1900)
       				tm.tm_hour,         // Heure
        			tm.tm_min);         // Minute
            fprintf(f_log, "%s;%s;%d;%s\n", id_coach, id_equipement, quantite_reservee, date_str);
            fclose(f_log);
            g_print("Historique mis à jour dans reservations.txt\n");
        } else {
            g_print("Erreur: Impossible d'ouvrir reservations.txt pour l'historique.\n");
        }
    }

    return reservation_succes;
}

int verifier_unicite_id_equipement(const char *id_a_verifier)
{
    FILE *f = fopen("equipements.txt", "r");
    Equipement e;
    
    if (f == NULL) {
        return 1;
    }

    while(fscanf(f, "%[^;];%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^\n]\n",
                 e.id, e.nom, e.centre, e.categorie, &e.quantite, e.etat, e.salle, e.couleur) != EOF)
    {
        if (strcmp(e.id, id_a_verifier) == 0) {
            fclose(f); 
            return 0; 
        }
    }

    fclose(f);
    return 1; 
}
