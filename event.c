/* En-têtes minimaux et suffisants pour event.c */
#include "event.h"

#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <errno.h>      
#include <limits.h>     
#include <unistd.h>     
#include <sys/types.h>  
#include <sys/wait.h>   
#include <ctype.h>  /* isspace() */
#include <fcntl.h>


static void trim_inplace(char *s)
{
    if (!s) return;
    /* trim right */
    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len-1])) { s[--len] = '\0'; }
    /* trim left */
    char *p = s;
    while (*p && isspace((unsigned char)*p)) ++p;
    if (p != s) memmove(s, p, strlen(p) + 1);
}

/* helper : sanitize champs texte pour enlever '|' et nouvelles lignes */
static void sanitize_field(char *dst, const char *src, size_t dstsize)
{
    if (!dst || !src || dstsize == 0) return;
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0' && j + 1 < dstsize; ++i) {
        char c = src[i];
        if (c == '|' || c == '\n' || c == '\r') {
            /* remplacer séparateur problématique par espace */
            if (j + 1 < dstsize) dst[j++] = ' ';
        } else {
            dst[j++] = c;
        }
    }
    dst[j] = '\0';
    trim_inplace(dst);
}

/* écrire un événement au format pipe (13 champs) */
int ajouter_event(char *filename, event e)
{
    if (!filename) return 0;

    enum { MAX_NOM = 199, MAX_TYPE = 99, MAX_SALLE = 99 };
    char nom_safe[MAX_NOM + 1];
    char type_safe[MAX_TYPE + 1];
    char salle_safe[MAX_SALLE + 1];

    /* sanitize + trim + truncate */
    sanitize_field(nom_safe, e.nom ? e.nom : "", sizeof(nom_safe));
    sanitize_field(type_safe, e.type ? e.type : "", sizeof(type_safe));
    sanitize_field(salle_safe, e.salle ? e.salle : "", sizeof(salle_safe));

    /* si champ vide, mettre une valeur vide (mais le champ existe) */
    if (nom_safe[0] == '\0') strncpy(nom_safe, "(nom)", sizeof(nom_safe)-1);
    if (type_safe[0] == '\0') strncpy(type_safe, "(type)", sizeof(type_safe)-1);
    if (salle_safe[0] == '\0') strncpy(salle_safe, "(salle)", sizeof(salle_safe)-1);

    /* Construire la ligne : exactement 13 champs séparés par '|' */
    char line[512];
    int n = snprintf(line, sizeof(line),
                     "%d|%s|%s|%d|%d|%d|%d|%d|%d|%d|%.2f|%s|%d\n",
                     e.id,
                     nom_safe,
                     type_safe,
                     e.jour, e.mois, e.annee,
                     e.heure_debut_h, e.heure_debut_m,
                     e.heure_fin_h, e.heure_fin_m,
                     (double)e.prix,
                     salle_safe,
                     e.capacite);

    if (n < 0 || n >= (int)sizeof(line)) {
        fprintf(stderr, "ajouter_event: snprintf failed or line too long (n=%d)\n", n);
        return 0;
    }

    FILE *f = fopen(filename, "a");
    if (!f) {
        fprintf(stderr, "ajouter_event: cannot open %s: %s\n", filename, strerror(errno));
        return 0;
    }

    if (fputs(line, f) == EOF) {
        fprintf(stderr, "ajouter_event: write failed: %s\n", strerror(errno));
        fclose(f);
        return 0;
    }

    fflush(f);
    fsync(fileno(f)); /* s'assurer que l'OS flush sur disque (utile pour debug) */
    fclose(f);

    /* log de debug (optionnel) */
    fprintf(stdout, "ajouter_event: OK -> %s", line);
    return 1;
}

//////////////////////
// GESTION ÉVÉNEMENTS
//////////////////////







