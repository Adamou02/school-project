#include "Miscellanous.h"



int RNG(int min, int max)
{
    return ( ( rand() % (max - min + 1) ) + min );
}

int CoordCompare(int** matrice_map, int int_x, int int_y, char constant_rep)
{
    //puts("on compare\n");
    return (matrice_map[int_x][int_y] == constant_rep);
}

int CoordCompare2(int** matrice_map, coordonnees coord, char constant_rep)
{
    return(CoordCompare(matrice_map, coord.x, coord.y, constant_rep));
}

int IsBetween(int int_Comp, int int_min, int int_max){
    return (int_Comp >= int_min && int_Comp <= int_max);
}

void printf_center(const char* str)
{
    unsigned int n;
    for (n = 0; n < (204-strlen(str)) / 2; n++)
    {
        putchar(' ');
    }
    printf("%s", str);
}

void InitRNG()
{
    srand(time(NULL)); //init RNG
}

coordonnees ModifCoord(coordonnees coord, int int_x, int int_y)
{
    coord.x= int_x;
    coord.y= int_y;
    return coord;  
}

int DefineStartPlayer(PlayerInfo* p_playerInfo, int int_mapSize) //fonction retournant un int entre 1  et 4 copris en fonction du placement de depart du personnage
{
    int int_maxCoord = int_mapSize - 1;
    if(p_playerInfo->coordonnees.x == 0){
        if(p_playerInfo->coordonnees.y == 0){
            return (1);
        } else if(p_playerInfo->coordonnees.y == int_maxCoord){
            return(3);
        } else {
            return (-1);
        }

    } else if(p_playerInfo->coordonnees.x == int_maxCoord){
        if(p_playerInfo->coordonnees.y == 0){
            return (2);
        } else if(p_playerInfo->coordonnees.y == int_maxCoord){
            return(4);
        } else {
            return (-1);
        }

    } else {
        return (-1);
    }    
}


coordonnees DefineEndGame(int int_mapSize, int** matrice_map)
{
    coordonnees coord;
    for(int i = 0; i<int_mapSize; i++)
    {
        for(int j = 0;j<int_mapSize; j++)
        {
            if (CoordCompare(matrice_map, i,j,REP_END))
            {
               
                coord.x = j;
                coord.y = i;
                return (coord);
            }
            
        }
    }
}


////////////////////////////////////////
// FONCTIONS POUR LES LISTES CHAINEES //
////////////////////////////////////////

Node* CreateNode(coordonnees coord, int is_bonus) // Créer une nouvelle node à ajouter dans la liste
{
    Node *node = malloc(sizeof(*node));
    if(!node){
        free(node);
        exit(EXIT_FAILURE);
    }
    node->coordonnees = coord;
    node->is_bonus = is_bonus;
    node->next = NULL;
    return node;
}

List* InitList(coordonnees coord, int is_bonus) //initialise une liste chaine de coord avec des coord en param
{
    List *list_new = malloc(sizeof(*list_new));
    Node *node_new = malloc(sizeof(*node_new));
    if(list_new == NULL || node_new == NULL){
        free(list_new);
        free(node_new);
        puts("Error in InitList");
        exit(EXIT_FAILURE);
    }
    node_new->next = NULL;
    node_new->coordonnees.x=coord.x;
    node_new->coordonnees.y=coord.y;
    node_new->is_bonus=is_bonus;
    list_new->firstnode = node_new;
    return(list_new);
}



void AddNode(List* p_list, coordonnees coord, int is_bonus) // Ajoute une node en début de liste 
{       
    /*creation de la nouvel node*/
    if(p_list == NULL){
        p_list = InitList(coord, 0);
    } else {
        Node *node_new = CreateNode(coord, is_bonus);
        if(p_list == NULL){
            puts("Error in AddNode");
            exit(EXIT_FAILURE);
        }
        node_new->next = p_list->firstnode;
        p_list->firstnode = node_new;
    }
}




void RemoveNode(List* p_list) // retire la dernière node de la liste
{
    if(p_list == NULL){
        puts("Error in RemoveNode");
        exit(EXIT_FAILURE);
    }
    if(p_list->firstnode != NULL){
        Node* node_toRemove =  p_list->firstnode;
        p_list->firstnode = p_list->firstnode->next;
        free(node_toRemove);
    }
}


long LengthList(List *p_list) // Permet d'obtenir la taille de la liste
{
    long long_taille = 0;
    Node* node_current = p_list->firstnode;
    while(node_current != NULL)
    {
        long_taille = long_taille + 1;
        node_current = node_current->next;
    }
    return long_taille;
}

void GetfirstNode(List* p_list, int* p_last_x, int* p_last_y, int* is_bonus) // renvoit les coordonnées de la dernière node ajoutée
{   
    if(p_list == NULL){
        exit(EXIT_FAILURE);
    }
    Node* node_current = p_list->firstnode;
    printf("%d %d\n", node_current->coordonnees.x, node_current->coordonnees.y);
    *p_last_x = node_current->coordonnees.x;
    *p_last_y = node_current->coordonnees.y;
    *is_bonus = node_current->is_bonus;
}  

void FreeList(List* p_list)// Libère la mémoire alloué à la liste
{
    if(p_list == NULL){
        return;
    }
    while(p_list->firstnode != NULL){
        RemoveNode(p_list);
    }
    free(p_list);
}

int IsInList(List* p_list, coordonnees coord) //verifie si des coordonnees appartienne à une liste passer en parametre
{
    if(p_list == NULL ){
        return 0;
    } else if(p_list->firstnode == NULL){
        return 0;
    } else {
         Node* node_current = p_list->firstnode;
        int bool_isIn = 0;
        while(node_current != NULL && !bool_isIn ){
            bool_isIn = (node_current->coordonnees.x == coord.x) && (node_current->coordonnees.y == coord.y);
            node_current = node_current->next;
        }   
        return (bool_isIn);
    }
}

void CopyList(List* p_list, List* p_listCopy){
    if(p_list == NULL || p_list->firstnode == NULL){
        return;
    } else {
        Node * node_current = p_list->firstnode;
        while(node_current != NULL){
            AddNode(p_listCopy,node_current->coordonnees,node_current->is_bonus);
            node_current = node_current->next;
        }
        return;
    }
}


void ClearTerm()
{
    //printf("\033[H\033[2J");
    system("clear");
}

void CopyMap(int** matrice_Map, int** matrice_MapCopy, int int_mapSize)
{
    for(int i=0; i<int_mapSize; i++){
        for(int j=0; j<int_mapSize; j++){
            matrice_MapCopy[i][j] = matrice_Map[i][j];
        }
    }
}

void CopyMatriceDist(int*** matrice_Distance, int*** matrice_DistanceCopy, int int_mapSize)
{
    for(int i=0; i<int_mapSize; i++){
        for(int j=0; j<int_mapSize; j++){
            for(int k=0; k<8; k++){
                matrice_DistanceCopy[i][j][k] = matrice_Distance[i][j][k];
            }
            
        }
    }
}


List* InvertList(List* p_list)
{   
    int int_ListSize= LengthList(p_list);
    coordonnees TabList[int_ListSize];
    Node* node_current = p_list->firstnode;
    for( int j=int_ListSize-1; j>=0; j--){
        TabList[j]= node_current->coordonnees;
        node_current = node_current->next;
        RemoveNode(p_list);
    } 
    List* p_listinverted = InitList(TabList[0], 0);
    for(int i=1; i<int_ListSize; i++){
       AddNode(p_listinverted, TabList[i], 0);
    }
    CopyList(p_listinverted, p_list);
    FreeList(p_listinverted);
    return (p_list);
}

