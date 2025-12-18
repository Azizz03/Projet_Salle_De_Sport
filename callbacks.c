#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "equipement.h" 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



static void get_combobox_text(GtkWidget *combo_box, char *buffer, size_t buffer_size)
{
    gint active = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
    if (active >= 0) {
        GtkTreeIter iter;
        GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(combo_box));
        gchar *text = NULL;
        
        if (gtk_tree_model_iter_nth_child(model, &iter, NULL, active)) {
            gtk_tree_model_get(model, &iter, 0, &text, -1);
        }
        
        if (text) {
            strncpy(buffer, text, buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
            g_free(text);
        } else {
            strncpy(buffer, "-", buffer_size - 1);
            buffer[buffer_size - 1] = '\0';
        }
    } else {
        strncpy(buffer, "-", buffer_size - 1);
        buffer[buffer_size - 1] = '\0';
    }
}

static void prepare_fenetre_modification(GtkWidget *fenetre, Equipement e)
{
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(fenetre, "id_equipement")), e.id);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(fenetre, "nom_equipement")), e.nom);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(fenetre, "centre_equipement")), e.centre);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(fenetre, "salle_equipement")), e.salle);
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(fenetre, "couleur_equipement")), e.couleur);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(fenetre, "quantite_equipement")), e.quantite);

    gtk_widget_set_sensitive(lookup_widget(fenetre, "id_equipement"), FALSE);

    g_object_set_data(G_OBJECT(fenetre), "mode_action", GINT_TO_POINTER(1)); // 1 = Modification
    g_object_set_data(G_OBJECT(fenetre), "original_id", g_strdup(e.id));
}


void on_btn_ajouter_equipement_clicked (GtkButton *button,gpointer user_data)
{
    GtkWidget *gestion_admin = gtk_widget_get_toplevel(GTK_WIDGET(button));
    if (gestion_admin) gtk_widget_destroy(gestion_admin);
    
    GtkWidget *Ajout_equipement = create_Ajout_equipement();
    
    GtkWidget *w_categorie = lookup_widget(Ajout_equipement, "categorie_equipement");
    GtkWidget *w_etat = lookup_widget(Ajout_equipement, "etat_equipement");
    
    GtkListStore *store_cat;
    GtkListStore *store_etat;
    GtkTreeIter iter;

    if (w_categorie) {
        store_cat = gtk_list_store_new (1, G_TYPE_STRING); 
        
        gtk_list_store_append (store_cat, &iter);
        gtk_list_store_set (store_cat, &iter, 0, "Cardio", -1);
        
        gtk_list_store_append (store_cat, &iter);
        gtk_list_store_set (store_cat, &iter, 0, "Musculation", -1);
        
        gtk_list_store_append (store_cat, &iter);
        gtk_list_store_set (store_cat, &iter, 0, "Accessoire", -1);

        gtk_combo_box_set_model (GTK_COMBO_BOX (w_categorie), GTK_TREE_MODEL (store_cat));
        g_object_unref (store_cat); 
    }

    if (w_etat) {
        store_etat = gtk_list_store_new (1, G_TYPE_STRING); 
        
        gtk_list_store_append (store_etat, &iter);
        gtk_list_store_set (store_etat, &iter, 0, "Disponible", -1);
        
        gtk_list_store_append (store_etat, &iter);
        gtk_list_store_set (store_etat, &iter, 0, "En maintenance", -1);

        gtk_list_store_append (store_etat, &iter);
        gtk_list_store_set (store_etat, &iter, 0, "Réservé", -1);


        gtk_combo_box_set_model (GTK_COMBO_BOX (w_etat), GTK_TREE_MODEL (store_etat));
        g_object_unref (store_etat); 
    }
    
    g_object_set_data(G_OBJECT(Ajout_equipement), "mode_action", GINT_TO_POINTER(0));
    g_object_set_data(G_OBJECT(Ajout_equipement), "original_id", NULL);
    
    gtk_widget_show(Ajout_equipement);
}

void on_btn_afficher_clicked (GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    if (current_window) gtk_widget_destroy(current_window);
    
    GtkWidget *gestion_admin = create_gestion_admin();
    gtk_widget_show(gestion_admin);
    
    GtkWidget *treeview_equipement = lookup_widget(gestion_admin,"treeview_equipement");

    if (treeview_equipement) afficher_equipement(treeview_equipement);
}