static int parse_event_line(const char *line, event *out)
{
    if (!line || !out) return 0;
    char *buf = strdup(line);
    if (!buf) return 0;
    /* enlever '\n' final */
    char *p = strchr(buf, '\n');
    if (p) *p = '\0';

    char *save = NULL;
    char *tok = strtok_r(buf, "|", &save);
    int i = 0;
    memset(out, 0, sizeof(*out));
    while (tok && i < 13) {
        trim_inplace(tok);
        switch (i) {
            case 0: out->id = atoi(tok); break;
            case 1: strncpy(out->nom, tok, sizeof(out->nom)-1); break;
            case 2: strncpy(out->type, tok, sizeof(out->type)-1); break;
            case 3: out->jour = atoi(tok); break;
            case 4: out->mois = atoi(tok); break;
            case 5: out->annee = atoi(tok); break;
            case 6: out->heure_debut_h = atoi(tok); break;
            case 7: out->heure_debut_m = atoi(tok); break;
            case 8: out->heure_fin_h = atoi(tok); break;
            case 9: out->heure_fin_m = atoi(tok); break;
            case 10: out->prix = (float)atof(tok); break;
            case 11: strncpy(out->salle, tok, sizeof(out->salle)-1); break;
            case 12: out->capacite = atoi(tok); break;
        }
        i++;
        tok = strtok_r(NULL, "|", &save);
    }

    free(buf);
    /* on considère réussi si on a lu au moins l'id (champ 0) */
    return (i >= 1) ? 1 : 0;
}

/* modifier_event : remplace la ligne dont id == id par la struct nouv (format pipe 13 champs).
   Retourne 1 si modifié, 0 sinon. */
int modifier_event(const char *filename, int id, event nouv)
{
    if (!filename) return 0;

    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("modifier_event: fopen");
        return 0;
    }

    char tmp_template[PATH_MAX];
    if ((size_t)snprintf(tmp_template, sizeof(tmp_template), "%s.tmpXXXXXX", filename)
        >= sizeof(tmp_template)) {
        fclose(f);
        fprintf(stderr, "modifier_event: filename too long\n");
        return 0;
    }

    int tmpfd = mkstemp(tmp_template);
    if (tmpfd == -1) {
        perror("modifier_event: mkstemp");
        fclose(f);
        return 0;
    }

    FILE *out = fdopen(tmpfd, "w");
    if (!out) {
        perror("modifier_event: fdopen");
        close(tmpfd);
        unlink(tmp_template);
        fclose(f);
        return 0;
    }

    char line[4096];
    int found = 0;

    /* sécuriser champs texte de nouv avant écriture */
    char nom_safe[256], type_safe[128], salle_safe[128];
    sanitize_field(nom_safe, nouv.nom ? nouv.nom : "", sizeof(nom_safe));
    sanitize_field(type_safe, nouv.type ? nouv.type : "", sizeof(type_safe));
    sanitize_field(salle_safe, nouv.salle ? nouv.salle : "", sizeof(salle_safe));
    if (nom_safe[0] == '\0') strncpy(nom_safe, "(nom)", sizeof(nom_safe)-1);
    if (type_safe[0] == '\0') strncpy(type_safe, "(type)", sizeof(type_safe)-1);
    if (salle_safe[0] == '\0') strncpy(salle_safe, "(salle)", sizeof(salle_safe)-1);

    while (fgets(line, sizeof(line), f) != NULL) {
        event cur;
        if (!parse_event_line(line, &cur)) {
            /* ligne mal formée -> recopier brute */
            if (fputs(line, out) == EOF) {
                perror("modifier_event: fputs");
                fclose(f);
                fclose(out);
                unlink(tmp_template);
                return 0;
            }
            continue;
        }

        if (cur.id == id) {
            /* écrire la nouvelle ligne au format identique à ajouter_event */
            if (fprintf(out, "%d|%s|%s|%d|%d|%d|%d|%d|%d|%d|%.2f|%s|%d\n",
                        nouv.id,
                        nom_safe,
                        type_safe,
                        nouv.jour, nouv.mois, nouv.annee,
                        nouv.heure_debut_h, nouv.heure_debut_m,
                        nouv.heure_fin_h, nouv.heure_fin_m,
                        (double)nouv.prix,
                        salle_safe,
                        nouv.capacite) < 0) {
                perror("modifier_event: fprintf");
                fclose(f);
                fclose(out);
                unlink(tmp_template);
                return 0;
            }
            found = 1;
        } else {
            /* recopier la ligne originale telle quelle (on la préserve) */
            if (fputs(line, out) == EOF) {
                perror("modifier_event: fputs2");
                fclose(f);
                fclose(out);
                unlink(tmp_template);
                return 0;
            }
        }
    }

    if (ferror(f) || ferror(out)) {
        perror("modifier_event: I/O error");
        fclose(f);
        fclose(out);
        unlink(tmp_template);
        return 0;
    }

    fclose(f);
    if (fclose(out) == EOF) {
        perror("modifier_event: fclose temp");
        unlink(tmp_template);
        return 0;
    }

    if (!found) {
        /* rien modifié -> supprimer temporaire */
        unlink(tmp_template);
        return 0;
    }

    if (rename(tmp_template, filename) != 0) {
        perror("modifier_event: rename");
        unlink(tmp_template);
        return 0;
    }

    return 1;
}

