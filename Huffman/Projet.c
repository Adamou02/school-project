#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globale.h"
#include "Prototypes.h"

int main (int argc, char* argv[]) {
    if(argc == 4) {     //il faut entrer dans l'executable un nom de fichier source et un nom de fichier à creer, sinon on lance pas
        if (strcmp(argv[1], "-c") == 0) {
            compresser(argv[2], argv[3]); //Prends en paramtere les informations que l'utilsateur entre dans l'executable
            printf("Compression terminée\nNom de votre fichier : %s\n", argv[3]);
        }
        else if (strcmp(argv[1], "-d") == 0) {
            decompresser(argv[2], argv[3]);
            printf("Décompression terminée\nNom de votre fichier : %s\n", argv[3]);
        }
    }
    else if ((argc == 2) && (strcmp(argv[1], "-h") == 0)) {
        system("clear");
        system("cat HELP");
    }
    else { 
        system ("clear");
        system("tail -n +15 README");
        printf("\n\n");
        exit(1);
    }
    return 0;
}

/*********************************************************************************************************************************************/
/*****************************************************COMPRESSION*****************************************************************************/
/*********************************************************************************************************************************************/

PArbre ABR_ENTETE[MAX_SYMBOLES]; //variable globale que pour l'entete du fichier binaire

void compresser (char* FichierDeBase, char* FichierACreer) {
    unsigned int i;
    Element car[MAX_SYMBOLES] = {0,0};                   //notre tableau qui va compter le nb d'apparitions de chaque car ascii dans le txt
    PArbre a[MAX_SYMBOLES];                      //notre arbre qui contient des racines avec un car ascii et son nombre d'apparitions
    FILE* fichierdebase = fopen(FichierDeBase, "r");
    if (fichierdebase == NULL) {                          //si le fichier n'existe pas, erreur.
        printf ("Erreur d'ouverture du fichier texte\n\n");
        system("cat README");
        exit(1);
    }
    InitialiserTab(car);
    Compteur(car, fichierdebase);
    TrieTabCroissant(car);
    for (i=0; i<MAX_SYMBOLES; i++) {             //on va créer un noeud pour chaque car ascii
        a[i] = CreerNoeud (car[i].car, car[i].nb_occurences);
    }
    Creer_Arbre_Huffman(a, car);        //on va creer un arbre grace à nos MAX_SYMBOLES noeuds qui ont chacun une val ascii avec l'occurence
    Parcours_arbre(a[0], 0, 0);   //donne un code "binaire" a chaque feuille
    strcat(FichierACreer, ".huff");     //on ajoute l'extansion .huff au nom du fichier à créer entré par l'utilisateur
    FILE* fichieracreer = fopen(FichierACreer, "w");
    if (fichieracreer == NULL) {        //on arrete le programme si le fichier binaire crée est null
        printf("Erreur de création du fichier binaire");
        exit(1);
    }
    //si le programme lit ces lignes, c'est que le fichier binaire a été crée avec succès
    Ecrire_Entete(fichieracreer);
    Ecrire_Codage(fichierdebase, fichieracreer);
    fclose(fichierdebase);
    fclose(fichieracreer);
}

//on initialise les cases du tableau à 0 pour nb_apparitions et à i pour la valeur ascii
void InitialiserTab(Element car[MAX_SYMBOLES]) {
    unsigned int i;
    for (i=0; i<MAX_SYMBOLES; i++) {
        car[i].car = i;
/*On sauvegarde dans notre tableau la case i du tableau (qui correspond à la val ascii) pour pouvoir trier le talbeau sans 
perdre notre valeur ascii.*/
        car[i].nb_occurences=0;
    }
}


/*Fonction qui va compter les occurences pour chaques valeurs ascii 
(si la valeur ascii n'est pas dans le texte, sa valeur "nb_occurences sera égale à 0")*/
void Compteur(Element car[MAX_SYMBOLES], FILE* fichierdebase) {
    unsigned int i;                                 //i va prendre la valeur ascii du caractere present dans le txt
    while ((i = fgetc(fichierdebase)) != EOF) {       //tant que le caractere n'est pas celui de la fin du fichier
        car[i].nb_occurences++;    
    }
}

