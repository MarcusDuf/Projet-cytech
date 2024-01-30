#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLT.h"
#include "ChainonT.h"

//Fonction de traitement de fichier csv
pAVL TraitementFichier(char *argv[], int n, pAVL a, int *h){
    char nom1[33]; //Chaine de caracteres pour la ville de la colonne de depart
    char nom2[33]; //Chaine de caracteres pour la ville de la colonne d arrivee
    int etape; //Valeur pour l etape de l itineraire
    FILE *entree = fopen(argv[n], "r"); //Ouverture fichier csv d entree 
    //Verrification fichier d entree valide
    if (entree==NULL) {
        printf("Erreur lors de l'ouverture du fichier d'entrée");
        exit(EXIT_FAILURE);
    }
    //Boucle de lexture du fichier csv ligne par ligne et insertion dans l'AVL
    while (fscanf(entree, "%*d;%d;%33[^;];%33[^;];%*f;%*[^\n]%*c", &etape, nom1, nom2)==3){
        //Verification taille des chaines de caracteres
        if (strlen(nom1)>=33) {
            printf("erreur : chaine trop longue\n");
            exit(EXIT_FAILURE);
        }
        if (strlen(nom2)>=33) {
            printf("erreur : chaine trop longue\n");
            exit(EXIT_FAILURE);
        }  
        else {
            //Incrementation de 1 pour les trajet depart et total
            if(etape==1){
                a=insertionAVLNom(a, 1, 1, h, nom1);
            }
            //Incrementation de 1 pour trajet total
            a=insertionAVLNom(a, 0, 1, h, nom2); 
        }
    }
    fclose(entree); //Fermeture fichier d entree
    return a;
}

//Fonction de remplissage d un AVL b par un AVL a
void RemplirAVL(pAVL a, pAVL  *b,int *h) {
    if (a != NULL) {
        *b=insertionAVLTrajet(*b, a->v.trajets_depart, a->v.trajets_total, h, a->v.nom);
        RemplirAVL(a->gauche, b, h);
        RemplirAVL(a->droit, b, h);
    }
}

//Fonction de remplissage des 10 plus grandes valeurs de l'AVL dans une liste chainee
void RemplirChainon(pAVL a, pChainon *p, int *r, int k){
    if(a!=NULL && *r<k){
        RemplirChainon(a->droit, p, r, k);
        if (a!=NULL && *r<k) {
           *p=InsertionChainon(*p, a->v.nom, a->v.trajets_depart, a->v.trajets_total);
        }
        *r=*r+1;
        RemplirChainon(a->gauche, p, r, k);
    }
}

//Fonction de comparaison des chaines de caractere
void insertionTrie(pChainon* pa, pChainon p){
    if(*pa==NULL || strcmp((*pa)->nom, p->nom)>=0){
        p->suivant=*pa;
        *pa=p;
    } 
    else{
        pChainon pb=*pa;
        while (pb->suivant!=NULL && strcmp(pb->suivant->nom, p->nom)<0){
            pb=pb->suivant;
        }
        p->suivant=pb->suivant;
        pb->suivant=p;
    }
}

//Fonction de trie de la liste chainee par ordre alphabetique
void TriChainon(pChainon* p){
    //Initialisation
    pChainon pa=NULL;
    pChainon pb=*p;
    //Boucle de remplissage de la liste chainee triee
    while (pb!=NULL){
        pChainon pc=pb->suivant;
        insertionTrie(&pa, pb);
        pb=pc;
    }
    *p=pa;
}

int main(int argc, char *argv[]){
    //Initialisation des 2 AVL et listes chainees
    pAVL a=NULL;
    pAVL b=NULL;
    int h1=0;
    int h2=0;
    int r=0;
    pChainon p=NULL;
    pChainon pb=NULL;
    //Verrification du nombre d'argument sinon erreur
    if (argc!=7) {
        printf("Erreur : problème d'arguments\n");
        exit(EXIT_FAILURE);
    }
    //Traitement des 6 fichiers csv et remplissage du premier AVL en fonction des noms
    for(int i=1; i<7; i++){
        a=TraitementFichier( argv, i, a, &h1);
    }
    RemplirAVL(a, &b, &h2); //Remplissage du second AVL en fonction du nombre total de trajets
    libererAVL(a); //Liberation du premier AVL
    RemplirChainon(b, &p, &r, 10); //Remplissage de la liste chainee en fonction des 10 plus grandes valeurs de l'AVL
    libererAVL(b); //Liberation du second AVL
    TriChainon(&p); //Tri par ordre alphabetique de la liste chainee
    FILE *sortie=fopen("CY-trucks/temp/Option_T.csv", "w"); //Ouverture fichier de sortie
    //Verification fichier de sortie valide
    if (sortie==NULL) {
        printf("Erreur lors de l'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }
    //Remplissage du fichier de sortie en fonction de la liste chainee et liberation de la liste chainee
    while(p!=NULL){
       fprintf(sortie, "%s;%d;%d\n", p->nom, p->trajets_total, p->trajets_depart);
       pb=p;
       p=p->suivant;
       free(pb);
    }
    fclose(sortie); //Fermeture du fichier de sortie
    return 0;
}

