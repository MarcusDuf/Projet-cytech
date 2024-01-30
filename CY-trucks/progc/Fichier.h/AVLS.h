#ifndef H_A
#define H_A
//Definition de la structure Itineraire
typedef struct Itineraire{
    int id; //Valeur de l identification de l itineraire
    float min; //Valeur minimal de la distance des etapes de l itineraire
    float moy; //Valeur moyenne de la distance des etapes de l itineraire
    float max; //Valeur maximum de la distance des etapes de l itineraire
    int etape; //Valeur du nombre d etapes de l itineraire
} Itineraire;
//Definition de la structure AVL
typedef struct AVL{
    Itineraire i;
    struct AVL*droit;
    struct AVL*gauche;
    int e;
}AVL;
typedef struct AVL *pAVL; //Definition du pointeur AVL
int max(int a, int b); //Fonction qui retourne le max entre deux valeurs
int min(int a, int b); //Fonction qui retourne le min entre deux valeurs
int minbis(int a, int b, int c); //Fonction qui retourne le min entre trois valeurs
int maxbis(int a, int b, int c); //Fonction qui retourne le max entre trois valeurs
pAVL creerAVL(int id ,float a, float b, float c, int etape); //Fonction de creation AVL
pAVL RotationGauche(pAVL a); //Fonction RotationGauche AVL
pAVL RotationDroite(pAVL a); //Fonction RotationDroite AVL
pAVL DoubleRotationDroite(pAVL a); //Fonction DoubleRotationDroite AVL
pAVL DoubleRotationGauche(pAVL a); //Fonction DoubleRotationGauche AVL
pAVL equilibrageAVL(pAVL a); //Fonction d equilibrage AVL
pAVL insertionAVLId(pAVL a, int id , float distance, int *h, int etape); //Fonction d insertion AVL en fonction de l id
pAVL insertionAVLTrie(pAVL a, int id , float min, float moy, float max, int *h, int etape); //Fonction d insertion AVL en fonction de distance max-min
void libererAVL(pAVL a); //Fonction de liberation d AVL
#endif

