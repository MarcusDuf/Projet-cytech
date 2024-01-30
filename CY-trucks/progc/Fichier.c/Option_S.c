#include <stdio.h>
#include <stdlib.h>
#include "AVLS.h"

//Fonction de traitement de fichier csv
pAVL TraitementFichier(char *argv[], int n, pAVL a, int *h){
    int id; //Valeur pour l identifiant de l itineraire
    float distance; //Valeur pour la distance parcourue
    FILE *entree=fopen(argv[n], "r"); //Ouverture fichier csv d entree 
    //Verrification fichier d entree valide
    if (entree==NULL) {
        printf("Erreur lors de l'ouverture du fichier d'entrée");
        exit(EXIT_FAILURE);
    }
    //Boucle de lexture du fichier csv ligne par ligne et insertion dans l'AVL
    while (fscanf(entree, "%d;%*d;%*[^;];%*[^;];%f;%*[^\n]%*c", &id , &distance)==2){
        a=insertionAVLId(a, id, distance, h, 1); 
    }
    fclose(entree);//Fermeture fichier csv d entree 
    return a;
}

//Fonction de remplissage d un AVL b par un AVL a
void RemplirAVL(pAVL a, pAVL  *b, int *h) {
    if (a != NULL) {
        *b=insertionAVLTrie(*b, a->i.id,  a->i.min, a->i.moy, a->i.max, h, a->i.etape);
        RemplirAVL(a->gauche, b, h);
        RemplirAVL(a->droit, b, h);
    }
}

//Fonction d ecriture des 50 plus grandes valeurs de l'AVL dans le fichier de sortie
void EcrireSortie(FILE* sortie, pAVL a, int* r, int k){
    if (a!=NULL && *r<k) {
        EcrireSortie(sortie, a->droit, r, k);
        if (a!=NULL && *r<k) {
           fprintf(sortie, "%d;%.3f;%.3f;%.3f\n", a->i.id,  a->i.min, a->i.moy, a->i.max);
        }
        *r=*r+1;
        EcrireSortie(sortie, a->gauche, r, k);
    }
}

int main(int argc, char *argv[]){
    //Initialisation des 2 AVL
    pAVL a=NULL;
    pAVL b=NULL;
    int h1=0;
    int h2=0;
    int r=0;
    //Verrification du nombre d'argument sinon erreur
    if (argc!=7) {
        printf("Erreur : problème d'arguments\n");
        exit(EXIT_FAILURE);
    }
    //Traitement des 6 fichiers csv et remplissage du premier AVL en fonction des noms
    for(int i=1; i<7; i++){
        a=TraitementFichier( argv, i, a, &h1);
    }
    RemplirAVL(a, &b, &h2); //Remplissage du second AVL en fonction de distance max-min
    libererAVL(a); //Liberation du premier AVL
    FILE *sortie=fopen("CY-trucks/temp/Option_S.csv", "w"); //Ouverture fichier de sortie
    //Verification fichier de sortie valide
    if (sortie==NULL) {
        printf("Erreur lors de l'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }
    //Remplissage du fichier de sortie en fonction du second AVL
    EcrireSortie(sortie, b, &r, 50);
    libererAVL(b); //Liberation du second AVL
    fclose(sortie); //Fermeture du fichier de sortie
    return 0;
}