void on_Retour_equipement_clicked (GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));

    if (current_window)
        gtk_widget_destroy(current_window);
        
    GtkWidget *gestion_admin = create_gestion_admin(); 
    gtk_widget_show(gestion_admin);
}

void on_btn_valider_ajout_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *Ajout_equipement = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    GtkWidget *w_id = lookup_widget(Ajout_equipement, "id_equipement");
    GtkWidget *w_nom = lookup_widget(Ajout_equipement, "nom_equipement");
    GtkWidget *w_centre = lookup_widget(Ajout_equipement, "centre_equipement");
    GtkWidget *w_categorie = lookup_widget(Ajout_equipement, "categorie_equipement");
    GtkWidget *w_quantite = lookup_widget(Ajout_equipement, "quantite_equipement");
    GtkWidget *w_etat = lookup_widget(Ajout_equipement, "etat_equipement");
    GtkWidget *w_salle = lookup_widget(Ajout_equipement, "salle_equipement");
    GtkWidget *w_couleur = lookup_widget(Ajout_equipement, "couleur_equipement");

    if (!w_id || !w_nom || !w_centre || !w_categorie || !w_quantite || !w_etat || !w_salle || !w_couleur) {
        g_print("Erreur: un widget est introuvable.\n");
        return;
    }

    Equipement e;
    const gchar *temp_text;
    
    gint mode_action = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(Ajout_equipement), "mode_action"));
    gchar *original_id = g_object_get_data(G_OBJECT(Ajout_equipement), "original_id");
    
    if (mode_action == 1 && original_id != NULL) {
        strncpy(e.id, original_id, sizeof(e.id) - 1); 
        e.id[sizeof(e.id) - 1] = '\0';
    } else {
        temp_text = gtk_entry_get_text(GTK_ENTRY(w_id));
        strncpy(e.id, temp_text, sizeof(e.id) - 1); e.id[sizeof(e.id) - 1] = '\0';
    }
    
    temp_text = gtk_entry_get_text(GTK_ENTRY(w_nom));
    strncpy(e.nom, temp_text, sizeof(e.nom) - 1); e.nom[sizeof(e.nom) - 1] = '\0';

    temp_text = gtk_entry_get_text(GTK_ENTRY(w_centre));
    strncpy(e.centre, temp_text, sizeof(e.centre) - 1); e.centre[sizeof(e.centre) - 1] = '\0';

    temp_text = gtk_entry_get_text(GTK_ENTRY(w_salle));
    strncpy(e.salle, temp_text, sizeof(e.salle) - 1); e.salle[sizeof(e.salle) - 1] = '\0';

    temp_text = gtk_entry_get_text(GTK_ENTRY(w_couleur));
    strncpy(e.couleur, temp_text, sizeof(e.couleur) - 1); e.couleur[sizeof(e.couleur) - 1] = '\0';

    e.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_quantite));

    get_combobox_text(w_categorie, e.categorie, sizeof(e.categorie));
    get_combobox_text(w_etat, e.etat, sizeof(e.etat));

    if (mode_action == 1) {
        if (modifier_equipement(e)) { 
             g_print("Equipement ID %s modifie avec succes !\n", e.id);
        } else {
             g_print("Erreur: Equipement ID %s non trouve pour la modification.\n", e.id);
        }
    } else {
        ajouter_equipement(e); 
        g_print("Equipement ajoute avec succes !\n");
    }

    if (mode_action == 1 && original_id != NULL) {
        g_free(original_id);
    }


    gtk_widget_destroy(Ajout_equipement);
    GtkWidget *gestion_admin = create_gestion_admin();
    gtk_widget_show(gestion_admin);
    
    GtkWidget *treeview_equipement = lookup_widget(gestion_admin, "treeview_equipement");
    if (treeview_equipement) {
        afficher_equipement(treeview_equipement);
    }
}

