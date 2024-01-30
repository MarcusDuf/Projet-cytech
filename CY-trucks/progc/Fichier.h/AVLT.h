#ifndef H_A
#define H_A
//Definition de la structure Ville
typedef struct Ville{
    char nom[32]; //chaine de caracteres pour le nom de la ville
    int trajets_depart; //Valeur pour le nombre de fois ou cette ville est une ville de depart d itineraire
    int trajets_total; //Valeur pour le nombre de fois ou cette ville est une ville d arrivee
} Ville;
//Definition de la structure AVL
typedef struct AVL{
    Ville v;
    struct AVL*droit;
    struct AVL*gauche;
    int e;
}AVL;
typedef struct AVL *pAVL; //Definition du pointeur AVL
int max(int a, int b); //Fonction qui retourne le max entre deux valeurs
int min(int a, int b); //Fonction qui retourne le min entre deux valeurs
int minbis(int a, int b, int c); //Fonction qui retourne le min entre trois valeurs
int maxbis(int a, int b, int c); //Fonction qui retourne le max entre trois valeurs
pAVL creerAVLDepart(char nom[],int a, int b); //Fonction de creation AVL
pAVL RotationGauche(pAVL a); //Fonction RotationGauche AVL
pAVL RotationDroite(pAVL a); //Fonction RotationDroite AVL
pAVL DoubleRotationDroite(pAVL a); //Fonction DoubleRotationDroite AVL
pAVL DoubleRotationGauche(pAVL a); //Fonction DoubleRotationGauche AVL
pAVL equilibrageAVL(pAVL a); //Fonction d equilibrage AVL
pAVL insertionAVLNom(pAVL a, int trajets_depart, int trajets_total, int *h, char nom[]); //Fonction d insertion AVL en fonction du nom
pAVL insertionAVLTrajet(pAVL a, int trajets_depart, int trajets_total, int *h, char nom[]); //Fonction d insertion AVL en fonction de trajets total
void libererAVL(pAVL a); //Fonction de liberation d AVL
#endif

