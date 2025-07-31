/*Beaucoup de lignes permettent de sécuriser le jeu, on appelle tous les joueurs à joueur pour chaque role pour pas que les gens se 
fassent démasquer en allant sur l'ordinateur lors du tour des loups par exepmpe. On demande a l'utilisateur d'entrer un nombre pour
eviter que le joueur x voit le role du joueur x+1 quand il a fini de jouer...*/
#include "Blabla.h"

typedef struct Joueur Joueur;
struct Joueur {
    char nom[20];
    char* role;
    int date_de_mort;
    int mort;
    int amour;
    int capitaine;
    int vote;
};

int poubelle; //variable globale utilisé dans chaque fonctions de ce programme pour gerer les system("clear")
int potion_vie = 1, potion_mort = 1; //potions de la sorciere

void capitaineVote(int nb_joueurs, Joueur joueur[nb_joueurs]); 
int chasseur(int date, int nb_joueurs, Joueur joueur[nb_joueurs]);
void clrVote (int nb_joueurs, Joueur joueur[nb_joueurs]);

void kill (int i, int date, int nb_joueurs, Joueur joueur[nb_joueurs]) {
    joueur[i].mort = 1;
    joueur[i].date_de_mort = date;  
}

void kill_amour (int date, int nb_joueurs, Joueur joueur[nb_joueurs], int i) {
    int j;
    for (j=0; j<nb_joueurs; j++) {
        if (joueur[j].amour == 1) {
            printf ("\nDe plus, %s, qui était %s, était l'amoureux de %s et meurt avec lui.", joueur[j].nom, joueur[j].role, joueur[i].nom);
            kill(j, date, nb_joueurs, joueur);
            joueur[j].amour = 0;
            /*ce mort ne sera pas rescité par la sorciere, mettre son jour de mort a date fera qu'il sera affiché dans le 
            compteRendu du matin alors que l'on ne veut pas qu'il y soit affiché, donc sa date_de_mort = -*/
            joueur[j].date_de_mort = -1;
            if (joueur[j].role == "Chasseur") {
                chasseur(date, nb_joueurs, joueur);
            }
            if (joueur[j].capitaine == 1) {
                printf ("\n%s est mort, il n'y a donc plus de capitaine dans le village.", joueur[j].nom);
                capitaineVote(nb_joueurs, joueur);
            }
        }
    }
}

void voleur (int i, int date, int nb_joueurs, Joueur joueur[nb_joueurs], int taille_deck, char* role[taille_deck]) {
    int j, pioche = 0;
    for (i=0; i<nb_joueurs; i++) {
        printf("\nNuit %d\tTour : Voleur\n\nBonjour %s, entrez 1 pour jouer ", date, joueur[i].nom);
        scanf("%d", &poubelle);
        system("clear");
        if (joueur[i].role == "Voleur") {
            printf ("\nVoleur preparez vous à jouer.");
            printf ("\n\nIl reste dans le deck\n\n");  
            for (j=0; j<taille_deck; j++) {  
                if (role[j] != "NULL") { //on affiche seulement les 2 cartes restantes du deck
                    printf ("\n%d) %s", j, role[j]);
                }
                if (role[j] == "Loup-garou") { //la regle oblige le voleur de prendre la carte loup si elle est dans le deck
                    joueur[i].role = role[j];
                    pioche = 1; 
                } 
            }
            if (pioche == 0) { //se lance seulement s'il n'y avait pas de carte loup dans le deck
                do {
                    printf ("\nQuelle carte voulez vous (entrez un nombre valide) : ");
                    scanf ("%d", &j);
                }while (j<0 || j>taille_deck-1 || role[j] == "NULL"); 
                //empeche au voleur de prendre un carte "NULL" du deck ou une carte hors du deck, il doit prendre un des deux roles disponible
                joueur[i].role = role[j];
                printf("%s, votre nouveau role est %s", joueur[i].nom, joueur[i].role);
            }
            else {
                printf ("\nIl y avait une carte loup-garou dans le deck, vous l'avez prise.");
            }
            printf ("\nEntrez 1 dès que vous avez mémorisé votre nouveau rôle.");
            scanf ("%d", &pioche); //on utilise une var deja existante comme poubelle pour ne pas gacher de la memoire à créer un nvlle var.
            system("clear");
        }
        else {
            Blabla();
        }
    }
}

