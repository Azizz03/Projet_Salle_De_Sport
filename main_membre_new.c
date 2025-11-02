#include <stdio.h>
#include <string.h>
#include "membre.h"

int main() {
    membre m1 = {100, "aziz", "hamadi", "centreA", "aziz.bentekaya@gmail.com", 20, "Decembre", 2003, "trimestriel", 50.2, 5.5, 15.2, "H", 190, "...", "...", "...", "+21694273829"};
    membre m2 = {1, "Hussein", "Ali", "centreA", "ali.bentekaya@gmail.com", 26, "novembre", 2003, "Annuel", 50.2, 5.5, 15.2, "H", 190, "...", "...", "...", "+21694273829"};
    membre m3;
    
    // Test ajouter membre
    int x = ajouter_membre("membre.txt", m1);
    if(x == 1)
        printf("Ajout de membre avec succes\n");
    else 
        printf("Echec d'ajout\n");
    
    // Test modifier membre
    x = modifier_membre("membre.txt", 1, m2);
    if(x == 1)
        printf("Modification de membre avec succes\n");
    else 
        printf("Echec modification\n");
    
    // Test supprimer membre
    x = supprimer_membre("membre.txt", 1);
    if(x == 1)
        printf("Suppression de membre avec succes\n");
    else 
        printf("Echec suppression\n");
    
    // Test chercher membre
    m3 = chercher_membre("membre.txt", 100);
    if(m3.id == -1)
        printf("Membre introuvable\n");
    else
        printf("Membre trouve: %s %s\n", m3.nom, m3.prenom);
    
    // Afficher tous les membres
    afficher_membre("membre.txt");
    
    return 0;
}
