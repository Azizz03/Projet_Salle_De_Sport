prog:ajout_membre_new.o main_membre_new.o
	gcc ajout_membre_new.o main_membre_new.o -o prog
main_membre.o:main_membre_new.c
	gcc -c main_membre_new.c
ajout_membre_new.o:ajout_membre_new.c
	gcc -c ajout_membre_new.c
