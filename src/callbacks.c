#include <gtk/gtk.h>
#include "callbacks.h"
#include "ajout_cour.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include <cairo.h>
cour cours_compatibles[50];
int nb_cours_compatibles = 0;


int sexe=0;
int restriction_med = 0;   // 0 = Non, 1 = Oui
cour cour_trouve; /* global */
void on_btn_suprimer_cours_clicked(GtkButton *button,
                                        gpointer   user_data)
{
    
}
void on_btn_modifier_cours_clicked(GtkButton *button,
                                        gpointer   user_data)

{
    
 
}
void on_button19_clicked(GtkButton *button,
                                        gpointer   user_data)
{
    
}
void on_btn_sinscrire_cours_clicked(GtkButton *button,
                                        gpointer   user_data)

{


    GtkWidget *window;

    window = gtk_widget_get_toplevel(GTK_WIDGET(button));

    if (confirmer_reservation("cour.txt", cour_trouve.id))
    {
        gtk_label_set_text(GTK_LABEL(
            lookup_widget(window,"sortie")),
            "Inscription confirmée");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(
            lookup_widget(window,"sortie")),
            "Capacité épuisée");
    }

  
}


void on_btn_ajouter_cours_clicked(GtkButton *button,
                                        gpointer   user_data)
{
}


void
on_duree_changed(GtkComboBox *combo,
                 gpointer user_data)
{
    GtkWidget *window;
    char *duree_choisie;
    int i;

    window = gtk_widget_get_toplevel(GTK_WIDGET(combo));

    duree_choisie =
        gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo));

    if (!duree_choisie)
        return;

    for (i = 0; i < nb_cours_compatibles; i++)
    {
        if (strcmp(cours_compatibles[i].duree,
                   duree_choisie) == 0)
        {
            cour_trouve = cours_compatibles[i];

            gtk_entry_set_text(GTK_ENTRY(
                lookup_widget(window,"salle")),
                cour_trouve.salle);

            gtk_entry_set_text(GTK_ENTRY(
                lookup_widget(window,"intensite")),
                cour_trouve.intensite);

            gtk_entry_set_text(GTK_ENTRY(
                lookup_widget(window,"publique_specifique")),
                cour_trouve.public_cible);

            gtk_entry_set_text(GTK_ENTRY(
                lookup_widget(window,"objectif")),
                cour_trouve.objectif);

            gtk_label_set_text(GTK_LABEL(
                lookup_widget(window,"sortie")),
                "Cours sélectionné");

            break;
        }
    }
}

/* =====================================================
   Helper : Retourne toujours une chaîne du widget donné
   ===================================================== */
static char *get_widget_text_safe(GtkWidget *w)
{
    if (!w) return g_strdup("");

    if (GTK_IS_ENTRY(w)) {
        return g_strdup(gtk_entry_get_text(GTK_ENTRY(w)));
    }

    if (GTK_IS_COMBO_BOX(w)) {
        gchar *t = gtk_combo_box_get_active_text(GTK_COMBO_BOX(w));
        return t ? t : g_strdup("");
    }

    if (GTK_IS_SPIN_BUTTON(w)) {
        int v = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w));
        char buf[16];
        snprintf(buf, sizeof(buf), "%d", v);
        return g_strdup(buf);
    }

    if (GTK_IS_LABEL(w)) {
        return g_strdup(gtk_label_get_text(GTK_LABEL(w)));
    }

    return g_strdup("");
}
void vider_combobox(GtkComboBox *combo)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    model = gtk_combo_box_get_model(combo);

    while (gtk_tree_model_get_iter_first(model, &iter))
    {
        gtk_combo_box_remove_text(combo, 0);
    }
}

void remplir_combobox_duree(GtkComboBox *combo, reservation r)
{
    FILE *f;
    cour c;
    int existe;
    char durees[20][20];
    int nb = 0;
    int i;

    f = fopen("cour.txt", "r");
    if (!f) return;

    vider_combobox(combo);

    while (fscanf(f, "%d %s %s %s %s %s %s %s %d %s %s %s %s %d %d %d",
                  &c.id, c.nom_c, c.type_c, c.coach, c.public_cible,
                  c.intensite, c.restrictions_medicales, c.objectif,
                  &c.capacite, c.type_equipement, c.salle, c.centre,
                  c.duree, &c.jour, &c.mois, &c.annee) != EOF)
    {
        if (strcmp(c.type_c, r.type) == 0 &&
            strcmp(c.centre, r.centre) == 0 &&
            c.jour == r.jour &&
            c.mois == r.mois &&
            c.annee == r.annee &&
            c.capacite > 0)
        {
            existe = 0;
            for (i = 0; i < nb; i++)
            {
                if (strcmp(durees[i], c.duree) == 0)
                {
                    existe = 1;
                    break;
                }
            }

            if (!existe)
            {
                strcpy(durees[nb], c.duree);
                gtk_combo_box_append_text(combo, c.duree);
                nb++;
            }
        }
    }

    fclose(f);

    if (nb > 0)
        gtk_combo_box_set_active(combo, 0);
}
// Checkbox restriction médicale
void on_restric_maladie_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    restriction_med = gtk_toggle_button_get_active(togglebutton);
}


