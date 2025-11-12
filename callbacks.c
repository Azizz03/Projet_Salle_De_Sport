#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
void on_bajout_clicked(GtkWidget* og, gpointer data){
    GtkWidget *j;
    GtkWidget *m;
    GtkWidget *a;
    GtkWidget *cb1;
    GtkWidget *cb2;
    GtkWidget *check;
    GtkWidget *id;
    GtkWidget *email;
    GtkWidget *nom;
    GtkWidget *pren;
    GtkWidget *salaire;
    GtkWidget *num;
    GtkWidget *h;
    GtkWidget *f;

    entreneur e;
    
    j = lookup_widget(og, "JOUR");
    m = lookup_widget(og, "MOIS");
    a = lookup_widget(og, "ANNEE");
    id = lookup_widget(og, "id");
    check= lookup_widget(og, "cp");   
    nom = lookup_widget(og, "nom");
    pren = lookup_widget(og, "pre");
    salaires = lookup_widget(og, "s");  //verifie salaires ou salaire
    cb1= lookup_widget(og, "spe");
    cb2= lookup_widget(og, "centre");
    //sexe= lookup_widget(og, "spe"); esr ce que c'est neccesaire 
    num= lookup_widget(og, "num");
    email= lookup_widget(og, "em");
    h= lookup_widget(og, "h");
    f= lookup_widget(og, "f");

    e.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(j));
    e.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(m));
    e.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(a));
    const gchar *email_text = email   ? gtk_entry_get_text(GTK_ENTRY(email)) : "";
    const gchar *num_text   = num     ? gtk_entry_get_text(GTK_ENTRY(num)) : "";
    const gchar *sal_text   = salaires ? gtk_entry_get_text(GTK_ENTRY(salaires)) : "";
    const gchar *id_text=gtk_get_text(GTK_ENTRY(id));
    gchar *nom_text=gtk_get_text(GTK_ENTRY(nom));
    gchar *pren_text=gtk_get_text(GTK_ENTRY(pren));
    strncpy(e.id,      id_text,    sizeof(e.id)-1);      e.id[sizeof(e.id)-1] = '\0';
    strncpy(e.nom,     nom_text,   sizeof(e.nom)-1);     e.nom[sizeof(e.nom)-1] = '\0';
    strncpy(e.prenom,  pren_text,  sizeof(e.prenom)-1);  e.prenom[sizeof(e.prenom)-1] = '\0';
    strncpy(e.email,   email_text, sizeof(e.email)-1);   e.email[sizeof(e.email)-1] = '\0';
    strncpy(e.num_tel, num_text,   sizeof(e.num_tel)-1); e.num_tel[sizeof(e.num_tel)-1] = '\0';
    //salaire 
     if (sal_text && strlen(sal_text) > 0) {
        e.salaires = atof(sal_text);
    } else {
        e.salaires = 0.0;
    }

     /*gchar *spec = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(cb1));
     gchar *c = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(cb2));
    if(spec) {
            strcpy(e->specialite,spec,sizeof(e->specialite)-1);
            e->specialite[sizeof(e->specialite)-1]='\0';
            g_free(spec);
        }  else
        e->specialite[0]='\0';
    if(c) {
            strcpy(e->centre,c,sizeof(e->centre)-1);
            e->centre[sizeof(e->centre)-1]='\0';
            g_free(c);
        }  else
        e->centre[0]='\0'; */  
    if (check) {
        gboolean checked = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check));
        e.cours_privee = checked ? 1 : 0;
    } else 
        e.cours_privee = 0;
    

    gchar *spec = NULL;
    gchar *c = NULL;
    if (cb1) {
        spec = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cb1));
        if (spec) {
            strncpy(e.specialite, spec, sizeof(e.specialite)-1);
            e.specialite[sizeof(e.specialite)-1] = '\0';
            g_free(spec);
            spec = NULL;
        } else {
            e.specialite[0] = '\0';
        }
    } else {
        e.specialite[0] = '\0';
    }

    if (cb2) {
        c = gtk_combo_box_get_active_text(GTK_COMBO_BOX(cb2));
        if (c) {
            strncpy(e.centre, c, sizeof(e.centre)-1);
            e.centre[sizeof(e.centre)-1] = '\0';
            g_free(c);
            c = NULL;
        } else {
            e.centre[0] = '\0';
        }
    } else {
        e.centre[0] = '\0';
    }
     if (h && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(h))) {
        strncpy(e.sexe, "H", sizeof(e.sexe)-1);
        e.sexe[sizeof(e.sexe)-1] = '\0';
    } else if (f && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(f))) {
        strncpy(e.sexe, "F", sizeof(e.sexe)-1);
        e.sexe[sizeof(e.sexe)-1] = '\0';
    } else {
        e.sexe[0] = '\0';
    }
    
}

    