/* supprimer_event : supprime la ligne dont id == id.
   Retourne 1 si supprimé, 0 si introuvable ou erreur. */
int supprimer_event(const char *filename, int id)
{
    if (!filename) return 0;

    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("supprimer_event: fopen");
        return 0;
    }

    char tmp_template[PATH_MAX];
    if ((size_t)snprintf(tmp_template, sizeof(tmp_template), "%s.tmpXXXXXX", filename)
        >= sizeof(tmp_template)) {
        fclose(f);
        fprintf(stderr, "supprimer_event: filename too long\n");
        return 0;
    }

    int tmpfd = mkstemp(tmp_template);
    if (tmpfd == -1) {
        perror("supprimer_event: mkstemp");
        fclose(f);
        return 0;
    }

    FILE *out = fdopen(tmpfd, "w");
    if (!out) {
        perror("supprimer_event: fdopen");
        close(tmpfd);
        unlink(tmp_template);
        fclose(f);
        return 0;
    }

    char line[4096];
    int found = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        event cur;
        if (!parse_event_line(line, &cur)) {
            /* ligne mal formée -> recopier brute */
            if (fputs(line, out) == EOF) {
                perror("supprimer_event: fputs");
                fclose(f);
                fclose(out);
                unlink(tmp_template);
                return 0;
            }
            continue;
        }

        if (cur.id == id) {
            /* sauter la ligne -> suppression */
            found = 1;
            continue;
        } else {
            /* réécrire la ligne normalisée (pour garder format propre) */
            if (fprintf(out, "%d|%s|%s|%d|%d|%d|%d|%d|%d|%d|%.2f|%s|%d\n",
                        cur.id, cur.nom, cur.type,
                        cur.jour, cur.mois, cur.annee,
                        cur.heure_debut_h, cur.heure_debut_m,
                        cur.heure_fin_h, cur.heure_fin_m,
                        (double)cur.prix, cur.salle, cur.capacite) < 0) {
                perror("supprimer_event: fprintf");
                fclose(f);
                fclose(out);
                unlink(tmp_template);
                return 0;
            }
        }
    }

    if (ferror(f) || ferror(out)) {
        perror("supprimer_event: I/O error");
        fclose(f);
        fclose(out);
        unlink(tmp_template);
        return 0;
    }

    fclose(f);
    if (fclose(out) == EOF) {
        perror("supprimer_event: fclose temp");
        unlink(tmp_template);
        return 0;
    }

    if (!found) {
        unlink(tmp_template);
        return 0;
    }

    if (rename(tmp_template, filename) != 0) {
        perror("supprimer_event: rename");
        unlink(tmp_template);
        return 0;
    }

    return 1;
}


/* ---------- safe_supprimer_event ---------- */
/* Wrapper qui exécute supprimer_event dans un processus enfant pour protéger l'UI
   en cas de crash interne. Retourne :
     1  -> suppression réussie,
     0  -> id non trouvé,
    -1  -> erreur (fork/wait/child crash) */
