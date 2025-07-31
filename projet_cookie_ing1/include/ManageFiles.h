#ifndef MANAGEFILE_H
#define MANAGEFILE_H 
    #include <stdio.h>
    #include <stdlib.h>
    #include "Constant.h"
    #include "InitGame.h"

    /// @brief Permet de savoir si un fichier existe ou non
    /// @param str_NameFile Nom du fichier et chemin pour y parvenir
    int ExistFile(char str_NameFile[]);

    /// @brief Creer un nouveau fichier vide
    void createFile(char str_NameFile[]);
   
    /// @brief Supprime un fichier
    int SupprFile(char str_NameFile[]);

    /// @brief Permet de savoir si un fichier est vide ou non
    /// @return Renvoie 1 si fichier vide ou n'existe pas, renvoie 0 si le fichier n'est pas vide
    int IsEmptyFile(char str_NameFile[]);

    /// @brief Supprime la dernière ligne d'un fichier
    void DeleteLastLine(char str_NameFile[]);

    /// @brief Compte le nombre de tours sauvegardés dans Current_Game.css
    int SavedTurnsCount(int int_mapSize, char str_NameFile[]);

    /// @brief Récupère les informations de la structure PlayerInfo dans la sauvegarde
    void GetPlayerInfo(int int_mapSize, PlayerInfo * s_playerInfo_player, int num_turn, char str_NameFile[]);

    /// @brief Récupère les informations de la carte dans la sauvegarde
    char* GetMapString(char* MapString, int int_mapSize, int num_turn, char str_NameFile[]);

    /// @brief Récupère les informations de distances dans la sauvegarde
    char* GetDistanceString(char* DistanceString, int int_mapSize, int num_turn, char str_NameFile[]);

    /// @brief Récupère les informations de la liste dans la sauvegarde
    char* GetListString(char* ListString, int int_mapSize, int num_turn);

    /// @brief Alloue la mémoire nécessaire pour enregistrer la carte
    char* AllocMapString(int int_mapSize);

    /// @brief Alloue la mémoire nécessaire pour enregistrer les distances
    char* AllocDistanceString(int int_mapSize);

    /// @brief Alloue la mémoire nécessaire pour enregistrer la liste
    char* AllocListString(int int_mapSize);

    /// @brief Ecrit la carte sous forme de chaine de caractères
    char* MatriceMapToString(int** matrice_Map, int int_mapSize, char* MapString);

    /// @brief Ecrit les distances sous forme de chaine de caractères
    char* MatriceDistanceToString(int*** matrice_Distance, int int_mapSize, char* DistanceString);

    /// @brief Ecrit la liste sous forme de chaine de caractères
    char* ListToString(List* p_list, char* ListString);
    
    /// @brief Restaure la carte depuis sa chaine de caractères
    int** StringToMatriceMap(char* MapString, int int_mapSize, int** matrice_Map);

    /// @brief Restaure les distances depuis sa chaine de caractères
    int*** StringToMatriceDistance(char* DistanceString, int int_mapSize, int*** matrice_Distance);

    /// @brief Compte le nombre d'éléments dans la liste
    int ListElementsCount(char* ListString);

    /// @brief Restaure la liste depuis sa chaine de caractères
    List* StringToList(List* p_list, char* ListString);

    /// @brief Transforme la carte en chaine
    char* SaveMap(int** matrice_Map, int int_mapSize);

    /// @brief Restaure la carte depuis le fichier de sauvegarde
    int** RestoreMap(int** matrice_Map, int int_mapSize, int num_turn, char str_NameFile[]);

    /// @brief Transforme les distances en chaine
    char* SaveDistance(int*** matrice_Distance, int int_mapSize);

    /// @brief Restaure les distances depuis le fichier de sauvegarde
    int*** RestoreDistance(int*** matrice_Distance, int int_mapSize, int num_turn, char str_NameFile[]);

    /// @brief Transforme la liste en chaine
    char* SaveList(List* p_list, int int_mapSize);

    /// @brief Restaure la liste depuis le fichier de sauvegarde
    List* RestoreList(int int_mapSize, int num_turn);

    /// @brief Sauvegarde toutes les informations du tour actuel
    void StockCurrentTurn(int** matrice_Map, int*** matrice_Distance, List* p_list, int int_mapSize, PlayerInfo * s_playerInfo_player);

    /// @brief Restaure toutes les informations d'un tour donné
    void RestoreTurn(int num_turn, int*** matrice_Map, int**** matrice_Distance, PlayerInfo* p_playerInfo, int int_mapSize, char str_NameFile[]);

    /// @brief Restaure la taille de la carte depuis un fichier donné
    int RestoreMapSize(char str_NameFile[]);

    /// @brief Sauvegarde la partie dans le fichier Save.css
    void Save(int int_mapSize);

    /// @brief Restaure la partie depuis le fichier Save.css
    void SaveToCurrentGame();

    /// @brief Sauvegarde la partie terminée dans l'historique
    void History(int int_mapSize);

    /// @brief Lis la partie numéro num_game depuis l'historique
    void ReadHistory(int num_game, int*** matrice_Map, int speed);

    /// @brief Compte le nombre de parties dans l'historique
    int CountHistory();

    /// @brief Efface l'historique
    void ClearHistory();
#endif
