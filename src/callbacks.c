#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <stdlib.h>
#include <string.h>
#include "entraineur.h"


static void show_message(GtkWindow *parent, GtkMessageType type,
                         const char *title, const char *text)
{
    GtkWidget *dlg = gtk_message_dialog_new(
        parent,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        type,
        GTK_BUTTONS_OK,
        "%s", text
    );
    gtk_window_set_title(GTK_WINDOW(dlg), title);
    gtk_dialog_run(GTK_DIALOG(dlg));
    gtk_widget_destroy(dlg);
}


void
on_btn_ajouter_membre_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}





void
on_btn_membre_login_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *Menu_login,*Login_users;
	Menu_login = lookup_widget(GTK_WIDGET(button),"Menu_login");
	gtk_widget_hide(Menu_login);
	Login_users=create_Login_users();
	gtk_widget_show(Login_users);
}



void
on_btn_entraineur_login_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *Menu_login,*Login_users;
	Menu_login = lookup_widget(GTK_WIDGET(button),"Menu_login");
	gtk_widget_hide(Menu_login);
	Login_users=create_Login_users();
	gtk_widget_show(Login_users);


}
void
on_btn_admin_login_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
     GtkWidget *gestion_admin,*Menu_login;
     Menu_login = lookup_widget(GTK_WIDGET(button),"Menu_login");
     gtk_widget_hide(Menu_login);
     gestion_admin=create_gestion_admin();
     gtk_widget_show(gestion_admin);
}
void
on_btn_supprimer_membre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_modifier_membre_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_rechercher_membre_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}



void on_btn_ajouter_entraineur_clicked(GtkWidget *og, gpointer data)
{
    
}


void
on_btn_supprimer_entraineur_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_modifier_entraineur_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_rechercher_entraineur_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_ajouter_cours_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_supprimer_cours_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_modifier_cours_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_ajouter_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_supprimer_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_modifier_centre_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_rechercher_centre_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_ajouter_equipement_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_supprimer_equipement_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_modifier_equipement_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_rechercher_equipement_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_ajouter_event_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}
void
on_btn_sinscrire_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}





void
on_btn_chercher_cours_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}
void
on_btn_sinscrire_cours_clicked         (GtkButton       *button,
                                      gpointer         user_data)
{

}

void
on_btn_participer_event_clicked        (GtkButton       *button,
                                       gpointer         user_data)
{

}

void
on_btn_valider_ajout_clicked           (GtkButton       *button,
                                       gpointer         user_data)
{

}

void
on_btn_reserver_equipement_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}
void
on_h_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}

void
on_f_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_btn_supprimer_event_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_modifier_event_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_rechercher_event_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