/*Trie ordre croissant avec les cases dont l'occurences vaut 0 à droite des cases dont le caractere apparait dans le txt*/
void TrieTabCroissant(Element car[MAX_SYMBOLES]) {
    unsigned int i, j;
    Element tmp; 
    //cette fonction est basique, nous l'appliquons simplement sur un Element plutot qu'un int ce qui alourdi un peu le code
    for (i=0; i<MAX_SYMBOLES; i++) {
        for (j=i; j<MAX_SYMBOLES; j++) {
            if (car[i].nb_occurences > car[j].nb_occurences) {
                tmp.nb_occurences = car[j].nb_occurences;
                tmp.car = car[j].car;
                car[j].nb_occurences = car [i].nb_occurences;
                car[j].car = car[i].car;
                car[i].nb_occurences = tmp.nb_occurences;
                car[i].car = tmp.car;
            }
        }
    }
    //Metre tous les car avec un nb_occ égale à 0 à droite de ceux qui sont presents dans le texte
    for (i=0; i<MAX_SYMBOLES; i++) {
        if (car[i].nb_occurences == 0) {
            for (j=i; j<MAX_SYMBOLES; j++) {
                if (car[j].nb_occurences != 0) {
                    tmp.nb_occurences = car[j].nb_occurences;
                    tmp.car = car[j].car;
                    car[j].nb_occurences = car [i].nb_occurences;
                    car[j].car = car[i].car;
                    car[i].nb_occurences = tmp.nb_occurences;
                    car[i].car = tmp.car;
                    j=MAX_SYMBOLES; //pour sortir de la boucle for quand le premier car[j] est trouvé
                }
            }
        }
    }
}


PArbre CreerNoeud(int caractere, int nb_occurences) {
    PArbre a;
    a=(PArbre)malloc(sizeof(PArbre));
    if (a == NULL) {
        printf("Erreur malloc");
        exit (1);
    }
    a->valeur.car = caractere;
    a->valeur.nb_occurences = nb_occurences;
    a->fg=NULL;
    a->fd=NULL;
    return a;
}


//On passe les deux plus petits noeuds du tableau de noeuds, avec on va créer un racine mère
PArbre Cons(PArbre a1, PArbre a2, int nb_occ, int car) {
    PArbre arbre;
    arbre = CreerNoeud(car, nb_occ);
    if (a1 != NULL) {
        arbre->fg = Cons(a1->fg, a1->fd, a1->valeur.nb_occurences, a1->valeur.car);
    }
    if (a2 != NULL) {
        arbre->fd = Cons(a2->fg, a2->fd, a2->valeur.nb_occurences, a2->valeur.car);
    }
    return arbre;
}

//on a nos MAX_SYMBOLES feuilles avec lesquels on va creer un arbre
void Creer_Arbre_Huffman(PArbre feuilles[MAX_SYMBOLES], Element car[MAX_SYMBOLES]) {
    unsigned int i, j;
    PArbre tmp;
    if ((tmp = (PArbre)malloc(sizeof(PArbre))) == NULL) {
        printf("Erreur malloc");
        exit(1);
    }
    /*on insert le noeud_mere qu'on crée dans la bonne case pour que ca reste trié mais à gauche des nb_occ == 0, puis on refait tant
    qu'il ne reste pas que le noeud mère contenant tout l'arbre, ce qui se traduit par un nb_occ égale à 0 pour toutes les cases du 
    tableau sauf la premiere case qui contient la racine de l'arbre.*/
    if (feuilles[1]->valeur.nb_occurences != 0) {
        PArbre noeud_mere = Cons(feuilles[0], feuilles[1], feuilles[0]->valeur.nb_occurences + feuilles[1]->valeur.nb_occurences, 0);
        feuilles[0] = noeud_mere;
        feuilles[1]->valeur.nb_occurences = 0;
        /*on fait sortir la feuille[1] car elle a un nb_occurences égale à 0 ce qui nous empeche de trier dans la zone restreintes des 
        premieres feuilles qui sont celles avec un nb_occ different de 0*/
        i=1;
        while (feuilles[i+1]->valeur.nb_occurences != 0) {
            tmp = feuilles[i];
            feuilles[i] = feuilles[i+1];
            feuilles[i+1] = tmp;
            i++;
        }
        //puis on trie la feuille[0] parmis les autres premieres feuilles ayant un nb_occurences
        i=0;
        while (feuilles[i+1]->valeur.nb_occurences != 0) {
            if (feuilles[i]->valeur.nb_occurences > feuilles[i+1]->valeur.nb_occurences) {
                tmp = feuilles[i];
                feuilles[i] = feuilles[i+1];
                feuilles[i+1] = tmp;
            }    
            i++;
        }
        Creer_Arbre_Huffman(feuilles, car);
    }
}

//Compression//