int safe_supprimer_event(const char *filename, int id)
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("safe_supprimer_event: fork");
        return -1;
    }

    if (pid == 0) {
        /* enfant : exécute la suppression et quitte avec code 0 si ok, 1 sinon */
        int ok = supprimer_event(filename, id);
        _exit(ok == 1 ? 0 : 1);
    } else {
        int status;
        pid_t w = waitpid(pid, &status, 0);
        if (w == -1) {
            perror("safe_supprimer_event: waitpid");
            return -1;
        }
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            return (code == 0) ? 1 : 0;
        } else if (WIFSIGNALED(status)) {
            fprintf(stderr, "safe_supprimer_event: child killed by signal %d\n", WTERMSIG(status));
            return -1;
        } else {
            fprintf(stderr, "safe_supprimer_event: child ended abnormally\n");
            return -1;
        }
    }
}
event chercher_event(char *filename, int id)
{
    event e;
    e.id = -1; 
    FILE *f = fopen(filename, "r");

    if (f != NULL)
    {
        while (fscanf(f, "%d %s %s %d %d %d %d %d %d %d %f %s %d",
                      &e.id, e.nom, e.type, &e.jour, &e.mois, &e.annee,
                      &e.heure_debut_h, &e.heure_debut_m, &e.heure_fin_h, &e.heure_fin_m,
                      &e.prix, e.salle, &e.capacite) != EOF)
        {
            if (e.id == id)
                break;
        }
        fclose(f);
    }
    return e;
}

int afficher_event(char *filename)
{
    FILE *f = fopen(filename, "r");
    event e;
    int trouve = 0;

    if (f == NULL)
    {
        printf(" Erreur : impossible d’ouvrir le fichier %s pour lecture.\n", filename);
        return 0;
    }

    printf(" Liste des événements enregistrés :\n");
    printf("------------------------------------------------------------\n");

    while (fscanf(f, "%d %s %s %d %d %d %d %d %d %d %f %s %d",
                  &e.id, e.nom, e.type,
                  &e.jour, &e.mois, &e.annee,
                  &e.heure_debut_h, &e.heure_debut_m,
                  &e.heure_fin_h, &e.heure_fin_m,
                  &e.prix, e.salle, &e.capacite) != EOF)
    {
        trouve = 1;
        printf("ID : %d | %s (%s)\n", e.id, e.nom, e.type);
        printf("Date : %02d/%02d/%04d | Heure : %02d:%02d - %02d:%02d\n",
               e.jour, e.mois, e.annee,
               e.heure_debut_h, e.heure_debut_m,
               e.heure_fin_h, e.heure_fin_m);
        printf("Salle : %s | Prix : %.2f DT | Capacité : %d\n",
               e.salle, e.prix, e.capacite);
        printf("------------------------------------------------------------\n");
    }

    fclose(f);

    if (!trouve)
    {
        printf("  Aucun événement trouvé dans le fichier %s.\n", filename);
        return 0;
    }

    return 1;
}

/////////////////////////////
// GESTION DES PARTICIPATIONS
/////////////////////////////

int ajouter_participation(char *filename, participation p)
{
    static int CAPACITE_MAX = 50;

    if (CAPACITE_MAX <= 0)
    {
        printf("  L'événement est complet. Impossible d'ajouter la participation.\n");
        return 0;
    }

    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, "%d %s %s %s %d %s %s %d %d %d %d %.2f %s %s\n",
                p.id_membre, p.nom, p.prenom, p.sexe,
                p.id_event, p.nom_event, p.type_event,
                p.jour, p.mois, p.annee, p.heure, p.prix, p.salle, p.niveau);

        fclose(f);
        CAPACITE_MAX--;
        printf(" Participation ajoutée. Places restantes : %d\n", CAPACITE_MAX);
        return 1;
    }

    printf(" Erreur lors de l’ouverture du fichier.\n");
    return 0;
}


enum
{
    E_ID,
    E_NOM,
    E_TYPE,
    E_DATE,
    E_HEURE,
    E_SALLE,
    E_PRIX,
    E_CAPACITE,
    E_COLS
};


