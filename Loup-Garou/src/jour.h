//#include "varext.h"
#define true 1
#define false 0

/*
    MEMO:
    -penser a réduire la variable nb_joueurs dans la fonction kill
    -ne pas oublier de variable dans la structure d'un joueurs c-a-d:
        -player.role
        -player.state
        -player.name
        -player.dateMort
        -player.amoureux
    -ne pas oublier le struct qui previent qu'une carte est présent dans le jeu exemple : chasseur.presence = true
    -la variable capitaine va être chiante car potentielement répétitif à attribué -> y reflechir en groupe
    -la fonction askRole doit etre dans la partie Initialisation de Adam car utilse pour savoir si un role est present dans la partie
    pour ne pas faire de boucle inutile (par contre prend plus de place) 
    -DEMANDER A ADAM COMMENT AVOIR LA FONCTION "CLEAR" 
    -essayer d'initialiser les flag à 0 dans le fichier initialisation pour ne pas les réinitialiser à 0 chaque jour 
    -le vote du capitaine doit se faire en debut de partie
*/

//-------------------------------------------------------------FONCTIONS-------------------------------------------------------------//


void clrVote (int nb_joueurs, Joueur joueur[nb_joueurs]) {
    int i;
    for(i=0;i<nb_joueurs;i++) {
        joueur[i].vote = 0;
    }
}


int votejour(int nb_joueurs, Joueur joueur[nb_joueurs]) { 
    int i, j, k, x, y, joueurMax = -1;   
    for (i=0; i<nb_joueurs; i++) { //boucle qui définit qui vote
        if (joueur[i].mort == false) {
            for (j=0; j<nb_joueurs; j++) { //affiche les votes possible
                if(joueur[j].mort == false) {
                    printf("%d = %s (%d vote(s) contre lui)\n", j, joueur[j].nom, joueur[j].vote);
                }
            }   
            do {
                printf ("\nBonjour %s, selectionner le joueur qui recoit votre vote : ", joueur[i].nom);
                scanf("%d", &x); //selection du joueur parmis la liste
            } while(x<0 || x>nb_joueurs-1 || joueur[x].mort==true); //s'assure que le joueur voté existe
            system ("clear");
            if (joueur[i].capitaine == true) { //lancement possible uniquement durant le vote de la journée
                joueur[x].vote = joueur[x].vote + 2;
            }
            else { //quand le capitaine meurt, plus personne n'a le capitaine == true, donc le vote du nv capitaine est equitable
                joueur[x].vote ++;
            }
        }
    }
    for (k=0; k<nb_joueurs; k++) {
        if (joueur[k].vote > joueurMax){
            y = k;
            joueurMax = joueur[k].vote;
        }
    }
    return y;
}

//-----------------------------------------------------Fonction-principale-----------------------------------------------------//



void capitaineVote(int nb_joueurs, Joueur joueur[nb_joueurs]) { 
    int x;
    printf("\n\nIl est l'heure d'élire un Capitaine\n");
    x = votejour(nb_joueurs, joueur);
    clrVote(nb_joueurs, joueur);
    printf("%s est maintenant le capitaine !\nLong vie au Capitaine %s !\n",joueur[x].nom,joueur[x].nom);
    joueur[x].capitaine = true;
}


void votePopulaire(int date, int nb_joueurs, Joueur joueur[nb_joueurs]) {
    int pendu, j;
    printf("\nLe vote de la journée va commencer, il est temps de débatre entre vous\nEntrez 1 dès que le débat est terminé\n");
    scanf("%d", &j);
    system("clear");

    pendu = votejour(nb_joueurs, joueur);
    clrVote(nb_joueurs, joueur);

    printf("\nLe village à décidé d'éliminer %s qui était un %s",joueur[pendu].nom,joueur[pendu].role);
    kill(pendu, date, nb_joueurs, joueur);
    if (joueur[pendu].role == "Loup-garou") {
        printf("\nLa foule saute de joie !");
    } 
    else {
        printf("\nLes habitant sont accablés de cette malheureuse perte");
    }
    if (joueur[pendu].role == "Chasseur") {
        chasseur(date, nb_joueurs, joueur); 
    }
    if (joueur[pendu].capitaine == 1) {
        printf ("\nLe capitaine a été pendu par le peuple");
        joueur[pendu].capitaine = 0;
        capitaineVote(nb_joueurs, joueur);
    }
    if (joueur[pendu].amour == 1) {
        joueur[pendu].amour = 0;  //l'amoureux deja mort n'a plus le .amour pour que ce soit celui encore en vie qui soit tuer
        kill_amour(date, nb_joueurs, joueur, pendu);
    }
}

int compteRendu(int date, int nb_joueurs, Joueur joueur[nb_joueurs]) { 
    int i, j, nb_mort=0;
    for (i=0; i<nb_joueurs; i++) {
        if (joueur[i].date_de_mort == date && joueur[i].mort == true) {
            printf("\nDans la nuit, %s est mort. Il était %s.\n",joueur[i].nom, joueur[i].role);
            if (joueur[i].amour == 1) {
                joueur[i].amour = 0;  //l'amoureux deja mort n'a plus le .amour pour que ce soit celui encore en vie qui soit tuer
                kill_amour(date, nb_joueurs, joueur, i);
            }
            if (joueur[i].role== "Chasseur") { 
                chasseur(date, nb_joueurs, joueur); 
            }
            if (joueur[i].capitaine == 1) {
                joueur[i].capitaine = 0;
                printf ("Le capitaine est donc mort durant cette nuit.");
                capitaineVote(nb_joueurs, joueur);
            }
        } 
    }
}

//----------------------------------------------------------------MAIN----------------------------------------------------------------//

void jour(int date, int nb_joueurs, Joueur joueur[nb_joueurs]){
    int poubelle;
    system("clear");
    clrVote(nb_joueurs, joueur);
    compteRendu(date, nb_joueurs, joueur);
    if (date == 1) {
        capitaineVote(nb_joueurs, joueur);   //Election du capitaine durant la premiere journée
    }
    votePopulaire(date, nb_joueurs, joueur);       //Le village choisit une personne à éliminer
    printf("\nLe village se rendort\nAppuyez sur 1 pour lancer la nuit");  //annonce de fin de la journée
    scanf("%d", &poubelle);
    system("clear");
}

/*
    Comment se déroule la journée dans le loup garou:
    -qui est victime de la sorciere ou loup garou
        -si chasseur alors carte activé
        -si joueurs amoureux alors le 2nd meurt
        -si capitaine mort alors désigne son succeseur
    -débat
    -vote (si égalité alors le capitaine départage (il est un vote compte double))
    (si chasseur, amoureux ou capitaine mort réefectuer leur fonctions)
    -annonce de la carte de la personne voté
    -le village se rendort
*/

int fin_de_partie(int nb_joueurs, Joueur joueur[nb_joueurs]) {
    int i, nb_loup=0, vie=0;
    for (i=0; i<nb_joueurs; i++) {
        if (joueur[i].role=="Loup-garou" && joueur[i].mort==0) { 
            nb_loup++; //permet de savoir combien de loups sont en vie
        }
        if (joueur[i].role!="Loup-garou" && joueur[i].mort==0) {
            vie++; //permet de savoir combien de citoyens sont en vie
        }
    }
    if (nb_loup == 0) {
        return 1;
    }
    else if (nb_loup >= vie){ //la partie s'arrete quand il n'y a que 1 citoyens de plus que de loups avant que la nuit tombe.
        return 2;
    }
    else {
        return 0; //la partie continue car aucune condtion de victoire n'est remplie.
    }
}