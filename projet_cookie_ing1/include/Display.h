#ifndef DISPLAY_H
#define DISPLAY_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include "InitGame.h"
    #include "Movements.h"
    #include "Constant.h"
    #include "Miscellanous.h"
      
    /// @brief Modifie le terminal pour l'adapter au jeu 
    void EditTerminal(); 

    /// @brief Menu lorsqu'on lance le programme, permet de lancer une nouvelle game, charger la précedente, ou voir l'historique.
    int MenuStartGame();

    /// @brief Menu qui permet de selectionner le replay à visonner parmi les n replays disponibles
    /// @return Return le numéro du replay selectionné
    int MenuGameHistory();

    /// @brief Menu pour choisir la partie à visionner
    int MenuHistory();void ShowKeyAvailable();
    
    ///@brief Menu pour que le user valid la suppression de l'historique
    int MenuConfirmClearHistory();

    /// @brief Menu pour choisir la difficulté 
    /// @return 1 pour une partie facile, 2 pour une partie normale, 3 pour une partie difficile
    int MenuDifficulty();

    /// @brief Menu pour choisir la taille de la carte
    /// @return 1 pour une petite map, 2 pour une map normale, 3 pour une grande map
    int MenuMapSize();

    /// @brief Menu lors de la fermeture de la partie
    /// @return 0 pour quitter sans sauvegarder, 1 pour sauvegarder et quitter, 2 pour retourner dans la partie
    int MenuSave();

    ///@brief attend que l'user appuis sur entrer pour continuer le process/affcihage 
    void MenuNext();
    
    ///@brief menu pour choisir la vitesse de replay de l'historique (et en fin de game)
    ///@return 1 pour un visionnage lent, 2 pour un visionnage normal, 3 pour un visionnage rapide
    int MenuSpeedHistory();

    ///@brief menu pour demander au joueur si il souhaite revoir sa partie apres qu'elle soit fini
    ///@return 1 if Yes 0 if No
    int MenuReplay();

    /// @brief Affiche les touches pour les coups dispos (et leur coup en distance)
    void ShowKeyAvailable();

    /// @brief Fonction d'affichage de la Map dans le terminal
    void DisplayMap(int** matrice_Map, int int_mapSize);

    /// @brief affiche la map avec le chemin suivis par une liste passer en parametre
    /// @param p_list liste contenant le chemin à afficher
    void DisplayPathInMap(int** matric_Map, int int_mapSize, List* p_list);

    /// @brief affiche la map avec le chemin suivis par une liste passer en parametre avec des fleches correspondant a la direction
    /// @param p_list liste contenant le chemin à afficher
    void DisplayPathInMapArrow(int** matric_Map, int int_mapSize, List* p_list);

    /// @brief Affiche les informations de victoire ou de défaite
    void VictoryMessage(int bool_victory, PlayerInfo *p_playerInfo);

    void DisplayList(List* p_list);

    /////////////////////////////////////////////////////////////////////////////
    //Fonctions de DEBUG pour dev, ne serons pas utiliser dans le process final//
    /////////////////////////////////////////////////////////////////////////////

    void DebugDisplayMap(int** matrice_Map, int int_mapSize);
    
    void DebugDisplayMatriceDistance(int int_mapSize, int*** matrice_Distance);
    
    /// @brief Affiche toutes les informations à propos du personnage
    void DebugInfoPlayer(PlayerInfo s_playerInfo);

    void PrintList(List* p_list);

    
    void PrintFirstList(List* p_list);

#endif