int chercher_entraineur_par_id(int id, char *username_out)
{
    FILE *f;
    int id_fichier;
    char username[50], role[20];

    f = fopen("compte.txt", "r");
    if (f == NULL)
        return 0;

    while (fscanf(f, "%d %s %s", &id_fichier, username, role) != EOF)
    {
        if (id_fichier == id && strcmp(role, "entraineur") == 0)
        {
            strcpy(username_out, username);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}


/*
void
on_btn_login_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *entry_username;
    GtkWidget *Login_users;
    GtkWidget *gestion_admin, *profil_entraineur, *Profil_membre;
    GtkWidget *dialog;

    FILE *f;
    int id_fichier, id_saisi;
    char username_fichier[50], role[20];
    int trouve = 0;

    entraineur e;   // structure entraineur

   
    entry_username = lookup_widget(button, "entry_username_login");
    id_saisi = atoi(gtk_entry_get_text(GTK_ENTRY(entry_username)));

    
    f = fopen("compte.txt", "r");
    if (f == NULL)
    {
        dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Erreur : fichier compte.txt introuvable !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

   
    while (fscanf(f, "%d %s %s", &id_fichier, username_fichier, role) != EOF)
    {
        if (id_fichier == id_saisi)
        {
            trouve = 1;
            break;
        }
    }
    fclose(f);

   Login_users = lookup_widget(button, "Login_users");

    if (!trouve)
    {
        dialog = gtk_message_dialog_new(GTK_WINDOW(Login_users),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "ID introuvable !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

   
    if (strcmp(role, "admin") == 0)
    {
        gtk_widget_hide(Login_users);
        gestion_admin = create_gestion_admin();
        gtk_widget_show(gestion_admin);
    }

 
    else if (strcmp(role, "entraineur") == 0)
    {
      char username[50];

      if (chercher_entraineur_par_id(id_saisi, username))
      {
	    coach_connecte_id = id_saisi;

	    gtk_widget_hide(Login_users);
	    profil_entraineur = create_profil_entraineur();
	    gtk_widget_show(profil_entraineur);

            
            GtkWidget *label_nom    = lookup_widget(profil_entraineur, "nom_mer");
            GtkWidget *label_prenom = lookup_widget(profil_entraineur, "prenom_res");
            GtkWidget *label_id     = lookup_widget(profil_entraineur, "id_res");
            GtkWidget *numero       = lookup_widget(profil_entraineur, "res_num");
            GtkWidget *specialite   = lookup_widget(profil_entraineur, "spe_res");

            char id_txt[20];
            sprintf(id_txt, "%d", e.id);

          
            gtk_label_set_text(GTK_LABEL(label_nom), e.nom);
            gtk_label_set_text(GTK_LABEL(label_prenom), e.prenom);
            gtk_label_set_text(GTK_LABEL(label_id), id_txt);
            gtk_label_set_text(GTK_LABEL(numero), e.num_tel);
            gtk_label_set_text(GTK_LABEL(specialite), e.specialite);
        }
        else
        {
            dialog = gtk_message_dialog_new(NULL,
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "Entraîneur introuvable !");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }

    
    else if (strcmp(role, "membre") == 0)
    {
        gtk_widget_hide(Login_users);
       Profil_membre =  create_Profil_membre();
        gtk_widget_show(Profil_membre);
    }

    else
    {
        dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Rôle invalide !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

*/
void
on_btn_login_clicked(GtkButton *button, gpointer user_data)
{
    entraineur e;
    int id_saisi;
    char nom_saisi[30];
    int trouve = 0;

    GtkWidget *username;
    GtkWidget *id;
    GtkWidget *output;

    username = lookup_widget(GTK_WIDGET(button), "entry_username_login");
    id       = lookup_widget(GTK_WIDGET(button), "entry_mdp_login");
    output   = lookup_widget(GTK_WIDGET(button), "label_succes_login");

    strcpy(nom_saisi, gtk_entry_get_text(GTK_ENTRY(username)));
    id_saisi = atoi(gtk_entry_get_text(GTK_ENTRY(id)));

    FILE *f = fopen("entraineur.txt", "r");
    if (f == NULL)
    {
        gtk_label_set_text(GTK_LABEL(output), "Erreur ouverture fichier !");
        return;
    }

    while (fscanf(f,
        "%d;%29[^;];%29[^;];%29[^;];%f;%9[^;];%d;%d;%d;%49[^;];%19[^;];%29[^;];%29[^\n]\n",
        &e.id, e.nom, e.prenom, e.specialite, &e.salaire, e.sexe,
        &e.date_inscription.jour,
        &e.date_inscription.mois,
        &e.date_inscription.annee,
        e.email, e.num_tel, e.centre, e.ville_pref) != EOF)
    {
        if (e.id == id_saisi == 0) //&& strcmp(e.nom, nom_saisi) == 0)
        {
            trouve = 1;
            break;
        }
    }

    fclose(f);

    if (trouve)
  {
    gtk_label_set_text(GTK_LABEL(output), "Connexion réussie !");

    
    coach_connecte_id = e.id;

    GtkWidget *Login_users = lookup_widget(GTK_WIDGET(button), "Login_users");
    GtkWidget *profil_entraineur = create_profil_entraineur();

    gtk_widget_show(profil_entraineur);
    gtk_widget_hide(Login_users);

    GtkWidget *label_nom     = lookup_widget(profil_entraineur, "nom_mer");
    GtkWidget *label_prenom  = lookup_widget(profil_entraineur, "prenom_res");
    GtkWidget *label_id      = lookup_widget(profil_entraineur, "id_res");
    GtkWidget *numero        = lookup_widget(profil_entraineur, "res_num");
    GtkWidget *specialite    = lookup_widget(profil_entraineur, "spe_res");
    char id_txt[20];
    sprintf(id_txt, "%d", e.id);

    gtk_label_set_text(GTK_LABEL(label_nom), e.nom);
    gtk_label_set_text(GTK_LABEL(label_prenom), e.prenom);
    gtk_label_set_text(GTK_LABEL(label_id), id_txt);
    gtk_label_set_text(GTK_LABEL(numero), e.num_tel);
    gtk_label_set_text(GTK_LABEL(specialite), e.specialite);
  }

    else
    {
        gtk_label_set_text(GTK_LABEL(output), "Identifiants incorrects !");
    }
}




void remplir_combobox_cours(GtkWidget *combo)
{
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f;
    int id;
    char nom[50];

    store = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);

    f = fopen("cour_res.txt", "r");
    if (f == NULL)
    {
        g_print("DEBUG: impossible d'ouvrir cour_res.txt\n");
        return;
    }

    while (fscanf(f, "%d %49s", &id, nom) != EOF)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, id,   
                           1, nom,  
                           -1);
    }

    fclose(f);

    gtk_combo_box_set_model(GTK_COMBO_BOX(combo), GTK_TREE_MODEL(store));
    g_object_unref(store);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo),
                                   renderer,
                                   "text", 1,
                                   NULL);
}
 