void cupidon(int date, int nb_joueurs, Joueur joueur[nb_joueurs]) {
    int i, amour = 0, premier;
    for (i=0; i<nb_joueurs; i++) {
        printf("\nNuit %d\tTour : Cupidon\n\nBonjour %s, entrez 1 pour jouer ", date, joueur[i].nom);
        scanf("%d", &poubelle);
        system("clear");
        if (joueur[i].role == "Cupidon") {
            printf ("\nCupidon preparez vous à jouer.");
            while (amour != 2){ //tant que le cupidon n'a pas fait deux amoureux
                for (i=0; i<nb_joueurs; i++) {
                    if (joueur[i].amour == 0) { //permet de ne plus afficher le premier amoureux lors du deuxieme tour
                        printf ("\n%d) %s peut tomber amoureux", i, joueur[i].nom);
                    }
                }
                if (amour == 0){ //si cupidon designe son premier amoureux on retient son nom pour l'affichage du deuxieme tour
                    do {
                        printf ("\nEntrez le numéro du premier amoureux : ");
                        scanf ("%d", &premier);
                    }while (premier<0 || premier>nb_joueurs-1);
                    joueur[premier].amour = 1;
                }
                else {
                    do {
                        printf ("\nAvec qui %s sera amoureux : ", joueur[premier].nom);
                        scanf ("%d", &i);
                    }while (i<0 || i>nb_joueurs-1 || joueur[i].amour == 1);
                    joueur[i].amour = 1;
                }
                amour++;
                system("clear");
            }
        }
        else {
            Blabla();
        }
    }
    //On appelle tous les joueurs pour leur dire s'ils sont amoureux ou pas, et si oui avec qui.
    for (i=0; i<nb_joueurs; i++) {
        printf("\nBonjour %s, appuyez sur 1 pour savoir si vous êtes amoureux ", joueur[i].nom);
        scanf ("%d", &poubelle);
        if (joueur[i].amour == 1) {
            for (premier=0; premier<nb_joueurs; premier++) { //on recycle la variable premier
                if (joueur[premier].amour==1 && premier!=i) {
                    printf ("Vous êtes en couple avec %s.\nAppuyez sur 1 une fois que vous avez mémorisé le nom de votre amoureux ", joueur[premier].nom);
                    scanf ("%d", &poubelle);
                }
            }
        }
        else {
            printf("Vous êtes célibataires.\nAppuyez sur 1 puis retournez à votre place");
            scanf ("%d", &poubelle);
        }
        system("clear");
    }
}

int chasseur (int date, int nb_joueurs, Joueur joueur[nb_joueurs]) {
    int i;
    printf ("\nLe chasseur prend son fusil\n");
    for (i=0; i<nb_joueurs; i++) {
        if (joueur[i].mort == 0) {
            printf ("%d) %s \n", i, joueur[i].nom);
        }
    }
    do {
        printf ("Quel joueur éliminer (entrez un numéro valide): ");
        scanf ("%d", &i);
    } while (joueur[i].mort != 0);
    kill(i, date, nb_joueurs, joueur); 
    system("clear");
    if (joueur[i].role == "Loup-garou") {
        printf ("\nBeau tir ! Le chasseur à tuer %s, qui était %s", joueur[i].nom, joueur[i].role);
    }
    else {
        printf ("\nAie ! Le chasseur à tuer %s, qui était %s", joueur[i].nom, joueur[i].role);
    } 
    if (joueur[i].amour == 1) {
        joueur[i].amour = 0;
        kill_amour(date, nb_joueurs, joueur, i);
    }
}

void Petite_Fille(int nb_joueurs, Joueur joueur[nb_joueurs]) {
    int i;
    printf ("Bonjour Petite fille, soyez discrète...");
    for (i=0; i<nb_joueurs; i++){
        if (joueur[i].role=="Loup-garou" && joueur[i].mort==0) {
            printf("\n%s est un Loup Garou", joueur[i].nom);
        }
    }
}

void Bruit(int nb_joueurs, Joueur joueur[nb_joueurs]) { 
//cette fonction permet de donner un indice aux roles qui n'ont rien à faire la nuit (probavilité : 2 chances sur nb_joueur)
    int i, j, h, k;  
    j = rand()%nb_joueurs;
    if (j<=1) {  //Plus la partie comporte beaucoup de gens, moins il y a de chance que ce passif soit executé (car il depend de nb_joueur)       
        for (i=0; i<nb_joueurs; i++) {
            if (joueur[i].role=="Loup-garou" && joueur[i].mort==0) {
                j = i; //on recycle j qui contient maintenant le numero d'un loup en vie
            }
        }
        do {
            h = rand()%nb_joueurs; 
        }while (joueur[h].mort == 1); //prend le numero d'un joueur aléatoire EN VIE
        do {
            k = rand()%nb_joueurs; 
        }while (joueur[k].mort == 1); //prend le numero d'un joueur aléatoire EN VIE
        printf("\nIl y a eu du bruit entre %s, %s et %s\nAppuyez sur 1 quand vous avez retenu vers qui il y a eu du bruit. ", joueur[j].nom , joueur[h].nom, joueur[k].nom);
    }
    else {
        printf("\nVous n'avez rien entendu cette nuit, appuyez sur 1 puis retournez dormir.");
    }
}

