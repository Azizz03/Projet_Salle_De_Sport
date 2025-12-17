#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "event.h"
#include <errno.h>
#include <limits.h> 
#include <glib.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"

typedef event EVENT;


#define EVENT_FILENAME "event.txt"
#define PARTICIPATION_FILENAME "participations.txt"


// Variables globales (à définir dans votre fichier callbacks.c ou .h)
int current_event_id = -1;
int last_selected_id = -1;

void on_treeview9_selection_changed(GtkTreeSelection *selection, gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;

    // 1. Vérifier si une ligne est réellement sélectionnée
    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        current_event_id = -1;
        last_selected_id = -1;
        return; 
    }

    // 2. Variables temporaires pour extraire les données du modèle
    gchar *temp_nom = NULL, *temp_type = NULL, *temp_salle = NULL;
    gfloat temp_prix = 0.0;
    EVENT e;
    memset(&e, 0, sizeof(EVENT));

    // 3. Récupération des données (Assurez-vous que les indices 0-11 sont corrects)
    gtk_tree_model_get(model, &iter,
        0,  &current_event_id, 
        1,  &temp_nom,         
        2,  &temp_type,        
        3,  &e.jour,
        4,  &e.mois,
        5,  &e.annee,
        6,  &e.heure_debut_h,
        7,  &e.heure_debut_m,
        8,  &e.heure_fin_h,
        9,  &e.heure_fin_m,
        10, &temp_prix,
        11, &temp_salle,      
        -1
    );
    e.prix = temp_prix;

    // 4. Éviter d'ouvrir la fenêtre deux fois pour la même sélection
    if (current_event_id == last_selected_id)
    {
        // On libère quand même les chaînes extraites par gtk_tree_model_get
        g_free(temp_nom); g_free(temp_type); g_free(temp_salle);
        return;
    }
    last_selected_id = current_event_id;

    // 5. Copie vers la structure EVENT (nettoyage des gchar*)
    if (temp_nom) strncpy(e.nom, temp_nom, sizeof(e.nom) - 1);
    if (temp_type) strncpy(e.type, temp_type, sizeof(e.type) - 1);
    if (temp_salle) strncpy(e.salle, temp_salle, sizeof(e.salle) - 1);

    // 6. Ouverture de l'interface
    GtkWidget *win = create_ajouter_event(); 
    
    if (win) {
        gtk_window_set_title(GTK_WINDOW(win), "Modifier l'évènement");

        // --- Pré-remplissage des champs standards ---
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(win, "entry_nom_event")), e.nom);
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(win, "entry_salle_event")), e.salle);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_prix_event")), e.prix);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_jour_event")), e.jour);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_annee_event")), e.annee);
        
        // --- Pré-remplissage des heures ---
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_debut_h")), e.heure_debut_h);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_debut_m")), e.heure_debut_m);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_fin_h")), e.heure_fin_h);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_fin_m")), e.heure_fin_m);

        // --- Pré-remplissage ComboBox TYPE ---
        GtkWidget *cb_type = lookup_widget(win, "combo_type_event");
        if (cb_type) {
            GtkTreeModel *m = gtk_combo_box_get_model(GTK_COMBO_BOX(cb_type));
            GtkTreeIter it;
            if (gtk_tree_model_get_iter_first(m, &it)) {
                do {
                    gchar *txt;
                    gtk_tree_model_get(m, &it, 0, &txt, -1);
                    if (g_strcmp0(txt, e.type) == 0) {
                        gtk_combo_box_set_active_iter(GTK_COMBO_BOX(cb_type), &it);
                        g_free(txt); break;
                    }
                    g_free(txt);
                } while (gtk_tree_model_iter_next(m, &it));
            }
        }

        // --- Pré-remplissage ComboBox MOIS ---
        GtkWidget *cb_mois = lookup_widget(win, "combo_mois_event");
        if (cb_mois) {
            // Astuce : Si votre combo mois est juste une liste de 1 à 12, 
            // vous pouvez utiliser l'index directement (index = mois - 1)
            gtk_combo_box_set_active(GTK_COMBO_BOX(cb_mois), e.mois - 1);
        }

        gtk_widget_show_all(win);
    }

    // 7. LIBÉRATION OBLIGATOIRE (pour éviter les fuites de mémoire RAM)
    g_free(temp_nom);
    g_free(temp_type);
    g_free(temp_salle);
}

