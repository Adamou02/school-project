void nuit(int date, int nb_joueurs, Joueur joueur[nb_joueurs], int taille_deck, char* role[taille_deck]) {
    int i, y, poubelle;
    //le voleur et cupidon joue que la nuit date == 1
    if (date == 1) {
        //on fait joueur le voleur en premier
        voleur(i, date, nb_joueurs, joueur, taille_deck, role);
        //on fait jouer cupidon apres le voleur, si le voleur pioche cupidon, alors il pourra jouer le role cupidon        
        cupidon(date, nb_joueurs, joueur); 
    }
    Loup_garou(date, nb_joueurs, joueur);
    Voyante(date, nb_joueurs, joueur);
    Sorciere(date, nb_joueurs, joueur);
    }