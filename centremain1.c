#include <stdio.h>
#include "centre.h"
int main(){
	centre c1={12345,"fitness1","rue20250","tunis",12345678,"1@gmail.com",10,60,"musculation","ouvert",8,23,10,18};
	centre c2={6789,"fitness2","rue2025","sfax",75236148,"2@gmail.com",10,60,"yoga","ferme",8,23,10,18};
	centre c3;
	int x = ajouter_centre("centre.txt", c1);
   	if (x == 1)
        	printf("\nAjout effectué avec succès !");
   	else
        	printf("\nÉchec d'ajout !");

    	x = modifier_centre("centre.txt", 12345, c2);
    	if (x == 1)
        	printf("\nModification réussie !");
    	else
        	printf("\nÉchec de modification !");

    	x = supprimer_centre("centre.txt", 12345);
    	if (x == 1)
        	printf("\nSuppression réussie !");
    	else
        	printf("\nÉchec de suppression !");

    	c3= chercher_centre("centre.txt", 12345);
    	if (c3.id == -1)
        	printf("\nIntrouvable !");
    	else
        	printf("\ncentre trouvé :le centre est %s ", c3.nom);

    	return 0;
}
