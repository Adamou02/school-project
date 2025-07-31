#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

int main (int argc, char* argv[]) {
    if (argc == 3) {
        int U0 = atoi(argv[1]);
        Calcul(U0, argv[2]);
    }
    else {
        system ("clear");
        system("cat HELP");
    } 
}

void Calcul(int U0, char* FICHIER_A_CREER) {
    FILE* fichier_a_creer = fopen(FICHIER_A_CREER, "w");
    if (fichier_a_creer == NULL) {
        printf ("Impossible de creer le fichier %s", FICHIER_A_CREER);
    }
    Ecrire_result(U0, fichier_a_creer);
    fclose(fichier_a_creer);
}

void Ecrire_result(int U0, FILE* fichier_a_creer) {
    int nb_occ = 0, alt_max = U0, U0_fixe = U0, duree_alt = 0, duree_alt_tmp = 0;
    fprintf(fichier_a_creer, "n Un\n");
    fprintf(fichier_a_creer, "%d %d\n", nb_occ, U0);
    while (U0 != 1) {
        if (U0%2 == 0) {
            U0 = U0/2;
            nb_occ++;
            fprintf(fichier_a_creer, "%d %d\n", nb_occ, U0);
        }
        else {
            U0 = (U0*3)+1;
            nb_occ++;
            fprintf(fichier_a_creer, "%d %d\n", nb_occ, U0);
            if (alt_max < U0) {
                alt_max = U0;
            }
        }
        if (U0 >= U0_fixe) {
            duree_alt_tmp++;
        }
        else {
            if (duree_alt_tmp >= duree_alt) {
                duree_alt = duree_alt_tmp;
            }
            duree_alt_tmp = 0;
        }
    }
    fprintf(fichier_a_creer, "altitudemax=%d\ndureedevol=%d\ndureevolaltitude=%d", alt_max, nb_occ, duree_alt);
}