// === AJOUTER COURS ===



void on_ajouter_clicked(GtkButton *button, gpointer user_data)
{
    cour c;

    /* Widgets */
    GtkWidget *w_id     = lookup_widget(GTK_WIDGET(button), "id");
    GtkWidget *w_nom    = lookup_widget(GTK_WIDGET(button), "nom");
    GtkWidget *w_type   = lookup_widget(GTK_WIDGET(button), "type");
    GtkWidget *w_coach  = lookup_widget(GTK_WIDGET(button), "coach");
    GtkWidget *w_public = lookup_widget(GTK_WIDGET(button), "public_spec");
    GtkWidget *w_intens = lookup_widget(GTK_WIDGET(button), "intensite");
    GtkWidget *w_cap    = lookup_widget(GTK_WIDGET(button), "capacite");
    GtkWidget *w_obj    = lookup_widget(GTK_WIDGET(button), "obj");
    GtkWidget *w_equip  = lookup_widget(GTK_WIDGET(button), "type_equi");
    GtkWidget *w_centre = lookup_widget(GTK_WIDGET(button), "centre");
    GtkWidget *w_duree  = lookup_widget(GTK_WIDGET(button), "duree");
    GtkWidget *w_salle  = lookup_widget(GTK_WIDGET(button), "salle");

    GtkWidget *w_jour   = lookup_widget(GTK_WIDGET(button), "jour");
    GtkWidget *w_mois   = lookup_widget(GTK_WIDGET(button), "mois");
    GtkWidget *w_annee  = lookup_widget(GTK_WIDGET(button), "annee");

    GtkWidget *labelSucces = lookup_widget(GTK_WIDGET(button), "label_sortie");

    /* Extraction */
    char *s_id    = get_widget_text_safe(w_id);
    char *s_nom   = get_widget_text_safe(w_nom);
    char *s_type  = get_widget_text_safe(w_type);
    char *s_coach = get_widget_text_safe(w_coach);
    char *s_public= get_widget_text_safe(w_public);
    char *s_intens= get_widget_text_safe(w_intens);
    char *s_cap   = get_widget_text_safe(w_cap);
    char *s_obj   = get_widget_text_safe(w_obj);
    char *s_equip = get_widget_text_safe(w_equip);
    char *s_centre= get_widget_text_safe(w_centre);
    char *s_duree = get_widget_text_safe(w_duree);
    char *s_salle = get_widget_text_safe(w_salle);

    /* ====== MOIS ====== */
    int mois_val = 0;

    if (GTK_IS_SPIN_BUTTON(w_mois)) {
        mois_val = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_mois));
    }
    else if (GTK_IS_COMBO_BOX(w_mois)) {
        gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(w_mois));
        mois_val = txt ? atoi(txt) : 0;
        g_free(txt);
    }
    else {
        char *txt = get_widget_text_safe(w_mois);
        mois_val = atoi(txt);
        g_free(txt);
    }

    if (mois_val < 1 || mois_val > 12) {
        g_print(" Mois invalide (%d) → mis automatiquement à 1\n", mois_val);
        mois_val = 1;
    }

    /* Copie dans la structure */
    c.id = atoi(s_id);
	/* ====== CONTROLE ID ====== */
if (id_cour_existe("cour.txt", c.id))
{
    gtk_label_set_text(GTK_LABEL(labelSucces),
                       "ID déjà existant, veuillez le changer !");
    return; // نوقف الإضافة
}
    strncpy(c.nom_c, s_nom, sizeof(c.nom_c)-1);
    strncpy(c.type_c, s_type, sizeof(c.type_c)-1);
    strncpy(c.coach, s_coach, sizeof(c.coach)-1);
    strncpy(c.public_cible, s_public, sizeof(c.public_cible)-1);
    strncpy(c.intensite, s_intens, sizeof(c.intensite)-1);
    strncpy(c.objectif, s_obj, sizeof(c.objectif)-1);
    strncpy(c.type_equipement, s_equip, sizeof(c.type_equipement)-1);
    strncpy(c.centre, s_centre, sizeof(c.centre)-1);
    strncpy(c.salle, s_salle, sizeof(c.salle)-1);
    strncpy(c.duree, s_duree, sizeof(c.duree)-1);

    if (restriction_med == 1)
        strcpy(c.restrictions_medicales, "Oui");
    else
        strcpy(c.restrictions_medicales, "Non");

    c.capacite = atoi(s_cap);
    c.jour     = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_jour));
    c.mois     = mois_val;
    c.annee    = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_annee));

    /* Sauvegarde */
    if (ajouter_cour("cour.txt", c))
        gtk_label_set_text(GTK_LABEL(labelSucces), "Cours ajouté avec succès !");
    else
        gtk_label_set_text(GTK_LABEL(labelSucces), "Erreur lors de l'ajout du cours !");

    g_print("Date enregistrée = %d / %d / %d\n", c.jour, c.mois, c.annee);

    /* free */
    g_free(s_id); g_free(s_nom); g_free(s_type); g_free(s_coach);
    g_free(s_public); g_free(s_intens); g_free(s_cap);
    g_free(s_obj); g_free(s_equip); g_free(s_centre);
    g_free(s_duree); g_free(s_salle);
}