GtkWidget* find_widget_by_name(GtkWidget *parent, const char *name)
{
    if (!GTK_IS_WIDGET(parent)) return NULL;

    if (g_strcmp0(gtk_widget_get_name(parent), name) == 0)
        return parent;

    if (GTK_IS_CONTAINER(parent))
    {
        GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
        for (GList *l = children; l != NULL; l = l->next)
        {
            GtkWidget *found = find_widget_by_name(GTK_WIDGET(l->data), name);
            if (found)
            {
                g_list_free(children);
                return found;
            }
        }
        g_list_free(children);
    }
    return NULL;
}




int get_last_id(const char* filename1) {
    FILE* f = fopen(filename1, "r");
    if (!f) return 0;

    int id = 0;
    char line[512];

    while (fgets(line, sizeof(line), f)) {
        int tmp_id;
        
        if (sscanf(line, "%d", &tmp_id) == 1) {
            if (tmp_id > id) id = tmp_id;
        }
    }

    fclose(f);
    return id;
}


int generate_new_id(const char* filename1) {
    return get_last_id(filename1) + 1;
}

void on_mer_reserver_clicked(GtkWidget *button, gpointer user_data)
{
    reservation r;

   
    GtkWidget *notebook = lookup_widget(GTK_WIDGET(button), "notebook4");
    if (!notebook) {
        g_print("Erreur: notebook non trouvé !\n");
        return;
    }

    GtkWidget *page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), 1); 
    if (!page) {
        g_print("Erreur: page réservation non trouvée !\n");
        return;
    }

    
    GtkWidget *w_cours    = lookup_widget(button, "W_res_cours");
    GtkWidget *w_prive    = lookup_widget(button, "w_res_prive");
    GtkWidget *w_cal      = lookup_widget(button, "W_res_calendar");
    GtkWidget *w_hour     = lookup_widget(button, "w_res_hour");
    GtkWidget *w_min      = lookup_widget(button, "w_res_min");
    GtkWidget *w_capacite = lookup_widget(button, "w_res_capacite");

    
    if (!w_cours || !w_prive || !w_cal || !w_hour || !w_min || !w_capacite) {
        g_print("Erreur: un ou plusieurs widgets n'ont pas été trouvés !\n");
        return;
    }

    
    r.reservation_id = generate_new_id("reservation.txt");

    
    r.coach_id = coach_connecte_id;

   
    GtkTreeIter iter;
    GtkTreeModel *model;
    if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(w_cours), &iter)) {
        model = gtk_combo_box_get_model(GTK_COMBO_BOX(w_cours));
        gtk_tree_model_get(model, &iter, 0, &r.cour_id, -1);
    } else {
        r.cour_id = -1;
    }

    
    r.cours_privee = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w_prive)) ? 1 : 0;

   
    r.heure.heure   = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_hour));
    r.heure.minutes = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_min));

    
    r.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_capacite));

  
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(w_cal), &year, &month, &day);
    r.date.jour  = day;
    r.date.mois  = month + 1;
    r.date.annee = year;

    
    ajouter_reservation(r);

    g_print("Réservation enregistrée : ID %d, Coach %d, Capacité %d\n",
            r.reservation_id, r.coach_id, r.capacite);
}


      
   