static char *gvalue_to_string(GtkTreeModel *model, GtkTreeIter *iter, gint col)
{
    GValue v = G_VALUE_INIT;
    char *res = NULL;

    gtk_tree_model_get_value(model, iter, col, &v);

    if (G_VALUE_HOLDS_STRING(&v)) {
        res = g_value_dup_string(&v);
    }
    else if (G_VALUE_HOLDS_INT(&v) || G_VALUE_HOLDS_LONG(&v)) {
        gint n = g_value_get_int(&v);
        res = g_strdup_printf("%d", n);
    }
    else if (G_VALUE_HOLDS_DOUBLE(&v) || G_VALUE_HOLDS_FLOAT(&v)) {
        double d = g_value_get_double(&v);
        res = g_strdup_printf("%.2f", d);
    }
    else if (G_VALUE_HOLDS_UINT(&v)) {
        guint u = g_value_get_uint(&v);
        res = g_strdup_printf("%u", u);
    }
    else {
        /* type inconnu ou non convertissable : renvoyer une chaîne explicite */
        res = g_strdup("<inconvertible>");
    }

    g_value_unset(&v);
    return res; /* caller doit g_free() */
}


int id_event_selectionne = -1;


char sexe_membre[10] = "";



void
on_button_event_clicked (GtkButton *button, gpointer user_data)
{
    GtkWidget *win = lookup_widget(GTK_WIDGET(button), "ajout_event");
    if (win)
        gtk_widget_show_all(win);
    (void)user_data;
}

void
on_button_ajouter_event_clicked (GtkButton *button, gpointer user_data)
{
     GtkWidget *win_gestion;
    GtkWidget *win_ajout;

    
    win_gestion = lookup_widget(GTK_WIDGET(button), "liste_admin_gestion");

   
    win_ajout = create_ajouter_event();

    
    if (win_gestion)
        gtk_widget_hide(win_gestion);

   
    if (win_ajout)
        gtk_widget_show(win_ajout);

    (void)user_data;
}

void
on_button_valider_clicked (GtkButton *button, gpointer user_data)
{
    
    on_button_valider_event_clicked(button, user_data);
}





void
on_button_participer_event_clicked (GtkButton *button, gpointer user_data)
{
    GtkWidget *w_nom     = lookup_widget(GTK_WIDGET(button), "entry_nom_membre");
    GtkWidget *w_prenom  = lookup_widget(GTK_WIDGET(button), "entry_prenom_membre");
    GtkWidget *w_radio_h = lookup_widget(GTK_WIDGET(button), "radio_homme_membre");
    GtkWidget *w_radio_f = lookup_widget(GTK_WIDGET(button), "radio_femme_membre");
    GtkWidget *w_prix    = lookup_widget(GTK_WIDGET(button), "spin_prix_event_membre");
    GtkWidget *w_salle   = lookup_widget(GTK_WIDGET(button), "entry_salle_event_membre");
    
    /* --- AJOUT DES WIDGETS DE NIVEAU --- */
    GtkWidget *w_debutant     = lookup_widget(GTK_WIDGET(button), "check_debutant");
    GtkWidget *w_intermediaire = lookup_widget(GTK_WIDGET(button), "check_intermediaire");
    GtkWidget *w_avance       = lookup_widget(GTK_WIDGET(button), "check_avance");

    if (!w_nom || !w_prenom) {
        GtkWidget *dlg = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
                                                "Widgets de participation introuvables.");
        gtk_dialog_run(GTK_DIALOG(dlg));
        gtk_widget_destroy(dlg);
        return;
    }

    participation p;
    memset(&p, 0, sizeof(p));

    p.id_event   = 0;
    p.id_membre  = 0;

    const char *nomtxt    = gtk_entry_get_text(GTK_ENTRY(w_nom));
    const char *prenomtxt = gtk_entry_get_text(GTK_ENTRY(w_prenom));
    strncpy(p.nom,    nomtxt    ? nomtxt    : "", sizeof(p.nom)-1);
    p.nom[sizeof(p.nom)-1] = '\0';
    strncpy(p.prenom, prenomtxt ? prenomtxt : "", sizeof(p.prenom)-1);
    p.prenom[sizeof(p.prenom)-1] = '\0';

    if (w_radio_h && GTK_IS_TOGGLE_BUTTON(w_radio_h) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w_radio_h))) {
        strncpy(p.sexe, "Homme", sizeof(p.sexe)-1);
        p.sexe[sizeof(p.sexe)-1] = '\0';
    } else if (w_radio_f && GTK_IS_TOGGLE_BUTTON(w_radio_f) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w_radio_f))) {
        strncpy(p.sexe, "Femme", sizeof(p.sexe)-1);
        p.sexe[sizeof(p.sexe)-1] = '\0';
    } else {
        p.sexe[0] = '\0';
    }

    /* --- TRAITEMENT DES CASES À COCHER (D'après TD Salade de fruits) --- */
    char niveau_str[100] = "";
    if (w_debutant && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w_debutant))) {
        strcat(niveau_str, "Débutant ");
    }
    if (w_intermediaire && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w_intermediaire))) {
        strcat(niveau_str, "Intermédiaire ");
    }
    if (w_avance && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w_avance))) {
        strcat(niveau_str, "Avancé ");
    }
    
    // Note : Si vous voulez stocker ce texte dans votre structure participation, 
    // assurez-vous d'avoir un champ suffisant (ex: p.niveau) dans votre .h

    if (w_prix && GTK_IS_SPIN_BUTTON(w_prix))
        p.prix = (float)gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_prix));

    if (w_salle && GTK_IS_ENTRY(w_salle)) {
        strncpy(p.salle, gtk_entry_get_text(GTK_ENTRY(w_salle)), sizeof(p.salle)-1);
        p.salle[sizeof(p.salle)-1] = '\0';
    } else {
        p.salle[0] = '\0';
    }

    int ok = ajouter_participation(PARTICIPATION_FILENAME, p);

    GtkWidget *dlg = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
                                            ok ? GTK_MESSAGE_INFO : GTK_MESSAGE_ERROR,
                                            GTK_BUTTONS_OK,
                                            ok ? "Participation enregistrée." : "Erreur d'enregistrement.");
    gtk_dialog_run(GTK_DIALOG(dlg));
    gtk_widget_destroy(dlg);

    (void)button; (void)user_data;
}









