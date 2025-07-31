#define MIN 8
#define MAX 12
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "role.h"
#include "debutdepartie.h"
#include "nuit.h"
#include "jour.h"



void main (int argc, char* argv[]) {
    int nb_joueurs = -1;
    while (nb_joueurs<MIN || nb_joueurs>MAX) {
        printf("Quel est le nombre de joueurs (minimum 8, maximum 12) : ");
        scanf ("%d", &nb_joueurs);
    }
    system ("clear");
    creation_partie(nb_joueurs);
}