void afficher_event_treeview(GtkWidget *treeview, char *filename)
{
    GtkListStore      *store;
    GtkTreeIter        iter;
    GtkCellRenderer   *renderer;
    GtkTreeViewColumn *column;
    FILE              *f;
    event              e;
    char               date[32];
    char               heure[32];
    int rows = 0;

    if (!treeview || !GTK_IS_TREE_VIEW(treeview)) {
        g_warning("afficher_event_treeview : widget invalide");
        return;
    }

    /* 1) nouveau modèle */
    store = GTK_LIST_STORE(gtk_list_store_new(
        E_COLS,
        G_TYPE_INT,     /* E_ID       */
        G_TYPE_STRING,  /* E_NOM      */
        G_TYPE_STRING,  /* E_TYPE     */
        G_TYPE_STRING,  /* E_DATE     */
        G_TYPE_STRING,  /* E_HEURE    */
        G_TYPE_STRING,  /* E_SALLE    */
        G_TYPE_FLOAT,   /* E_PRIX     */
        G_TYPE_INT      /* E_CAPACITE */
    ));

    /* 2) colonnes (une seule fois) */
    static gboolean columns_created = FALSE;
    if (!columns_created) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", E_ID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", E_NOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", E_TYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", E_DATE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", E_HEURE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Salle", renderer, "text", E_SALLE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", E_PRIX, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", E_CAPACITE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        columns_created = TRUE;
    }

    /* 3) lecture du fichier */
    f = fopen(filename, "r");
    if (!f) {
        g_warning("afficher_event_treeview : impossible d'ouvrir %s", filename);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store);
        return;
    }

    g_print("afficher_event_treeview : lecture de %s\n", filename);

    {
        char line[1024];
        while (fgets(line, sizeof(line), f) != NULL) {
            /* retirer newline */
            size_t L = strlen(line);
            if (L && (line[L-1] == '\n' || line[L-1] == '\r')) line[L-1] = '\0';

            /* tokenizer '|' en priorité */
            char tmp[1024];
            strncpy(tmp, line, sizeof(tmp)-1);
            tmp[sizeof(tmp)-1] = '\0';

            char *saveptr = NULL;
            char *fields[13];
            int nf = 0;
            char *tok = strtok_r(tmp, "|", &saveptr);
            while (tok && nf < 13) { fields[nf++] = tok; tok = strtok_r(NULL, "|", &saveptr); }

            if (nf == 13) {
                e.id = (int)strtol(fields[0], NULL, 10);
                strncpy(e.nom, fields[1], sizeof(e.nom)-1); e.nom[sizeof(e.nom)-1] = '\0';
                strncpy(e.type, fields[2], sizeof(e.type)-1); e.type[sizeof(e.type)-1] = '\0';
                e.jour = (int)strtol(fields[3], NULL, 10);
                e.mois = (int)strtol(fields[4], NULL, 10);
                e.annee = (int)strtol(fields[5], NULL, 10);
                e.heure_debut_h = (int)strtol(fields[6], NULL, 10);
                e.heure_debut_m = (int)strtol(fields[7], NULL, 10);
                e.heure_fin_h = (int)strtol(fields[8], NULL, 10);
                e.heure_fin_m = (int)strtol(fields[9], NULL, 10);
                e.prix = (float)strtod(fields[10], NULL);
                strncpy(e.salle, fields[11], sizeof(e.salle)-1); e.salle[sizeof(e.salle)-1] = '\0';
                e.capacite = (int)strtol(fields[12], NULL, 10);
            } else {
                /* fallback avec scanf classique (whitespace) */
                int r = sscanf(line,
                               "%d %49s %29s %d %d %d %d %d %d %d %f %29s %d",
                               &e.id, e.nom, e.type,
                               &e.jour, &e.mois, &e.annee,
                               &e.heure_debut_h, &e.heure_debut_m,
                               &e.heure_fin_h, &e.heure_fin_m,
                               &e.prix, e.salle, &e.capacite);
                if (r != 13) {
                    g_warning("afficher_event_treeview : ligne ignorée (r=%d) -> %s", r, line);
                    continue;
                }
            }

            /* DEBUG: afficher ce qu'on ajoute */
            g_print("-> parsed: id=%d nom='%s' type='%s' date=%02d/%02d/%04d heure=%02d:%02d-%02d:%02d prix=%.2f salle=%s cap=%d\n",
                    e.id, e.nom, e.type, e.jour, e.mois, e.annee,
                    e.heure_debut_h, e.heure_debut_m, e.heure_fin_h, e.heure_fin_m,
                    e.prix, e.salle, e.capacite);

            /* formater date/heure */
            snprintf(date, sizeof(date), "%02d/%02d/%04d", e.jour, e.mois, e.annee);
            snprintf(heure, sizeof(heure), "%02d:%02d-%02d:%02d",
                     e.heure_debut_h, e.heure_debut_m, e.heure_fin_h, e.heure_fin_m);

            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               E_ID,       e.id,
                               E_NOM,      e.nom,
                               E_TYPE,     e.type,
                               E_DATE,     date,
                               E_HEURE,    heure,
                               E_SALLE,    e.salle,
                               E_PRIX,     e.prix,
                               E_CAPACITE, e.capacite,
                               -1);
            rows++;
        } /* while */
    }

    fclose(f);

    g_print("afficher_event_treeview : %d lignes ajoutées au model.\n", rows);

    /* ATTACHER et FORCER actualisation */
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    /* ajuste les colonnes pour être sûr que rien n'est masqué */
    gtk_tree_view_columns_autosize(GTK_TREE_VIEW(treeview));
    /* redessine */
    gtk_widget_queue_draw(treeview);

    g_object_unref(store);
}