void
on_radio_femme_membre_toggled (GtkToggleButton *togglebutton,
                               gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
        strcpy(sexe_membre, "Femme");
        g_print("Sexe membre = %s\n", sexe_membre);
    }
    (void)user_data;
}

void
on_radio_homme_membre_toggled (GtkToggleButton *togglebutton,
                               gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
    {
        strcpy(sexe_membre, "Homme");
        g_print("Sexe membre = %s\n", sexe_membre);
    }
    (void)user_data;
}




















void on_button_login_clicked(GtkButton *button, gpointer user_data) {
    // Récupération de la fenêtre actuelle (Login)
    GtkWidget *fenetre_login = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    // Déclarations des variables locales
    char login[50], password[50];
    GtkWidget *input_user = lookup_widget(fenetre_login, "entry_username"); //
    GtkWidget *input_pass = lookup_widget(fenetre_login, "entry_password"); //
    GtkWidget *label_msg = lookup_widget(fenetre_login, "label296"); // Label pour messages d'erreur

    // 1. Extraction du texte des champs de saisie
    strcpy(login, gtk_entry_get_text(GTK_ENTRY(input_user)));
    strcpy(password, gtk_entry_get_text(GTK_ENTRY(input_pass)));

    // 2. Appel de la fonction de vérification
    int role = verifier(login, password);

    // 3. Traitement selon le résultat
    if (role != -1) {
        // Succès : On ferme la fenêtre de login
        gtk_widget_hide(fenetre_login);

        // Redirection vers l'interface appropriée selon le rôle
        if (role == 1) {
            // Création de l'Espace Administrateur
            GtkWidget *win_admin = create_gestion_admin(); 
            gtk_widget_show_all(win_admin);
        } 
        else if (role == 2) {
            // Création de l'Espace Membre
            GtkWidget *win_membre = create_Profil_membre(); 
            gtk_widget_show_all(win_membre);
        }
        else if (role == 3) {
            // Création de l'Espace Entraîneur
            GtkWidget *win_coach = create_profil_entraineur();
            gtk_widget_show_all(win_coach);
        }
    } 
    else {
        // Échec : On informe l'utilisateur sans fermer la fenêtre
        if (label_msg) {
            gtk_label_set_markup(GTK_LABEL(label_msg), 
                "<span foreground='red' size='medium'><b>Accès refusé :</b> Identifiants incorrects.</span>");
        }
        // Optionnel : Vider le champ mot de passe pour des raisons de sécurité
        gtk_entry_set_text(GTK_ENTRY(input_pass), "");
    }
}



void
on_button_Afficher_clicked (GtkButton *button, gpointer user_data)
{
    
    GtkWidget *win_aff = create_Afficher_event();

    if (!win_aff) {
        g_warning("Impossible de créer Afficher_event");
        return;
    }

    gtk_widget_show_all(win_aff);

    g_print(">> Bouton Afficher : fenêtre Afficher_event créée et affichée.\n");

    (void)button;
    (void)user_data;
}


    
 void
