#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "membre.h"


int ajouter_membre(char *filename, membre m) {
    FILE *f = fopen(filename, "a");
    if(f != NULL) {
        fprintf(f, "%d %s %s %s %s %d %s %d %s %.2f %.2f %.2f %s %d %s %s %s %d %d \n",
                m.id, m.nom, m.prenom, m.centre, m.email,
                m.jour, m.mois, m.annee, m.type_abonnement,
                m.poids, m.masse_musculaire, m.masse_graisseuse,
                m.sexe, m.taille, m.objectif,
                m.descr_maladie, m.num_tel,m.duree_prog, m.maladie);
        fclose(f);
        return 1;
    }
    else 
        return 0;
}

void afficher_membres_treeview(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    int id;
    char nom[30];
    char prenom[30];
    char centre[40];
    char email[30];
    int jour;
    char mois[30];
    int annee;
    char type_abonnement[40];
    float poids;
    float masse_musculaire;
    float masse_graisseuse;
    char sexe[20];
    int taille;
    char objectif[40];
    char descr_maladie[100];
    char num_tel[20];
    int duree_prog;
    int maladie;
    FILE *f;

    
    if (liste == NULL)
        return;

    
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL)
    {
        

        // 1
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 2
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 3
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", PRENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 4
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("centre", renderer, "text", CENTRE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 5
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("email", renderer, "text", EMAIL, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 6
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text", JOUR, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 7
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text", MOIS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 8
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text", ANNEE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 9
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("type_abonnement", renderer, "text", TYPE_ABONNEMENT, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 10
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("poids", renderer, "text", POIDS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 11
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("masse_musculaire", renderer, "text", MASSE_MUSCU, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 12
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("masse_graisseuse", renderer, "text", MASSE_GRAISS, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 13
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text", SEXE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 14
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("taille", renderer, "text", TAILLE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 15
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("objectif", renderer, "text", OBJECTIF, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 16
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("descr_maladie", renderer, "text", DESC_MALADIE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 17
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("num_tel", renderer, "text", TELEPHONE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 18
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("duree_prog", renderer, "text", DUREE_PROG, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        // 19
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("maladie", renderer, "text", MALADIE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        
        store = gtk_list_store_new(
            COLUMNS,
            G_TYPE_INT,    
            G_TYPE_STRING, 
            G_TYPE_STRING, 
            G_TYPE_STRING, 
            G_TYPE_STRING, 
            G_TYPE_INT,    
            G_TYPE_STRING, 
            G_TYPE_INT,    
            G_TYPE_STRING, 
            G_TYPE_FLOAT,  
            G_TYPE_FLOAT,  
            G_TYPE_FLOAT,  
            G_TYPE_STRING, 
            G_TYPE_INT,    
            G_TYPE_STRING, 
            G_TYPE_STRING, 
            G_TYPE_STRING, 
            G_TYPE_INT,    
            G_TYPE_INT     
        );
    }
    else
    {
        
        gtk_list_store_clear(store);
    }

    
    f = fopen("membre.txt", "r");
    if (f == NULL)
    {
        
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        return;
    }

    
    while (fscanf(f,
                  "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %d %d",
                  &id, nom, prenom, centre, email,
                  &jour, mois, &annee, type_abonnement,
                  &poids, &masse_musculaire, &masse_graisseuse,
                  sexe, &taille, objectif,
                  descr_maladie, num_tel, &duree_prog, &maladie) != EOF)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           ID, id,
                           NOM, nom,
                           PRENOM, prenom,
                           CENTRE, centre,
                           EMAIL, email,
                           JOUR, jour,
                           MOIS, mois,
                           ANNEE, annee,
                           TYPE_ABONNEMENT, type_abonnement,
                           POIDS, poids,
                           MASSE_MUSCU, masse_musculaire,
                           MASSE_GRAISS, masse_graisseuse,
                           SEXE, sexe,
                           TAILLE, taille,
                           OBJECTIF, objectif,
                           DESC_MALADIE, descr_maladie,
                           TELEPHONE, num_tel,
                           DUREE_PROG, duree_prog,
                           MALADIE, maladie,
                           -1);
    }

    fclose(f);

    
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));

    
    g_object_unref(store);
}


void vider(GtkWidget *liste){
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
int id;
char nom[30];
char prenom[30];
char centre[40];
char email[30];
int jour;
char mois[30];
int annee;
char type_abonnement[40];
float poids;
float masse_musculaire;
float masse_graisseuse;
char sexe[20];
int taille;
char objectif[40];
char descr_maladie[100];
char num_tel[20];
int duree_prog;
int maladie;
store = NULL;
FILE *f;
store = gtk_tree_view_get_model(liste);
if(store==NULL)
//1
{renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("id",renderer,"text",ID,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//2
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("nom",renderer,"text",NOM,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//3
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("prenom",renderer,"text",PRENOM,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//4
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("centre",renderer,"text",CENTRE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//5
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("email",renderer,"text",EMAIL,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//6
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("jour",renderer,"text",JOUR,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//7
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("mois",renderer,"text",MOIS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//8
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("annee",renderer,"text",ANNEE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//9
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("type_abonnement",renderer,"text",TYPE_ABONNEMENT,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//10
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("poids",renderer,"text",POIDS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//11
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("masse_musculaire",renderer,"text",MASSE_MUSCU,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//12
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("masse_graisseuse",renderer,"text",MASSE_GRAISS,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//13
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("sexe",renderer,"text",SEXE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

//14
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("taille",renderer,"text",TAILLE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

//15
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("objectif",renderer,"text",OBJECTIF,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//16
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("descr_maladie",renderer,"text",DESC_MALADIE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//17
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("num_tel",renderer,"text",TELEPHONE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//18
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("duree_prog",renderer,"text",DUREE_PROG,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
//19
renderer = gtk_cell_renderer_text_new();
column = gtk_tree_view_column_new_with_attributes("maladie",renderer,"text",MALADIE,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
}
store = gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,
			   G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_FLOAT,G_TYPE_FLOAT,G_TYPE_FLOAT,G_TYPE_STRING,G_TYPE_INT,
                           G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT);
gtk_list_store_append(store,&iter);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));



}
int modifier_membre(char *filename, int id, membre nouv) {
    membre m;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if (f == NULL || aux == NULL)
        return 0;

    while (fscanf(f, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %d %d",
                  &m.id, m.nom, m.prenom, m.centre, m.email,
                  &m.jour, m.mois, &m.annee, m.type_abonnement,
                  &m.poids, &m.masse_musculaire, &m.masse_graisseuse,
                  m.sexe, &m.taille, m.objectif,
                  m.descr_maladie, m.num_tel, &m.duree_prog, &m.maladie) != EOF) {
        if (m.id == id) {
            fprintf(aux, "%d %s %s %s %s %d %s %d %s %.2f %.2f %.2f %s %d %s %s %s %d %d \n",
                    m.id, nouv.nom, nouv.prenom, nouv.centre, nouv.email,
                    nouv.jour, nouv.mois, nouv.annee, nouv.type_abonnement,
                    nouv.poids, nouv.masse_musculaire, nouv.masse_graisseuse,
                    nouv.sexe, nouv.taille, nouv.objectif,
                    nouv.descr_maladie, nouv.num_tel, nouv.duree_prog, nouv.maladie);
            trouve = 1;
        } else {
            fprintf(aux, "%d %s %s %s %s %d %s %d %s %.2f %.2f %.2f %s %d %s %s %s %d %d \n",
                    m.id, m.nom, m.prenom, m.centre, m.email,
                    m.jour, m.mois, m.annee, m.type_abonnement,
                    m.poids, m.masse_musculaire, m.masse_graisseuse,
                    m.sexe, m.taille, m.objectif,
                    m.descr_maladie, m.num_tel, m.duree_prog, m.maladie);
        }
    }

    fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);
    return trouve;
}

int supprimer_membre(char *filename, int id) {
    membre m;
    FILE *f = fopen(filename, "r");
    FILE *aux = fopen("aux.txt", "w");
    int trouve = 0;

    if (f == NULL || aux == NULL)
        return 0;

    while (fscanf(f, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %d %d",
                  &m.id, m.nom, m.prenom, m.centre, m.email,
                  &m.jour, m.mois, &m.annee, m.type_abonnement,
                  &m.poids, &m.masse_musculaire, &m.masse_graisseuse,
                  m.sexe, &m.taille, m.objectif,
                  m.descr_maladie, m.num_tel, &m.duree_prog, &m.maladie) != EOF) {
        if (m.id != id) {
            fprintf(aux, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %d %d\n",
                    m.id, m.nom, m.prenom, m.centre, m.email,
                    m.jour, m.mois, m.annee, m.type_abonnement,
                    m.poids, m.masse_musculaire, m.masse_graisseuse,
                    m.sexe, m.taille, m.objectif,
                    m.descr_maladie, m.num_tel, m.duree_prog, m.maladie);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(aux);
    remove(filename);
    rename("aux.txt", filename);
    return trouve;
}

membre chercher_membre(char *filename, int id) {
    membre m;
    membre vide = {-1};
    
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return vide;

    while (fscanf(f, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d %s %s %s %d %d",
                  &m.id, m.nom, m.prenom, m.centre, m.email,
                  &m.jour, m.mois, &m.annee, m.type_abonnement,
                  &m.poids, &m.masse_musculaire, &m.masse_graisseuse,
                  m.sexe, &m.taille, m.objectif,
                  m.descr_maladie, m.num_tel, &m.duree_prog, &m.maladie) != EOF) {
        if (m.id == id) {
            fclose(f);
            return m;
        }
    }

    fclose(f);
    return vide;
}

void afficher_membre(char *filename) {
    membre m;
    FILE *f = fopen(filename, "r");
    
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier!\n");
        return;
    }
    
    printf("\n=== LISTE DES MEMBRES ===\n");
    while (fscanf(f, "%d %s %s %s %s %d %s %d %s %f %f %f %s %d  %s %s %s %d %d ",
                  &m.id, m.nom, m.prenom, m.centre, m.email,
                  &m.jour, m.mois, &m.annee, m.type_abonnement,
                  &m.poids, &m.masse_musculaire, &m.masse_graisseuse,
                  m.sexe, &m.taille, m.objectif,
                  m.descr_maladie, m.num_tel, &m.duree_prog, &m.maladie) != EOF) {
        printf("ID: %d\n", m.id);
        printf("Nom: %s\n", m.nom);
        printf("Prenom: %s\n", m.prenom);
        printf("Centre: %s\n", m.centre);
        printf("Email: %s\n", m.email);
        printf("Date de naissance: %d %s %d\n", m.jour, m.mois, m.annee);
        printf("Type abonnement: %s\n", m.type_abonnement);
        printf("Poids: %.2f kg\n", m.poids);
        printf("Masse musculaire: %f kg\n", m.masse_musculaire);
        printf("Masse graisseuse: %f kg\n", m.masse_graisseuse);
        printf("Sexe: %s\n", m.sexe);
        printf("Taille: %d cm\n", m.taille);
        printf("Objectif: %s\n", m.objectif);
        printf("Maladies: %s\n", m.descr_maladie);
        printf("Telephone: %s\n", m.num_tel);
	printf("duree programme: %d\n", m.duree_prog);
	printf("maladie: %d\n", m.maladie);
        printf("---------------------------\n");
    }
    
    fclose(f);} 

   static int toMin(int h, int m) { return h * 60 + m; }

/* Chevauchement [a1,a2[ et [b1,b2[ */
static int chevauche(int a1, int a2, int b1, int b2)
{
    return (a1 < b2) && (b1 < a2);
}
int tableau_reservations_coach(reservationCoach tab[], int max, char fichier[100])
{
    FILE *f;
    int n = 0;

    f = fopen(fichier, "r");
    if (f == NULL) return 0;

    /* Format (1 réservation / ligne), à garder stable :
       id nom prenom centre salle coach specialite sexe jour mois annee hd md hf mf
       Exemple :
       12 Amine Fahem CentreA Salle1 "Ali Karim" Muscu Homme 19 11 2025 9 0 10 30
       IMPORTANT : Pour éviter les espaces dans coach, on stocke coach en "Nom_Prenom"
                  ou on écrit nomCoach et prenomCoach séparés.
       -> Ici je conseille : coach = Nom_Prenom (underscore).
    */

    while (n < max &&
           fscanf(f, "%d %29s %29s %39s %29s %59s %29s %9s %d %d %d %d %d %d %d",
                  &tab[n].id_membre,
                  tab[n].nom_membre,
                  tab[n].prenom_membre,
                  tab[n].centre,
                  tab[n].salle,
                  tab[n].coach,
                  tab[n].specialite,
                  tab[n].sexe,
                  &tab[n].date.jour,
                  &tab[n].date.mois,
                  &tab[n].date.annee,
                  &tab[n].hd, &tab[n].md,
                  &tab[n].hf, &tab[n].mf) == 15)
    {
        n++;
    }

    fclose(f);
    return n;
}

int verifier_reservation_coach(reservationCoach tab[], int n,
                               char coach[60], char centre[40],
                               Date d,
                               int hd, int md, int hf, int mf)
{
    int i;
    int deb_new = toMin(hd, md);
    int fin_new = toMin(hf, mf);

    for (i = 0; i < n; i++) {
        if (strcmp(tab[i].coach, coach) != 0) continue;
        if (strcmp(tab[i].centre, centre) != 0) continue;

        if (tab[i].date.jour  != d.jour)  continue;
        if (tab[i].date.mois  != d.mois)  continue;
        if (tab[i].date.annee != d.annee) continue;

        {
            int deb_old = toMin(tab[i].hd, tab[i].md);
            int fin_old = toMin(tab[i].hf, tab[i].mf);
            if (chevauche(deb_new, fin_new, deb_old, fin_old))
                return 1; /* réservé (conflit) */
        }
    }
    return 0; /* pas réservé */
}
int tableau_coachs_disponibles(char noms[][60], int max,
                               char specialite[30], char sexe[10],
                               char centre[40],
                               Date d,
                               int hd, int md, int hf, int mf,
                               char f_coachs[100], char f_reserve[100])
{
    FILE *f;
    reservationCoach tabRes[1000];
    int nRes, nb = 0;

    /* Charger les réservations existantes */
    nRes = tableau_reservations_coach(tabRes, 1000, f_reserve);

    /* Parcourir coachs depuis coach.txt */
    f = fopen(f_coachs, "r");
    if (f == NULL) return 0;

    /* Format coach.txt (simple, 1 coach/ligne) :
       coach specialite sexe centre
       Exemple :
       Ali_Karim Muscu Homme CentreA
       Leila_Amara Muscu Femme CentreB
    */

    while (nb < max) {
        char coach[60];
        char spec[30];
        char sx[10];
        char ctr[40];

        if (fscanf(f, "%59s %29s %9s %39s", coach, spec, sx, ctr) != 4)
            break;

        /* Filtre spécialité */
        if (strcmp(spec, specialite) != 0) continue;

        /* Filtre centre */
        if (strcmp(ctr, centre) != 0) continue;

        /* Filtre sexe (si sexe == "Indiff" ou "" => pas de filtre) */
        if (strcmp(sexe, "Indiff") != 0 && strcmp(sexe, "") != 0) {
            if (strcmp(sx, sexe) != 0) continue;
        }

        /* Filtre disponibilité (conflit réservation) */
        if (verifier_reservation_coach(tabRes, nRes, coach, centre, d, hd, md, hf, mf))
            continue;

        /* OK => ajouter à la liste */
        strcpy(noms[nb], coach);
        nb++;
    }

    fclose(f);
    return nb;
}
void reserver_coach(reservationCoach r, char f_reserve[100])
{
    FILE *f = fopen(f_reserve, "a");
    if (f == NULL) return;

    fprintf(f, "%d %s %s %s %s %s %s %s %d %d %d %d %d %d %d %d\n",
            r.id_membre,
            r.nom_membre,
            r.prenom_membre,
            r.centre,
            r.salle,
            r.coach,
            r.specialite,
            r.sexe,
            r.date.jour,
            r.date.mois,
            r.date.annee,
            r.hd, r.md, r.hf, r.mf,r.nbre_seance);

    fclose(f);
}

int compter_homme_femme(char fichier[100], int *nb_h, int *nb_f)
{
    FILE *f;
    char ligne[512];

    *nb_h = 0;
    *nb_f = 0;

    f = fopen(fichier, "r");
    if (f == NULL)
        return 0;

    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        if (strstr(ligne, "Homme") != NULL) (*nb_h)++;
        else if (strstr(ligne, "Femme") != NULL) (*nb_f)++;
    }

    fclose(f);
    return 1;
}


























