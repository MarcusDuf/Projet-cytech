CC=gcc
CFLAGS=-Wall -Wextra

all: Division Option_T Option_S

Division: Fichier.c/Division.c
	$(CC) $(CFLAGS) -o Division Fichier.c/Division.c

Option_T: Fichier.c/Option_T.c Fichier.c/AVLT.c Fichier.c/ChainonT.c
	$(CC) $(CFLAGS) -o Option_T Fichier.c/Option_T.c Fichier.c/AVLT.c Fichier.c/ChainonT.c -I Fichier.h
	
Option_S: Fichier.c/Option_S.c Fichier.c/AVLS.c 
	$(CC) $(CFLAGS) -o Option_S Fichier.c/Option_S.c Fichier.c/AVLS.c -I Fichier.h
	
clean:
	rm -f Division Option_T Option_S