/* === Membres === */
void
on_btn_admin_login_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *Menu_login;
    GtkWidget *gestion_admin;

    Menu_login = lookup_widget(GTK_WIDGET(button), "Menu_login");
    if (Menu_login)
        gtk_widget_hide(Menu_login);

    gestion_admin = create_gestion_admin();
    gtk_widget_show(gestion_admin);

}
void
on_btn_membre_login_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

      GtkWidget *Menu_login = NULL;
    GtkWidget *Login_users = NULL;

    Menu_login = lookup_widget(GTK_WIDGET(button), "Menu_login");
    if (Menu_login)
        gtk_widget_hide(Menu_login);

    Login_users = create_Login_users();
    if (Login_users)
        gtk_widget_show(Login_users);



}
void
on_btn_entraineur_login_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

   GtkWidget *Menu_login = NULL;
    GtkWidget *Login_users = NULL;

    Menu_login = lookup_widget(GTK_WIDGET(button), "Menu_login");
    if (Menu_login)
        gtk_widget_hide(Menu_login);

    Login_users = create_Login_users();
    if (Login_users)
        gtk_widget_show(Login_users);


}

void on_btn_supprimer_membre_clicked(GtkButton *b, gpointer d) {}
void on_btn_modifier_membre_clicked(GtkButton *b, gpointer d) {}
void on_btn_rechercher_membre_clicked(GtkButton *b, gpointer d) {}

/* === Centres === */
void on_btn_ajouter_centre_clicked(GtkButton *b, gpointer d) {}
void on_btn_supprimer_centre_clicked(GtkButton *b, gpointer d) {}
void on_btn_modifier_centre_clicked(GtkButton *b, gpointer d) {}
void on_btn_rechercher_centre_clicked(GtkButton *b, gpointer d) {}

/* === Équipements === */
void on_btn_ajouter_equipement_clicked(GtkButton *b, gpointer d) {}
void on_btn_supprimer_equipement_clicked(GtkButton *b, gpointer d) {}
void on_btn_modifier_equipement_clicked(GtkButton *b, gpointer d) {}
void on_btn_rechercher_equipement_clicked(GtkButton *b, gpointer d) {}
void on_btn_reserver_equipement_clicked(GtkButton *b, gpointer d) {}

/* === Événements === */
void on_btn_ajouter_event_clicked(GtkButton *b, gpointer d) {}
void on_btn_supprimer_event_clicked(GtkButton *b, gpointer d) {}
void on_btn_modifier_event_clicked(GtkButton *b, gpointer d) {}
void on_btn_rechercher_event_clicked(GtkButton *b, gpointer d) {}
void on_btn_participer_event_clicked(GtkButton *b, gpointer d) {}

/* === Login général === */
/*void on_btn_login_clicked(GtkButton *b, gpointer d) 
{

}

/* === Inscription centre === */
void on_btn_sinscrire_centre_clicked(GtkButton *b, gpointer d) {}
void on_btn_ajouter_entraineur_clicked(GtkButton *button, gpointer user_data) {}
    // ton code ici
    void on_btn_supprimer_entraineur_clicked(GtkButton *button, gpointer user_data) {}
void on_btn_modifier_entraineur_clicked(GtkButton *button, gpointer user_data) {}
void on_btn_rechercher_entraineur_clicked(GtkButton *button, gpointer user_data) {}
void on_btn_valider_ajout_clicked(GtkButton *button, gpointer user_data) {}  
void on_btn_ajouter_membre_clicked(GtkButton *button, gpointer user_data){} 
void on_btn_supprimer_cours_clicked(GtkButton *button, gpointer user_data){} 
 



void
on_afficher_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_retour_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_retour_cours_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

    GtkWidget *gestion_admin;
    GtkWidget *ajout_cours;

    // Récupérer la fenêtre gestion_admin
    gestion_admin = lookup_widget(GTK_WIDGET(button), "gestion_admin");
    
    // Cacher gestion_admin
    gtk_widget_hide(gestion_admin);

    // Ouvrir la fenêtre d’ajout de cours
    ajout_cours = create_ajout_cours();
    gtk_widget_show(ajout_cours);

}