void
on_mer_actualiser_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *gestion_admin,*w1;
    GtkWidget *treeview;
    w1 = lookup_widget(GTK_WIDGET(button),"gestion_admin");
    gestion_admin = create_gestion_admin();
    gtk_widget_hide(w1);
    treeview = lookup_widget(button, "mer_tree");
    vider(treeview);
    afficher_entraineur(treeview);
}


void on_mer_modifier_clicked(GtkWidget *og, gpointer data)
{
    GtkWidget *j, *m, *a;
    GtkWidget *cb1, *cb2;
    GtkWidget *id_entry, *email, *nom, *pren, *salaire_entry, *num, *h, *f, *vp;
    GtkWidget *label_resultat;
    entraineur e;

    
    j = lookup_widget(og, "JOUR");
    m = lookup_widget(og, "MOIS");
    a = lookup_widget(og, "ANNEE");

    id_entry      = lookup_widget(og, "id");
    nom           = lookup_widget(og, "nom");
    pren          = lookup_widget(og, "pre");
    salaire_entry = lookup_widget(og, "s");
    cb1           = lookup_widget(og, "spe");
    cb2           = lookup_widget(og, "centre");
    num           = lookup_widget(og, "num");
    email         = lookup_widget(og, "em");
    h             = lookup_widget(og, "h");
    f             = lookup_widget(og, "f");
    vp            = lookup_widget(og, "vp");
    label_resultat = lookup_widget(og, "label_resultat");

    
    e.date_inscription.jour  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(j));
    e.date_inscription.mois  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m));
    e.date_inscription.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a));

    const char *id_txt = gtk_entry_get_text(GTK_ENTRY(id_entry));
    e.id = (id_txt && id_txt[0] != '\0') ? atoi(id_txt) : 0;

    strcpy(e.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
    strcpy(e.prenom, gtk_entry_get_text(GTK_ENTRY(pren)));
    strcpy(e.email, gtk_entry_get_text(GTK_ENTRY(email)));
    strcpy(e.num_tel, gtk_entry_get_text(GTK_ENTRY(num)));
    strcpy(e.ville_pref, gtk_entry_get_text(GTK_ENTRY(vp)));

    const char *sal_txt = gtk_entry_get_text(GTK_ENTRY(salaire_entry));
    e.salaire = (sal_txt && sal_txt[0] != '\0') ? atof(sal_txt) : 0.0;

    
    gchar *spec = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cb1));
    strcpy(e.specialite, (spec != NULL) ? spec : "");
    if (spec) g_free(spec);

    gchar *ct = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cb2));
    strcpy(e.centre, (ct != NULL) ? ct : "");
    if (ct) g_free(ct);

    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(h)))
        strcpy(e.sexe, "Homme");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(f)))
        strcpy(e.sexe, "Femme");
    else
        strcpy(e.sexe, "");

    
    const char *erreur = valider_entraineur_msg(e);
    if (erreur != NULL) {
        gtk_label_set_text(GTK_LABEL(label_resultat), erreur);  
        return;
    }
    if (modifier(e.id, e)) {
        gtk_label_set_text(GTK_LABEL(label_resultat),
                           "Entraîneur modifié avec succès !");
    } else {
        gtk_label_set_text(GTK_LABEL(label_resultat),
                           "Erreur : impossible de modifier l'entraîneur.");
    }
}





