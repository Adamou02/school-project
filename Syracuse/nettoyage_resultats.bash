#!/bin/bash

echo "Voulez vous vraiment supprimer votre dossier contenant les résultats du programme Syracuse (graphiques et synthèses) ? [Y/n]"
read var 

while [ "$var" != "Y" ] && [ "$var" != "n" ]
do
    clear
    echo "Veuillez taper Y pour effacer les résultats ou n pour quitter le script :"
    read var
done
if [ "$var" = "Y" ]
then 
    if [ -d resultats ]
    then
        rm -r resultats
        echo "Dossier supprimé avec succès, au revoir."
    else
        echo "Le dossier [resultats] n'existe pas. Au revoir"
    fi
    sleep 2
    clear
else
    clear
fi