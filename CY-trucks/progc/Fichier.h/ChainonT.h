#ifndef H_B
#define H_B
//Definition de la structure Chainon
typedef struct Chainon {
    char nom[33]; //Chaine de caracteres pour le nom de la ville
    int trajets_depart; //Valeur pour le nombre de fois ou cette ville est une ville de depart d itineraire
    int trajets_total; //Valeur pour le nombre de fois ou cette ville est une ville d arrivee
    struct Chainon *suivant;
} Chainon;
typedef struct Chainon *pChainon; //Definition du pointeur Chainon
pChainon creerChainon(char nom[], int trajets_depart, int trajets_total); //Fonction de creation chainon
pChainon InsertionChainon(pChainon a, char nom[], int trajets_depart, int trajets_total); //Fonction d insertion chainon
pChainon RechercheChainon(pChainon a, char nom[]); //Fonction de recherche chainon en fonction du nom
#endif




