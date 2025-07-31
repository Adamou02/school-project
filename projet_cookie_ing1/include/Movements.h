#ifndef MOVEMENTS_H
#define MOVEMENTS_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <termios.h>
    #include "Constant.h"
    #include "Miscellanous.h"
    #include "Game.h"

    static struct termios old, current; //Structure qui permet de garder les deux états paramètres du terminal
    
    //Verifie la touche pressée
    int KeyAvailable(int key);

    //Change les valeur des variables dans UpdatePosition pour changer la position du personnage dans la matrice map
    void ChangePosition(int key, int* x, int* y, PlayerInfo *p_playerInfo);

    //Fait un retour à la ligne quand la fonction est appelée (permet de bien afficher les différentes touches disponibles sur plusieurs lignes)
    void SkipLine(int line_count, int* p_line_count);

    //Permet de lire la touche pressé. Le programme est en pause tant que utilisateur appuie touche
    int ListenKeyboard();

    /// @brief Met à jour les informations de la map en fonction du déplacement
    /// @param int_wanted_x position x où le joueur souhaite aller
    /// @param int_wanted_y position y où le joueur souhaite aller
    int** UpdatePosition(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo); // 

    /// @brief Renvoie la direction choisie par le joueur
    int GetDirection(int x, int y, int going_x, int going_y, int direction);    

    /// @brief Met à jour les infos du joueur en fonction du déplacement
    void UpdatePlayerInfo(int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo,  int*** matrice_Distance);

    /// @brief Fait les actions nécessaire lorsque le joueur se déplace sur un bonus
    void PlayerOnBonus(PlayerInfo *p_playerInfo);

    /// @brief Fait les actions nécessaire lorsque le joueur se déplace sur un obstacle
    void PlayerOnObstacle(PlayerInfo *p_playerInfo);
 
    /// @brief Met à jour la liste contenant tous les déplacements du joueur ainsi que les moments où les cases étaient des obstacles
    void UpdatePathList(PlayerInfo *p_playerInfo, List* p_list, int is_bonus);

    /// @brief Remet le bonus en place si le joueur fait un retour arrière
    int** WasABonus(int** matrice_map, int last_x, int last_y, PlayerInfo *p_playerInfo, char CST);
  
    /// @brief Fait les actions nécessaire lorsque le joueur veut faire un retour en arrière
    void StepBack(List* p_list, int** matrice_map, PlayerInfo *p_playerInfo, int*** matrice_Distance);

    /// @brief Permet de savoir si le joueur est déjà passé sur la case ou non
    int AlreadyBeen(int int_wanted_x, int int_wanted_y, List* p_list);

    /// @brief Appelle les fonctions qui permettent de faire le déplacement en fonction de ma direction choisie et de la map
    int** AfterMovement(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo, int int_mapSize, int *bool_victory, List* p_list,  int*** matrice_Distance, int *bool_isanObstacle);// Permet de déplacer ou non le joueur en fonction du déplacement demandé et de la carte

#endif