//Va donner un code à chaque feuille
void Parcours_arbre(PArbre racine, int code, int nb_bits) {
    if (racine->fg==NULL && racine->fd==NULL) {
        racine->code = code;        //donne un valeur binaire (sous forme decimale) de la feuille en fonction de sa position dans l'arbre
        racine->nb_bits = nb_bits;  //nous donne l'hauteur du noeud et donc le nombre de place qu'il va prendre dans un octet (par exemple si nb_bits = 3 alors ce caractere va prendre 3 bits sur les 8 disponibles dans un octet)
        //On sauvegarde l'information de chaque feuilles pour créer notre tableau dans l'entete du fichier binaire
        ABR_ENTETE[NbSymboles] = racine;
        //l'entete aura donc la valeur ascii, le nb d'ocurrence et son equivalent binaire
        NbSymboles++;
    }
    else {
        Parcours_arbre(racine->fg, (code<<1), nb_bits++);
        Parcours_arbre(racine->fd, (code<<1)+1, nb_bits++);
    }
}


/*cette fonction va nous permettre d'avoir le code binaire de chaque caractere dans l'entete du fichier binaire, ainsi on aura dans le fichier
des nombres binaires que l'on pourra associer à un caractere*/
void Ecrire_Entete(FILE* fichieracreer) {
    /*unsigned int occ_nb_octets = 1;
    unsigned char tab_octets[8];*/
    unsigned int i;
        //ajoute le nombre de symbole ascii differents dans le fichier decompresse, puis ecrit leur car, nb_occ et code binaire dans l'entete du fichier bin 
        fprintf(fichieracreer, "%d\n", NbSymboles);
    for (i=0; i<NbSymboles; i++) {
        fprintf(fichieracreer, "%d%d%d", ABR_ENTETE[i]->valeur.car, ABR_ENTETE[i]->valeur.nb_occurences, ABR_ENTETE[i]->code);
        /*les caracteres sont collés dans le fichier binaire mais lors de la décompression on va lire l'entete octet par octet 
        (avec un (for i<taille) pour savoir quand s'arrete l'entete) donc on pourra récolter les informations meme si il n'y a pas d'espace 
        entre chaque caractere*/
    }
    fprintf(fichieracreer, "\n");
}

//on ecrit dans le corps du fichier compresser
void Ecrire_Codage(FILE* fichierdebase, FILE* fichieracreer) {
    unsigned char octet, octet_rempli;
    int code_binaire_car, nb_bits_car, nb_bits_int, nb_bits_tampon = 0, tampon = 0;
    unsigned int i;
    nb_bits_int = sizeof(int)*8;
    rewind(fichierdebase);      //on fait revenir le pointeur au debut du fichier de base (décompressé)
    while ((fscanf(fichierdebase, "%c", &octet)) != EOF){   //tant qu'on est pas à la fin de notre fichier txt
        for (i=0; i<NbSymboles; i++) {
            if (ABR_ENTETE[i]->valeur.car == octet) {
                code_binaire_car = ABR_ENTETE[i]->code;     //sauvegarder le code et le nb de bits du caractere lu dans le txt
                nb_bits_car = ABR_ENTETE[i]->nb_bits;
            }
        }
        //on decale la valeur binaire (sous forme de bit) le plus a gauche possible d'un octet de taille int
        code_binaire_car = (code_binaire_car<<(nb_bits_int-nb_bits_car));
        //On met la valeur binaire à droite des bits disponible du tampon
        code_binaire_car = (code_binaire_car>>nb_bits_tampon);      
        tampon = tampon|code_binaire_car;
        //On met a jour le nombre de bits qui sont dans le tampon
        nb_bits_tampon = nb_bits_tampon + nb_bits_car;
        /*si le tampon a plus de 8 bits, on écrit un octet avec les 8 premiers bits. On repete l'operation tant qu'il a plus de 8 bits 
        (normalement qu'une fois car le tampon est sensé avoir au maximum 7bits sinon il se serait vidé au tour d'avant. Et le code binaire qu'on
        ajoute au tampon fait maximum 8bits), mais les gens disent sur internet qu'il faut vider le tampon tant que et non pas si le nb_bits du
        tamon est supérieur à 8*/
        while (nb_bits_tampon>=8) {
            //on donne les 8 premiers bits du tampon dans un octet que l'on ecrit dans le fichier binaire
            octet_rempli = (tampon>>(nb_bits_int-8));
            fprintf(fichieracreer, "%c", octet_rempli);
            //On change la valeur du tampon en enlevant les 8 bits (octet) qu'on vient d'ecrire dans le fichier binaire et on maj le nb_bits_tampon
            tampon = tampon<<8;
            nb_bits_tampon = nb_bits_tampon-8;
        }
    }
    /*Si on est arrivé à la fin du fichier d'origine mais qu'il reste de l'information dans le tampon, on le vide en écrivant un octet partiellement
    rempli, le seul du fichier binaire :)*/
    if (nb_bits_tampon != 0) {
        octet_rempli = (tampon>>(nb_bits_int-8));
        fprintf(fichieracreer, "%c", octet_rempli);
        //on vide le tampon et on met son nb_bits à 0 
        tampon = tampon<<nb_bits_tampon;
        nb_bits_tampon = 0;
    }
}



