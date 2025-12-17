#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "membre.h"
int g_nb_h = 0;
int g_nb_f = 0;
int sexe = 0;      
int maladie = 0; 
//////////FONCTION AZIZ////////////////////////////
void
on_btn_ajout_membre_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *entry_id, *input_nom, *input_prenom, *entry_email;
    GtkWidget *combo_centre, *combo_type, *combo_mois, *combo_objectif;
    GtkWidget *spin_taille, *spin_poids, *spin_mass_musc, *spin_mass_graiss;
    GtkWidget *spin_jour, *spin_annee, *spin_duree_prog;
    GtkWidget *entry_descr_maladie, *labelSucces,*num_tel;
    GtkWidget *label_erreur1, *label_erreur2;

    char sexe_txt[20], type_abonnement[40], descr_maladie[100];
    char centre[40], email[30], mois[30], objectif[40],numero_tel[20];
    int taille, id, jour, annee, duree_prog;
    float poids, masse_musculaire, masse_graisseuse;

    membre m;
    int erreur = 0;

    
    entry_id = lookup_widget(GTK_WIDGET(button), "entry_id_membre");
    input_nom = lookup_widget(GTK_WIDGET(button), "entry_nom_membre");
    input_prenom = lookup_widget(GTK_WIDGET(button), "entry_prenom_membre");
    entry_email = lookup_widget(GTK_WIDGET(button), "entry_email_membre");
    combo_centre = lookup_widget(GTK_WIDGET(button), "combo_centre_membre");
    combo_type = lookup_widget(GTK_WIDGET(button), "combo_type_abo");
    combo_mois = lookup_widget(GTK_WIDGET(button), "combo_mois_naiss_membre");
    combo_objectif = lookup_widget(GTK_WIDGET(button), "combo_objectif_membre");
    num_tel = lookup_widget(GTK_WIDGET(button), "entry_tel_membre");

    spin_taille = lookup_widget(GTK_WIDGET(button), "spin_taille_membre");
    spin_poids = lookup_widget(GTK_WIDGET(button), "spin_poids_membre");
    spin_mass_musc = lookup_widget(GTK_WIDGET(button), "spin_mass_musc");
    spin_mass_graiss = lookup_widget(GTK_WIDGET(button), "spin_mass_graiss");
    spin_jour = lookup_widget(GTK_WIDGET(button), "jour_naiss_membre");
    spin_annee = lookup_widget(GTK_WIDGET(button), "annee_naiss_membre");
    spin_duree_prog = lookup_widget(GTK_WIDGET(button), "duree_prog_membre");

    entry_descr_maladie = lookup_widget(GTK_WIDGET(button), "entry_descr_maladie");
    labelSucces = lookup_widget(GTK_WIDGET(button), "labelSucces");
    label_erreur1 = lookup_widget(GTK_WIDGET(button),"labe_erreur_tel");
    label_erreur2 = lookup_widget(GTK_WIDGET(button),"label_erreur_mail");

    
    id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
    
    
    strncpy(m.nom, gtk_entry_get_text(GTK_ENTRY(input_nom)), sizeof(m.nom)-1);
    strncpy(m.prenom, gtk_entry_get_text(GTK_ENTRY(input_prenom)), sizeof(m.prenom)-1);
    strncpy(email, gtk_entry_get_text(GTK_ENTRY(entry_email)), sizeof(email)-1);
    strncpy(m.email, email, sizeof(m.email)-1);
    if(strlen(m.email)==0){
    gtk_label_set_text(GTK_LABEL(label_erreur2), "Le champs de l'email est obligatoire");
    return;}
    strncpy(m.num_tel, gtk_entry_get_text(GTK_ENTRY(num_tel)), sizeof(m.num_tel)-1);
    if(strlen(m.num_tel)!=8){
    gtk_label_set_text(GTK_LABEL(label_erreur1), "Le numero de tel doit contenir 8 chiffres");
    return;}
    poids = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(spin_poids));
    masse_musculaire = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(spin_mass_musc));
    masse_graisseuse = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(spin_mass_graiss));
    m.poids = poids;
    m.masse_musculaire = masse_musculaire;
    m.masse_graisseuse = masse_graisseuse;

    taille = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_taille));
    m.taille = taille;

    jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));
    m.jour = jour;
    m.annee = annee;

    duree_prog = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_duree_prog));
    m.duree_prog = duree_prog;
    

    
strncpy(m.mois,
        gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_mois)),
        sizeof(m.mois)-1);


strncpy(m.centre,
        gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre)),
        sizeof(m.centre)-1);


strncpy(m.type_abonnement,
        gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_type)),
        sizeof(m.type_abonnement)-1);