static void combo_set_active_text(GtkComboBox *cb, const char *text)
{
    if (!cb || !text) return;

    GtkTreeModel *model = gtk_combo_box_get_model(cb);
    if (!model) return;

    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
    int index = 0;

    while (valid) {
        GValue val = G_VALUE_INIT;
        gtk_tree_model_get_value(model, &iter, 0, &val);
        const gchar *row_text = g_value_get_string(&val);
        if (row_text && strcmp(row_text, text) == 0) {
            gtk_combo_box_set_active(cb, index);
            g_value_unset(&val);
            return;
        }
        g_value_unset(&val);
        valid = gtk_tree_model_iter_next(model, &iter);
        index++;
    }
}
void
on_mer_rechercher_clicked(GtkButton *og, gpointer user_data)
{
    GtkWidget *j, *m, *a;
    GtkWidget *cb1, *cb2;
    GtkWidget *id_entry, *email, *nom, *pren, *salaire_entry, *num, *h, *f, *vp;

    entraineur e;
    int id;
    char txt[50];

    j = lookup_widget(og, "JOUR");
    m = lookup_widget(og, "MOIS");
    a = lookup_widget(og, "ANNEE");
    id_entry      = lookup_widget(og, "id");
    nom           = lookup_widget(og, "nom");
    pren          = lookup_widget(og, "pre");
    salaire_entry = lookup_widget(og, "s");
    num           = lookup_widget(og, "num");
    email         = lookup_widget(og, "em");
    vp            = lookup_widget(og, "vp");
    cb1 = lookup_widget(og, "spe");
    cb2 = lookup_widget(og, "centre");

    h = lookup_widget(og, "h");
    f = lookup_widget(og, "f");

   
    id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));
    if (id <= 0)
        return;
    e = chercher(id);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(j), e.date_inscription.jour);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(m), e.date_inscription.mois);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a), e.date_inscription.annee);

   
    sprintf(txt, "%d", e.id);
    gtk_entry_set_text(GTK_ENTRY(id_entry), txt);

    gtk_entry_set_text(GTK_ENTRY(nom), e.nom);
    gtk_entry_set_text(GTK_ENTRY(pren), e.prenom);
    gtk_entry_set_text(GTK_ENTRY(email), e.email);
    gtk_entry_set_text(GTK_ENTRY(vp), e.ville_pref);
    gtk_entry_set_text(GTK_ENTRY(num), e.num_tel);

    sprintf(txt, "%.2f", e.salaire);
    gtk_entry_set_text(GTK_ENTRY(salaire_entry), txt);

    
    /*gtk_combo_box_set_active(GTK_COMBO_BOX(cb1),
        get_index_from_combobox(cb1, e.specialite));

   	
    gtk_combo_box_set_active(GTK_COMBO_BOX(cb2),
        get_index_from_combobox(cb2, e.centre));*/

combo_set_active_text(GTK_COMBO_BOX(cb1), e.specialite);
combo_set_active_text(GTK_COMBO_BOX(cb2), e.centre);
    
    if (strcmp(e.sexe, "Homme") == 0)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(h), TRUE);
    else if (strcmp(e.sexe, "Femme") == 0)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(f), TRUE);

}



    /*GtkWidget *entry, *label;
    const char *txt;
    int id;
    entraineur e;
    char msg[300];

    entry = lookup_widget(button, "rech_id");
    label = lookup_widget(button, "label_resultat");

    txt = gtk_entry_get_text(GTK_ENTRY(entry));
    if (txt == NULL || strlen(txt) == 0)
        return;

    id = atoi(txt);

    e = chercher_entraineur("entraineur.txt", id);

    if (e.id == -1)
    {
        gtk_label_set_text(GTK_LABEL(label), "Entraineur non trouvé");
    }
    else
    {
        sprintf(msg,
                "Nom : %s\nPrenom : %s\nSpécialité : %s\nCentre : %s\nTel : %s",
                e.nom, e.prenom, e.specialite, e.centre, e.num_tel);

        gtk_label_set_text(GTK_LABEL(label), msg);
    }*/



void
on_mer_tree_row_activated              (GtkTreeView     *liste,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{ 
    GtkTreeModel *model;
    GtkTreeIter iter;
    gint id;

    model = gtk_tree_view_get_model(liste);
    if (model == NULL)
        return; 

    if (gtk_tree_model_get_iter(model, &iter, path))
    {

        gtk_tree_model_get(model, &iter, 0, &id, -1);

	g_print("The activated row is: %d", id);

        supprimer_entraineur("entraineur.txt",id);
        GtkWidget *tree= GTK_WIDGET(liste);

        vider(tree);
     
        afficher_entraineur(tree);
    }
}






void
on_mer_clicked                         (GtkButton       *button,
                                        gpointer         user_data)
{

}



void on_mer_afficher_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *ajout_entraineur;
    GtkWidget *he_entraineur;
    GtkWidget *liste;

    ajout_entraineur = lookup_widget(button, "ajouter_entraineur");
    if (ajout_entraineur)
        gtk_widget_hide(ajout_entraineur);

   
    he_entraineur = create_gestion_admin();
    gtk_widget_show(he_entraineur);

    liste = lookup_widget(he_entraineur, "mer_tree");

  
    afficher_entraineur(liste);

    
}










void
on_mer_retourner_clicked (GtkWidget *button, gpointer user_data)
{
    GtkWidget *fenetre_tree;
    GtkWidget *Menu_login;

    fenetre_tree = lookup_widget(GTK_WIDGET(button), "gestion_admin");
    if (fenetre_tree)
        gtk_widget_hide(fenetre_tree);

    Menu_login = lookup_widget(GTK_WIDGET(button), "Menu_login");

    
    if (Menu_login == NULL)
        Menu_login = create_Menu_login();

    gtk_widget_show(Menu_login);
}