void Petite_Fille2(int nb_joueurs, Joueur joueur[nb_joueurs]){ 
    int i,j;
//cette fonction permet de reveler le nom de la petite fille avant que les loups votes (probavilité : 1 chance sur nb_joueur)
    j = rand()%nb_joueurs;
    if (j=0){
        for (i=0; i<nb_joueurs; i++){
            if (joueur[i].role == "Petite Fille"){
                printf("\n%s vous observe", joueur[i].nom);
            }
        }
    }
}

/*                               **Quand il y a egalite dans les votes**
L'architecture de la fonction loup fait que le premier loup indique au deuxieme contre qui il a vote, donc le deuxieme loup peut
suivre le vote du premier, ou alors il vote pour quelqu'un d'autre en "ayant le vote le plus fort"*/

void Loup_garou(int date, int nb_joueurs, Joueur joueur[nb_joueurs]){
    int i, j, k, x, y, max = 0;
    clrVote(nb_joueurs, joueur);
    srand(time(NULL)); //permet l'aleatoire pour le role petite fille et Villageois
    for (i=0; i<nb_joueurs; i++){
        if (joueur[i].mort==0 || date==joueur[i].date_de_mort) { 
            //le joueur joue s'il est en vie ou s'il est mort mais qu'il ne le sait pas encore (tuer durant cette nuit).
            printf("\nNuit %d\tTour : Loup-garou\n\nBonjour %s, entrez 1 pour jouer ", date, joueur[i].nom);
            scanf("%d", &poubelle);
            if (joueur[i].role=="Loup-garou"){
                Petite_Fille2(nb_joueurs, joueur);
                printf("\n%s, qui souhaitez vous tuer ce soir : ", joueur[i].nom);
                for (j=0; j<nb_joueurs; j++){
                    if (joueur[j].role!="Loup-garou" && joueur[j].mort==0){
                        printf("\nTapez %d pour %s (%d vote(s) contre lui)", j , joueur[j].nom, joueur[j].vote);
                    }
                }
                do{
                    printf("\nEntrez le numéro : ");
                    scanf("%d", &x);
                }while(x<0 || x>nb_joueurs-1 || joueur[x].mort==1 || joueur[x].role=="Loup-garou");
                joueur[x].vote++;
            }
            else if (joueur[i].role=="Petite fille") {
                Petite_Fille (nb_joueurs, joueur);
                printf ("\nTapez 1 dès que vous avez retenu le nom des loups. ");
                scanf("%d", &poubelle); //temps de pause pour que le joueur puisse voir les infos a l'ecran avant le clear
            }
            else { 
                //cette fonction bruit pdt la nuit concerne tous les roles sauf loup et petite fille
                Bruit(nb_joueurs, joueur); 
                scanf("%d", &poubelle); //temps de pause pour que le joueur puisse voir les infos a lecran avant le clear
            }
            system("clear");
        }
    }
    for(k=0; k<nb_joueurs; k++){
        if(joueur[k].vote > max){
            y = k;
            max = joueur[k].vote;
        }
    }
    kill(y, date, nb_joueurs, joueur);
}

void Voyante(int date, int nb_joueurs, Joueur joueur[nb_joueurs]){
    int i, j, k;
    for (i=0; i<nb_joueurs; i++){
        if (joueur[i].mort==0 || date==joueur[i].date_de_mort) { 
            //le joueur joue s'il est en vie ou s'il est mort mais qu'il ne le sait pas encore (tuer durant cette nuit).
            printf("\nNuit %d\tTour : Voyante\n\nBonjour %s, entrez 1 pour jouer ", date, joueur[i].nom);
            scanf("%d", &poubelle);
            if (joueur[i].role == "Voyante"){
                printf("La carte de quel joueur souhaitez-vous voir ?");
                for (j=0; j<nb_joueurs; j++){
                    //on affiche tout ceux qui étaient en vie au debut de la nuit (Y COMPRIS celui tué par les loups), mais pas la voyante;
                    if (joueur[j].role!="Voyante") { //on a donc 3 conditions && et || d'où l'utilisation d'une double boucle if
                        if (joueur[j].mort==0 || date==joueur[j].date_de_mort) {
                            printf("\nTapez %d pour voir le role de %s", j, joueur[j].nom);
                        }
                    }
                }
                do{
                    scanf("%d", &k);
                }while(k<0 || k>nb_joueurs-1 || joueur[k].role=="Voyante" || (joueur[k].mort==1 && joueur[k].date_de_mort!=date)); 
                /*on n'accepte pas que la voyante regarde la carte de quelqu'un qui est mort en dehors de cette nuit
                (qqun qui n'a pas été affiche par la boucle 10 lignes au dessus) ou quelle essaye de regarder sa propre carte*/
                printf("\n%s est %s\nAppuyez sur 1 quand vous avez mémorisé le role de %s", joueur[k].nom, joueur[k].role, joueur[k].nom);
                scanf("%d", &poubelle);
                system("clear");
            }
            else{
                Blabla();
            }
        }
    }
}

