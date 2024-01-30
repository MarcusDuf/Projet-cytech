#!/bin/bash

#Verification nombre d'arguments
if [ "$#" -lt 1 ]; then 
    echo "Erreur : Probleme d'arguments"
    echo "Pour un message d'aide : -h"
    exit 1
fi

if [ "$#" -gt 6 ]; then
    echo "Erreur : Trop d'arguments"
    exit 1
fi

#Utilisation argument -h pour aide sur les options disponible 
for ((i=1; i<7; i++)); do
    if [ "${!i}" = "-h"  ]; then
        echo "Options disponibles:"
        echo "-Option_D1"
        echo "-Option_D2"
        echo "-Option_L"
        echo "-Option_T"
        echo "-Option_S"
        exit 1
    fi
done

#Verification existence fichier progc sinon erreur
if [ ! -d CY-trucks/progc ]; then
    echo "Erreur : dossier progc manquant"
    exit 1
fi

#Verification existence des programmes compiles sinon la compilation est faite
if [ ! -f CY-trucks/progc/Division ] || [ ! -f CY-trucks/progc/Option_T ] || [ ! -f CY-trucks/progc/Option_S ]; then
    cd CY-trucks
    cd progc
    make
    if [ $? -ne 0 ]; then
        echo "Erreur : La compilation a échoué."
        exit 1
    fi
    cd
    cd
fi

#Verification existence fichier gnuplot sinon erreur
if [ ! -d CY-trucks/gnuplot ]; then
    echo "Erreur : dossier gnuplot manquant"
    exit 1
fi

#Verification existence fichier temp sinon creation
if [ ! -d CY-trucks/temp ]; then
    mkdir CY-trucks/temp
else
    rm -rf CY-trucks/temp/*
fi

#Verification existence fichier images sinon creation
if [ ! -d CY-trucks/images ]; then
    mkdir CY-trucks/images
fi

#Traitement Option_D1
for ((i=2; i<7; i++)); do
    if [ "${!i}" = "Option_D1"  ]; then
        #Lancement chronometre
	start_time=$(date +%s)
        echo "Traitement de Option_D1"
        #Tri du Fichier csv 
        awk -F";" 'NR>2 && !visited[$1]++ {count[$6]++} END {for (i in count) print count[i] ";" i}' $1 | sort -t";" -k1,1nr | head -10 > CY-trucks/temp/Option_D1.csv
        #Traitement du graphique Option_D1
        gnuplot -persist -e "load 'CY-trucks/gnuplot/Option_D1.gp'"
        #Affichage du graphique Option_D1
        xdg-open CY-trucks/images/Option_D1.png
        #Fin chronometre + affichage
        end_time=$(date +%s)
        duration=$((end_time - start_time))
        echo "Durée totale du traitement: $duration secondes"
     fi
done

#Traitement Option_D2
for ((i=2; i<7; i++)); do
    if [ "${!i}" = "Option_D2"  ]; then
        #Lancement chronometre
	start_time=$(date +%s)
	echo "Traitement de Option_D2"
	#Tri du Fichier csv 
        awk -F";" 'NR>2 {sum[$6]+=$5} END {for (driver in sum) print driver ";" sum[driver]}' $1 | sort -t";" -k2,2nr | head -10 > CY-trucks/temp/Option_D2.csv
        #Traitement du graphique Option_D2
        gnuplot -persist -e "load 'CY-trucks/gnuplot/Option_D2.gp'"
        #Affichage du graphique Option_D2
        xdg-open CY-trucks/images/Option_D2.png
        #Fin chronometre + affichage
        end_time=$(date +%s)
        duration=$((end_time - start_time))
        echo "Durée totale du traitement: $duration secondes"
     fi
done

#Traitement Option_L
for ((i=2; i<7; i++)); do
    if [ "${!i}" = "Option_L"  ]; then
        #Lancement chronometre
	start_time=$(date +%s)
	echo "Traitement de Option_L"
	#Tri du Fichier csv 
        awk -F";" 'NR>2 {sum[$1]+=$5} END {for (key in sum) print key ";" sum[key]}' $1 | sort -t";" -k2,2nr | head -10 > CY-trucks/temp/Option_L.csv
        sort -t";" -k1,1nr -o CY-trucks/temp/Option_L.csv CY-trucks/temp/Option_L.csv
        #Traitement du graphique Option_L
        gnuplot -persist -e "load 'CY-trucks/gnuplot/Option_L.gp'"
        #Affichage du graphique Option_L
        xdg-open CY-trucks/images/Option_L.png
        #Fin chronometre + affichage
        end_time=$(date +%s)
        duration=$((end_time - start_time))
        echo "Durée totale du traitement: $duration secondes"
     fi
done

#Traitement Option_T
for ((i=2; i<7; i++)); do
    if [ "${!i}" = "Option_T"  ]; then
        #Lancement chronometre
	start_time=$(date +%s)
	echo "Traitement de Option_T"
	#Utilisaton d'un progc pour diviser en plusieurs parties le fichier csv
        CY-trucks/progc/Division $1
        #Utilisaton d'un progc pour trier les fichiers csv
        CY-trucks/progc/Option_T CY-trucks/temp/Data_{1..6}.csv
        #Traitement du graphique Option_T
        gnuplot -persist -e "load 'CY-trucks/gnuplot/Option_T.gp'"
        #Affichage du graphique Option_T
        xdg-open CY-trucks/images/Option_T.png
        #Fin chronometre + affichage
        end_time=$(date +%s)
        duration=$((end_time - start_time))
        echo "Durée totale du traitement: $duration secondes"
     fi
done

#Traitement Option_S
for ((i=2; i<7; i++)); do
    if [ "${!i}" = "Option_S"  ]; then
        #Lancement chronometre
	start_time=$(date +%s)
	echo "Traitement de Option_S"
        #Utilisaton d'un progc pour diviser en plusieurs parties le fichier csv
        CY-trucks/progc/Division $1
        #Utilisaton d'un progc pour trier les fichiers csv
        CY-trucks/progc/Option_S CY-trucks/temp/Data_{1..6}.csv
        #Traitement du graphique Option_S
        gnuplot -persist -e "load 'CY-trucks/gnuplot/Option_S.gp'"
        #Affichage du graphique Option_S
        xdg-open CY-trucks/images/Option_S.png
        #Fin chronometre + affichage
        end_time=$(date +%s)
        duration=$((end_time - start_time))
        echo "Durée totale du traitement: $duration secondes"
     fi
done

#Suppression des fichiers temporaires
rm -rf CY-trucks/temp/*










