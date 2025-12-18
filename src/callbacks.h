#include <gtk/gtk.h>


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
on_btn_ajouter_entraineur_clicked      	(GtkWidget       *og,
                                        gpointer         data);

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
on_btn_login_clicked                   (GtkButton        *button,
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
on_h_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_check_toggled                       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_f_toggled                           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_bajout_clicked                      (GtkWidget       *og,
                                        gpointer         data);

void
on_btnreserv_clicked                   (GtkWidget       *button,
                                        gpointer         user_data);



void
on_mer_actualiser_clicked              (GtkButton       *button,
                                        gpointer         user_data);



void
on_mer_rechercher_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_mer_tree_row_activated              (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_mer_modifier_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_mer_reserver_clicked                (GtkWidget       *button,
                                        gpointer         user_data);

void
on_mer_clicked                         (GtkButton       *button,
                                        gpointer         user_data);

void
on_mer_afficher_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_mer_retourner_clicked               (GtkWidget       *button,
                                        gpointer         user_data);

void
on_mer_ajouter_clicked                 (GtkButton       *button,
                                        gpointer         user_data);


void on_mer_confirmer_clicked  (GtkWidget *og, gpointer data);

void
on_mer_rechercher_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_valider_res_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_profil_entraineur_show              (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_window_login_show                   (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_notebook4_switch_page               (GtkNotebook     *notebook,
                                       GtkWidget *page,
                                        guint            page_num,
                                        gpointer         user_data);




gboolean
on_drawinHist_expose_event             (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_mer_stats_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_retourner_profil_clicked            (GtkWidget       *button,
                                        gpointer         user_data);