void Sorciere(int date, int nb_joueurs, Joueur joueur[nb_joueurs]) {
int i,j,k,x;
    for(i=0; i<nb_joueurs; i++){
        if (joueur[i].mort==0 || date==joueur[i].date_de_mort) { 
            system("clear");
            //le joueur joue s'il est en vie ou s'il est mort mais qu'il ne le sait pas encore (tuer durant cette nuit).
            printf("\nNuit %d\tTour : Sorcière\n\nBonjour %s, entrez 1 pour jouer ", date, joueur[i].nom);
            scanf("%d", &poubelle);
            if (joueur[i].role == "Sorcière") {
                system("clear");
                for (j=0; j<nb_joueurs; j++) {
                    if (joueur[j].date_de_mort == date) { //permet d'afficher que les morts de cette nuit
                        printf("\n%s est mort cette nuit", joueur[j].nom);
                        x=j; //on retient la position du joueur mort cette nuit
                    }
                }
                if (potion_vie==1 && potion_mort==1) {
                    printf("\nVous avez une potion de soin et une potion de poison. \nTapez 0 pour ne rien faire \nTapez 1 pour sauver le joueur mort \nTapez 2 pour tuer un autre joueur \nTapez 3 pour sauver le joueur mort et tuer un autre joueur");
                    do{
                        printf("\nEntrez le numéro : ");
                        scanf(" %d", &k);
                    }while(k<0 || k>3); //on veut soit 0, 1, 2 ou 3
                }
                else{
                    if (potion_vie==1 && potion_mort==0){
                        printf("\nVous avez une potion de soin \nTapez 0 pour ne rien faire \nTapez 1 pour sauver le joueur mort");
                        do{
                            printf("\nEntrez le numéro : ");
                            scanf("%d", &k);
                        }while(k!=0 && k!=1); //on veut 0 ou 1
                    }
                    else{
                        if (potion_mort==1 && potion_vie==0){
                            printf("\nVous avez une potion de poison \nTapez 0 pour ne rien faire \nTapez 2 pour tuer un joueur");
                            do{
                                printf("\nEntrez le numéro : ");
                                scanf("%d", &k);
                            }while(k!=0 && k!=2);
                        }
                        else {
                            printf ("\nIl ne vous reste aucune potion");
                            k = 0;
                        }
                    }
                }
                switch(k) { //on a securisé au dessus pour que k soit egale à 0, 1,2 ou 3
                    case 0 :
                        printf("\nVous avez choisi de ne rien faire.\nTapez 1 pour vous rendormir");
                        scanf("%d", &poubelle);
                        break;
                    case 1 : //reanimé joueur[x]
                        joueur[x].mort = 0;
                        joueur[x].date_de_mort = -1;
                        potion_vie = 0;
                        printf("\nVous avez réanimé %s\nTapez 1 pour vous rendormir", joueur[x].nom);
                        scanf("%d", &poubelle);
                        break;
                    case 2 : //tuer joueur[x]
                        system("clear");
                        printf("Vous avez choisi d'utiliser votre poison\n");
                        for (j=0; j<nb_joueurs; j++){ //on recycle j
                            if (joueur[j].mort == 0){
                                printf("\nTapez %d pour tuer %s", j, joueur[j].nom);
                            }
                        }
                        do{
                            printf("\nEntrez le numéro : ");
                            scanf("%d", &j); 
                        }while(j<0 || j>nb_joueurs-1 || joueur[j].mort==1);
                        kill(j, date, nb_joueurs, joueur);
                        potion_mort = 0;
                        printf("\nTapez 1 pour vous rendormir");
                        scanf("%d", &poubelle);
                        break;
                    default : //default ne peut que s'executer quand k=3, tuer qqun et soigne qqun
                        system("clear");
                        printf("Vous avez choisi d'utiliser votre soin sur %s\n Qui voulez vous empoisonner \n", joueur[x].nom);
                        joueur[x].mort = 0;
                        joueur[x].date_de_mort = -1;
                        for(j=0; j<nb_joueurs; j++){
                            if(joueur[j].mort == 0){
                                printf("\nTapez %d pour tuer %s", j, joueur[j].nom);
                            }
                        }
                        do{
                            printf("\nEntrez le numéro : ");
                            scanf("%d", &j);
                        }while(j<0 || j<nb_joueurs-1 || joueur[j].mort==1);
                        kill(j, date, nb_joueurs, joueur);
                        potion_vie = 0;
                        potion_mort =0;
                        printf("\nTapez 1 pour vous rendormir");
                        scanf("%d", &poubelle);
                        break;
                }
            }
            else{
                Blabla();
            }
        }
    }
}