#ifndef INITGAME_H
#define INITGAME_H
    #include <stdlib.h>
    #include <math.h>
    #include <stdio.h>
    #include <time.h>
    #include "Constant.h"
    #include "Miscellanous.h"
    #include "Display.h"
    #include "Movements.h"
    
    PlayerInfo SetupPlayer();

    ///@brief selection de difficulté
    float ChooseDifficulty();
    
    ///@brief selection de taille de map
    int ChooseMapSize();

    ///@brief Initialise l'énergie de base du joueur en fonction de la taille de la carte
    void InitEnergy(PlayerInfo* p_playerInfo, int int_mapSize); 

    ///@brief libere l'espace allouer a une matrice de taille int_mapSize
    void UnallocMatriceMap(int** matrice_Map, int int_mapSize);

    ///@brief alloue une matrice de int de taille int_mapSize
    ///@return retourn la matrice allouer
    int** AllocMatriceMap(int int_mapSize);

    ///@brief libere l'espace allouer d'une matrice de dimmension 3 de taille int_mapSize * int_mapSize * 8
    void UnallocMatriceDistance(int*** matrice_Distance, int int_mapSize);

    ///@brief alloue une matrice de dimansion 3 de int de taille int_mapSize * int_mapSize * 8
    int*** AllocMatriceDistance(int int_mapSize);

    ///@brief Initialise une matrice avec de int de taille int_mapSize avec une valeur par defaut
    int** InitMatriceMap(int** matrice_Map, int int_mapSize);

    ///@brief place un obstacle sur la map en fonction du difficulty rate, de la taille de la map et de la RNG, crée un "fillon" d'obstacles 
    int** PlaceObstacle(int** matrice_Map, int int_row, int int_col, int int_mapSize, float float_diffRate, int int_distBase, int constant_rep); 

    ///@brief Genere la Map (place le personnage, les bonus , les obstacle et le drapeau)
    int** GenerateMap(int** matrice_Map, int int_mapSize, float float_diffRate, PlayerInfo *p_playerInfo); //Work In Progress

    ///@brief Genere les distance entre chaque Case de la map
    int*** GenerateMatriceDistance(int int_mapSize, int*** matrice_Distance);

    /// @brief verifie chaque direction depuis une case pour 
    /// @return retourne 1 s'il s'agit du drapeau 0 si le chemin s'arrete
    int CheckEachDirection(int** matrice_Map, coordonnees coord_curr, int int_maxCoord, int int_Start, int int_Energy);

    ///@brief verifie si une map passer en parametre est faisable
    int CheckPath(int** matrice_Map, coordonnees coord_curr, int int_maxCoord, int int_Start, int int_Energy); 

    ///@brief //Alloue, init et genere la map
    int** InitMap(int int_mapSize, float float_diffRate, PlayerInfo* p_playerInfo); 

    ///@brief Alloue, et genere la matrice Distance
    int*** InitDistance(int int_mapSize);

#endif

