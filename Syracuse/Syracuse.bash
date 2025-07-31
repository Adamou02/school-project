#!/bin/bash

clear
#Dans tous les cas, le fichier C sera appelé. Donc on le compile dès le début
gcc Syracuse.c -o Syracuse
#On vérifie que les 2 paramètres entrés vérifient les conditions définies dans le README et le HELP
if [ $# -eq 2 ] && let $1 2>/dev/null && let $2 2>/dev/null && [ $1 -lt $2 ] && [ $1 -gt 0 ]
then
    if [ ! -d tmp ]
    then
        mkdir tmp
    fi
    if [ ! -d resultats ]
    then
        mkdir resultats
    fi
    if [ ! -d resultats/resultats-$1-$2 ]
    then
        mkdir resultats/resultats-$1-$2
    fi
    #Récolte des informations dans le fichier .dat
    echo -ne 'Script en cours de fonctionnement, veuillez ne pas couper le processus.\n\n#######################################                                                                              (33%)\r'
    for (( i=$1; i<=$2; i++))
    do
        ./Syracuse $i "tmp/f$i.dat"
        head -n -3 tmp/f$i.dat | tail -n +2 >> tmp/fonction_un$i.dat
        echo "$i `tail -n -3 tmp/f$i.dat | head -n +1 | cut -d "=" -f2`" >> tmp/altitude.dat
        echo "$i `tail -n -2 tmp/f$i.dat | head -n +1 | cut -d "=" -f2`" >> tmp/dureevol.dat
        echo "$i `tail -n -1 tmp/f$i.dat | cut -d "=" -f2`" >> tmp/dureealtitude.dat
    done
    clear
    echo -ne 'Script en cours de fonctionnement, veuillez ne pas couper le processus.\n\n##############################################################################                                       (66%)\r'
    #Affichage graphique
    gnuplot -persist <<-EOFMarker
        set terminal jpeg
        set output "resultats/resultats-$1-$2/Vols-$1-$2.jpeg"
        set xlabel "n"
        set ylabel "Un"
        unset key
        set title "Un en fonction de n pour tous les U0 dans [$1;$2]"
        plot for[i = $1:$2] "tmp/fonction_un".i.".dat" w l lt rgb "#6b04bf"
EOFMarker
    gnuplot -persist <<-EOFMarker
        set terminal jpeg
        set output "resultats/resultats-$1-$2/Altitude_max-$1-$2.jpeg"
        set xlabel "U0"
        set ylabel "Nombre d'occurences"
        set title "Altitude maximum atteinte en fonction de U0"
        plot "tmp/altitude.dat" w l
EOFMarker
    gnuplot -persist <<-EOFMarker
        set terminal jpeg
        set output "resultats/resultats-$1-$2/DuréeVol-$1-$2.jpeg"
        set xlabel "U0"
        set ylabel "Nombre d'occurences"
        set title "Durée de vol en fonction de U0"
        plot "tmp/dureevol.dat" w l
EOFMarker
    gnuplot -persist <<-EOFMarker
        set terminal jpeg
        set output "resultats/resultats-$1-$2/DuréeAltitude-$1-$2.jpeg"
        set xlabel "U0"
        set ylabel "Nombre d'occurences"
        set title "Durée de vol en altitude en fonction de U0"
        plot "tmp/dureealtitude.dat" w l
EOFMarker
    #Création de la synthèse
    moyenne_altitude=0 max_altitude=0
    list=`tail +1 tmp/altitude.dat | cut -d " " -f2`
    min_altitude=`head -n 1 tmp/altitude.dat | cut -d " " -f2`
    for i in $list
    do
        if [ $min_altitude -ge $i ]
        then
            min_altitude=$i
        fi
        if [ $max_altitude -le $i ]
        then
            max_altitude=$i
        fi
        moyenne_altitude=$(( $moyenne_altitude+$i ))
    done
    moyenne_altitude=$(( $moyenne_altitude/($2-$1) ))
    ###########################################################################################################
    moyenne_duree_vol=0 max_duree_vol=0
    list=`tail +1 tmp/dureevol.dat | cut -d " " -f2`
    min_duree_vol=`head -n 1 tmp/dureevol.dat | cut -d " " -f2`
    for i in $list
    do
        if [ $min_duree_vol -ge $i ]
        then
            min_duree_vol=$i
        fi
        if [ $max_duree_vol -le $i ]
        then
            max_duree_vol=$i
        fi
        moyenne_duree_vol=$(( $moyenne_duree_vol+$i ))
    done
    moyenne_duree_vol=$(( $moyenne_duree_vol/($2-$1) ))
    ###########################################################################################################
    moyenne_duree_altitude=0 max_duree_altitude=0
    list=`tail +1 tmp/dureealtitude.dat | cut -d " " -f2`
    min_duree_altitude=`head -n 1 tmp/dureealtitude.dat | cut -d " " -f2`
    for i in $list
    do
        if [ $min_duree_altitude -ge $i ]
        then
            min_duree_altitude=$i
        fi
        if [ $max_duree_altitude -le $i ]
        then
            max_duree_altitude=$i
        fi
        moyenne_duree_altitude=$(( $moyenne_duree_altitude+$i ))
    done
    moyenne_duree_altitude=$(( $moyenne_duree_altitude/($2-$1) ))
    #Suppression de tous les fichiers temporaires .dat
    rm -r tmp #commenter cette ligne permet de visualiser les fichiers .dat (attention, exécuter le script plusieurs fois sans supprimer les 
              #fichiers temporaires faussera les résultats obtenus).
    echo "Altitude minimale : $min_altitude" > resultats/resultats-$1-$2/synthèse-$1-$2.txt
    echo "Altitude moyenne : $moyenne_altitude" >> resultats/resultats-$1-$2/synthèse-$1-$2.txt
    echo "Altitude maximale : $max_altitude" >> resultats/resultats-$1-$2/synthèse-$1-$2.txt
    echo "Durée de vol minimale : $min_duree_vol" >> resultats/resultats-$1-$2/synthèse-$1-$2.txt
    echo "Durée de vol moyenne : $moyenne_duree_vol" >> resultats/resultats-$1-$2/synthèse-$1-$2.txt
    echo "Durée de vol maximale : $max_duree_vol" >> resultats/resultats-$1-$2/synthèse-$1-$2.txt
    echo "Durée de vol en altitude minimale : $min_duree_altitude" >> resultats/resultats-$1-$2/synthèse-$1-$2.txt
    echo "Durée de vol en altitude moyenne : $moyenne_duree_altitude" >> resultats/resultats-$1-$2/synthèse-$1-$2.txt
    echo "Durée de vol en altitude maximale : $max_duree_altitude" >> resultats/resultats-$1-$2/synthèse-$1-$2.txt
    clear
    echo -ne 'Script en cours de fonctionnement, veuillez ne pas couper le processus.\n\n#####################################################################################################################(100%)\r'
    sleep 0.5
    clear
    echo "Script exécuté avec succès en $SECONDS secondes"
    echo "Script exécuté en $SECONDS secondes" >> resultats/resultats-$1-$2/synthèse-$1-$2.txt
    cd resultats/resultats-$1-$2
    echo "Adresse du fichier : `pwd`"
else
    ./Syracuse -h
fi