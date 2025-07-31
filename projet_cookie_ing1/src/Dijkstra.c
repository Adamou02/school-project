#include "Dijkstra.h"

List_d* InitList_d(int int_x, int int_y) //initialise une liste chaine de coord avec des coord en param
{
    List_d *list_new = malloc(sizeof(*list_new));
    Node_d *node_new = malloc(sizeof(*node_new));
    if(list_new == NULL || node_new == NULL){
        free(list_new);
        free(node_new);
        puts("Error in InitList_d");
        exit(EXIT_FAILURE);
    }
    node_new->next = NULL;
    node_new->DataD.x=int_x;
    node_new->DataD.y=int_y;
    node_new->DataD.distance=0;
    for(int i = 0 ; i < (3*(TAILLE_BIG_MAP * TAILLE_BIG_MAP)); i ++){ node_new->DataD.chemin[i] = 100;}
    node_new->DataD.chemin[0] = int_x;
    node_new->DataD.chemin[1] = int_y;
    list_new->firstnode = node_new;
    return(list_new);
}


coordonnees FindLastStep (Node_d* Node)
{
    int int_cpt = 0;
    while (Node->DataD.chemin[int_cpt] != 100)
    {
        int_cpt++;
        if(int_cpt == (3*(TAILLE_BIG_MAP * TAILLE_BIG_MAP))) break;
    }

    coordonnees coord; 
    
    if(int_cpt == 2 || int_cpt == 3)
    {
        coord.x = 1000;
        coord.y = 1000;
        return (coord);
    }
    coord.x = Node->DataD.chemin[int_cpt - 4];
    coord.y = Node->DataD.chemin[int_cpt - 3 ];
    return (coord);
}



int ReturnDiff(int** matrice_map, int*** matrice_distance, int int_mapSize, Node_d* Node,int int_diffX, int int_diffY,int int_position,int int_mode)
{

    if ( IsBetween((Node->DataD.y)+(int_diffY), 0, int_mapSize-1) && IsBetween((Node->DataD.x)+(int_diffX), 0, int_mapSize-1) && !(matrice_distance[Node->DataD.x][Node->DataD.y][int_position] == 0))
        {
            if( !CoordCompare(matrice_map, (Node->DataD.x)+(int_diffX), (Node->DataD.y)+(int_diffY), REP_OBSTACLE1) &&  !CoordCompare(matrice_map, (Node->DataD.x)+(int_diffX), (Node->DataD.y)+(int_diffY), REP_OBSTACLE2)){
                if (((FindLastStep(Node).x) != ((Node->DataD.x)+(int_diffX))) || ((FindLastStep(Node).y) != ((Node->DataD.y)+(int_diffY)) ))
                {
                    if(int_mode == 1) return (Node->DataD.distance + matrice_distance[(Node->DataD.x)][(Node->DataD.y)][int_position]);
                    if(int_mode == 2){
                        if( CoordCompare(matrice_map, (Node->DataD.x)+(int_diffX), (Node->DataD.y)+(int_diffY), REP_BONUS1) || CoordCompare(matrice_map, (Node->DataD.x)+(int_diffX), (Node->DataD.y)+(int_diffY), REP_BONUS2))
                        {
                            matrice_distance[Node->DataD.x][Node->DataD.y][int_position] = 1-GAIN_ENERGY;
                            return((Node->DataD.distance)+(1-GAIN_ENERGY));
                        }
                    matrice_distance[Node->DataD.x][Node->DataD.y][int_position] = 1;
                    return((Node->DataD.distance) + 1);
                    } 
                }else{
                matrice_distance[Node->DataD.x][Node->DataD.y][int_position] = 0;
            }
            }else{
                matrice_distance[Node->DataD.x][Node->DataD.y][int_position] = 0;
            }
    }
}


