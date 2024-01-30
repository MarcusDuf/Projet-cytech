#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//Definition du pointeur AVL
typedef struct AVL *pAVL;

//Fonction qui retourne le max entre deux valeurs
int max(int a, int b){
    if(a>=b){
        return a;
    }
    else{
        if(a<b){
            return b;
        }
        else{
            exit(0);
        }
    }
}

//Fonction qui retourne le min entre deux valeurs
int min(int a, int b){
    if(a>=b){
        return b;
    }
    else{
        if(a<b){
            return a;
        }
        else{
            exit(0);
        }
    }
}

//Fonction qui retourne le min entre trois valeurs
int minbis(int a, int b, int c){
    int k;
    k=min(a,b);
    k=min(k,c);
    return k;
}

//Fonction qui retourne le max entre trois valeurs
int maxbis(int a, int b, int c){
    int k;
    k=max(a,b);
    k=max(k,c);
    return k;
}

//Fonction de creation AVL
pAVL creerAVLDepart(char nom[],int a, int b){
    pAVL p;
    p=malloc(sizeof(AVL));
    if(p==NULL){
       printf("erreur : allocation AVL\n");
       exit(1);
    }
    else{
       p->v.trajets_depart=a;
       p->v.trajets_total=b;
       strcpy(p->v.nom, nom);
       p->droit=NULL;
       p->gauche=NULL;
       p->e=0;
    }
    return p;
}

//Fonction RotationGauche AVL
pAVL RotationGauche(pAVL a){
    pAVL pivot=NULL;
    int eq_a, eq_p;
    pivot=a->droit;
    a->droit=pivot->gauche;
    pivot->gauche=a;
    eq_a=a->e;
    eq_p=pivot->e;
    a->e=eq_a-max(eq_p,0)-1;
    pivot->e=minbis(eq_a-2,eq_a+eq_p-2,eq_p-1);
    a=pivot;
    return a;
}

//Fonction RotationDroite AVL
pAVL RotationDroite(pAVL a){
    pAVL pivot=NULL;
    int eq_a, eq_p;
    pivot=a->gauche;
    a->gauche=pivot->droit;
    pivot->droit=a;
    eq_a=a->e;
    eq_p=pivot->e;
    a->e=eq_a-min(eq_p,0)+1;
    pivot->e=maxbis(eq_a+2,eq_a+eq_p+2,eq_p+1);
    a=pivot;
    return a;
}

//Fonction DoubleRotationDroite AVL
pAVL DoubleRotationDroite(pAVL a){
    a->gauche=RotationGauche(a->gauche);
    return RotationDroite(a);
}

//Fonction DoubleRotationGauche AVL
pAVL DoubleRotationGauche(pAVL a){
    a->droit=RotationDroite(a->droit);
    return RotationGauche(a);
}

//Fonction d equilibrage AVL
pAVL equilibrageAVL(pAVL a){
    if(a->e>=2){
        if(a->droit->e>=0){
            return RotationGauche(a);
        }
        else{
            return DoubleRotationGauche(a);    
        }
    }
    else{
        if(a->e<=-2){
            if(a->gauche->e<=0){
                return RotationDroite(a);
            }
            else{
                return DoubleRotationDroite(a);    
            }
        }
    }
    return a;
}

//Fonction d insertion AVL en fonction du nom
pAVL insertionAVLNom(pAVL a, int trajets_depart, int trajets_total, int *h, char nom[]){
    pAVL p=NULL;
    if(a==NULL){
        *h=1;
        p=creerAVLDepart(nom, trajets_depart, trajets_total);
        return p;
    }
    else{
        if(strcasecmp(a->v.nom, nom)==0){
           a->v.trajets_depart=a->v.trajets_depart+trajets_depart;
           a->v.trajets_total=a->v.trajets_total+trajets_total;
        }
        else{
           if(strcmp(a->v.nom, nom)>0){
              a->gauche=insertionAVLNom(a->gauche, trajets_depart, trajets_total, h, nom);
              *h=-*h;
           }
           else{
              if(strcmp(a->v.nom, nom)<0){
                 a->droit=insertionAVLNom(a->droit, trajets_depart, trajets_total, h, nom);
              }
              else{
                 *h=0;
                 return a;
              }
           }
        }
     }
     if(*h!=0){
        a->e=a->e+*h;
        a=equilibrageAVL(a);
        if(a->e==0){
            *h=0;
        }
        else{
           *h=1;
        }
    }
    return a;
}

//Fonction d insertion AVL en fonction de trajets total
pAVL insertionAVLTrajet(pAVL a, int trajets_depart, int trajets_total, int *h, char nom[]){
    pAVL p=NULL;
    if(a==NULL){
        *h=1;
        p=creerAVLDepart(nom, trajets_depart, trajets_total);
        return p;
    }
    else{
        if(a->v.trajets_total>trajets_total){
           a->gauche=insertionAVLTrajet(a->gauche, trajets_depart, trajets_total, h, nom);
           *h=-*h;
        }
        else{
           if(a->v.trajets_total<trajets_total){
              a->droit=insertionAVLTrajet(a->droit, trajets_depart, trajets_total, h, nom);
           }
           else{
              *h=0;
              return a;
              
           }
        }
     }
     if(*h!=0){
        a->e=a->e+*h;
        a=equilibrageAVL(a);
        if(a->e==0){
            *h=0;
        }
        else{
           *h=1;
        }
    }
    return a;
}

//Fonction de liberation d AVL
void libererAVL(pAVL a){
    if (a==NULL){
        return;
    }
    libererAVL(a->gauche);
    libererAVL(a->droit);
    free(a);
}

