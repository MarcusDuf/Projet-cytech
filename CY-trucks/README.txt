-----------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------Bienvenue dans le CY-trucks---------------------------------------------------------------

1-Placer le dossier CY-trucks dans votre dossier personnel et placer votre fichier csv à traiter dans CY-trucks/data

2-Ouvrir le terminal, pour lancer le programme il vous faut lancer le script.sh en utilisant son chemin avec comme 1er argument le chemin du fichier.csv à traiter et en second argument l'option que vous voulez avoir, soit une commande de la forme : ./<Chemin script.sh> <Chemin fichier.csv> <Option>

3-Pour afficher un message d'aide afin d'avoir les options disponibles, utiliser l'argument -h avec le script.sh, tel que : ./<Chemin script.sh> <-h>

4-Vous pouvez ainsi traiter plusieurs options avec la meme commande en les écrivant à la suite qu'importe leur ordre, tel que : ./<Chemin script.sh> <Chemin fichier.csv> <Option1> <Option2> <Option3>

5-Le programme n'accepte pas plus de 6 arguments mais vous pouvez traiter la même option plusieurs fois et vous pouvez bien traiter toutes les options disponibles, tel que : ./<Chemin script.sh> <Chemin fichier.csv> <Option1> <Option2> <Option1> <Option4> <Option5>

6-Soit les options disponibles : <Option_D1> <Option_D2> <Option_L> <Option_T> <Option_S>

7-Enfin voici un exemple de commande pour traiter toutes les options avec un fichier data.csv : ./CY-trucks/script.sh CY-trucks/data/data.csv Option_L Option_S Option_D1 Option_D2 Option_T

8-Un exemple d'appel de -h : ./CY-trucks/script.sh -h

9-La compilation du Makefile se fait automatiquement 

-----------------------------------------Merci d'être passer-----------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------