void
on_rechercher_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry_id_rech, *entry_id, *entry_nom, *entry_type;
    GtkWidget *entry_coach, *entry_public, *entry_intensite;
    GtkWidget *entry_obj, *entry_equip, *entry_centre;
    GtkWidget *entry_salle, *entry_duree;
    GtkWidget *spin_capacite, *spin_jour, *spin_mois, *spin_annee;
    GtkWidget *check_restriction;
    GtkWidget *label_sortie;

    cour c;
    int id;
    char id_str[20];

    /* === 1. Récupération widgets === */
    entry_id_rech    = lookup_widget(GTK_WIDGET(button), "id");
    entry_id         = lookup_widget(GTK_WIDGET(button), "id");
    entry_nom        = lookup_widget(GTK_WIDGET(button), "nom");
    entry_type       = lookup_widget(GTK_WIDGET(button), "type");
    entry_coach      = lookup_widget(GTK_WIDGET(button), "coach");
    entry_public     = lookup_widget(GTK_WIDGET(button), "public_spec");
    entry_intensite  = lookup_widget(GTK_WIDGET(button), "intensite");
    spin_capacite    = lookup_widget(GTK_WIDGET(button), "capacite");
    entry_obj        = lookup_widget(GTK_WIDGET(button), "obj");
    entry_equip      = lookup_widget(GTK_WIDGET(button), "type_equi");
    entry_centre     = lookup_widget(GTK_WIDGET(button), "centre");
    entry_salle      = lookup_widget(GTK_WIDGET(button), "salle");
    entry_duree      = lookup_widget(GTK_WIDGET(button), "duree");
    spin_jour        = lookup_widget(GTK_WIDGET(button), "jour");
    spin_mois        = lookup_widget(GTK_WIDGET(button), "mois");
    spin_annee       = lookup_widget(GTK_WIDGET(button), "annee");
    check_restriction= lookup_widget(GTK_WIDGET(button), "restric_maladie");
    label_sortie     = lookup_widget(GTK_WIDGET(button), "label_sortie");

    /* === Vérification des NULL === */
    if (!entry_id_rech || !entry_id || !entry_nom || !entry_type || !entry_coach ||
        !entry_public || !entry_intensite || !spin_capacite || !entry_obj ||
        !entry_equip || !entry_centre || !entry_salle || !entry_duree ||
        !spin_jour || !spin_mois || !spin_annee || !check_restriction || !label_sortie)
    {
        g_print("Erreur: un widget n'a pas été trouvé !\n");
        return;
    }

    /* === 2. Récupérer ID recherché === */
    id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id_rech)));

    /* === 3. Recherche dans fichier === */
    c = chercher_cour("cour.txt", id);

    if (c.id == -1) {
        gtk_label_set_text(GTK_LABEL(label_sortie), "Cours introuvable !");
        return;
    }

    /* === 4. Remplissage widgets === */
    sprintf(id_str, "%d", c.id);
    gtk_entry_set_text(GTK_ENTRY(entry_id), id_str);
    gtk_entry_set_text(GTK_ENTRY(entry_nom), c.nom_c);
    gtk_entry_set_text(GTK_ENTRY(entry_coach), c.coach);

    /* ===== Combo TYPE cours ===== */
    if (strcmp(c.type_c, "relaxation") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_type), 0);
    else if (strcmp(c.type_c, "cardio") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_type), 1);

    /* ===== Combo CENTRE ===== */
    if (strcmp(c.centre, "centrea") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_centre), 0);
    else if (strcmp(c.centre, "centreb") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_centre), 1);
    else if (strcmp(c.centre, "centrec") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_centre), 2);

    /* ===== Combo SALLE ===== */
    if (strcmp(c.salle, "salle1") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_salle), 0);
    else if (strcmp(c.salle, "salle2") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_salle), 1);
    else if (strcmp(c.salle, "salle3") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_salle), 2);

    /* ===== Combo DUREE ===== */
    if (strcmp(c.duree, "de_10_a_12") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_duree), 0);
    else if (strcmp(c.duree, "de_14_a_15") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_duree), 1);
    else if (strcmp(c.duree, "de_20_a_22") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_duree), 2);

    /* ===== Combo TYPE ÉQUIPEMENT ===== */
    if (strcmp(c.type_equipement, "tapis") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_equip), 0);
    else if (strcmp(c.type_equipement, "tapis_yoga") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_equip), 1);
    else if (strcmp(c.type_equipement, "machine") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_equip), 2);

    /* ===== Combo INTENSITE ===== */
    if (strcmp(c.intensite, "faible") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_intensite), 0);
    else if (strcmp(c.intensite, "moyenne") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_intensite), 1);
    else if (strcmp(c.intensite, "hard") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_intensite), 2);

    /* ===== Combo PUBLIC SPECIFIQUE ===== */
    if (strcmp(c.public_cible, "femme_adulte") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_public), 0);
    else if (strcmp(c.public_cible, "homme_adulte") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_public), 1);
    else if (strcmp(c.public_cible, "adulte_mixte") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_public), 2);
    else if (strcmp(c.public_cible, "enfants_filles") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_public), 3);
    else if (strcmp(c.public_cible, "enfants_garcons") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_public), 4);
    else if (strcmp(c.public_cible, "enfants_mixte") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_public), 5);

    /* ===== Combo OBJECTIF ===== */
    if (strcmp(c.objectif, "perte_de_poids") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_obj), 0);
    else if (strcmp(c.objectif, "souplesse") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_obj), 1);
    else if (strcmp(c.objectif, "musculation") == 0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(entry_obj), 2);

    /* ===== Spin buttons ===== */
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_capacite), c.capacite);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour),     c.jour);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mois),     c.mois);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee),    c.annee);

    /* ===== Restriction médicale ===== */
    if (strcmp(c.restrictions_medicales, "Oui") == 0)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_restriction), TRUE);
    else
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_restriction), FALSE);

    /* === 5. Message de succès === */
    gtk_label_set_text(GTK_LABEL(label_sortie), "Cours trouvé !");

}