strncpy(m.objectif,
        gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_objectif)),
        sizeof(m.objectif)-1);

    
    strncpy(descr_maladie, gtk_entry_get_text(GTK_ENTRY(entry_descr_maladie)), sizeof(descr_maladie)-1);
    strncpy(m.descr_maladie, descr_maladie, sizeof(m.descr_maladie)-1);

    
    if (sexe == 1)
        strncpy(sexe_txt, "Homme", sizeof(sexe_txt)-1);
    else if (sexe == 2)
        strncpy(sexe_txt, "Femme", sizeof(sexe_txt)-1);
    else
        strncpy(sexe_txt, "Inconnu", sizeof(sexe_txt)-1);
    strncpy(m.sexe, sexe_txt, sizeof(m.sexe)-1);

    m.maladie = maladie;
    m.id = id;
    

    
    if (ajouter_membre("membre.txt", m))
        gtk_label_set_text(GTK_LABEL(labelSucces), "Ajout effectué avec succès !");
    else
        gtk_label_set_text(GTK_LABEL(labelSucces), "Erreur lors de l'ajout !");

    
    printf("\n------ Membre Ajouté -------\n");
    printf("ID        : %d\n", m.id);
    printf("Nom       : %s\n", m.nom);
    printf("Prénom    : %s\n", m.prenom);
    printf("Email     : %s\n", m.email);
    printf("Centre    : %s\n", m.centre);
    printf("Sexe      : %s\n", m.sexe);
    printf("Taille    : %d\n", m.taille);
    printf("Poids     : %.2f\n", m.poids);
    printf("Masse Musc: %.2f\n", m.masse_musculaire);
    printf("Masse Graiss: %.2f\n", m.masse_graisseuse);
    printf("Date de naissance: %d %s %d\n", m.jour, m.mois, m.annee);
    printf("Type Abon : %s\n", m.type_abonnement);
    printf("Objectif  : %s\n", m.objectif);
    printf("Durée prog: %d\n", m.duree_prog);
    printf("Maladie   : %d\n", m.maladie);
    printf("Description: %s\n", m.descr_maladie);
}

void
on_CheckMaladie_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    maladie = gtk_toggle_button_get_active(togglebutton);
}

void on_radio_H_membre_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        sexe = 1; 
}

void on_radio_F_membre_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        sexe = 2; 
}
//fct recherche qui fonctionne
void
on_btn_rechercher_membre1_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entry_id_rech,*entry_id, *input_nom, *input_prenom, *entry_email;
    GtkWidget *combo_centre, *combo_type, *combo_mois, *combo_objectif;
    GtkWidget *spin_taille, *spin_poids, *spin_mass_musc, *spin_mass_graiss;
    GtkWidget *spin_jour, *spin_annee, *spin_duree_prog;
    GtkWidget *entry_descr_maladie, *output,*num_tel;
    GtkWidget *toggle_homme,*toggle_femme;
    GtkWidget *check_maladie;
membre m;
int id;
char id_str[20];
//1
check_maladie = lookup_widget(GTK_WIDGET(button),"CheckMaladie");
//2
toggle_homme = lookup_widget(GTK_WIDGET(button),"radio_H_membre");
//3
toggle_femme = lookup_widget(GTK_WIDGET(button),"radio_F_membre");
//4
//entry_id_rech = lookup_widget(GTK_WIDGET(button), "entry_id_membre_recherche");
//5
entry_id = lookup_widget(GTK_WIDGET(button), "entry_id_membre");
//6
input_nom = lookup_widget(GTK_WIDGET(button), "entry_nom_membre");
//7
input_prenom = lookup_widget(GTK_WIDGET(button), "entry_prenom_membre");
//8
entry_email = lookup_widget(GTK_WIDGET(button), "entry_email_membre");
//9
combo_centre = lookup_widget(GTK_WIDGET(button), "combo_centre_membre");
//10
combo_type = lookup_widget(GTK_WIDGET(button), "combo_type_abo");
//11
combo_mois = lookup_widget(GTK_WIDGET(button), "combo_mois_naiss_membre");
//12
combo_objectif = lookup_widget(GTK_WIDGET(button), "combo_objectif_membre");
//13
num_tel = lookup_widget(GTK_WIDGET(button), "entry_tel_membre");
//14
spin_taille = lookup_widget(GTK_WIDGET(button), "spin_taille_membre");
//15
spin_poids = lookup_widget(GTK_WIDGET(button), "spin_poids_membre");
//16
spin_mass_musc = lookup_widget(GTK_WIDGET(button), "spin_mass_musc");
//17
spin_mass_graiss = lookup_widget(GTK_WIDGET(button), "spin_mass_graiss");
//18
spin_jour = lookup_widget(GTK_WIDGET(button), "jour_naiss_membre");
//19
spin_annee = lookup_widget(GTK_WIDGET(button), "annee_naiss_membre");
//20
spin_duree_prog = lookup_widget(GTK_WIDGET(button), "duree_prog_membre");
//21
entry_descr_maladie = lookup_widget(GTK_WIDGET(button), "entry_descr_maladie");
id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
m =  chercher_membre("membre.txt", id);

gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_taille),m.taille);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_poids),m.poids);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mass_musc),m.masse_musculaire); 
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mass_graiss),m.masse_graisseuse); 
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee),m.annee); 
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_duree_prog),m.duree_prog); 
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour),m.jour);
//sprintf(id_str, "%d", m.id);
//gtk_entry_set_text(GTK_ENTRY(entry_id), id_str);
gtk_entry_set_text(GTK_ENTRY(input_nom), m.nom);
gtk_entry_set_text(GTK_ENTRY(input_prenom), m.prenom);
gtk_entry_set_text(GTK_ENTRY(entry_email), m.email);
gtk_entry_set_text(GTK_ENTRY(num_tel), m.num_tel);
gtk_entry_set_text(GTK_ENTRY(entry_descr_maladie), m.descr_maladie);
if(strcmp(m.sexe,"Homme")==0){
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_homme),TRUE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_femme),FALSE);
}
else if(strcmp(m.sexe,"Femme")==0){
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_femme),TRUE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_homme),FALSE);}
if(m.maladie==1){
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_maladie),TRUE);}

if (strcmp(m.centre, "A") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 0);
    } else if (strcmp(m.centre, "B") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 1);
    } else if (strcmp(m.centre, "C") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 2);
    }else if (strcmp(m.centre, "D") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 3);
    } else if (strcmp(m.centre, "E") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 4);
    }
    
if (strcmp(m.type_abonnement, "mensuel") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), 0);
    } else if (strcmp(m.type_abonnement, "trimestriel") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), 1);
    } else if (strcmp(m.type_abonnement, "Annuel") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), 2);
    }
if (strcmp(m.objectif, "perte_poids") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_objectif), 0);
    } else if (strcmp(m.objectif, "gain_masse_musculaire") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_objectif), 1);
    } else if (strcmp(m.objectif, "garder_la_forme") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_objectif), 2);
    }
    if (strcmp(m.mois, "Janvier") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 0);
    }
    else if (strcmp(m.mois, "Fevrier") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 1);
    }
    else if (strcmp(m.mois, "Mars") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 2);
    }
    else if (strcmp(m.mois, "Avril") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 3);
    }
    else if (strcmp(m.mois, "Mai") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 4);
    }
    else if (strcmp(m.mois, "Juin") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 5);
    }
    else if (strcmp(m.mois, "Juillet") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 6);
    }
    else if (strcmp(m.mois, "Août") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 7);
    }
    else if (strcmp(m.mois, "Septembre") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 8);
    }
    else if (strcmp(m.mois, "Octobre") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 9);
    }
    else if (strcmp(m.mois, "Novembre") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 10);
    }
    else if (strcmp(m.mois, "Decembre") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 11);
    }

 

}

void
on_btn_rechercher_membre_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entry_id_rech,*entry_id, *input_nom, *input_prenom, *entry_email;
    GtkWidget *combo_centre, *combo_type, *combo_mois, *combo_objectif;
    GtkWidget *spin_taille, *spin_poids, *spin_mass_musc, *spin_mass_graiss;
    GtkWidget *spin_jour, *spin_annee, *spin_duree_prog;
    GtkWidget *entry_descr_maladie, *output,*num_tel;
    GtkWidget *toggle_homme,*toggle_femme;
    GtkWidget *check_maladie;
GtkWidget *Ajout_Membre;
GtkWidget *gestion_admin;
Ajout_Membre = lookup_widget(GTK_WIDGET(button),"Ajout_Membre");
gestion_admin = lookup_widget(GTK_WIDGET(button),"gestion_admin");
Ajout_Membre = create_Ajout_Membre();
gtk_widget_show(Ajout_Membre);
gtk_widget_hide(gestion_admin);
membre m;
int id;
char id_str[20];
check_maladie = lookup_widget(Ajout_Membre,"CheckMaladie");
toggle_homme = lookup_widget(Ajout_Membre,"radio_H_membre");
toggle_femme = lookup_widget(Ajout_Membre,"radio_F_membre");
entry_id_rech = lookup_widget(GTK_WIDGET(button), "entry_id_rech_membre");
entry_id = lookup_widget(Ajout_Membre, "entry_id_membre");
input_nom = lookup_widget(Ajout_Membre, "entry_nom_membre");
input_prenom = lookup_widget(Ajout_Membre, "entry_prenom_membre");
entry_email = lookup_widget(Ajout_Membre, "entry_email_membre");
combo_centre = lookup_widget(Ajout_Membre, "combo_centre_membre");
combo_type = lookup_widget(Ajout_Membre, "combo_type_abo");
combo_mois = lookup_widget(Ajout_Membre, "combo_mois_naiss_membre");
combo_objectif = lookup_widget(Ajout_Membre, "combo_objectif_membre");
num_tel = lookup_widget(Ajout_Membre, "entry_tel_membre");

spin_taille = lookup_widget(Ajout_Membre, "spin_taille_membre");
spin_poids = lookup_widget(Ajout_Membre, "spin_poids_membre");
spin_mass_musc = lookup_widget(Ajout_Membre, "spin_mass_musc");
spin_mass_graiss = lookup_widget(Ajout_Membre, "spin_mass_graiss");
spin_jour = lookup_widget(Ajout_Membre, "jour_naiss_membre");
spin_annee = lookup_widget(Ajout_Membre, "annee_naiss_membre");
spin_duree_prog = lookup_widget(Ajout_Membre, "duree_prog_membre");

