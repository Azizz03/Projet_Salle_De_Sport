#include <gtk/gtk.h>

void
on_btn_ajouter_equipement_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_supprimer_equipement_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier_equipement_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_rechercher_equipement_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_valider_ajout_clicked           (GtkButton       *button,
                                        gpointer         user_data);
void
on_Retour_equipement_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_Actualiser_equipement_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_afficher_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_equipement_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);
void
on_categorie_equipement_reserver_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data);

void on_btn_reserver_equipement_clicked (GtkButton *button, gpointer user_data);

void
on_categorie_equipement_reserver_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data);




void on_btn_ajouter_membre_clicked (GtkButton *button, gpointer user_data);
void on_btn_supprimer_membre_clicked (GtkButton *button, gpointer user_data);
void on_btn_modifier_membre_clicked (GtkButton *button, gpointer user_data);
void on_btn_rechercher_membre_clicked (GtkButton *button, gpointer user_data);

void on_btn_ajouter_entraineur_clicked (GtkButton *button, gpointer user_data);
void on_btn_supprimer_entraineur_clicked (GtkButton *button, gpointer user_data);
void on_btn_modifier_entraineur_clicked (GtkButton *button, gpointer user_data);
void on_btn_rechercher_entraineur_clicked (GtkButton *button, gpointer user_data);

void on_btn_ajouter_cours_clicked (GtkButton *button, gpointer user_data);
void on_btn_supprimer_cours_clicked (GtkButton *button, gpointer user_data);
void on_btn_modifier_cours_clicked (GtkButton *button, gpointer user_data);
void on_button19_clicked (GtkButton *button, gpointer user_data); 

void on_btn_ajouter_centre_clicked (GtkButton *button, gpointer user_data);
void on_btn_supprimer_centre_clicked (GtkButton *button, gpointer user_data);
void on_btn_modifier_centre_clicked (GtkButton *button, gpointer user_data);
void on_btn_rechercher_centre_clicked (GtkButton *button, gpointer user_data);

void on_btn_ajouter_event_clicked (GtkButton *button, gpointer user_data);
void on_btn_supprimer_event_clicked (GtkButton *button, gpointer user_data);
void on_btn_modifier_event_clicked (GtkButton *button, gpointer user_data);
void on_btn_rechercher_event_clicked (GtkButton *button, gpointer user_data);

void on_btn_admin_login_clicked (GtkButton *button, gpointer user_data);
void on_btn_membre_login_clicked (GtkButton *button, gpointer user_data);
void on_btn_entraineur_login_clicked (GtkButton *button, gpointer user_data);
void on_btn_login_clicked (GtkButton *button, gpointer user_data);

void on_btn_sinscrire_cours_clicked (GtkButton *button, gpointer user_data);
void on_btn_participer_event_clicked (GtkButton *button, gpointer user_data);

void on_btn_sinscrire_centre_clicked (GtkButton *button, gpointer user_data);