/*void
on_modifier_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *entry_id, *entry_nom, *entry_coach;
    GtkWidget *combo_type, *combo_public, *combo_intensite, *combo_obj;
    GtkWidget *combo_type_equi, *combo_centre, *combo_salle, *combo_duree;
    GtkWidget *spin_capacite, *spin_jour, *spin_mois, *spin_annee;
    GtkWidget *toggle_restric, *label_modif;

    cour nouv;
    int id;

    char type_txt[50], public_txt[50], intensite_txt[50], obj_txt[50];
    char type_equi_txt[50], centre_txt[50], salle_txt[50], duree_txt[50];

    /* --- Widgets --- */
   /* entry_id         = lookup_widget(GTK_WIDGET(button), "id");
    entry_nom        = lookup_widget(GTK_WIDGET(button), "nom");
    entry_coach      = lookup_widget(GTK_WIDGET(button), "coach");

    combo_type       = lookup_widget(GTK_WIDGET(button), "type");
    combo_public     = lookup_widget(GTK_WIDGET(button), "public_spec");
    combo_intensite  = lookup_widget(GTK_WIDGET(button), "intensite");
    combo_obj        = lookup_widget(GTK_WIDGET(button), "obj");

    combo_type_equi  = lookup_widget(GTK_WIDGET(button), "type_equi");
    combo_centre     = lookup_widget(GTK_WIDGET(button), "centre");
    combo_salle      = lookup_widget(GTK_WIDGET(button), "salle");
    combo_duree      = lookup_widget(GTK_WIDGET(button), "duree");

    spin_capacite    = lookup_widget(GTK_WIDGET(button), "capacite");
    spin_jour        = lookup_widget(GTK_WIDGET(button), "jour");
    spin_mois        = lookup_widget(GTK_WIDGET(button), "mois");
    spin_annee       = lookup_widget(GTK_WIDGET(button), "annee");

   /* toggle_restric   = lookup_widget(GTK_WIDGET(button), "restric_maladie");

    label_modif      = lookup_widget(GTK_WIDGET(button), "label_sortie");

    /* --- ID --- */
   /* id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
    nouv.id = id;

    /* --- Text --- */
   /* strcpy(nouv.nom_c, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    strcpy(nouv.coach, gtk_entry_get_text(GTK_ENTRY(entry_coach)));

    /* --- Combobox GTK2 --- */

   /* GtkTreeIter iter;
    GtkTreeModel *model;

    #define GET_COMBO_TEXT(widget, dest) \
        model = gtk_combo_box_get_model(GTK_COMBO_BOX(widget)); \
        if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(widget), &iter)) \
            gtk_tree_model_get(model, &iter, 0, dest, -1); \
        else strcpy(dest, "");

    GET_COMBO_TEXT(combo_type,        type_txt);
    GET_COMBO_TEXT(combo_public,      public_txt);
    GET_COMBO_TEXT(combo_intensite,   intensite_txt);
    GET_COMBO_TEXT(combo_obj,         obj_txt);
    GET_COMBO_TEXT(combo_type_equi,   type_equi_txt);
    GET_COMBO_TEXT(combo_centre,      centre_txt);
    GET_COMBO_TEXT(combo_salle,       salle_txt);
    GET_COMBO_TEXT(combo_duree,       duree_txt);

    strcpy(nouv.type_c,          type_txt);
    strcpy(nouv.public_cible,    public_txt);
    strcpy(nouv.intensite,       intensite_txt);
    strcpy(nouv.objectif,        obj_txt);
    strcpy(nouv.type_equipement, type_equi_txt);
    strcpy(nouv.centre,          centre_txt);
    strcpy(nouv.salle,           salle_txt);
    strcpy(nouv.duree,           duree_txt);

    /* --- Spin --- */
   /* nouv.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    nouv.jour     = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    nouv.mois     = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    nouv.annee    = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));

    /* --- Toggle --- */
   /* if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_restric)))
        strcpy(nouv.restrictions_medicales, "Oui");
    else
        strcpy(nouv.restrictions_medicales, "Non");

    /* --- Appel modification --- */
   /* if (modifier_cour("cour.txt", id, nouv))
        gtk_label_set_text(GTK_LABEL(label_modif), " Modification effectuée !");
    else
        gtk_label_set_text(GTK_LABEL(label_modif), " Erreur : cours introuvable !");



/*}*/