entry_descr_maladie = lookup_widget(Ajout_Membre, "entry_descr_maladie");
output = lookup_widget(GTK_WIDGET(button), "label_modif");
id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id_rech)));
m =  chercher_membre("membre.txt", id);

gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_taille),m.taille);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_poids),m.poids);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mass_musc),m.masse_musculaire); 
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_mass_graiss),m.masse_graisseuse); 
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_annee),m.annee); 
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_duree_prog),m.duree_prog); 
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_jour),m.jour);
sprintf(id_str, "%d", m.id);
gtk_entry_set_text(GTK_ENTRY(entry_id), id_str);
gtk_entry_set_text(GTK_ENTRY(input_nom), m.nom);
gtk_entry_set_text(GTK_ENTRY(input_prenom), m.prenom);
gtk_entry_set_text(GTK_ENTRY(entry_email), m.email);
gtk_entry_set_text(GTK_ENTRY(num_tel), m.num_tel);
gtk_entry_set_text(GTK_ENTRY(entry_descr_maladie), m.descr_maladie);
if(strcmp(m.sexe,"Homme")==0){
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_homme),TRUE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_femme),FALSE);
}
else if(strcmp(m.sexe,"Femme")==0){
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_femme),TRUE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle_homme),FALSE);}
if(m.maladie==1){
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_maladie),TRUE);}

if (strcmp(m.centre, "A") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 0);
    } else if (strcmp(m.centre, "B") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 1);
    } else if (strcmp(m.centre, "C") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 2);
    }else if (strcmp(m.centre, "D") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 3);
    } else if (strcmp(m.centre, "E") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_centre), 4);
    }
    
if (strcmp(m.type_abonnement, "mensuel") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), 0);
    } else if (strcmp(m.type_abonnement, "trimestriel") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), 1);
    } else if (strcmp(m.type_abonnement, "Annuel") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), 2);
    }
if (strcmp(m.objectif, "perte_poids") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_objectif), 0);
    } else if (strcmp(m.objectif, "gain_masse_musculaire") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_objectif), 1);
    } else if (strcmp(m.objectif, "garder_la_forme") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_objectif), 2);
    }
    if (strcmp(m.mois, "Janvier") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 0);
    }
    else if (strcmp(m.mois, "Fevrier") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 1);
    }
    else if (strcmp(m.mois, "Mars") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 2);
    }
    else if (strcmp(m.mois, "Avril") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 3);
    }
    else if (strcmp(m.mois, "Mai") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 4);
    }
    else if (strcmp(m.mois, "Juin") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 5);
    }
    else if (strcmp(m.mois, "Juillet") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 6);
    }
    else if (strcmp(m.mois, "Août") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 7);
    }
    else if (strcmp(m.mois, "Septembre") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 8);
    }
    else if (strcmp(m.mois, "Octobre") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 9);
    }
    else if (strcmp(m.mois, "Novembre") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 10);
    }
    else if (strcmp(m.mois, "Decembre") == 0) {
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_mois), 11);
    }

 

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
on_btn_login_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{char username[40];
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
void
on_treeview_membre_row_activated (GtkTreeView       *treeview,
                                  GtkTreePath       *path,
                                  GtkTreeViewColumn *column,
                                  gpointer           user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    gint id;

    
    model = gtk_tree_view_get_model(treeview);
    if (model == NULL)
        return; /* sécurité */

    
    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        
        gtk_tree_model_get(model, &iter,
                           ID, &id,
                           -1);

        g_print("Suppression du membre avec ID = %d\n", id);

        
        supprimer_membre("membre.txt", id);

        
        GtkWidget *treeview_widget = GTK_WIDGET(treeview);

        vider(treeview_widget);

        afficher_membres_treeview(treeview_widget);
    }
}

void
on_btn_afficher_membres_clicked (GtkButton *button,
                                 gpointer   user_data)
{
    GtkWidget *gestion_admin;
    GtkWidget *treeview1;

    
    gestion_admin = lookup_widget(GTK_WIDGET(button), "gestion_admin");

    
    treeview1 = lookup_widget(gestion_admin, "treeview_membre");
    if (treeview1 == NULL) {
        g_print("Erreur : widget 'treeview_membre' introuvable dans gestion_admin.\n");
        return;
    }

    
    afficher_membres_treeview(treeview1);
}



void
on_btn_actualiser_membre_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *gestion_admin,*w1;
GtkWidget *treeview1;
w1 = lookup_widget(GTK_WIDGET(button),"gestion_admin");
gestion_admin = create_gestion_admin();
gtk_widget_show(gestion_admin);
gtk_widget_hide(w1);
treeview1 = lookup_widget(gestion_admin,"treeview_membre");
vider(treeview1);
afficher_membres_treeview(treeview1);
}

void
on_btn_retour_membre_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Ajout_Membre,*gestion_admin;

