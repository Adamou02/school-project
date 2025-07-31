int fin_de_partie(int nb_joueurs, Joueur joueur[nb_joueurs]);
void nuit(int date, int nb_joueurs, Joueur joueur[nb_joueurs], int taille_deck, char* role[taille_deck]); 
void jour(int date, int nb_joueurs, Joueur joueur[nb_joueurs]);

void role_joueur(int nb_joueurs, int taille_deck, Joueur joueur[nb_joueurs], char* role[taille_deck]) { 
    srand(time(NULL));    //permet d'avoir de l'aléatoire différent à chaque exécution.
    int i, j, poubelle;
    for (i=0; i<nb_joueurs; i++) {
        printf("Bonjour joueur %d, quel est ton pseudo (20 caractères max): ", i+1);
        scanf("%s", joueur[i].nom);
        j = rand () % taille_deck;        //on tire un role aleatoirement dans le deck
        while (role[j] == "NULL") {       //si role[j] a déjà été donné a un joueur, on redonne une valeur aleatoire à j pour avoir un nouveau role[j]
            j = rand () % taille_deck;
        }
        joueur[i].role = role[j];
        role[j] = "NULL";
        system ("clear");
        printf("%s, ton rôle est : %s \nTape 1 pour effacer ton rôle de l'écran.", joueur[i].nom, joueur[i].role);   
        scanf("%d", &poubelle);
        system ("clear");
        joueur[i].mort = 0;
        joueur[i].date_de_mort = -1;
        joueur[i].amour = 0;
    }
}



void debutdepartie(int nb_joueurs, Joueur joueur[nb_joueurs]) {
    int i, taille_deck = nb_joueurs+2, date = 1, fin = 0; //on met nb_joueurs+2 cartes dans le deck à cause du role Voleur qui necessite un deck de nb_joueurs+2 cartes
    //On prend le nombre maximal de joueurs (12) et on adapte les parties qui ont moins de joueurs en "supprimant" les derniers cartes.
    char* role[]= {"Villageois", "Villageois", "Loup-garou", "Loup-garou", "Voyante", "Sorcière", "Cupidon", "Voleur", "Chasseur", "Petite fille", "Villageois", "Villageois", "Villageois", "Loup-garou"};
    //Pour une partie de nb_joueurs, on supprime les cartes de nb_joueurs+2 jusqu'à la derniere carte atteinte dans une partie de 12 joueurs
    for (i=taille_deck; i<MAX+2; i++) {
        role[i] = "NULL";
    }
    role_joueur(nb_joueurs, taille_deck, joueur, role);
    
    //Le jeu est maintenant ici :

    while (fin == 0) {
    nuit(date, nb_joueurs, joueur, taille_deck, role); 
    fin = fin_de_partie(nb_joueurs, joueur);
    if (fin != 0) {
        break; //si la fin de la partie
    }
    jour(date, nb_joueurs, joueur);
    fin = fin_de_partie(nb_joueurs, joueur);
    date++; 
    }
    if (fin == 1) {
        printf ("Bravo le village, vous avez gagné !!\n");
    }
    else { //si fin == 2 mais pas besoin de faire la verif car si fin!=0 et fin!=1 alors il est obligatoirement fin==2.
        printf ("Bravo les loups, vous avez gagné !!\n");
    }
}

void creation_partie (int nb_joueurs) {
    int i;
    Joueur joueur[nb_joueurs];                                
    debutdepartie(nb_joueurs, joueur);
//    presence_role_debut_de_partie(nb_joueurs, joueur); un tableau qui permet de savoir quelles sont les roles encore en vie dans le jeu 
}