#ifndef DIJKSTRA_H
#define DIJKSTRA_H
    #define square(a)  (a)*(a)
    #include <stdlib.h>
    #include <math.h>
    #include <stdio.h>
    #include "Constant.h"
    #include "Miscellanous.h"
    #include "Display.h"
    
    typedef struct DataD DataD;
    struct DataD{ // Structure contenant séquence du parcours, coordonnées actuelles, distance du point de départ
        int x;
        int y;
        int distance;
        int chemin[(3*(TAILLE_BIG_MAP * TAILLE_BIG_MAP))];
    };

    typedef struct Node_d{ // enregistre les  distance dans une liste
        DataD DataD;
        struct Node_d *next;
    } Node_d;

    typedef struct List_d{
        Node_d* firstnode;
    } List_d;
    

    /// @brief Initialize a List_d type list with the first node containing the given coordinates, a distance of zero, and the path array initialized to the start.
    List_d* InitList_d(int int_x, int int_y);

    /// @brief Retrieve the coordinates of the last move of the node passed as a parameter
    /// @return the coordinates of the last move in the form of the "coordonnees" structure.
    coordonnees FindLastStep (Node_d* Node);

    /// @brief Determine, using the character's position on the map and the chosen move, the correct value based on what is on the next square.Taking into account the mode (energy or distance traversal)
    /// @return 0 if there is an obstacle or if we are leaving the map, and otherwise the distance between the current square and the tested square.
    int ReturnDiff(int** matrice_map, int*** matrice_distance, int int_mapSize, Node_d* Node,int int_diffX, int int_diffY,int int_position,int int_mode);
    
    /// @brief Takes all data of the character and the map, tests all possible combinations, and returns the best one according to the Dijkstra algorithm
    /// @return the best node-d in the list_d "p_list", and also modifies the value of the "*int_position" pointer passed as a parameter to have the best position from the right node
    Node_d* FindLowerWay(List_d* p_list, Node_d* Node, Node_d* GoodNode, int** matrice_map, int*** matrice_distance, int int_mapSize, int int_goodDistance, int *int_position, int *int_distance, coordonnees coordEnd, int int_mode);

    /// @brief Takes the final node of the algorithm as a parameter and transforms it into a list "List" with the final value (energy or distance) and the entire path taken stored in the nodes of the list.
    /// @return the final list
    List* EndDijkstra(Node_d * Arrive);
    
    /// @brief Create a node of the form "node_d" and initialize it with all the data passed as parameters (coordinates, distance, previous node and next node
    Node_d* CreateDNode( int int_x, int int_y, int distance, Node_d* NodeD, Node_d* Node_Suivante);

    int AddNode_d(List_d* p_list, Node_d* firstNode, int int_x, int int_y, int int_distance, Node_d* NodeD);

    /// @brief Remove the nodes in the list (list_d) whose distance values are all equal to 0.
    void RemoveNode_d(List_d* p_list);
    
    /// @brief Free la list (list_d) et free toutes ses nodes (node_d)
    void FreeList_d(List_d* p_list);

    /// @brief through the AlgoDijkstra function, and is called each time to apply the recursive model of the Dijkstra algorithm.
    Node_d* recurseDijkstra(List_d* p_list, Node_d* firstnode, int** matrice_Map, int*** matrice_Distance, int int_mapSize , coordonnees coordEnd,int int_mode);

    /// @brief "Takes all game data as a parameter, And through all the functions created in initgame.c and miscellaneous.c, applies the principle of the Dijkstra algorithm to find the best path to the destination.
    List* AlgoDijkstra(int** matrice_Map,int*** matrice_Distance, PlayerInfo* p_playerInfo, int int_mapSize, int int_mode);
  
#endif