gestion_admin = lookup_widget(GTK_WIDGET(button),"gestion_admin");
gtk_widget_hide(gestion_admin);
Ajout_Membre=create_Ajout_Membre();
gtk_widget_show(Ajout_Membre);

}

void
on_btn_afficher_membre_treeview_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *Ajout_Membre;
    GtkWidget *gestion_admin;
    GtkWidget *treeview1;

    
    Ajout_Membre = lookup_widget(GTK_WIDGET(button), "Ajout_Membre");
    if (Ajout_Membre != NULL)
        gtk_widget_hide(Ajout_Membre);

    
    gestion_admin = create_gestion_admin();
    gtk_widget_show(gestion_admin);

    
    treeview1 = lookup_widget(gestion_admin, "treeview_membre");
    if (treeview1 == NULL) {
        g_print("Erreur : widget 'treeview_membre' introuvable dans gestion_admin.\n");
        return;
    }

    
    afficher_membres_treeview(treeview1);

}
void
on_btn_confirmer_modif_membre_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entry_id, *input_nom, *input_prenom, *entry_email;
    GtkWidget *combo_centre, *combo_type, *combo_mois, *combo_objectif;
    GtkWidget *spin_taille, *spin_poids, *spin_mass_musc, *spin_mass_graiss;
    GtkWidget *spin_jour, *spin_annee, *spin_duree_prog;
    GtkWidget *entry_descr_maladie, *label_modif, *num_tel;

    membre nouv;
    int id, taille, jour, annee, duree_prog;
    float poids, masse_musculaire, masse_graisseuse;
    char email[30];
    char sexe_txt[20];
    char centre[40], mois[30], objectif[40], type_abonnement[40];
    char descr_maladie[100];

    
    entry_id        = lookup_widget(GTK_WIDGET(button), "entry_id_membre");
    input_nom       = lookup_widget(GTK_WIDGET(button), "entry_nom_membre");
    input_prenom    = lookup_widget(GTK_WIDGET(button), "entry_prenom_membre");
    entry_email     = lookup_widget(GTK_WIDGET(button), "entry_email_membre");
    combo_centre    = lookup_widget(GTK_WIDGET(button), "combo_centre_membre");
    combo_type      = lookup_widget(GTK_WIDGET(button), "combo_type_abo");
    combo_mois      = lookup_widget(GTK_WIDGET(button), "combo_mois_naiss_membre");
    combo_objectif  = lookup_widget(GTK_WIDGET(button), "combo_objectif_membre");
    num_tel         = lookup_widget(GTK_WIDGET(button), "entry_tel_membre");

    spin_taille     = lookup_widget(GTK_WIDGET(button), "spin_taille_membre");
    spin_poids      = lookup_widget(GTK_WIDGET(button), "spin_poids_membre");
    spin_mass_musc  = lookup_widget(GTK_WIDGET(button), "spin_mass_musc");
    spin_mass_graiss= lookup_widget(GTK_WIDGET(button), "spin_mass_graiss");
    spin_jour       = lookup_widget(GTK_WIDGET(button), "jour_naiss_membre");
    spin_annee      = lookup_widget(GTK_WIDGET(button), "annee_naiss_membre");
    spin_duree_prog = lookup_widget(GTK_WIDGET(button), "duree_prog_membre");

    entry_descr_maladie = lookup_widget(GTK_WIDGET(button), "entry_descr_maladie");
    label_modif         = lookup_widget(GTK_WIDGET(button), "labelSucces");

    /* 1) ID du membre à modifier (clé) */
    id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
    nouv.id = id; /* même id, on ne le change pas dans le fichier */

    /* 2) Champs texte simples */
    strncpy(nouv.nom,
            gtk_entry_get_text(GTK_ENTRY(input_nom)),
            sizeof(nouv.nom)-1);
    nouv.nom[sizeof(nouv.nom)-1] = '\0';

    strncpy(nouv.prenom,
            gtk_entry_get_text(GTK_ENTRY(input_prenom)),
            sizeof(nouv.prenom)-1);
    nouv.prenom[sizeof(nouv.prenom)-1] = '\0';

    strncpy(email,
            gtk_entry_get_text(GTK_ENTRY(entry_email)),
            sizeof(email)-1);
    email[sizeof(email)-1] = '\0';
    strncpy(nouv.email, email, sizeof(nouv.email)-1);
    nouv.email[sizeof(nouv.email)-1] = '\0';

    strncpy(nouv.num_tel,
            gtk_entry_get_text(GTK_ENTRY(num_tel)),
            sizeof(nouv.num_tel)-1);
    nouv.num_tel[sizeof(nouv.num_tel)-1] = '\0';

    /* 3) Spinners numériques */
    poids            = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(spin_poids));
    masse_musculaire = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(spin_mass_musc));
    masse_graisseuse = gtk_spin_button_get_value_as_float(GTK_SPIN_BUTTON(spin_mass_graiss));
    taille           = gtk_spin_button_get_value_as_int  (GTK_SPIN_BUTTON(spin_taille));
    jour             = gtk_spin_button_get_value_as_int  (GTK_SPIN_BUTTON(spin_jour));
    annee            = gtk_spin_button_get_value_as_int  (GTK_SPIN_BUTTON(spin_annee));
    duree_prog       = gtk_spin_button_get_value_as_int  (GTK_SPIN_BUTTON(spin_duree_prog));

    nouv.poids            = poids;
    nouv.masse_musculaire = masse_musculaire;
    nouv.masse_graisseuse = masse_graisseuse;
    nouv.taille           = taille;
    nouv.jour             = jour;
    nouv.annee            = annee;
    nouv.duree_prog       = duree_prog;

    /* 4) Combobox (centre, mois, type abo, objectif) */
    strncpy(nouv.mois,
            gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_mois)),
            sizeof(nouv.mois)-1);
    nouv.mois[sizeof(nouv.mois)-1] = '\0';

    strncpy(nouv.centre,
            gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre)),
            sizeof(nouv.centre)-1);
    nouv.centre[sizeof(nouv.centre)-1] = '\0';

    strncpy(nouv.type_abonnement,
            gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_type)),
            sizeof(nouv.type_abonnement)-1);
    nouv.type_abonnement[sizeof(nouv.type_abonnement)-1] = '\0';

    strncpy(nouv.objectif,
            gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_objectif)),
            sizeof(nouv.objectif)-1);
    nouv.objectif[sizeof(nouv.objectif)-1] = '\0';

    
    strncpy(descr_maladie,
            gtk_entry_get_text(GTK_ENTRY(entry_descr_maladie)),
            sizeof(descr_maladie)-1);
    descr_maladie[sizeof(descr_maladie)-1] = '\0';
    strncpy(nouv.descr_maladie, descr_maladie, sizeof(nouv.descr_maladie)-1);
    nouv.descr_maladie[sizeof(nouv.descr_maladie)-1] = '\0';

    
    if (sexe == 1)
        strncpy(sexe_txt, "Homme", sizeof(sexe_txt)-1);
    else if (sexe == 2)
        strncpy(sexe_txt, "Femme", sizeof(sexe_txt)-1);
    else
        strncpy(sexe_txt, "Inconnu", sizeof(sexe_txt)-1);
    sexe_txt[sizeof(sexe_txt)-1] = '\0';

    strncpy(nouv.sexe, sexe_txt, sizeof(nouv.sexe)-1);
    nouv.sexe[sizeof(nouv.sexe)-1] = '\0';

    
    nouv.maladie = maladie;

    
    if (modifier_membre("membre.txt", id, nouv))
        gtk_label_set_text(GTK_LABEL(label_modif), "Modification effectuée avec succès !");
    else
        gtk_label_set_text(GTK_LABEL(label_modif), "Erreur : membre introuvable ou fichier indisponible !");


}
void
on_radio_sex_H_coach_prv_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
        sexe = 1; 

}