void on_btn_modifier_equipement_clicked (GtkButton *button, gpointer user_data)
{
    GtkWidget *gestion_admin = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *treeview_equipement = lookup_widget(gestion_admin, "treeview_equipement");
    
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview_equipement));

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) 
    {
        gchar *id, *nom, *centre, *categorie, *etat, *salle, *couleur;
        gint quantite;
        Equipement e_a_modifier;

        gtk_tree_model_get(model, &iter,
                           0, &id,
                           1, &nom,
                           2, &centre,
                           3, &categorie,
                           4, &quantite,
                           5, &etat,
                           6, &salle,
                           7, &couleur,
                           -1);

        strncpy(e_a_modifier.id, id, sizeof(e_a_modifier.id) - 1); e_a_modifier.id[sizeof(e_a_modifier.id) - 1] = '\0';
        strncpy(e_a_modifier.nom, nom, sizeof(e_a_modifier.nom) - 1); e_a_modifier.nom[sizeof(e_a_modifier.nom) - 1] = '\0';
        strncpy(e_a_modifier.centre, centre, sizeof(e_a_modifier.centre) - 1); e_a_modifier.centre[sizeof(e_a_modifier.centre) - 1] = '\0';
        strncpy(e_a_modifier.categorie, categorie, sizeof(e_a_modifier.categorie) - 1); e_a_modifier.categorie[sizeof(e_a_modifier.categorie) - 1] = '\0';
        e_a_modifier.quantite = quantite;
        strncpy(e_a_modifier.etat, etat, sizeof(e_a_modifier.etat) - 1); e_a_modifier.etat[sizeof(e_a_modifier.etat) - 1] = '\0';
        strncpy(e_a_modifier.salle, salle, sizeof(e_a_modifier.salle) - 1); e_a_modifier.salle[sizeof(e_a_modifier.salle) - 1] = '\0';
        strncpy(e_a_modifier.couleur, couleur, sizeof(e_a_modifier.couleur) - 1); e_a_modifier.couleur[sizeof(e_a_modifier.couleur) - 1] = '\0';

        g_free(id); g_free(nom); g_free(centre); g_free(categorie); g_free(etat); g_free(salle); g_free(couleur);

        g_print("Equipement sélectionné pour modification: %s\n", e_a_modifier.id);

        if (gestion_admin) gtk_widget_destroy(gestion_admin);

        GtkWidget *Fenetre_Modification = create_Ajout_equipement(); 
        
        prepare_fenetre_modification(Fenetre_Modification, e_a_modifier);
        
        gtk_widget_show(Fenetre_Modification);
        
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gestion_admin),
                                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                                     GTK_MESSAGE_WARNING,
                                                     GTK_BUTTONS_CLOSE,
                                                     "Veuillez sélectionner un équipement à modifier.");
         gtk_dialog_run(GTK_DIALOG(dialog));
         gtk_widget_destroy(dialog);
    }
}

void on_btn_supprimer_equipement_clicked (GtkButton *button, gpointer user_data)
{
    g_print("Suppression via bouton non implémentée (utilisez le double-clic).\n");
}


void on_Actualiser_equipement_clicked (GtkButton *button, gpointer user_data)
{
    GtkWidget *gestion_admin = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    GtkWidget *treeview_equipement = lookup_widget(gestion_admin,"treeview_equipement");

    if (treeview_equipement) 
        afficher_equipement(treeview_equipement);
    else 
        g_print("Erreur : Treeview introuvable pour l'actualisation.\n");
}


void on_treeview_equipement_row_activated (GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeIter iter;
    gchar* id;
    gchar* nom;
    gchar* centre;
    gchar* categorie;
    int quantite;
    gchar* etat;
    gchar* salle;
    gchar* couleur;
    Equipement e;
    GtkTreeModel *model= gtk_tree_view_get_model(treeview);
    if(gtk_tree_model_get_iter(model,&iter,path))
    {
        gtk_tree_model_get(GTK_TREE_MODEL(model),&iter,0,&id,1,&nom,2,&centre,3,&categorie,4,&quantite,5,&etat,6,&salle,7,&couleur,-1);
        strcpy(e.id,id);
        strcpy(e.nom,nom);
        strcpy(e.centre,centre);
        strcpy(e.categorie,categorie);
        e.quantite=quantite;
        strcpy(e.etat,etat);
        strcpy(e.salle,salle);
        strcpy(e.couleur,couleur);
        supprimer_equipement(e);
        afficher_equipement(GTK_WIDGET(treeview));
    }
}