on_button_actualiser_clicked (GtkButton *button, gpointer user_data)
{
    GtkWidget *win_afficher;
    GtkWidget *treeview;

    g_print(">> on_button_actualiser_clicked()\n");

    
    win_afficher = gtk_widget_get_toplevel(GTK_WIDGET(button));

    
    treeview = lookup_widget(win_afficher, "treeview9");
    if (!treeview) {
        g_warning("treeview9 introuvable dans Afficher_event");
        return;
    }

    if (!GTK_IS_TREE_VIEW(treeview)) {
        g_warning("treeview9 n’est pas un GtkTreeView");
        return;
    }

    
    afficher_event_treeview(treeview, EVENT_FILENAME);

    (void)user_data;
}
  

void
on_button_retour_clicked (GtkButton *button, gpointer user_data)
{
    GtkWidget *win_aff = gtk_widget_get_toplevel(GTK_WIDGET(button));

    g_print(">> Retour : on ferme Afficher_event et on revient à gestion_admin.\n");

    if (win_aff)
        gtk_widget_destroy(win_aff);

    GtkWidget *win_gest = create_gestion_admin();
    if (win_gest)
        gtk_widget_show_all(win_gest);

    (void)user_data;
}


gboolean on_treeview9_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
    // 1. Réagir uniquement au clic gauche simple
    if (event->type != GDK_BUTTON_PRESS || event->button != 1)
        return FALSE;

    GtkTreeView *treeview = GTK_TREE_VIEW(widget);
    GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
    GtkTreeModel *model;
    GtkTreeIter iter;

    // 2. Vérifier si une ligne est sélectionnée
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) 
    {
        gchar *temp_nom = NULL, *temp_type = NULL, *temp_salle = NULL;
        int j, m, a, hd, md, hf, mf;
        float prix;

        // 3. Extraction des données du modèle (Ordre des colonnes à vérifier selon votre ListStore)
        gtk_tree_model_get(model, &iter,
            0,  &current_event_id, 
            1,  &temp_nom,        
            2,  &temp_type,       
            3,  &j, 
            4,  &m, 
            5,  &a,
            6,  &hd, 
            7,  &md, 
            8,  &hf, 
            9,  &mf,
            10, &prix, 
            11, &temp_salle,     
            -1);

        // 4. Création de la fenêtre d'ajout
        GtkWidget *win = create_ajouter_event(); 
        if (!win) return FALSE;

        // Modifier le titre pour indiquer la modification
        gtk_window_set_title(GTK_WINDOW(win), "Modifier l'événement");

        // 5. PRÉ-REMPLISSAGE DES WIDGETS
        
        // Champs Texte
        if (temp_nom) gtk_entry_set_text(GTK_ENTRY(lookup_widget(win, "entry_nom_event")), temp_nom);
        if (temp_salle) gtk_entry_set_text(GTK_ENTRY(lookup_widget(win, "entry_salle_event")), temp_salle);

        // SpinButtons (Nombres)
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_prix_event")), (double)prix);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_jour_event")), (double)j);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_annee_event")), (double)a);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_debut_h")), (double)hd);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_debut_m")), (double)md);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_fin_h")), (double)hf);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_fin_m")), (double)mf);

        // ComboBox MOIS (Sélection par index : 1=Janvier -> Index 0)
        GtkWidget *combo_mois = lookup_widget(win, "combo_mois_event");
        if (combo_mois) gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), m - 1);

        // ComboBox TYPE (Recherche par texte)
        GtkWidget *w_type = lookup_widget(win, "combo_type_event");
        if (w_type && temp_type) {
            GtkComboBox *combo_t = GTK_COMBO_BOX(w_type);
            GtkTreeModel *m_type = gtk_combo_box_get_model(combo_t);
            GtkTreeIter it_t;
            if (gtk_tree_model_get_iter_first(m_type, &it_t)) {
                do {
                    gchar *txt;
                    gtk_tree_model_get(m_type, &it_t, 0, &txt, -1);
                    if (g_strcmp0(txt, temp_type) == 0) {
                        gtk_combo_box_set_active_iter(combo_t, &it_t);
                        g_free(txt);
                        break;
                    }
                    g_free(txt);
                } while (gtk_tree_model_iter_next(m_type, &it_t));
            }
        }

        // 6. Afficher la fenêtre remplie
        gtk_widget_show_all(win);

        // 7. Libération de la mémoire
        if (temp_nom) g_free(temp_nom);
        if (temp_type) g_free(temp_type);
        if (temp_salle) g_free(temp_salle);
    }

    return FALSE;
}

