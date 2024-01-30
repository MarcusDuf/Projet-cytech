#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definition de la structure Chainon
typedef struct Chainon {
    char nom[33]; //Chaine de caracteres pour le nom de la ville
    int trajets_depart; //Valeur pour le nombre de fois ou cette ville est une ville de depart d itineraire
    int trajets_total; //Valeur pour le nombre de fois ou cette ville est une ville d arrivee
    struct Chainon *suivant;
} Chainon;

//Definition du pointeur Chainon
typedef struct Chainon *pChainon;

//Fonction de creation chainon
pChainon creerChainon(char nom[], int trajets_depart, int trajets_total){
    pChainon p=malloc(sizeof(Chainon));
    if (p==NULL) {
        printf("Erreur : allocation Chainon\n");
        exit(1);
    } 
    else {
        strcpy(p->nom, nom);
        p->trajets_depart=trajets_depart;
        p->trajets_total=trajets_total;
        p->suivant=NULL;
    }
    return p;
}

//Fonction d insertion chainon
pChainon InsertionChainon(pChainon a, char nom[], int trajets_depart, int trajets_total){
    pChainon p=creerChainon(nom, trajets_depart, trajets_total);
    if (a==NULL) {
        return p;
    } 
    else{
        p->suivant=a;
        a=p;
        return a;
    }
}

//Fonction de recherche chainon en fonction du nom
pChainon RechercheChainon(pChainon a, char nom[]){
    if(a==NULL){
        return NULL;
    }
    else{
    	if (strcasecmp(a->nom, nom)==0){
            return a;
        }
        else{
            return RechercheChainon(a->suivant, nom);  
        }
    }
}