Node_d* FindLowerWay(List_d* p_list, Node_d* Node, Node_d* GoodNode, int** matrice_map, int*** matrice_distance, int int_mapSize, int int_goodDistance, int *int_position, int *int_distance, coordonnees coordEnd, int int_mode)
{
    if(Node == NULL && int_goodDistance != 1000){
        return CreateDNode(-1,-1,-1,NULL,NULL);
    }
    if (Node->DataD.x == coordEnd.y && Node->DataD.y == coordEnd.x)
    { 
        return (Node);
    }

    int tab[8];
        
    for(int u = 0 ; u <8; u++){ tab[u] = INF;}

    tab[0] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,-1,-1,0,int_mode);
    tab[1] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,-1,0,1,int_mode);
    tab[2] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,-1,1,2,int_mode);
    tab[3] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,0,1,3,int_mode);
    tab[4] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,1,1,4,int_mode);
    tab[5] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,1,0,5,int_mode);
    tab[6] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,1,-1,6,int_mode);
    tab[7] = ReturnDiff(matrice_map,matrice_distance,int_mapSize,Node,0,-1,7,int_mode);

    int int_tmp = int_goodDistance;
    for(int test = 0 ; test < 8; test++)
    {
        if ((tab[test] < int_goodDistance) && tab[test] != 0)
        {
            int_goodDistance = tab[test];
            *int_position = test;
        }
    }
    
    if(int_goodDistance == 1000){
        return(FindLowerWay(p_list, Node->next, GoodNode,matrice_map, matrice_distance, int_mapSize , int_goodDistance,int_position,int_distance,coordEnd,int_mode));
    }
    if (int_goodDistance != int_tmp)
    {
        *int_distance = matrice_distance[Node->DataD.x][Node->DataD.y][*int_position];   
    
        if (Node->next == NULL)
        {
            matrice_distance[Node->DataD.x][Node->DataD.y][*int_position] = 0;
            return (Node);
        }else{ 
            
            return (FindLowerWay(p_list, Node->next, Node, matrice_map, matrice_distance, int_mapSize, int_goodDistance,int_position,int_distance,coordEnd,int_mode));
        }
    }else{
        if (Node->next== NULL)
        {
            matrice_distance[GoodNode->DataD.x][GoodNode->DataD.y][*int_position] = 0;
            return (GoodNode);
        }else{ 
            
            return (FindLowerWay(p_list , Node->next, GoodNode,matrice_map, matrice_distance, int_mapSize , int_goodDistance,int_position,int_distance,coordEnd,int_mode));
        }
    }

}

int AddEnd(Node* NodeHere, Node* node){
    while(NodeHere->next != NULL){
        return(AddEnd(NodeHere->next,node));
    }
    NodeHere->next = node;
    return 0;
}



List* EndDijkstra(Node_d * Arrive)
{
    int i = 0;
    int rien;
    coordonnees FirstNode;
    FirstNode.x = Arrive->DataD.chemin[i];
    FirstNode.y = Arrive->DataD.chemin[i+1];
    //printf("%d - %d\n", FirstNode.x,FirstNode.y);
    List* BetterWay = InitList(FirstNode, 0);
    i = i + 2;
    while (Arrive->DataD.chemin[i] != 100)
    {
        coordonnees tmp;
        tmp.x = Arrive->DataD.chemin[i];
        tmp.y = Arrive->DataD.chemin[i+1];
        Node* tmp_Node = CreateNode(tmp,0);
        rien = AddEnd(BetterWay->firstnode,tmp_Node);
        i = i + 2 ;
    }

    return (BetterWay);
}



Node_d* CreateDNode(int int_x, int int_y, int distance, Node_d* NodeD, Node_d* Node_Suivante) // Créer une nouvelle node à ajouter dans la liste
{
    Node_d *node = malloc(sizeof(*node));
    if(!node){
        free(node);
        exit(EXIT_FAILURE);
    }
    node->DataD.x = int_x;
    node->DataD.y = int_y;
    node->DataD.distance = distance + NodeD->DataD.distance;

    int int_cpt = 0;

    for(int i = 0 ; i < (3*(TAILLE_BIG_MAP * TAILLE_BIG_MAP)); i++)
    {
        node->DataD.chemin[i] = 100; 
    }
    while((NodeD->DataD.chemin[int_cpt]) != 100) {
        node->DataD.chemin[int_cpt] = NodeD->DataD.chemin[int_cpt];
        int_cpt++;
    }
    node->DataD.chemin[int_cpt] = int_x;
    node->DataD.chemin[int_cpt+1] = int_y;
    node->next = Node_Suivante;

    return (node);
}


int AddNode_d(List_d* p_list, Node_d* firstNode, int int_x, int int_y, int int_distance, Node_d* NodeD)
{
    if (firstNode->next == NULL)
    {
        firstNode->next = CreateDNode(int_x, int_y, int_distance, NodeD, NULL);
        return (0);
    }else{
        if (firstNode->next->DataD.x == int_x && firstNode->next->DataD.y == int_y)
        {
            if (firstNode->next->DataD.distance > int_distance + NodeD->DataD.distance)
            {
                firstNode->next->DataD.distance = int_distance + NodeD->DataD.distance;
                firstNode->next->DataD.chemin[100] = NodeD->DataD.chemin[100];
                return (0);
            }else{
                return (0);                
            }
        }else{
            return(AddNode_d(p_list, firstNode->next, int_x, int_y, int_distance, NodeD));
        }
    }
}