/// Appelée après la création de la fenêtre "Afficher_event"
// Cette fonction doit être appelée dans main.c, après le chargement de l'interface.
void setup_treeview_signals(GtkWidget *fenetre_afficher_event)
{
    GtkTreeView *treeview9 = GTK_TREE_VIEW(lookup_widget(fenetre_afficher_event, "treeview9"));

    if (treeview9) {
        // --- CONNEXION POUR LE SIMPLE CLIC (MODIFICATION) ---
        GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview9);
        
        g_signal_connect(G_OBJECT(selection), "changed",
                         G_CALLBACK(on_treeview9_selection_changed),
                         fenetre_afficher_event); 
        
        // --- CONNEXION POUR LE DOUBLE CLIC (SUPPRESSION) ---
        // Si vous voulez la suppression par double clic, laissez ceci :
        g_signal_connect(G_OBJECT(treeview9), "row-activated",
                         G_CALLBACK(on_treeview9_row_activated),
                         fenetre_afficher_event); 
    }
}
void on_treeview9_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    GtkTreeIter iter;

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        // 1. Création d'une boîte de dialogue avec des boutons d'action
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(treeview))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_NONE,
            "Quelle action souhaitez-vous effectuer ?");

        gtk_dialog_add_buttons(GTK_DIALOG(dialog),
                               "Modifier l'événement", 1,
                               "Supprimer l'événement", 2,
                               "Annuler", GTK_RESPONSE_CANCEL,
                               NULL);

        gint result = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // 2. Traitement du choix
        if (result == 1) {
            // Appelle votre logique de modification existante
            GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
            on_treeview9_selection_changed(selection, NULL);
        } 
        else if (result == 2) {
            // --- LOGIQUE DE SUPPRESSION ---
            int id_a_supprimer;
            gtk_tree_model_get(model, &iter, 0, &id_a_supprimer, -1);
            
            // Appel de la fonction de fichier
            if (supprimer_event("event.txt", id_a_supprimer)) {
                // Rafraîchissement immédiat de la liste
                rafraichir_liste_event(GTK_WIDGET(treeview), "event.txt");
                
                // Message de succès
                GtkWidget *msg = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO,
                                                       GTK_BUTTONS_OK, "Événement ID %d supprimé.", id_a_supprimer);
                gtk_dialog_run(GTK_DIALOG(msg));
                gtk_widget_destroy(msg);
            }
        }
    }
}