/*********************************************************************************************************************************************/
/***************************************************DECOMPRESSION*****************************************************************************/
/*********************************************************************************************************************************************/


void decompresser (char* FichierDeBase, char* FichierACreer) {
    FILE* fichierdebase = fopen(FichierDeBase, "r"); //notre fichier compressé
    if (fichierdebase == NULL) {                    //si le fichier n'existe pas, erreur.
        printf ("Erreur d'ouverture du fichier compressé\n\n");
        system("cat README");
        exit(1);
    }
    strcat (FichierACreer, "_décompressé.txt");
    FILE* fichieracreer = fopen(FichierACreer, "w"); //notre fichier decompressé
    if (fichieracreer == NULL) {                    //si le fichier n'existe pas, erreur.
        printf ("Erreur d'ouverture du fichier décompressé\n\n");
        system("cat README");
        exit(1);
    }
    taille_tab(fichierdebase, fichieracreer);       //va donner a la variable globale le NbSymbole dans l'entete (et donc dans le texte compressé)
}


void taille_tab (FILE* fichierdebase, FILE* fichieracreer) {
    unsigned char car[NbSymboles/3];                //car lentete contient Nbsymboles dont 1/3 sont des car, 1/3 des nb_occ et 1/3 des codes 
    unsigned int nb_occ[NbSymboles/3];
    unsigned int code[NbSymboles/3];
    int i, poubelle;
    unsigned int carac, nb_occurences, code_bin;
    fscanf(fichierdebase, "%d", &NbSymboles);       //variable globale
    printf("%d\n", NbSymboles);
    fscanf(fichierdebase, "%d", &poubelle);         //on lit ici le \n que l'on ne veut pas stocker d'ou la variable poubelle
    //On lit lentete et on rempli 3 tableau en fonction de ce quon lit 
    for (i=0; i<(NbSymboles/3); i++) {
        fscanf(fichierdebase, "%d%d%d", &carac, &nb_occurences, &code_bin); //ne marche pas non plus avec un fread
        car[i] = carac;
        nb_occ[i] = nb_occurences;
        code[i] = code_bin;
        printf("%d %d %d\n", car[i], nb_occ[i], code[i]);
    }
    int lecture = 0, masque, temp = 0, tampon = 0, nb_bits_int, nb_bits_tampon = 0;
    unsigned char bit;
    nb_bits_int=sizeof(int)*8; //1 octet = 8 bits
    /*On a un tableau avec le caractere et son code associé, on parcourt le corps du fichier compressé. On lit un premier bit, si on ne trouve 
    aucun code binaire associé dans le tableau code[i], alors on lit ce premier bit avec le deuxieme... jusqu'à ce qu'on trouve une coresspondance
    dans le tableau code, et on ecrit le car associé à ce code dans le fichier decompressé*/
    masque = (masque<<(nb_bits_int-1)); //Le masque va contenir entre 0 et 7 bits car valeur dans code[i] font entre 1 et 7 bits
    lecture = fscanf(fichierdebase, "%c", &bit);
    while (lecture != EOF) {
        temp = bit;                                     //on sauvegarde le bit dans un octet
        temp = (temp<<(nb_bits_int-nb_bits_tampon));    //Decalage binaire vers la gauche par rapport au nb_bits dans le tampon
        tampon = tampon|temp;                           //on ajoute le bit de temp a droite du dernier bit de tampon
        nb_bits_tampon = nb_bits_tampon++;
        for (i=0; i<NbSymboles; i++) {
            if (code[i] == tampon) {                    //car code[i] est un octet de type int avec les bits a gauche
                fprintf(fichieracreer, "%c", car[i]);
                tampon = tampon<<nb_bits_tampon;        //on vide le tampon
                nb_bits_tampon = 0;
            }
        }
    }
}