void RemoveNode_d(List_d* p_list) // retire la dernière node de la liste
{
    if(p_list == NULL){
        puts("Error in RemoveNode");
        exit(EXIT_FAILURE);
    }
    if(p_list->firstnode != NULL){
        Node_d* node_toRemove =  p_list->firstnode;
        p_list->firstnode = p_list->firstnode->next;
        free(node_toRemove);
    }
}



void FreeList_d(List_d* p_list)// Libère la mémoire alloué à la liste
{
    if(p_list == NULL){
        return;
    }
    while(p_list->firstnode != NULL){
        RemoveNode_d(p_list);
    }
    free(p_list);
}


Node_d* recurseDijkstra(List_d* p_list, Node_d* firstnode, int** matrice_Map, int*** matrice_Distance, int int_mapSize, coordonnees coordEnd, int int_mode){

    int int_position = 10;
    int int_distance;
    int int_x;
    int int_y;

    Node_d* NodeHere = FindLowerWay(p_list,firstnode,firstnode,matrice_Map, matrice_Distance,int_mapSize,1000,&int_position,&int_distance,coordEnd,int_mode);

    if(NodeHere->DataD.x == -1 && NodeHere->DataD.y == -1 ){
        return (NodeHere);        
    }
    if(NodeHere->DataD.x == coordEnd.y && NodeHere->DataD.y == coordEnd.x ){
        return(NodeHere);
    }

    switch (int_position){
        case 0 :
            int_x = (NodeHere->DataD.x) - 1;
            int_y = (NodeHere->DataD.y) - 1;
        break;

        case 1:
            int_x = (NodeHere->DataD.x) - 1;
            int_y = (NodeHere->DataD.y);
        break;

        case 2:
            int_x = (NodeHere->DataD.x) - 1;
            int_y = (NodeHere->DataD.y) + 1 ;
        break;

        case 3:
            int_x = (NodeHere->DataD.x);
            int_y = (NodeHere->DataD.y) + 1 ;
        break;

        case 4:
            int_x = (NodeHere->DataD.x) + 1;
            int_y = (NodeHere->DataD.y) + 1 ;
        break;

        case 5:
            int_x = (NodeHere->DataD.x) +1;
            int_y = (NodeHere->DataD.y);
        break;

        case 6:
            int_x = (NodeHere->DataD.x) + 1;
            int_y = (NodeHere->DataD.y) - 1 ;
        break;

        case 7:
            int_x = (NodeHere->DataD.x);
            int_y = (NodeHere->DataD.y) - 1 ;
        break;

        default:
        break;
    }

    int int_execution = AddNode_d(p_list,firstnode, int_x, int_y, int_distance,NodeHere);
    return(recurseDijkstra(p_list,firstnode,matrice_Map,matrice_Distance,int_mapSize, coordEnd,int_mode));
}

List* AlgoDijkstra(int** matrice_Map,int*** matrice_Distance, PlayerInfo* p_playerInfo, int int_mapSize, int int_mode)
{

    int int_x;
    int int_y;
    coordonnees coordEnd = DefineEndGame(int_mapSize, matrice_Map);
    coordonnees coordStart;
    

    switch (DefineStartPlayer(p_playerInfo, int_mapSize))
    {
    case 1:
        coordStart.x = 0;
        coordStart.y = 0;
    break;
    case 3:
        coordStart.x = 0;
        coordStart.y = int_mapSize-1;
    break;
    case 2:
        coordStart.x = int_mapSize-1;
        coordStart.y =0;
    break;
    case 4:
        coordStart.x = int_mapSize-1;
        coordStart.y = int_mapSize-1;
    break;
    default:
        exit(0);
    break;
    }

    List_d* ListDrijkstra = InitList_d(coordStart.x, coordStart.y);

    Node_d* Arrive= recurseDijkstra(ListDrijkstra, ListDrijkstra->firstnode, matrice_Map, matrice_Distance, int_mapSize, coordEnd,int_mode);

    if(Arrive->DataD.x == -1 && Arrive->DataD.y == -1 ){
         puts("Error in Dijkstra Energy, the energy of the path to go to the first accessible bonus makes it negative and is less than the number of squares available from the starting square\n");
         MenuNext();
         return (NULL);
         
    }
    List* BetterWay = EndDijkstra(Arrive);

    BetterWay->firstnode->is_bonus = Arrive->DataD.distance;
   
    FreeList_d(ListDrijkstra);

  
    return(BetterWay);
}