void ajouter(char nom[], char prenom[], char user[], char pass[], int role) {
    FILE *f = fopen("personne.txt", "a"); // "a" permet d'ajouter à la fin du fichier
    if (f != NULL) {
        // On écrit les données séparées par des espaces ou un délimiteur
        fprintf(f, "%s %s %s %s %d\n", nom, prenom, user, pass, role);
        fclose(f);
    } else {
        // En cas d'erreur d'ouverture du fichier
        printf("Erreur d'ouverture du fichier personne.txt\n");
    }
}

int verifier(char login[], char password[]) {
    char n[50], p[50], l[50], pw[50];
    int r;
    FILE *f = fopen("personne.txt", "r");
    
    
    if (strcmp(login, "Admin") == 0 && strcmp(password, "Admin123") == 0) {
        if (f) fclose(f);
        return 1; 
    }

    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %d", n, p, l, pw, &r) != EOF) {
            if (strcmp(login, l) == 0 && strcmp(password, pw) == 0) {
                fclose(f);
                return r; 
            }
        }
        fclose(f);
    }
    return -1; 
}


void rafraichir_liste_event(GtkWidget *liste, char *nom_fichier) {
    GtkListStore *store;
    GtkTreeIter iter;
    FILE *f = fopen(nom_fichier, "r");
    char line[1024];

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    if (!store) return;

    gtk_list_store_clear(store);

    if (f != NULL) {
        while (fgets(line, sizeof(line), f)) {
            event e;
            // On utilise la fonction de parsing que vous avez déjà définie plus haut dans event.c
            if (parse_event_line(line, &e)) {
                char date_str[32];
                char heure_str[32];

                snprintf(date_str, sizeof(date_str), "%02d/%02d/%04d", e.jour, e.mois, e.annee);
                snprintf(heure_str, sizeof(heure_str), "%02d:%02d-%02d:%02d", 
                         e.heure_debut_h, e.heure_debut_m, e.heure_fin_h, e.heure_fin_m);

                gtk_list_store_append(store, &iter);
                
                // ATTENTION : Utilisez les noms d'énumération E_ID, E_NOM... 
                // pour être sûr de ne pas vous tromper de colonne.
                gtk_list_store_set(store, &iter, 
                    E_ID, e.id, 
                    E_NOM, e.nom, 
                    E_TYPE, e.type, 
                    E_DATE, date_str,
                    E_HEURE, heure_str,
                    E_SALLE, e.salle,
                    E_PRIX, e.prix,
                    E_CAPACITE, e.capacite,
                    -1);
            }
        }
        fclose(f);
    }
    // Forcer le redessin pour éviter que l'ancien affichage reste
    gtk_widget_queue_draw(liste);
}