void
on_afficher_cours_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

    GtkWidget *ajout_cours;
    GtkWidget *gestion_admin;
    GtkWidget *treeview;

    // Récupérer la fenêtre ajout_cours et la cacher
    ajout_cours = lookup_widget(GTK_WIDGET(button), "ajout_cours");
    gtk_widget_hide(ajout_cours);

    // Ouvrir la fenêtre gestion_admin
    gestion_admin = create_gestion_admin();
    gtk_widget_show(gestion_admin);

    // Récupérer le treeview_cours
    treeview = lookup_widget(gestion_admin, "treeview_cours");
    if (treeview == NULL) {
        g_print("Erreur : widget 'treeview_cours' introuvable dans gestion_admin.\n");
        return;
    }

    // Charger les cours dans le treeview
    afficher_cour(treeview);


}


void
on_modifier_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

  GtkWidget *entry_id, *entry_nom, *entry_coach;
    GtkWidget *combo_type, *combo_public, *combo_intensite, *combo_obj;
    GtkWidget *combo_type_equi, *combo_centre, *combo_salle, *combo_duree;
    GtkWidget *spin_capacite, *spin_jour, *spin_mois, *spin_annee;
    GtkWidget *toggle_restric, *label_modif;

    cour nouv;
    int id;

    char type_txt[50], public_txt[50], intensite_txt[50], obj_txt[50];
    char type_equi_txt[50], centre_txt[50], salle_txt[50], duree_txt[50];

    /* --- Widgets --- */
    entry_id         = lookup_widget(GTK_WIDGET(button), "id");
    entry_nom        = lookup_widget(GTK_WIDGET(button), "nom");
    entry_coach      = lookup_widget(GTK_WIDGET(button), "coach");

    combo_type       = lookup_widget(GTK_WIDGET(button), "type");
    combo_public     = lookup_widget(GTK_WIDGET(button), "public_spec");
    combo_intensite  = lookup_widget(GTK_WIDGET(button), "intensite");
    combo_obj        = lookup_widget(GTK_WIDGET(button), "obj");

    combo_type_equi  = lookup_widget(GTK_WIDGET(button), "type_equi");
    combo_centre     = lookup_widget(GTK_WIDGET(button), "centre");
    combo_salle      = lookup_widget(GTK_WIDGET(button), "salle");
    combo_duree      = lookup_widget(GTK_WIDGET(button), "duree");

    spin_capacite    = lookup_widget(GTK_WIDGET(button), "capacite");
    spin_jour        = lookup_widget(GTK_WIDGET(button), "jour");
    spin_mois        = lookup_widget(GTK_WIDGET(button), "mois");
    spin_annee       = lookup_widget(GTK_WIDGET(button), "annee");

    toggle_restric   = lookup_widget(GTK_WIDGET(button), "restric_maladie");

    label_modif      = lookup_widget(GTK_WIDGET(button), "label_sortie");

    /* --- ID --- */
    id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
    nouv.id = id;

    /* --- Text --- */
    strcpy(nouv.nom_c, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    strcpy(nouv.coach, gtk_entry_get_text(GTK_ENTRY(entry_coach)));

    /* --- Combobox GTK2 --- */

    GtkTreeIter iter;
    GtkTreeModel *model;

   
#define GET_COMBO_TEXT(widget, dest)                     \
{                                                        \
    GtkTreeIter iter;                                    \
    GtkTreeModel *model =                               \
        gtk_combo_box_get_model(GTK_COMBO_BOX(widget)); \
    gchar *tmp = NULL;                                   \
                                                         \
    if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(widget), &iter)) \
    {                                                    \
        gtk_tree_model_get(model, &iter, 0, &tmp, -1);  \
        if (tmp)                                         \
        {                                                \
            strcpy(dest, tmp);                           \
            g_free(tmp);                                 \
        }                                                \
        else strcpy(dest, "");                           \
    }                                                    \
    else strcpy(dest, "");                               \
}


    GET_COMBO_TEXT(combo_type,        type_txt);
    GET_COMBO_TEXT(combo_public,      public_txt);
    GET_COMBO_TEXT(combo_intensite,   intensite_txt);
    GET_COMBO_TEXT(combo_obj,         obj_txt);
    GET_COMBO_TEXT(combo_type_equi,   type_equi_txt);
    GET_COMBO_TEXT(combo_centre,      centre_txt);
    GET_COMBO_TEXT(combo_salle,       salle_txt);
    GET_COMBO_TEXT(combo_duree,       duree_txt);

    strcpy(nouv.type_c,          type_txt);
    strcpy(nouv.public_cible,    public_txt);
    strcpy(nouv.intensite,       intensite_txt);
    strcpy(nouv.objectif,        obj_txt);
    strcpy(nouv.type_equipement, type_equi_txt);
    strcpy(nouv.centre,          centre_txt);
    strcpy(nouv.salle,           salle_txt);
    strcpy(nouv.duree,           duree_txt);

    /* --- Spin --- */
    nouv.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    nouv.jour     = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    nouv.mois     = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    nouv.annee    = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));

    /* --- Toggle --- */
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_restric)))
        strcpy(nouv.restrictions_medicales, "Oui");
    else
        strcpy(nouv.restrictions_medicales, "Non");

    /* --- Appel modification --- */
    if (modifier_cour("cour.txt", id, nouv))
        gtk_label_set_text(GTK_LABEL(label_modif), " Modification effectuée !");
    else
        gtk_label_set_text(GTK_LABEL(label_modif), " Erreur : cours introuvable !");

}


