prog3:event.o mainev.o
	gcc event.o mainev.o -o prog3 -g
main_membre.o:mainev.c
	gcc -c mainev.c -g
membre.o:membre.c
	gcc -c event.c -g
