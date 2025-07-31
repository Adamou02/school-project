#ifndef PROTOTYPES_H // Si la constante n'a pas été définie le fichier n'a jamais été inclus
#define PROTOTYPES_H // On définit la constante pour que la prochaine fois le fichier ne soit plus inclus

typedef struct Case {            //chaque élément est égal à un charactere ascii, et ils ont chacun un nombre d'occurences.
    unsigned char car;
    int nb_occurences;
}Element;


typedef struct Noeud {
	Element valeur;
	struct Noeud* fg;
	struct Noeud* fd;
	int code;
	int nb_bits;
}*PArbre;

typedef struct lst {
	PArbre arbre;
	struct lst* suivant;
}*Liste;


PArbre ABR_ENTETE[256]; //notre arbre qui va nous permettre de construires notre entete en stockant toutes les informations du fichier decompressé

void compresser(char* FichierDeBase, char* FichierACreer);
unsigned int Taille_tab(Element car[MAX_SYMBOLES]);
void InitialiserTab(Element car[MAX_SYMBOLES]);
void Compteur(Element car[MAX_SYMBOLES], FILE* fichierdebase);
PArbre Cons(PArbre a1, PArbre a2, int nb_occ, int car);
void TrieTabCroissant(Element car[MAX_SYMBOLES]);
PArbre CreerNoeud (int caractere, int nb_occurences);
void Creer_Arbre_Huffman(PArbre a[MAX_SYMBOLES], Element car[MAX_SYMBOLES]);
void Parcours_arbre(PArbre a, int code, int nb_bits);
void parcoursPrefixe(PArbre a);
void Ecrire_Entete(FILE* fichieracreer);
void Ecrire_Codage(FILE* fichierdebase, FILE* fichieracreer);

void decompresser(char* FichierDeBase, char* FichierACreer);
void taille_tab (FILE* fichierdebase, FILE* fichieracreer);
void Ajouter_entete(FILE* fichierdebase);

#endif