void
on_treeview_cours_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

    GtkTreeModel *model;
    GtkTreeIter iter;
    gint id;

    
    model = gtk_tree_view_get_model(treeview);
    if (model == NULL)
        return; /* sÃ©curitÃ© */

    
    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        
        gtk_tree_model_get(model, &iter,
                           COL_ID, &id,
                           -1);

        g_print("Suppression du membre avec ID = %d\n", id);

        
        supprimer_cour("cour.txt", id);

        
        GtkWidget *treeview_widget = GTK_WIDGET(treeview);

        vider_cours(treeview_widget);

        afficher_cour(treeview_widget);
    }
}


/*void
on_femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
   
}


void
on_homme_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
   
}*/


void
on_femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(togglebutton))
        sexe = 2;
}


void
on_homme__toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
        sexe = 1;
}



void
on_btn_valider_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{


    GtkWidget *window;
    GtkWidget *combo_duree;
    reservation r;
    int i;

    window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    combo_duree = lookup_widget(window, "duree");

    /* lire les champs */
    strcpy(r.type,
        gtk_combo_box_get_active_text(
            GTK_COMBO_BOX(lookup_widget(window,"type"))));

    strcpy(r.centre,
        gtk_combo_box_get_active_text(
            GTK_COMBO_BOX(lookup_widget(window,"centre"))));

    r.jour  = gtk_spin_button_get_value_as_int(
        GTK_SPIN_BUTTON(lookup_widget(window,"jour")));
    r.mois  = gtk_spin_button_get_value_as_int(
        GTK_SPIN_BUTTON(lookup_widget(window,"mois")));
    r.annee = gtk_spin_button_get_value_as_int(
        GTK_SPIN_BUTTON(lookup_widget(window,"annee")));

    r.sexe = sexe;
    r.restriction_med = restriction_med;

    /* rechercher cours compatibles */
    nb_cours_compatibles =
        rechercher_cours_compatibles(
            "cour.txt",
            r,
            cours_compatibles);

    /* vider combo durée */
    while (gtk_combo_box_get_active(
            GTK_COMBO_BOX(combo_duree)) != -1)
    {
        gtk_combo_box_remove_text(
            GTK_COMBO_BOX(combo_duree), 0);
    }

    if (nb_cours_compatibles == 0)
    {
        gtk_label_set_text(GTK_LABEL(
            lookup_widget(window,"sortie")),
            "Aucun cours compatible");
        return;
    }

    /* remplir combo durée */
    for (i = 0; i < nb_cours_compatibles; i++)
    {
        gtk_combo_box_append_text(
            GTK_COMBO_BOX(combo_duree),
            cours_compatibles[i].duree);
    }

    gtk_label_set_text(GTK_LABEL(
        lookup_widget(window,"sortie")),
        "Choisissez une durée puis cliquez sur Remplir");



}


void
on_btn_calculer_stats_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

    int h = 0, f = 0;
    char txt[20];

    calculer_stats_sexe("cour.txt", &h, &f);

    sprintf(txt, "%d", h);
    gtk_entry_set_text(GTK_ENTRY(
        lookup_widget(GTK_WIDGET(button),"entry_hommes")), txt);

    sprintf(txt, "%d", f);
    gtk_entry_set_text(GTK_ENTRY(
        lookup_widget(GTK_WIDGET(button),"entry_femmes")), txt);

}


void
on_btn_graphique_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{

    GtkWidget *window, *drawing;

    calculer_stats_centres("cour.txt");   

    window = create_window_graphique();
    gtk_widget_show(window);

    drawing = lookup_widget(window, "drawingarea1");
    gtk_widget_queue_draw(drawing);

}


void
on_btn_retour_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

    GtkWidget *window_actuelle;
    GtkWidget *gestion_admin;

    
    window_actuelle = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window_actuelle);

   
    gestion_admin = create_gestion_admin();
    gtk_widget_show(gestion_admin);

}