void
on_radio_sex_F_coach_prv_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
        sexe = 2; 

}


void
on_btn_reserver_coach_clicked (GtkButton *button,
                               gpointer   user_data)
{GtkWidget *spin_jour, *spin_mois, *spin_annee;
    GtkWidget *spin_hd, *spin_md, *spin_hf, *spin_mf,*spin_seance;
    GtkWidget *combo_specialite, *combo_centre, *combo_coach;
    GtkWidget *radio_h, *radio_f;
    GtkWidget *label_msg;

    Date d;
    int hd, md, hf, mf;
    char specialite[30];
    char centre[40];
    char sexe[10];

    char noms[200][60];
    int n, i;

    /* Widgets (adapte les NOMS à ton .glade) */
    spin_jour  = lookup_widget(GTK_WIDGET(button), "spin_jour_reser");
    spin_mois  = lookup_widget(GTK_WIDGET(button), "spin_mois_reserr");
    spin_annee = lookup_widget(GTK_WIDGET(button), "spin_annee_reser_prv");

    spin_hd = lookup_widget(GTK_WIDGET(button), "spin_hr_debut_prv");
    spin_md = lookup_widget(GTK_WIDGET(button), "spin_min_debut_prv");
    spin_hf = lookup_widget(GTK_WIDGET(button), "spin_hr_fin_prv");
    spin_mf = lookup_widget(GTK_WIDGET(button), "spin_min_fin_prv");

    combo_specialite = lookup_widget(GTK_WIDGET(button), "combo_spec_prv");
    combo_centre     = lookup_widget(GTK_WIDGET(button), "combo_centre_prv");
    combo_coach      = lookup_widget(GTK_WIDGET(button), "combo_nom_coach_prv");

    radio_h = lookup_widget(GTK_WIDGET(button), "radio_sex_H_coach_prv");
    radio_f = lookup_widget(GTK_WIDGET(button), "radio_sex_F_coach_prv");
    

    label_msg = lookup_widget(GTK_WIDGET(button), "label_succes_reser");

    /* Lire Date */
    d.jour  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    d.mois  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    d.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));

    /* Lire créneau */
    hd = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_hd));
    md = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_md));
    hf = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_hf));
    mf = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mf));

    /* Vérif simple */
    if (hd > hf || (hd == hf && md >= mf)) {
        gtk_label_set_text(GTK_LABEL(label_msg), "Erreur : fin doit être après début.");
        return;
    }

    /* Lire combo specialite + centre */
    strcpy(specialite, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_specialite)));
    strcpy(centre,     gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre)));

    /* Lire sexe souhaité */
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_h))) strcpy(sexe, "Homme");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_f))) strcpy(sexe, "Femme");
    

    /* Calculer coachs disponibles (même logique que tableau_salle_disponible) */
    n = tableau_coachs_disponibles(noms, 200,
                                   specialite, sexe, centre,
                                   d,
                                   hd, md, hf, mf,
                                   "coach.txt",
                                   "reservations_coach.txt");

    /* Remplir combo dynamique (comme atelier: comboBox3) */
    /* IMPORTANT : si tu veux vider correctement le combo, le plus simple est de recréer la fenêtre,
       OU de vider le modèle (comme on faisait). Ici, on fait le plus simple: on vide via model. */
    {
        GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(combo_coach));
        if (model != NULL) {
            GtkListStore *store = GTK_LIST_STORE(model);
            gtk_list_store_clear(store);
        }
    }

    for (i = 0; i < n; i++) {
        gtk_combo_box_append_text(GTK_COMBO_BOX(combo_coach), noms[i]);
    }

    if (n == 0) gtk_label_set_text(GTK_LABEL(label_msg), "Aucun coach disponible.");
    else gtk_label_set_text(GTK_LABEL(label_msg), "Liste coachs mise à jour.");
}


