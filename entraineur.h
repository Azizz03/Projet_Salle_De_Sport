typedef struct { 
int jour, mois, annee;
} date;

typedef struct {
    int id;
    char nom[30];
    char prenom[30];
    char specialite[30];
    float salaire;
    char sexe[10];
    date date_inscription;
    char email[50];
    char num_tel[20];
    int cours_privee; // 0 = non, 1 = oui
    char centre[30];
    char ville_pref[30];
} entraineur;

typedef struct {
    int reservation_id;
    int equipment_id;
    char coach_id[50];
    char cour_id[50];
    char reservation_date[20];
    int reserved_qty;
} reservation;

// -------- FONCTIONS --------

// Entraîneur
int ajouter(const char *filename, entraineur e);
int modifier(const char *filename, int id, entraineur nouv);
int supprimer(const char *filename, int id);
entraineur chercher(const char *filename, int id);

// Réservation
int ajouter_reservation(const char *filename, reservation r);
int supprimer_reservation(const char *filename, int reservation_id);
reservation rechercher_reservation(const char *filename, int reservation_id);

// Contrôle de saisie
int valider_entraineur(entraineur e);

#endif


int ajouter(char *entraineur.txt, entraineur e);
int modifier(char *entraineur.txt, int id, entraineur nouv);
int supprimer(char *entraineur.txt, int id);
entraineur chercher(char *entraineur.txt, int id);

int ajouter_reservation(char* entraineur.tx, char* equip_file, reservation_cours r) ;
int supprimer_reservation(char* entraineur.txt, int reservation_id) ;
reservation rechercher_reservation_cours(char* entraineur.txt, int reservation_id);