void
on_mer_ajouter_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *fenetre_tree;
    GtkWidget *fenetre_ajouter;

    fenetre_tree = lookup_widget(GTK_WIDGET(button), "gestion_admin");
    if (fenetre_tree)
        gtk_widget_hide(fenetre_tree);

    fenetre_ajouter = lookup_widget(GTK_WIDGET(button), "ajouter_entraineur");

    
    if (fenetre_ajouter == NULL)
        fenetre_ajouter = create_ajouter_entraineur();

    gtk_widget_show(fenetre_ajouter);

}




void on_mer_confirmer_clicked(GtkWidget *og, gpointer data)
{
    GtkWidget *j, *m, *a;
    GtkWidget *cb1, *cb2;
    GtkWidget *id_entry, *email, *nom, *pren, *salaire_entry, *num, *h, *f, *vp;
    GtkWindow *parent_window;
    entraineur e;

    
    parent_window = GTK_WINDOW(gtk_widget_get_toplevel(og));

    
    j = lookup_widget(og, "JOUR");
    m = lookup_widget(og, "MOIS");
    a = lookup_widget(og, "ANNEE");

    id_entry      = lookup_widget(og, "id");
    nom           = lookup_widget(og, "nom");
    pren          = lookup_widget(og, "pre");
    salaire_entry = lookup_widget(og, "s");
    cb1           = lookup_widget(og, "spe");
    cb2           = lookup_widget(og, "centre");
    num           = lookup_widget(og, "num");
    email         = lookup_widget(og, "em");
    h             = lookup_widget(og, "h");
    f             = lookup_widget(og, "f");
    vp            = lookup_widget(og, "vp");

    
    if (gtk_entry_get_text_length(GTK_ENTRY(nom)) == 0) {
        show_message(parent_window, GTK_MESSAGE_WARNING,
                     "Champ obligatoire", "Le nom est obligatoire.");
        return;
    }

    if (gtk_entry_get_text_length(GTK_ENTRY(pren)) == 0) {
        show_message(parent_window, GTK_MESSAGE_WARNING,
                     "Champ obligatoire", "Le prénom est obligatoire.");
        return;
    }

    if (gtk_entry_get_text_length(GTK_ENTRY(id_entry)) == 0) {
        show_message(parent_window, GTK_MESSAGE_WARNING,
                     "Champ obligatoire", "L'ID est obligatoire.");
        return;
    }

    
    e.date_inscription.jour  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(j));
    e.date_inscription.mois  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m));
    e.date_inscription.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a));

    e.id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));

    strcpy(e.nom, gtk_entry_get_text(GTK_ENTRY(nom)));
    strcpy(e.prenom, gtk_entry_get_text(GTK_ENTRY(pren)));
    strcpy(e.email, gtk_entry_get_text(GTK_ENTRY(email)));
    strcpy(e.num_tel, gtk_entry_get_text(GTK_ENTRY(num)));
    strcpy(e.ville_pref, gtk_entry_get_text(GTK_ENTRY(vp)));

    e.salaire = atof(gtk_entry_get_text(GTK_ENTRY(salaire_entry)));

    gchar *spec = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cb1));
    strcpy(e.specialite, spec ? spec : "");
    g_free(spec);

    gchar *ct = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cb2));
    strcpy(e.centre, ct ? ct : "");
    g_free(ct);

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(h)))
        strcpy(e.sexe, "Homme");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(f)))
        strcpy(e.sexe, "Femme");
    else
        strcpy(e.sexe, "");

    
    if (ajouter(e)) {
        show_message(parent_window, GTK_MESSAGE_INFO,
                     "Succès", "Entraîneur ajouté avec succès !");
    } else {
        show_message(parent_window, GTK_MESSAGE_ERROR,
                     "Erreur", "Échec de l'ajout de l'entraîneur.");
    }
}



void
on_valider_res_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_profil_entraineur_show              (GtkWidget       *widget,
                                        gpointer         user_data)
{

}

void
on_window_login_show(GtkWidget *window, gpointer user_data)
{
    /*GtkWidget *combo;

    combo = lookup_widget(window, "W_res_cours");
    if (combo)
        remplir_combobox_cours(combo);*/
}


