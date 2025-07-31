#include "Movements.h"

//Verifie la touche pressée
int KeyAvailable(int key)
{
    if (key == UP || key == MAJ_UP || key == DOWN || key == MAJ_DOWN ||key == LEFT || key == MAJ_LEFT ||key == RIGHT || key == MAJ_RIGHT ||key == UP_LEFT || key == MAJ_UP_LEFT ||key == UP_RIGHT || key == MAJ_UP_RIGHT || key == DOWN_LEFT || key == MAJ_DOWN_LEFT || key == DOWN_RIGHT || key == MAJ_DOWN_RIGHT || key == STEP_BACK || key == MAJ_STEP_BACK || key == LEAVE || key == MAJ_LEAVE || key == ENTER) { 
        return 1;
    }
    else {
        return 0;
    }
}

//Change les valeur des variables dans UpdatePosition pour changer la position du personnage dans la matrice map
void ChangePosition(int key, int* x, int* y, PlayerInfo *p_playerInfo)
{
    *x=p_playerInfo->coordonnees.x;
    *y=p_playerInfo->coordonnees.y;
    switch (key)
    {
    case LEFT:
        *y=*y-1;
        break;
    case MAJ_LEFT:
        *y=*y-1;
        break;
    case RIGHT:
        *y=*y+1;
        break;
    case MAJ_RIGHT:
        *y=*y+1;
        break;
    case UP:
        *x=*x-1;
        break;
    case MAJ_UP:
        *x=*x-1;
        break;
    case DOWN:
        *x=*x+1;
        break;
    case MAJ_DOWN:
        *x=*x+1;
        break;
    case UP_LEFT:
        *x=*x-1;
        *y=*y-1;
        break;
    case MAJ_UP_LEFT:
        *x=*x-1;
        *y=*y-1;
        break;
    case DOWN_LEFT:
        *x=*x+1;
        *y=*y-1;
        break;
    case MAJ_DOWN_LEFT:
        *x=*x+1;
        *y=*y-1;
        break;
    case UP_RIGHT:
        *x=*x-1;
        *y=*y+1;
        break;
    case MAJ_UP_RIGHT:
        *x=*x-1;
        *y=*y+1;
        break;
    case DOWN_RIGHT:
        *x=*x+1;
        *y=*y+1;
        break;
    case MAJ_DOWN_RIGHT:
        *x=*x+1;
        *y=*y+1;
        break;
    default:
        break;
    }
}

//Saute une ligne à chaque fois qu'on affiche 3 blocs touche sur le terminal
void SkipLine(int line_count, int *p_line_count) 
{
    if (line_count == 3) {
        printf("\n\n");
        *p_line_count=0;
    }
}

//Permet de lire la touche pressé. Le programme est en pause tant que utilisateur appuie touche
int ListenKeyboard()
{
    FILE* flux = stdin;
    tcgetattr(0, &old); //On recupere les propriétés actuelles du terminal
    current = old; //on les stock dans une variable
    current.c_lflag &= ~ICANON; //desactive input/output du terminal
    current.c_lflag &= ~ECHO; //Active le mode silencieux (pas de sortie texte du terminal)
    tcsetattr(0, TCSANOW, &current); //Applique ces modifications sur le terminal
    int ch;

    do
    {
        ch = getc(flux);
    } while (!KeyAvailable(ch));

    current.c_lflag |= ECHO; //desactive le mode silencieux
    tcsetattr(0, TCSANOW, &current); //Applique cette modification sur le terminal
    return ch;
}



int** UpdatePosition(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo) // Met à jour les informations de la map en fonction du déplacement
{   
    matrice_map[p_playerInfo->coordonnees.x][p_playerInfo->coordonnees.y] = REP_VOID;
    matrice_map[int_wanted_x][int_wanted_y] = REP_CHARACTER;
    return (matrice_map);
}

int GetDirection(int x, int y, int going_x, int going_y, int direction)
{
    if(
        x == going_x + 1 &&
        y == going_y
    ){
                direction= 5;
    } else if (
        x == going_x &&
        y == going_y + 1
    ){
                direction= 3;
    } else if (
        x == going_x + 1 &&
        y == going_y + 1
    ){
                direction= 4;
    } else if(
        x == going_x - 1 &&
        y == going_y
    ){
                direction= 1;
    } else if (
        x == going_x &&
        y == going_y - 1
    ){
                direction= 7;
    } else if (
    x == going_x - 1 &&
        y == going_y - 1
    ){
                direction= 0;
    } else if (
        x == going_x - 1 &&
        y == going_y + 1
    ){
                direction= 2;
    } else if (
        x == going_x + 1 &&
        y == going_y - 1
    ){
                direction = 6;
    }
    return direction;
}

void UpdatePlayerInfo(int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo,  int*** matrice_Distance)//Met à jour les infos du joueur en fonction du déplacement
{
    int direction=0;
    direction = GetDirection(int_wanted_x, int_wanted_y, p_playerInfo->coordonnees.x, p_playerInfo->coordonnees.y, direction);
    p_playerInfo->distance = p_playerInfo->distance + matrice_Distance[p_playerInfo->coordonnees.x][p_playerInfo->coordonnees.y][direction];
    p_playerInfo->coordonnees.x = int_wanted_x;
    p_playerInfo->coordonnees.y = int_wanted_y;
    p_playerInfo->energy = (p_playerInfo->energy) - STEP_ENERGY;
}

void PlayerOnBonus(PlayerInfo *p_playerInfo)//Donne de l'énergie à un joueur lorsqu'il marche sur un bonus
{
    p_playerInfo->energy = (p_playerInfo->energy) + GAIN_ENERGY;
    p_playerInfo->gain_energy = (p_playerInfo->gain_energy) + GAIN_ENERGY;
}