gboolean
on_drawingarea1_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{


    cairo_t *cr = gdk_cairo_create(widget->window);

    int x = 50, y = 300, largeur = 60;

    for (int i = 0; i < nb_centres; i++)
    {
        cairo_set_source_rgb(cr, 0.3, 0.6, 0.9);
        cairo_rectangle(cr, x, y - tab[i].nb * 40,
                         largeur, tab[i].nb * 40);
        cairo_fill(cr);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, x, y + 15);
        cairo_show_text(cr, tab[i].centre);

        char txt[10];
        sprintf(txt, "%d", tab[i].nb);
        cairo_move_to(cr, x + 15, y - tab[i].nb * 40 - 5);
        cairo_show_text(cr, txt);

        x += 100;
    }

    cairo_destroy(cr);
    return FALSE;


}






void
on_btn_actualiser_cours_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{


    GtkWidget *window;
    GtkWidget *treeview;

   
    window = gtk_widget_get_toplevel(GTK_WIDGET(button));

   
    treeview = lookup_widget(window, "treeview_cours");
    if (treeview == NULL)
    {
        g_print("Erreur : treeview_cours introuvable\n");
        return;
    }

   
    afficher_cour(treeview);



}


void
on_btn_remplir_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

    GtkWidget *window;
    GtkWidget *combo_duree;
    gchar *duree;
    int i;

    window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    combo_duree = lookup_widget(window, "duree");

    duree = gtk_combo_box_get_active_text(
                GTK_COMBO_BOX(combo_duree));

    if (!duree)
        return;

    for (i = 0; i < nb_cours_compatibles; i++)
    {
        if (strcmp(
                cours_compatibles[i].duree,
                duree) == 0)
        {
            cour_trouve = cours_compatibles[i];

            gtk_entry_set_text(GTK_ENTRY(
                lookup_widget(window,"salle")),
                cour_trouve.salle);

            gtk_entry_set_text(GTK_ENTRY(
                lookup_widget(window,"intensite")),
                cour_trouve.intensite);

            gtk_entry_set_text(GTK_ENTRY(
                lookup_widget(window,"publique_specifique")),
                cour_trouve.public_cible);

            gtk_entry_set_text(GTK_ENTRY(
                lookup_widget(window,"objectif")),
                cour_trouve.objectif);

            break;
        }
    }

}


void
on_btn_login_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

char username[40];
char id_profil[20];
char taille_profil[20];
int id;
int trouve = 0;
membre m;
GtkWidget *label_nom ;
GtkWidget *label_prenom ;
GtkWidget *label_id ;
GtkWidget *label_taille ;
GtkWidget *entry_username,*entry_id,*output;
entry_username = lookup_widget(GTK_WIDGET(button), "entry_username_login");
entry_id = lookup_widget(GTK_WIDGET(button), "entry_mdp_login");
output = lookup_widget(GTK_WIDGET(button), "label_succes_login");
strcpy(username, gtk_entry_get_text(GTK_ENTRY(entry_username)));
id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
FILE *f = fopen("membre.txt", "r");
    if (f == NULL) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur fichier !");
        return;
    }

    while (fscanf(f, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %d %d",
                  &m.id, m.nom, m.prenom, m.centre, m.email,
                  &m.jour, m.mois, &m.annee, m.type_abonnement,
                  &m.poids, &m.masse_musculaire, &m.masse_graisseuse,
                  m.sexe, &m.taille, m.objectif,
                  m.descr_maladie, m.num_tel, &m.duree_prog, &m.maladie) != EOF)
    {
        if (strcmp(m.nom, username) == 0 && m.id == id) {
            trouve = 1;
            break;
        }
    }

    fclose(f);

    if (trouve) {
        gtk_label_set_text(GTK_LABEL(output), "Connexion réussie !");

        
       GtkWidget *Login_users = lookup_widget(GTK_WIDGET(button), "window_login");
       GtkWidget *Profil_membre = create_Profil_membre();

        gtk_widget_show(Profil_membre);
        gtk_widget_hide(Login_users);
	label_nom = lookup_widget(Profil_membre, "label_nom_membre_profil");
        label_prenom = lookup_widget(Profil_membre, "label_prenom_membre_profil");
        label_id = lookup_widget(Profil_membre, "label_id_membre_profil");
        label_taille = lookup_widget(Profil_membre, "label_taille_membre_profil");
	sprintf(id_profil, "%d", m.id);
        sprintf(taille_profil, "%d", m.taille);
	gtk_label_set_text(GTK_LABEL(label_nom), m.nom);
        gtk_label_set_text(GTK_LABEL(label_prenom), m.prenom);
        gtk_label_set_text(GTK_LABEL(label_id), id_profil);
        gtk_label_set_text(GTK_LABEL(label_taille), taille_profil);
    }
    else {
        gtk_label_set_text(GTK_LABEL(output), "Identifiants incorrects !");
    }
}