void
on_notebook4_switch_page(GtkNotebook *notebook,
                        GtkWidget   *page,
                        guint        page_num,
                        gpointer     user_data)
{
    
    if (page_num == 1)
    {
        GtkWidget *combo;

        combo = lookup_widget(GTK_WIDGET(notebook), "W_res_cours");
        if (combo)
        {
            remplir_combobox_cours(combo);
            gtk_widget_set_sensitive(combo, TRUE);
            gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
        }
    }
}




int g_nb_deb = 0;
int g_nb_int = 0;
int g_nb_pro = 0;


gboolean
on_drawinHist_expose_event(GtkWidget *widget,
                           GdkEventExpose *event,
                           gpointer user_data)
{
    cairo_t *cr;
    int w, h, margin = 30;
    int maxv;
    double scale, bw;
    double x1, x2, x3;
    double h1, h2, h3;

    w = widget->allocation.width;
    h = widget->allocation.height;

    cr = gdk_cairo_create(widget->window);

    /* Fond */
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    /* Axes */
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);
    cairo_move_to(cr, margin, margin);
    cairo_line_to(cr, margin, h - margin);
    cairo_line_to(cr, w - margin, h - margin);
    cairo_stroke(cr);

    /* Max */
    maxv = g_nb_deb;
    if (g_nb_int > maxv) maxv = g_nb_int;
    if (g_nb_pro > maxv) maxv = g_nb_pro;
    if (maxv <= 0) maxv = 1;

    scale = (h - 2 * margin) / (double) maxv;
    bw = (w - 2 * margin) / 6.0;

    x1 = margin + bw * 1;
    x2 = margin + bw * 3;
    x3 = margin + bw * 5;

    h1 = g_nb_deb * scale;
    h2 = g_nb_int * scale;
    h3 = g_nb_pro * scale;

    /* Débutant */
    cairo_set_source_rgb(cr, 0.2, 0.6, 0.9);
    cairo_rectangle(cr, x1, h - margin - h1, bw, h1);
    cairo_fill(cr);

    /* Intermédiaire */
    cairo_set_source_rgb(cr, 0.4, 0.8, 0.4);
    cairo_rectangle(cr, x2, h - margin - h2, bw, h2);
    cairo_fill(cr);

    /* Professionnel */
    cairo_set_source_rgb(cr, 0.9, 0.4, 0.4);
    cairo_rectangle(cr, x3, h - margin - h3, bw, h3);
    cairo_fill(cr);

    /* Texte */
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 11);

    cairo_move_to(cr, x1, h - margin + 18);
    cairo_show_text(cr, "Débutant");

    cairo_move_to(cr, x2, h - margin + 18);
    cairo_show_text(cr, "Intermédiaire");

    cairo_move_to(cr, x3, h - margin + 18);
    cairo_show_text(cr, "Professionnel");

    cairo_destroy(cr);
    return FALSE;
}






void
on_mer_stats_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *drawing;
    GtkWidget *label;
    char msg[120];

    drawing = lookup_widget(GTK_WIDGET(button), "drawinHist");
    label   = lookup_widget(GTK_WIDGET(button), "label_stats");

    if (!compter_specialite_entraineur("entraineur.txt",
                                       &g_nb_deb,
                                       &g_nb_int,
                                       &g_nb_pro)) {
        gtk_label_set_text(GTK_LABEL(label),
                           "Erreur : entraineur.txt introuvable");
        return;
    }

    sprintf(msg,
            "Débutant: %d   Intermédiaire: %d   Professionnel: %d",
            g_nb_deb, g_nb_int, g_nb_pro);

    gtk_label_set_text(GTK_LABEL(label), msg);

    gtk_widget_queue_draw(drawing);
}


void
on_retourner_profil_clicked            (GtkWidget      *button,
                                        gpointer         user_data)
{
    GtkWidget *profil_entraineur;
    GtkWidget *Menu_login;

    profil_entraineur = lookup_widget(GTK_WIDGET(button), "profil_entraineur");
    if (profil_entraineur)
        gtk_widget_hide(profil_entraineur);

    Menu_login = lookup_widget(GTK_WIDGET(button), "Menu_login");

    
    if (Menu_login == NULL)
        Menu_login = create_Menu_login();

    gtk_widget_show(Menu_login);
}

