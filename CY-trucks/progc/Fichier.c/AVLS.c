#include <stdio.h>
#include <stdlib.h>

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
pAVL creerAVL(int id ,float a, float b, float c, int etape){
    pAVL p;
    p=malloc(sizeof(AVL));
    if(p==NULL){
       printf("erreur : allocation AVL\n");
       exit(1);
    }
    else{
       p->i.id=id;
       p->i.min=a;
       p->i.moy=b;
       p->i.max=c;
       p->i.etape=etape;
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

//Fonction d insertion AVL en fonction de l id
pAVL insertionAVLId(pAVL a, int id , float distance, int *h, int etape){
    pAVL p=NULL;
    if(a==NULL){
        *h=1;
        p=creerAVL(id, distance, distance, distance, etape);
        return p;
    }
    else{
        if(a->i.id==id){
           if(a->i.max<distance){
	       a->i.max=distance;
	   }
	   if(a->i.min>distance){
	       a->i.min=distance;
	   }
	   a->i.moy=a->i.moy+distance;
	   a->i.etape=a->i.etape+1;
        }
        else{
           if(a->i.id>id){
              a->gauche=insertionAVLId(a->gauche, id, distance, h, etape);
              *h=-*h;
           }
           else{
              if(a->i.id<id){
                 a->droit=insertionAVLId(a->droit, id , distance, h, etape);
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

//Fonction d insertion AVL en fonction de distance max-min
pAVL insertionAVLTrie(pAVL a, int id , float min, float moy, float max, int *h, int etape){
    pAVL p=NULL;
    if(a==NULL){
        *h=1;
        p=creerAVL(id, min, moy, max, etape);
        p->i.moy=p->i.moy/etape;
        return p;
    }
    else{
        if(a->i.max-a->i.min>max-min){
            a->gauche=insertionAVLTrie(a->gauche, id, min, moy, max, h, etape);
            *h=-*h;
        }
        else{
            if(a->i.max-a->i.min<max-min){
                a->droit=insertionAVLTrie(a->droit, id , min, moy, max, h, etape);
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

