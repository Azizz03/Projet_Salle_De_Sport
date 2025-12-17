#include <gtk/gtk.h>



void
on_radio_F_membre_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_H_membre_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_CheckMaladie_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data);
void
on_btn_ajout_membre_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_ajouter_membre_clicked          (GtkButton       *button,
                                        gpointer         user_data);
void
on_btn_admin_login_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_membre_login_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_entraineur_login_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_supprimer_membre_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier_membre_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_rechercher_membre_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_ajouter_entraineur_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_supprimer_entraineur_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier_entraineur_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_rechercher_entraineur_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_ajouter_cours_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_supprimer_cours_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier_cours_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_ajouter_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_supprimer_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier_centre_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_rechercher_centre_clicked       (GtkButton       *button,
                                        gpointer         user_data);

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
on_btn_ajouter_event_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_supprimer_event_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_modifier_event_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_rechercher_event_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_login_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_sinscrire_cours_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_participer_event_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_valider_ajout_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_reserver_equipement_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_sinscrire_centre_clicked        (GtkButton       *button,
                                        gpointer         user_data);





void
on_btn_chercher_cours_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_membre_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_afficher_membres_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_retour_membre_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_treeview_entraineur_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_cours_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_centre_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_equipement_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeview_event_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_btn_actualiser_membre_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_button67_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button68_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button69_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button70_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button71_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_afficher_membre_treeview_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_rechercher_membre1_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_radio_sex_H_coach_prv_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radio_sex_F_coach_prv_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_reserver_coach_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_confirmer_modif_membre_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_confirmer_reser_clicked         (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_drawinHist_expose_event             (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_btn_stats_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_Retour_equipement_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_Actualiser_equipementclicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_btn_afficher_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_categorie_equipement_reserver_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_radiobutton_homme_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_femme_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton_mixte_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_btn_afficher_centre_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_rechercher_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_modifier_clicked             (GtkButton       *button,
                                        gpointer         user_data);