void PlayerOnObstacle(PlayerInfo *p_playerInfo) //retire de l'énergie au joueur lorsqu'il rentre dans un obstacle
{
    p_playerInfo->energy = (p_playerInfo->energy) - LOST_ENERGY;
    p_playerInfo->lost_energy = (p_playerInfo->lost_energy) + LOST_ENERGY;
}

void UpdatePathList(PlayerInfo *p_playerInfo, List* p_list, int is_bonus) // met à jour la dernière position du joueur dans la lise chainée
{
    AddNode(p_list, p_playerInfo->coordonnees, is_bonus);
}

int** WasABonus(int** matrice_map, int last_x, int last_y, PlayerInfo *p_playerInfo, char CST)
{

    matrice_map[p_playerInfo->coordonnees.x][p_playerInfo->coordonnees.y] = CST;
    matrice_map[last_x][last_y] = REP_CHARACTER;
    return (matrice_map);
}

void StepBack(List* p_list, int** matrice_map, PlayerInfo *p_playerInfo, int*** matrice_Distance) // Permet de faire un retour en arrière supprimant les infos dans la liste et en mettant à jour la map et le joueur
{
    int last_x;
    int last_y;
    int direction = 0;
    int nb_back = p_playerInfo-> backward;
    int was_bonus;
    GetfirstNode(p_list, &last_x, &last_y, &was_bonus);
    if(was_bonus == 1){
        RemoveNode(p_list);
        GetfirstNode(p_list, &last_x, &last_y, &was_bonus);
        matrice_map = WasABonus(matrice_map, last_x, last_y, p_playerInfo, REP_BONUS1);
        p_playerInfo->energy = (p_playerInfo->energy) - GAIN_ENERGY;
        p_playerInfo->gain_energy = (p_playerInfo->energy) - GAIN_ENERGY;
    }else if(was_bonus == 2){
        RemoveNode(p_list);
        GetfirstNode(p_list, &last_x, &last_y, &was_bonus);
        matrice_map = WasABonus(matrice_map, last_x, last_y, p_playerInfo, REP_BONUS2);
        p_playerInfo->energy = (p_playerInfo->energy) - GAIN_ENERGY;
        p_playerInfo->gain_energy = (p_playerInfo->energy) - GAIN_ENERGY;
    }else {
        RemoveNode(p_list);
        GetfirstNode(p_list, &last_x, &last_y, &was_bonus);
        matrice_map = UpdatePosition(matrice_map, last_x, last_y, p_playerInfo); // attention à changer parce que soucis si c'était un bonus
    }
    direction = GetDirection(p_playerInfo->coordonnees.x, p_playerInfo->coordonnees.y, last_x, last_y, direction);
    p_playerInfo-> backward = p_playerInfo-> backward - 1;
    p_playerInfo->coordonnees.x = last_x;
    p_playerInfo->coordonnees.y = last_y;
    p_playerInfo->energy = (p_playerInfo->energy) + STEP_ENERGY;
    p_playerInfo->distance = p_playerInfo->distance - matrice_Distance[last_x][last_y][direction];
}

int AlreadyBeen(int int_wanted_x, int int_wanted_y, List* p_list)
{
    coordonnees coord_wanted;
    coord_wanted.x = int_wanted_x;
    coord_wanted.y = int_wanted_y;
    return IsInList(p_list, coord_wanted);
}

int** AfterMovement(int** matrice_map, int int_wanted_x, int int_wanted_y, PlayerInfo *p_playerInfo, int int_mapSize, int *int_victory, List* p_list,  int*** matrice_Distance, int* p_bool_isanObstacle)// Permet de déplacer ou non le joueur en fonction du déplacement demandé et de la carte
{
    if(int_wanted_x>=0 && int_wanted_x<int_mapSize && int_wanted_y>=0 && int_wanted_y<int_mapSize){
      switch(matrice_map[int_wanted_x][int_wanted_y])
        {
        case REP_OBSTACLE1 :
            PlayerOnObstacle(p_playerInfo);
            *p_bool_isanObstacle = 1;
            break;

        case REP_OBSTACLE2 :
            PlayerOnObstacle(p_playerInfo);
              *p_bool_isanObstacle = 1;
            break;
        
        case REP_BONUS1 :
            PlayerOnBonus(p_playerInfo);
            matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
            UpdatePlayerInfo(int_wanted_x, int_wanted_y, p_playerInfo, matrice_Distance);
            UpdatePathList(p_playerInfo, p_list, 1);
            break;

        case REP_BONUS2 :
        PlayerOnBonus(p_playerInfo);
        matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
        UpdatePlayerInfo(int_wanted_x, int_wanted_y, p_playerInfo, matrice_Distance);
        UpdatePathList(p_playerInfo, p_list, 2);
        break;
    
        case REP_END :
            matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
            UpdatePlayerInfo(int_wanted_x, int_wanted_y, p_playerInfo, matrice_Distance);
            UpdatePathList(p_playerInfo, p_list, 0);
            *int_victory = 1;
            break;
        
        case REP_VOID :
            matrice_map = UpdatePosition(matrice_map, int_wanted_x, int_wanted_y, p_playerInfo);
            UpdatePlayerInfo(int_wanted_x, int_wanted_y, p_playerInfo, matrice_Distance);
            UpdatePathList(p_playerInfo, p_list, 0);
            break;
        
        default :
            return (matrice_map);
            break;
       }
     
    }
    return (matrice_map);
}