void
on_btn_confirmer_reser_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry_id,*entry_nom,*entry_prenom; 
    GtkWidget *entry_salle, *combo_centre, *combo_specialite, *combo_coach;
    GtkWidget *spin_jour, *spin_mois, *spin_annee;
    GtkWidget *spin_hd, *spin_md, *spin_hf, *spin_mf,*spin_nbre_seance;
    GtkWidget *radio_h, *radio_f;
    GtkWidget *label_msg;

    reservationCoach r;
    char buf[20];

    /* Widgets (adapte noms) */
    entry_id     = lookup_widget(GTK_WIDGET(button), "entry_id_membre_reser");
    entry_nom    = lookup_widget(GTK_WIDGET(button), "entry_nom_membre_reser");
    entry_prenom = lookup_widget(GTK_WIDGET(button), "entry_prenom_membre_reser");

    entry_salle  = lookup_widget(GTK_WIDGET(button), "combo_salle_prv");
    combo_centre = lookup_widget(GTK_WIDGET(button), "combo_centre_prv");

    combo_specialite = lookup_widget(GTK_WIDGET(button), "combo_spec_prv");
    combo_coach      = lookup_widget(GTK_WIDGET(button), "combo_nom_coach_prv");

    spin_jour  = lookup_widget(GTK_WIDGET(button), "spin_jour_reser");
    spin_mois  = lookup_widget(GTK_WIDGET(button), "spin_mois_reserr");
    spin_annee = lookup_widget(GTK_WIDGET(button), "spin_annee_reser_prv");
    spin_nbre_seance = lookup_widget(GTK_WIDGET(button),"spin_nbre_seance_prv");

    spin_hd = lookup_widget(GTK_WIDGET(button), "spin_hr_debut_prv");
    spin_md = lookup_widget(GTK_WIDGET(button), "spin_min_debut_prv");
    spin_hf = lookup_widget(GTK_WIDGET(button), "spin_hr_fin_prv");
    spin_mf = lookup_widget(GTK_WIDGET(button), "spin_min_fin_prv");

    radio_h = lookup_widget(GTK_WIDGET(button), "radio_sex_H_coach_prv");
    radio_f = lookup_widget(GTK_WIDGET(button), "radio_sex_F_coach_prv");
    
    label_msg = lookup_widget(GTK_WIDGET(button), "label_succes_reser");

    /* ID membre */
    strcpy(buf, gtk_entry_get_text(GTK_ENTRY(entry_id)));
    if (buf[0] == '\0') { gtk_label_set_text(GTK_LABEL(label_msg), "ID membre obligatoire."); return; }
    r.id_membre = atoi(buf);

    /* nom/prenom */
    strcpy(r.nom_membre, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    strcpy(r.prenom_membre, gtk_entry_get_text(GTK_ENTRY(entry_prenom)));
    if (strlen(r.nom_membre) == 0 || strlen(r.prenom_membre) == 0) {
        gtk_label_set_text(GTK_LABEL(label_msg), "Nom et prénom obligatoires."); return;
    }

    /* centre + salle */
    strcpy(r.centre, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre)));
    strcpy(r.salle, gtk_combo_box_get_active_text(GTK_COMBO_BOX(entry_salle)));
    if (strlen(r.salle) == 0) { gtk_label_set_text(GTK_LABEL(label_msg), "Salle obligatoire."); return; }

    /* spécialité + coach sélectionné */
    strcpy(r.specialite, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_specialite)));
    if (gtk_combo_box_get_active(GTK_COMBO_BOX(combo_coach)) == -1) {
        gtk_label_set_text(GTK_LABEL(label_msg), "Choisir un coach."); return;
    }
    strcpy(r.coach, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_coach)));

    /* sexe souhaité */
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_h))) strcpy(r.sexe, "Homme");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_f))) strcpy(r.sexe, "Femme");
    else strcpy(r.sexe, "Indiff");

    /* date + créneau */
    r.date.jour  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_jour));
    r.date.mois  = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mois));
    r.date.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_annee));
    r.nbre_seance = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_nbre_seance));

    r.hd = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_hd));
    r.md = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_md));
    r.hf = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_hf));
    r.mf = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_mf));

    if (r.hd > r.hf || (r.hd == r.hf && r.md >= r.mf)) {
        gtk_label_set_text(GTK_LABEL(label_msg), "Créneau invalide."); return;
    }

    /* écrire dans fichier */
    reserver_coach(r, "reservations_coach.txt");
    gtk_label_set_text(GTK_LABEL(label_msg), "Réservation enregistrée.");
}

