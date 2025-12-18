#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
#include "ajout_cour.h"
GtkWidget *create_gestion_admin(void);
GtkWidget *create_ajout_cours(void);

static char *get_widget_text_safe(GtkWidget *w);
//char *get_widget_text_safe(GtkWidget *w);
void
on_btn_ajouter_cours_clicked            (GtkButton *button,
                                        gpointer   user_data);


//btn aff et retour 
/*void
on_afficher_cours_clicked              (GtkButton       *button,
                                        gpointer         user_data);
void on_retour_cours_clicked                (GtkButton       *button,
                                        gpointer         user_data);*/

// Bouton : Modifier cours
void vider_combobox(GtkComboBox *combo);
void remplir_combobox_duree(GtkComboBox *combo, reservation r);
void
on_btn_modifier_cours_clicked           (GtkButton *button,
                                        gpointer   user_data);

// Bouton : Supprimer cours
void
on_btn_supprimer_cours_clicked          (GtkButton *button,
                                        gpointer   user_data);

void
on_duree_changed(GtkComboBox *combo,
                 gpointer user_data);

// Bouton : Rechercher cours
//void
//on_button19_clicked         (GtkButton *button,
                                      //  gpointer   user_data);

// Callback utilisé dans ton fichier : button19
void
on_button19_clicked                    (GtkButton *button,
                                        gpointer   user_data);

/* ============================
   CALLBACKS POUR INSCRIPTION / RESERVATION
   ============================ */

// Bouton : S’inscrire à un cours
void
on_btn_sinscrire_cours_clicked          (GtkButton *button,
                                        gpointer   user_data);

/* ============================
   AUTRES (si utilisés par interface Glade)
   ============================ */

// Bouton ou signal générique “ajouter”
void
on_ajouter_clicked                     (GtkButton *button,
                                        gpointer   user_data);

void on_check_restriction_toggled(GtkToggleButton *togglebutton, gpointer user_data);

/* ———— Membres ———— */
void on_radio_F_membre_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_radio_H_membre_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_CheckMaladie_toggled(GtkToggleButton *togglebutton, gpointer user_data);

void on_btn_ajout_membre_clicked(GtkButton *button, gpointer user_data);
//void on_btn_ajouter_membre_clicked(GtkButton *button, gpointer user_data);

void on_btn_admin_login_clicked(GtkButton *button, gpointer user_data);
void on_btn_membre_login_clicked(GtkButton *button, gpointer user_data);
void on_btn_entraineur_login_clicked(GtkButton *button, gpointer user_data);

void on_btn_supprimer_membre_clicked(GtkButton *button, gpointer user_data);
void on_btn_modifier_membre_clicked(GtkButton *button, gpointer user_data);
void on_btn_rechercher_membre_clicked(GtkButton *button, gpointer user_data);


/* ———— Centres ———— */
void on_btn_ajouter_centre_clicked(GtkButton *button, gpointer user_data);
void on_btn_supprimer_centre_clicked(GtkButton *button, gpointer user_data);
void on_btn_modifier_centre_clicked(GtkButton *button, gpointer user_data);
void on_btn_rechercher_centre_clicked(GtkButton *button, gpointer user_data);

/* ———— Equipements ———— */
void on_btn_ajouter_equipement_clicked(GtkButton *button, gpointer user_data);
void on_btn_supprimer_equipement_clicked(GtkButton *button, gpointer user_data);
void on_btn_modifier_equipement_clicked(GtkButton *button, gpointer user_data);
void on_btn_rechercher_equipement_clicked(GtkButton *button, gpointer user_data);
void on_btn_reserver_equipement_clicked(GtkButton *button, gpointer user_data);

/* ———— Événements ———— */
void on_btn_ajouter_event_clicked(GtkButton *button, gpointer user_data);
void on_btn_supprimer_event_clicked(GtkButton *button, gpointer user_data);
void on_btn_modifier_event_clicked(GtkButton *button, gpointer user_data);
void on_btn_rechercher_event_clicked(GtkButton *button, gpointer user_data);
void on_btn_participer_event_clicked(GtkButton *button, gpointer user_data);

/* ———— Autres ———— */
void on_btn_sinscrire_centre_clicked(GtkButton *button, gpointer user_data);
void on_btn_login_clicked(GtkButton *button, gpointer user_data);

/* Fonction lookup utilisée par Glade */
GtkWidget *lookup_widget(GtkWidget *widget, const gchar *name);
void on_btn_ajouter_entraineur_clicked(GtkButton *button, gpointer user_data);
void on_btn_supprimer_entraineur_clicked(GtkButton *button, gpointer user_data);
void on_btn_modifier_entraineur_clicked(GtkButton *button, gpointer user_data);
void on_btn_rechercher_entraineur_clicked(GtkButton *button, gpointer user_data);
void on_btn_valider_ajout_clicked(GtkButton *button, gpointer user_data); 
void on_btn_ajouter_membre_clicked(GtkButton *button, gpointer user_data);
void on_btn_supprimer_cours_clicked(GtkButton *button, gpointer user_data);    


void
on_restric_maladie_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_afficher_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_clicked                      (GtkButton       *button,
                                        gpointer         user_data);

void
on_retour_cours_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_rechercher_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_modifier_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_afficher_cours_clicked              (GtkButton       *button,
                                        gpointer         user_data);


void
on_modifier_clicked                    (GtkButton       *button,
                                        gpointer         user_data);


void
on_treeview_cours_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

/*void
on_femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_homme_toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);*/



void
on_femme_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_homme__toggled                      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

#endif

void
on_btn_valider_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_calculer_stats_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_graphique_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_drawingarea1_expose_event           (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_btn_actualiser_cours_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_remplir_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_login_clicked                   (GtkButton       *button,
                                        gpointer         user_data);
