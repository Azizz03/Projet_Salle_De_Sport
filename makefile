prog:membre.o main_membre.o
	gcc membre.o main_membre.o -o prog
main_membre.o:main_membre.c
	gcc -c main_membre.c
ajout_membre_new.o:membre.c
	gcc -c membre.c