gboolean
on_drawinHist_expose_event             (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{cairo_t *cr;
    int w, h, margin;
    int maxv;
    double scale;
    double bw, xH, xF;
    double hH, hF;

    w = widget->allocation.width;
    h = widget->allocation.height;
    margin = 30;

    cr = gdk_cairo_create(widget->window);

    /* Fond blanc */
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_rectangle(cr, 0, 0, w, h);
    cairo_fill(cr);

    /* Axes */
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);
    cairo_move_to(cr, margin, margin);
    cairo_line_to(cr, margin, h - margin);
    cairo_line_to(cr, w - margin, h - margin);
    cairo_stroke(cr);

    /* Déterminer max */
    maxv = g_nb_h;
    if (g_nb_f > maxv) maxv = g_nb_f;
    if (maxv <= 0) maxv = 1;

    /* échelle verticale */
    scale = (h - 2 * margin - 10) / (double)maxv;

    /* largeur barres */
    bw = (w - 2 * margin) / 5.0;
    xH = margin + bw * 1.2;
    xF = margin + bw * 3.0;

    hH = g_nb_h * scale;
    hF = g_nb_f * scale;

    /* Barre Homme (bleu) */
    cairo_set_source_rgb(cr, 0.2, 0.4, 0.9);
    cairo_rectangle(cr, xH, (h - margin) - hH, bw, hH);
    cairo_fill(cr);

    /* Barre Femme (rose) */
    cairo_set_source_rgb(cr, 0.9, 0.3, 0.5);
    cairo_rectangle(cr, xF, (h - margin) - hF, bw, hF);
    cairo_fill(cr);

    /* Texte */
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12);

    cairo_move_to(cr, xH, h - margin + 18);
    cairo_show_text(cr, "Homme");

    cairo_move_to(cr, xF, h - margin + 18);
    cairo_show_text(cr, "Femme");

    cairo_destroy(cr);

  return FALSE;
}


void
on_btn_stats_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{GtkWidget *drawing;
    GtkWidget *label;
    char msg[80];

    drawing = lookup_widget(GTK_WIDGET(button), "drawinHist");
    label   = lookup_widget(GTK_WIDGET(button), "label_stats");

    /* Calcul */
    if (!compter_homme_femme("membre.txt", &g_nb_h, &g_nb_f)) {
        if (label != NULL)
            gtk_label_set_text(GTK_LABEL(label), "Erreur : membre.txt introuvable.");
        return;
    }

    sprintf(msg, "Homme: %d   Femme: %d", g_nb_h, g_nb_f);
    if (label != NULL)
        gtk_label_set_text(GTK_LABEL(label), msg);

    /* Redessiner le graphe */
    if (drawing != NULL)
        gtk_widget_queue_draw(drawing);

}

////////////FONCTION SEIF////////////////////////////////

void
on_Retour_equipement_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_Actualiser_equipementclicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_btn_afficher_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_categorie_equipement_reserver_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{

}
void
on_btn_rechercher_equipement_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{

}
void
on_btn_valider_ajout_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}
void
on_btn_modifier_equipement_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}
void
on_treeview_equipement_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}
void
on_btn_reserver_equipement_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}

////////////// FONCTION MOLKA /////////////////////////////////////////
void
on_btn_ajouter_centre_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}
void
on_btn_rechercher_centre_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}

void
on_button_rechercher_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button_modifier_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

}

void
on_radiobutton_homme_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_femme_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobutton_mixte_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_btn_afficher_centre_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_treeview_centre_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}




void
on_btn_ajouter_entraineur_clicked      (GtkButton       *button,
                                        gpointer         user_data)
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
on_btn_ajouter_event_clicked           (GtkButton       *button,
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
on_treeview_entraineur_row_activated   (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_treeview_cours_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}







void
on_treeview_event_row_activated        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_button67_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_button68_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_button69_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_button70_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_button71_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
}










void
on_btn_ajouter_membre_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

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
