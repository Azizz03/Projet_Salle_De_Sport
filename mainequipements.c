#include <stdio.h>
#include <string.h>
#include "equipement.h"

int main() {
    Equipement e = {"EQ001", "Tapis", "Centre_Sportif_A", "Cardio", 10, "En_maintenance", "Salle_1", "Noir"};
    Equipement r;
    int res;


    FILE *f = fopen("equipements.txt", "a");
    if (f == NULL) { perror("open equipements.txt"); return 1; }
    res = ajouter_equipement(f, &e);
    fclose(f);
    printf("Ajout : %s\n", res ? "OK" : "Erreur");


    f = fopen("equipements.txt", "r");
    if (f == NULL) { perror("open equipements.txt"); return 1; }
    res = modifier_equipement(f, &e);
    fclose(f);
    if (res) { remove("equipements.txt"); rename("temp.txt", "equipements.txt"); printf("Modification OK\n"); }
    else { remove("temp.txt"); printf("Modification: non trouvé\n"); }


    f = fopen("equipements.txt", "r");
    if (f == NULL) { printf("Fichier introuvable lors de la recherche\n"); }
    else {
        res = rechercher_equipement(f, "EQ001", &r);
        fclose(f);
        if (res) printf("Trouvé: %s %s %d\n", r.id, r.nom, r.quantite);
        else printf("Recherche: non trouvé\n");
    }


 /*
    // --- SUPPRESSION
    f = fopen("equipements.txt", "r");
    if (f == NULL) { printf("Fichier introuvable lors de la suppression\n"); }
    else {
        res = supprimer_equipement(f, "EQ001");
        fclose(f);
        if (res) { remove("equipements.txt"); rename("temp.txt", "equipements.txt"); printf("Suppression OK\n"); }
        else { remove("temp.txt"); printf("Suppression: non trouvé\n"); }
    }
*/

    return 0;
}

