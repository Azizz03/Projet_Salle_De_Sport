#include <stdio.h>
#include <stdlib.h>

int main()
{
  #include <stdio.h>
#include "event_member.h"

void inscription_event(event e) {
    printf("Inscription à l'événement : %s\n", e.nom);
    // logiques d'inscription ici
}

void validation_event(event e) {
    printf("Validation de l'événement : %s\n", e.nom);
    // logiques de validation ici
}

void annulation_event(event e) {
    printf("Annulation de l'événement : %s\n", e.nom);
    // logiques d'annulation ici
}
    return 0;
}