void
on_button_valider_event_clicked (GtkButton *button, gpointer user_data)
{
    GtkWidget *w_nom  = lookup_widget(GTK_WIDGET(button), "entry_nom_event");
    GtkWidget *w_type = lookup_widget(GTK_WIDGET(button), "combo_type_event");
    if (!w_type)
        w_type = lookup_widget(GTK_WIDGET(button), "entry_type_event");

    GtkWidget *w_jour = lookup_widget(GTK_WIDGET(button), "spin_jour_event");
    GtkWidget *w_mois = lookup_widget(GTK_WIDGET(button), "combo_mois_event");
    if (!w_mois)
        w_mois = lookup_widget(GTK_WIDGET(button), "spin_mois_event");

    GtkWidget *w_annee  = lookup_widget(GTK_WIDGET(button), "spin_annee_event");
    GtkWidget *w_hdeb_h = lookup_widget(GTK_WIDGET(button), "spin_heure_debut_h");
    GtkWidget *w_hdeb_m = lookup_widget(GTK_WIDGET(button), "spin_heure_debut_m");
    GtkWidget *w_hfin_h = lookup_widget(GTK_WIDGET(button), "spin_heure_fin_h");
    GtkWidget *w_hfin_m = lookup_widget(GTK_WIDGET(button), "spin_heure_fin_m");
    GtkWidget *w_prix   = lookup_widget(GTK_WIDGET(button), "spin_prix_event");
    GtkWidget *w_salle  = lookup_widget(GTK_WIDGET(button), "entry_salle_event");

   
    event e;
    memset(&e, 0, sizeof(e));
    e.id = (int)time(NULL);  

   
    if (w_nom && GTK_IS_ENTRY(w_nom)) {
        const char *nom = gtk_entry_get_text(GTK_ENTRY(w_nom));
        strncpy(e.nom, nom ? nom : "", sizeof(e.nom)-1);
        e.nom[sizeof(e.nom)-1] = '\0';
    }

   
    if (w_type && GTK_IS_COMBO_BOX_TEXT(w_type)) {
        gchar *t = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(w_type));
        if (t) {
            strncpy(e.type, t, sizeof(e.type)-1);
            e.type[sizeof(e.type)-1] = '\0';
            g_free(t);
        }
    } else if (w_type && GTK_IS_ENTRY(w_type)) {
        const char *tt = gtk_entry_get_text(GTK_ENTRY(w_type));
        strncpy(e.type, tt ? tt : "", sizeof(e.type)-1);
        e.type[sizeof(e.type)-1] = '\0';
    }

    /* ---- date ---- */
    if (w_jour && GTK_IS_SPIN_BUTTON(w_jour))
        e.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_jour));

    if (w_mois && GTK_IS_COMBO_BOX_TEXT(w_mois)) {
        gchar *m = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(w_mois));
        e.mois = m ? atoi(m) : 0;
        if (m) g_free(m);
    } else if (w_mois && GTK_IS_SPIN_BUTTON(w_mois)) {
        e.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_mois));
    }

    if (w_annee && GTK_IS_SPIN_BUTTON(w_annee))
        e.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_annee));

    
    if (w_hdeb_h && GTK_IS_SPIN_BUTTON(w_hdeb_h))
        e.heure_debut_h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_hdeb_h));
    if (w_hdeb_m && GTK_IS_SPIN_BUTTON(w_hdeb_m))
        e.heure_debut_m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_hdeb_m));
    if (w_hfin_h && GTK_IS_SPIN_BUTTON(w_hfin_h))
        e.heure_fin_h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_hfin_h));
    if (w_hfin_m && GTK_IS_SPIN_BUTTON(w_hfin_m))
        e.heure_fin_m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(w_hfin_m));

    
    if (w_prix && GTK_IS_SPIN_BUTTON(w_prix))
        e.prix = (float)gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_prix));

   
    if (w_salle && GTK_IS_ENTRY(w_salle)) {
        const char *s = gtk_entry_get_text(GTK_ENTRY(w_salle));
        strncpy(e.salle, s ? s : "", sizeof(e.salle)-1);
        e.salle[sizeof(e.salle)-1] = '\0';
    }

    e.capacite = 100;  

   
    int ok = ajouter_event(EVENT_FILENAME, e);

    GtkWidget *dlg = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL,
        ok ? GTK_MESSAGE_INFO : GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        ok ? "Évènement ajouté et enregistré dans event.txt."
           : "Erreur : impossible d'écrire dans event.txt."
    );
    gtk_dialog_run(GTK_DIALOG(dlg));
    gtk_widget_destroy(dlg);

    
    GtkWidget *win = lookup_widget(GTK_WIDGET(button), "ajout_event");
    if (win)
        gtk_widget_hide(win);

    (void)user_data;
/* après int ok = ajouter_event(...); et après la boîte de dialogue */

if (ok) {
    /* chercher la fenêtre Afficher_event parmi les toplevels */
    GList *tops = gtk_window_list_toplevels();
    for (GList *l = tops; l != NULL; l = l->next) {
        GtkWidget *w = GTK_WIDGET(l->data);
        const gchar *name = gtk_widget_get_name(w);
        if (name && g_strcmp0(name, "Afficher_event") == 0) {
            /* on a trouvé la fenêtre d'affichage ouverte */
            GtkWidget *tree = lookup_widget(w, "treeview9");
            if (tree && GTK_IS_TREE_VIEW(tree)) {
                afficher_event_treeview(tree, EVENT_FILENAME);
            } else {
                g_warning("on_button_valider_event_clicked: treeview9 non trouvé dans Afficher_event");
            }
            break; /* on a rafraîchi, on peut sortir */
        }
    }
    g_list_free(tops);
}

}



