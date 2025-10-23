#ifndef EVENT_MEMBER_H
#define EVENT_MEMBER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// Structure pour un participant
typedef struct {
    char nom et pr�nom[50];
    int age;
    char sexe[10]


    char nom �v�nement [50];
    char type evenement[11];
    char date[40];
    int heure;
    int minute;
    int annee;
    char mois[40]; // format: JJ/MM/AAAA
    char time[6];// format: HH:MM
    char salle[50]
    int max_participants;
    int prix;


void inscription_event(event)
void validation_event(event)
void annulation_event(event)

#endif // EVENT_MEMBER_H