void on_btn_rechercher_equipement_clicked(GtkButton *button, gpointer user_data) {
	GtkWidget *gestion_admin = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    	GtkWidget *entry_recherche = lookup_widget(gestion_admin, "entry_recherche_equipement"); 
    	GtkWidget *treeview_equipement = lookup_widget(gestion_admin, "treeview_equipement");
    
    	if (entry_recherche && treeview_equipement)
    	{
        	const gchar *terme_recherche = gtk_entry_get_text(GTK_ENTRY(entry_recherche));
        
       		afficher_equipement_filtre(treeview_equipement, terme_recherche);
        
        	g_print("Recherche effectuée pour : %s\n", terme_recherche);
        
    	} else {
        	g_print("Erreur: Widget de recherche ou treeview introuvable.\n");

    	}
}
void
on_categorie_equipement_reserver_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
    GtkWidget *profile_entraineur = gtk_widget_get_toplevel(GTK_WIDGET(combobox));
    
    GtkWidget *w_type = lookup_widget(profile_entraineur, "type_equipement_reserver");

    if (!w_type) {
        g_print("Erreur: ComboBox 'Type' introuvable. Vérifiez l'ID .\n");
        return;
    }
    gchar *categorie_choisie_gstr = NULL;
    GtkTreeIter iter;

    if (gtk_combo_box_get_active_iter(combobox, &iter)) {
        GtkTreeModel *model = gtk_combo_box_get_model(combobox);
        gtk_tree_model_get(model, &iter, 0, &categorie_choisie_gstr, -1);
    }
    
    const char *categorie_choisie = (categorie_choisie_gstr) ? categorie_choisie_gstr : "";

    remplir_type_equipement(w_type, categorie_choisie);

    if (categorie_choisie_gstr) {
        g_free(categorie_choisie_gstr); 
    }	
}
void on_btn_reserver_equipement_clicked (GtkButton *button, gpointer user_data) {

    GtkWidget *profile_entraineur = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    GtkWidget *w_id_coach = lookup_widget(profile_entraineur, "entry_id_entraineur");
    GtkWidget *w_id_equip = lookup_widget(profile_entraineur, "id_equipement_reserver"); 
    GtkWidget *w_nombre = lookup_widget(profile_entraineur, "nombre_equipement_reserver"); 

    if (!w_id_coach || !w_id_equip || !w_nombre) {
        g_print("Erreur, Un ou plusieurs widgets sont introuvables.\n");
        return;
    }
    //const char *id_coach = gtk_label_get_text(GTK_LABEL(w_id_coach));
    const char *id_coach = "COACH_DEBUG";
    const char *id_equip = gtk_entry_get_text(GTK_ENTRY(w_id_equip));
    int quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_nombre));

    if (id_coach[0] == '\0') {
        g_print("Erreur: ID Entraîneur non détecté (vérifiez la connexion).\n");
        return;
    }
    if (id_equip[0] == '\0' || quantite <= 0) {
        g_print("Erreur: ID équipement manquant ou quantité invalide.\n");
        return;
    }

    int reservation_succes = reserver_equipement(id_equip, quantite, id_coach);

    if (reservation_succes) {
       	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(profile_entraineur), 
                                               GTK_DIALOG_MODAL, 
                                               GTK_MESSAGE_INFO, 
                                               GTK_BUTTONS_OK, 
                                               "Succès : Réservation effectuée pour l'équipement %s", id_equip);
       	gtk_dialog_run(GTK_DIALOG(dialog));
   
       	gtk_widget_destroy(dialog);

       	gtk_spin_button_set_value(GTK_SPIN_BUTTON(w_nombre), 1);
    } 
    else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(profile_entraineur), 
                                               GTK_DIALOG_MODAL, 
                                               GTK_MESSAGE_ERROR, 
                                               GTK_BUTTONS_OK, 
                                               "Erreur : Stock insuffisant ou équipement introuvable!");
    	gtk_dialog_run(GTK_DIALOG(dialog));
    
    	gtk_widget_destroy(dialog);
    }
}





void on_btn_ajouter_membre_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_supprimer_membre_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_modifier_membre_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_rechercher_membre_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_ajouter_entraineur_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_supprimer_entraineur_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_modifier_entraineur_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_rechercher_entraineur_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_ajouter_cours_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_supprimer_cours_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_modifier_cours_clicked (GtkButton *button, gpointer user_data) {}
void on_button19_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_ajouter_centre_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_supprimer_centre_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_modifier_centre_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_rechercher_centre_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_ajouter_event_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_supprimer_event_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_modifier_event_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_rechercher_event_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_admin_login_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_membre_login_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_entraineur_login_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_login_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_sinscrire_cours_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_participer_event_clicked (GtkButton *button, gpointer user_data) {}
void on_btn_sinscrire_centre_clicked (GtkButton *button, gpointer user_data) {}



