#ifndef MISCELLANOUS_H
#define MISCELLANOUS_H
    #define square(a)  (a)*(a)
    #include <stdlib.h>
    #include <math.h>
    #include <stdio.h>
    #include <time.h>
    #include <string.h>
    #include <time.h>  
    #include "Constant.h" 

    typedef struct coordonnees{ // Structure contenant des coordonnées 
        int x;
        int y;
    } coordonnees;

    typedef struct Node{ // enregistre les coordonnées dans une list 
        coordonnees coordonnees;
        int is_bonus;
        struct Node *next;
    } Node;

    typedef struct List{
        Node* firstnode;
    } List;

    typedef struct PlayerInfo{ // Structure contennant les informations du joueur
        coordonnees coordonnees;
        int energy;
        int distance;
        int gain_energy;
        int lost_energy;
        int backward;
    } PlayerInfo;

    typedef struct GameInformation{ // Structure contenant toute les infos necessaire pour pouvoir debuter une partie et pour liberer la memoire allouer a tout moment 
        int int_mapSize;
        float float_diffRate;
        int **matrice_Map;
        int ***matrice_Distance;
        List* p_listpath;
        List* p_listBestWay;
        List* p_listBestWayEnergy;
        PlayerInfo s_playerInfo;
        int bool_victory;
    } GameInformation;

    int RNG(int min, int max);

    int CoordCompare(int** matrice_map, int int_x, int int_y, char constant_rep);

    int CoordCompare2(int** matrice_map, coordonnees coord, char constant_rep);

    int IsBetween(int int_Comp, int int_min, int int_max);

    void printf_center(const char* str);

    void InitRNG();

    int DefineStartPlayer(PlayerInfo* p_playerInfo, int int_mapSize);

    coordonnees ModifCoord(coordonnees coord, int int_x, int int_y);
    
    coordonnees DefineEndGame(int int_mapSize, int** matrice_map);
    
    Node* CreateNode(coordonnees coord, int bonus);

    List* InitList(coordonnees coord, int is_bonus);

    /// @brief ajoute une node en début de liste, avec les dernière coordonnées du joueur et si la case était un bonus ou non
    void AddNode(List* p_list, coordonnees coord, int bonus);
    
    /// @brief Supprime la dernière node ajoutée à la liste
    void RemoveNode(List* p_list);
    
    /// @brief Renvoie la taille de la liste
    long LengthList(List *p_list);
    
    /// @brief Permet de récupérer la dernière node ajoutée à la liste, avec les coordonnées et l'information de si c'est un bonus
    void GetfirstNode(List* p_list, int* p_last_x, int* p_last_y, int* is_bonus);
    
    /// @brief Free la list et free toutes ses nodes
    void FreeList(List* p_list);


    /// @return 1 if coord belongs to the list, 0 otherwise
    int IsInList(List* p_list, coordonnees coord);

    /// @brief copy a List*
    /// @param matrice_Map original List
    /// @param matrice_MapCopy copy of the List, needs to be alloc before
    void CopyList(List* p_list, List* p_listCopy);

    /// @brief clear the terminal where the 
    void ClearTerm();

    /// @brief copy a matrice_Map
    /// @param matrice_Map original matrice (size: int_mapSize x int_mapSize)
    /// @param matrice_MapCopy copy of the matrice, needs to be alloc before
    void CopyMap(int** matrice_Map, int** matrice_MapCopy, int int_mapSize);

    /// @brief copy a matrice_distance
    /// @param matrice_Distance original matrice (size: int_mapSize x int_mapSize x 8)
    /// @param matrice_DistanceCopy copy of the matrice, needs to be alloc before
    void CopyMatriceDist(int*** matrice_Distance, int*** matrice_DistanceCopy, int int_mapSize);

    /// @brief invert a list
    /// @return Inverted List ("isbonus" is not keep from the original list)
    List* InvertList(List* p_list);

#endif
