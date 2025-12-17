

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

void
on_button_event_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_ajouter_event_clicked        (GtkButton       *button,
                                        gpointer         user_data);



void
on_button_modifier_event_clicked       (GtkButton       *button,
                                        gpointer         user_data);



void
on_button_valider_clicked              (GtkButton       *button,
                                        gpointer         user_data);



void
on_button_participer_event_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_valider_event_clicked        (GtkButton       *button,
                                        gpointer         user_data);







void
on_radio_femme_membre_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_homme_membre_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);






void
on_treeview9_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);


void
on_button_retour_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_actualiser_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_Afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data);





void
on_button_login_clicked                (GtkButton       *button,
                                        gpointer         user_data);






void
on_button_rechercher_clicked           (GtkButton       *button,
                                       gpointer         user_data);





void
on_button_inscription_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modifier_event_clicked       (GtkButton       *button,
                                        gpointer         user_data);


void on_treeview9_selection_changed(GtkTreeSelection *selection, gpointer user_data);

void on_treeview9_row_activated(GtkTreeView *treeview,
                                GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data);



void setup_treeview_signals(GtkWidget *fenetre_principale);



void on_treeview9_selection_changed(GtkTreeSelection *selection, gpointer user_data);

void on_treeview9_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);


#endif

void
on_check_debutant_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_check_intermediaire_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_check_avance_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