void
on_button_rechercher_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *win = GTK_WIDGET(gtk_widget_get_toplevel(GTK_WIDGET(button)));
    GtkWidget *entry = NULL;
    GtkWidget *treeview = NULL;
    GtkWidget *label_result = NULL; /* label pour afficher le message dans l'UI */
    const gchar *txt;

    GtkTreeModel *model;
    GtkTreeIter iter;
    gboolean valid;
    gboolean found = FALSE;

    /* RÉCUP: adapte ces noms si besoin selon ton Glade */
    entry = lookup_widget(win, "entry_id_rech_event");
    treeview = lookup_widget(win, "treeview9");
    label_result = lookup_widget(win, "label_rech_result"); /* OPTIONAL : label dans Glade */

    if (!entry) {
        g_warning("entry_id_rech_event introuvable.");
        return;
    }
    if (!treeview) {
        g_warning("treeview9 introuvable.");
        return;
    }

    txt = gtk_entry_get_text(GTK_ENTRY(entry));
    if (!txt || txt[0] == '\0') {
        /* on affiche aussi si label présent */
        if (label_result) gtk_label_set_text(GTK_LABEL(label_result), "Veuillez saisir un ID à rechercher.");
        else {
            GtkWidget *dlg = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                    "Veuillez saisir un ID à rechercher.");
            gtk_dialog_run(GTK_DIALOG(dlg));
            gtk_widget_destroy(dlg);
        }
        return;
    }

    model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (!model) {
        g_warning("Le TreeView n'a pas de modèle.");
        return;
    }

    valid = gtk_tree_model_get_iter_first(model, &iter);
    while (valid) {
        char *id_as_str = gvalue_to_string(model, &iter, 0); /* colonne 0 = ID (adapter si nécessaire) */

        if (id_as_str != NULL && g_strcmp0(id_as_str, txt) == 0) {
            /* sélectionner la ligne trouvée */
            GtkTreeSelection *sel = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
            if (sel) gtk_tree_selection_select_iter(sel, &iter);

            /* faire défiler pour rendre visible */
            {
                GtkTreePath *path = gtk_tree_model_get_path(model, &iter);
                gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(treeview), path, NULL, TRUE, 0.5, 0.0);
                gtk_tree_path_free(path);
            }

            /* construire un message de résultat compréhensible */
            char *c0 = NULL, *c1 = NULL, *c2 = NULL, *c3 = NULL;
            c0 = gvalue_to_string(model, &iter, 0); /* ID */
            c1 = gvalue_to_string(model, &iter, 1); /* Nom (ex) */
            c2 = gvalue_to_string(model, &iter, 2); /* Type (ex) */
            c3 = gvalue_to_string(model, &iter, 3); /* Date/Heure etc. */

            gchar *msg = g_strdup_printf("Évènement avec l'ID %s trouvé.\nID:%s\nNom:%s\nType:%s\n%s",
                                         txt,
                                         c0?c0:"<null>",
                                         c1?c1:"<null>",
                                         c2?c2:"<null>",
                                         c3?c3:"");

            /* --- OPTION A : afficher DANS L'UI via un label (recommandé) --- */
            if (label_result) {
                gtk_label_set_text(GTK_LABEL(label_result), msg);
            } else {
                /* --- OPTION B : boîte de dialogue si pas de label --- */
                GtkWidget *dlg = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                        "%s", msg);
                gtk_dialog_run(GTK_DIALOG(dlg));
                gtk_widget_destroy(dlg);
            }

            /* nettoyage */
            g_free(msg);
            if (id_as_str) g_free(id_as_str);
            if (c0) g_free(c0);
            if (c1) g_free(c1);
            if (c2) g_free(c2);
            if (c3) g_free(c3);

            found = TRUE;
            break; /* stop après 1er trouvé */
        }

        if (id_as_str) g_free(id_as_str);
        valid = gtk_tree_model_iter_next(model, &iter);
    }

    if (!found) {
        const gchar *notfound = g_strdup_printf("Aucun évènement avec l'ID %s.", txt);
        if (label_result) {
            gtk_label_set_text(GTK_LABEL(label_result), notfound);
        } else {
            GtkWidget *dlg = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                                    "%s", notfound);
            gtk_dialog_run(GTK_DIALOG(dlg));
            gtk_widget_destroy(dlg);
        }
        g_free((gchar*)notfound);
    }

    (void)user_data;
}



 
void on_button_inscription_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *fenetre_insc = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    // Récupération des données
    const char *nom = gtk_entry_get_text(GTK_ENTRY(lookup_widget(fenetre_insc, "entry_nom")));
    const char *prenom = gtk_entry_get_text(GTK_ENTRY(lookup_widget(fenetre_insc, "entry_prenom")));
    const char *user = gtk_entry_get_text(GTK_ENTRY(lookup_widget(fenetre_insc, "entry_username")));
    const char *pass = gtk_entry_get_text(GTK_ENTRY(lookup_widget(fenetre_insc, "entry_password")));
    const char *role_str = gtk_entry_get_text(GTK_ENTRY(lookup_widget(fenetre_insc, "entry_role")));

    // Validation
    if (strlen(nom) == 0 || strlen(user) == 0 || strlen(pass) == 0) {
        GtkWidget *dlg_err = gtk_message_dialog_new(GTK_WINDOW(fenetre_insc),
            GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
            "Veuillez remplir tous les champs obligatoires.");
        gtk_dialog_run(GTK_DIALOG(dlg_err));
        gtk_widget_destroy(dlg_err);
        return;
    }

    // Ajout au fichier
    int role_int = atoi(role_str);
    ajouter((char*)nom, (char*)prenom, (char*)user, (char*)pass, role_int);

    // --- AFFICHAGE DU MESSAGE DE RÉUSSITE ---
    GtkWidget *dlg_ok = gtk_message_dialog_new(GTK_WINDOW(fenetre_insc),
        GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Vous êtes bien inscrit !");
    gtk_dialog_run(GTK_DIALOG(dlg_ok));
    gtk_widget_destroy(dlg_ok);

    // Fermeture et retour au login
    gtk_widget_destroy(fenetre_insc);
    GtkWidget *win_login = create_Login_users();
    gtk_widget_show_all(win_login);
}
void on_button_modifier_event_clicked(GtkButton *button, gpointer user_data)
{
    // 1. Récupérer la fenêtre de modification (top-level)
    GtkWidget *win = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    // 2. Initialiser la structure pour stocker les nouvelles valeurs
    EVENT e;
    memset(&e, 0, sizeof(EVENT));

    // 3. Récupération des données textuelles (Entry)
    const gchar *nom = gtk_entry_get_text(GTK_ENTRY(lookup_widget(win, "entry_nom_event")));
    const gchar *salle = gtk_entry_get_text(GTK_ENTRY(lookup_widget(win, "entry_salle_event")));
    
    strncpy(e.nom, nom, sizeof(e.nom) - 1);
    strncpy(e.salle, salle, sizeof(e.salle) - 1);

    // 4. Récupération des données numériques (SpinButtons)
    e.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(win, "spin_jour_event")));
    e.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(win, "spin_annee_event")));
    e.prix = gtk_spin_button_get_value(GTK_SPIN_BUTTON(lookup_widget(win, "spin_prix_event")));
    
    e.heure_debut_h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_debut_h")));
    e.heure_debut_m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_debut_m")));
    e.heure_fin_h = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_fin_h")));
    e.heure_fin_m = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(win, "spin_heure_fin_m")));

    // 5. Récupération des ComboBox
    // Mois : l'index 0 correspond au mois 1
    e.mois = gtk_combo_box_get_active(GTK_COMBO_BOX(lookup_widget(win, "combo_mois_event"))) + 1;

    // Type : on récupère le texte sélectionné
    GtkComboBox *cb_type = GTK_COMBO_BOX(lookup_widget(win, "combo_type_event"));
    GtkTreeIter iter_type;
    if (gtk_combo_box_get_active_iter(cb_type, &iter_type)) {
        gchar *type_txt;
        gtk_tree_model_get(gtk_combo_box_get_model(cb_type), &iter_type, 0, &type_txt, -1);
        strncpy(e.type, type_txt, sizeof(e.type) - 1);
        g_free(type_txt);
    }

    // 6. Action de modification
    // current_event_id a été rempli lors du clic sur le treeview
    if (current_event_id != -1) 
    {
        // Appel de votre fonction de traitement de fichier
        modifier_event("event.txt", current_event_id, e);

        // --- AFFICHAGE DU DIALOGUE DE SUCCÈS ---
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(win),
                                                 GTK_DIALOG_MODAL,
                                                 GTK_MESSAGE_INFO,
                                                 GTK_BUTTONS_OK,
                                                 "Modification effectuée avec succès !");
        
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        // ---------------------------------------

        // 7. Nettoyage et fermeture
        current_event_id = -1; // Réinitialisation de l'ID global
        gtk_widget_destroy(win); // Fermeture de l'interface de modification

        // 8. RAPPEL : Vous devez rafraîchir votre TreeView ici si nécessaire
        // Exemple : afficher_event_treeview(widget_du_treeview, "events.txt");
    }
    else 
    {
        // Cas de sécurité si aucun ID n'est sélectionné
        GtkWidget *dialog_err = gtk_message_dialog_new(GTK_WINDOW(win),
                                                     GTK_DIALOG_MODAL,
                                                     GTK_MESSAGE_ERROR,
                                                     GTK_BUTTONS_OK,
                                                     "Erreur : Aucun événement sélectionné.");
        gtk_dialog_run(GTK_DIALOG(dialog_err));
        gtk_widget_destroy(dialog_err);
    }
}
int niveau_debutant = 0;
int niveau_intermediaire = 0;
int niveau_avance = 0;
void
on_check_debutant_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
        niveau_debutant = 1;
    else
        niveau_debutant = 0;
}


void
on_check_intermediaire_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
        niveau_intermediaire = 1;
    else
        niveau_intermediaire = 0;
}


void
on_check_avance_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
        niveau_avance = 1;
    else
        niveau_avance = 0;
}

