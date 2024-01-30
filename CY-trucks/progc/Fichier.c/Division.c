#include <stdio.h>
#include <stdlib.h>

//Fonction pour diviser le fichier csv en plusieurs partie
void DivisionCSV( int MaxLigne, char *argv[]){
    char ligne[2000]; //Chaine de caractere pour chaque ligne
    int nbfichier=1; //Nombre de fichier sortant
    int nbligne=0; //Nombre de lignes lues
    FILE *entree=fopen(argv[1], "r"); //Ouverture fichier d entree
    if (entree==NULL) {
        printf("Erreur lors de l'ouverture du fichier d'entrée");
        exit(EXIT_FAILURE);
    }
    FILE *sortie=NULL; //Initialisation fichier de sortie
    //Verification fichier d entree valide
    if (fgets(ligne, sizeof(ligne), entree)==NULL) {
        printf("Le fichier est vide ou ne peut pas être lu.");
        fclose(entree);
        exit(EXIT_FAILURE);
    }
    //Boucle de lecture du fichier ligne par ligne
    while(fgets(ligne, sizeof(ligne), entree)!=NULL){
        // Si le nombre de lignes est max ou si on est a la premiere ligne
        if(nbligne%MaxLigne==0 || nbligne==0){
            //Fermeture fichier de sortie précedent s'il existe
            if(sortie!=NULL){
                fclose(sortie);
            }
            char SortieNom[50]; //Initialisation nom du fichier de sortie
            snprintf(SortieNom, 50, "CY-trucks/temp/%s_%d.csv", "Data", nbfichier); //creation fichier de sortie
            sortie=fopen(SortieNom, "w"); //Ouverture fichier de sortie
            if (sortie==NULL) {
               printf("Erreur lors de l'ouverture du fichier de sortie");
               fclose(entree);
               exit(EXIT_FAILURE);
            }
            nbfichier=nbfichier+1;
        }
        fputs(ligne, sortie); //Ecriture de la ligne dans le fichier de sortie
        nbligne=nbligne+1;
    }
    //Fermeture dernier fichier de sortie
    if(sortie!=NULL){
        fclose(sortie); 
    }
     fclose(entree); //Fermeture fichier d'entree
}

int main(int argc, char *argv[]){
    int FichierTailleMax; //Taille max des fichier generer en mega-octet
    int MaxLigne; //Nombre max de ligne des fichier generer
    //Verification nombre d arguments sinon erreur
    if (argc!=2) {
        printf("Erreur : problème d'arguments\n");
        exit(EXIT_FAILURE);
    }
    //Initialisation des donnees
    FichierTailleMax=1050;
    MaxLigne=(FichierTailleMax*1024*1024)/1024;
    DivisionCSV(MaxLigne, argv);//Appel fonction de division
    return 0;
}

