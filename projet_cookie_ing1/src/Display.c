#include "Display.h"


void EditTerminal()
{
    system("\
coX=`xdpyinfo | grep dimensions | sed -r 's/^[^0-9]*([0-9]+x[0-9]+).*$/\\1/' | cut -d 'x' -f1`;\n\
coY=`xdpyinfo | grep dimensions | sed -r 's/^[^0-9]*([0-9]+x[0-9]+).*$/\\1/' | cut -d 'x' -f2`;\n\
resize -s `echo \"$(( $coY / 10 )) $(( $coX / 8 ))\"`>/dev/null;\n\
");

}


int MenuStartGame()
{
    int input;
    int position = 1; //1 = position haute
    ClearTerm();
    printf("\nWhat's your choice :\n> Continue your previous game\n Start a new game\n View game history\n Exit\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if ((input == UP || input == MAJ_UP) && position!=1)
        { 
            position--;
        }
        else if ((input == DOWN || input == MAJ_DOWN) && position !=4)
        {
            position++;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 1) {
            ClearTerm();
            printf("\nWhat's your choice :\n> Continue your previous game\n Start a new game\n View game history\n Exit\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 2) {
            ClearTerm();
            printf("\nWhat's your choice :\n Continue your previous game\n> Start a new game\n View game history\n Exit\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 3) {
            ClearTerm();
            printf("\nWhat's your choice :\n Continue your previous game\n Start a new game\n> View game history\n Exit\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 4) {
            ClearTerm();
            printf("\nWhat's your choice :\n Continue your previous game\n Start a new game\n View game history\n> Exit\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

int MenuGameHistory()
{
    ClearTerm();
    int i, count = CountHistory();
    int input;
    int position = 0; //0 = position haute
    while(1)
    {
        printf("\nChoose the Game to rewatch\n");
        if(count != 0){
            for(i=0; i<count; i++){
                if(position == i)
                    printf(">");
                printf(" Rewatch game n°%d\n", i+1);
            }
            printf("\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else {
            printf("No Game has been saved yet\n");
        }
        input = ListenKeyboard();
        if ((input == UP || input == MAJ_UP) && position!=0)
        { 
            position--;
        }
        else if ((input == DOWN || input == MAJ_DOWN) && position !=count-1)
        {
            position++;
        }
        else if (input == ENTER) {
            return position+1;
        }
        ClearTerm();
    }
}

int MenuHistory()
{
    int input;
    int position = 1; //1 = position haute
    ClearTerm();
    printf("\nWhat's your choice :\n> View game history\n Clear the history\n Go back\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if ((input == UP || input == MAJ_UP) && position!=1)
        { 
            position--;
        }
        else if ((input == DOWN || input == MAJ_DOWN) && position !=3)
        {
            position++;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 1) {
            ClearTerm();
            printf("\nWhat's your choice :\n> View game history\n Clear the history\n Go back\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 2) {
            ClearTerm();
            printf("\nWhat's your choice :\n View game history\n> Clear the history\n Go back\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 3) {
            ClearTerm();
            printf("\nWhat's your choice :\n View game history\n Clear the history\n> Go back\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

int MenuConfirmClearHistory()
{
    int input;
    int position = 1; //1 = position haute
    ClearTerm();
    printf("\nWhat's your choice :\n> Clear the history\n Go back\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if ((input == UP || input == MAJ_UP) && position!=1)
        { 
            position--;
        }
        else if ((input == DOWN || input == MAJ_DOWN) && position !=2)
        {
            position++;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 1) {
            ClearTerm();
            printf("\nWhat's your choice :\n> Clear the history\n Go back\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 2) {
            ClearTerm();
            printf("\nWhat's your choice :\n Clear the history\n> Go back\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

int MenuDifficulty()
{
    int input;
    int position = 1; //1 = position haute
    ClearTerm();
    printf("\nChoose a Difficulty :\n> Easy\n Normal\n Hard\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if ((input == UP || input == MAJ_UP) && position!=1)
        { 
            position--;
        }
        else if ((input == DOWN || input == MAJ_DOWN) && position !=3)
        {
            position++;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 1) {
            ClearTerm();
            printf("\nChoose a Difficulty :\n> Easy\n Normal\n Hard\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 2) {
            ClearTerm();
            printf("\nChoose a Difficulty :\n Easy\n> Normal\n Hard\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 3) {
            ClearTerm();
            printf("\nChoose a Difficulty :\n Easy\n Normal\n> Hard\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

int MenuMapSize()
{
    int input;
    int position = 1; //1 = position haute
    ClearTerm();
    printf("\nChoose the map size :\n> Little\n Average\n Big\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if ((input == UP || input == MAJ_UP) && position!=1)
        { 
            position--;
        }
        else if ((input == DOWN || input == MAJ_DOWN) && position !=3)
        {
            position++;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 1) {
            ClearTerm();
            printf("\nChoose the map size :\n> Little\n Average\n Big\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 2) {
            ClearTerm();
            printf("\nChoose the map size :\n Little\n> Average\n Big\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 3) {
            ClearTerm();
            printf("\nChoose the map size :\n Little\n Average\n> Big\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

int MenuSave() 
{
    int input;
    int position = 0; //0 = position haute
    ClearTerm();
    printf("\n> Quit Game without saving?\n Save Game!\n Go back\n\n\n%s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if ((input == UP || input == MAJ_UP) && position!=0)
        {
            position--;
        }
        else if ((input == DOWN || input == MAJ_DOWN) && position !=2)
        {
            position++;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 0) {
            ClearTerm();
            printf("\n> Quit Game without saving?\n Save Game!\n Go back\n\n\n%s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 1) {
            ClearTerm();
            printf("\n Quit Game without saving?\n> Save Game!\n Go back\n\n\n%s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 2) {
            ClearTerm();
            printf("\n Quit Game without saving?\n Save Game!\n> Go back\n\n\n%s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

void MenuNext()
{
    int input = -1;
    printf("Press %s Enter to continue :\n", ENTER_ICON);
    while(input != ENTER){
        input = ListenKeyboard();
    }
    ClearTerm();
    
}

int MenuSpeedHistory()
{
    int input;
    int position = 1; //1 = position haute
    ClearTerm();
    printf("\nChoose the speed for your replay :\n> Slow\n Normal\n Fast\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if ((input == UP || input == MAJ_UP) && position!=1)
        { 
            position--;
        }
        else if ((input == DOWN || input == MAJ_DOWN) && position !=3)
        {
            position++;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 1) {
            ClearTerm();
            printf("\nChoose the speed for your replay :\n> Slow\n Normal\n Fast\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 2) {
            ClearTerm();
            printf("\nChoose the speed for your replay :\n Slow\n> Normal\n Fast\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 3) {
            ClearTerm();
            printf("\nChoose the speed for your replay :\n Slow\n Normal\n> Fast\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

int MenuReplay()
{
    int input;
    int position = 1; //1 = position haute
    ClearTerm();
    printf("\nDo you want to rewatch your game :\n> Yes\n No\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
    while(1)
    {
        input = ListenKeyboard();
        if ((input == UP || input == MAJ_UP) && position!=1)
        { 
            position++;
        }
        else if ((input == DOWN || input == MAJ_DOWN) && position !=0)
        {
            position--;
        }
        else if (input == ENTER) {
            return position;
        }
        if (position == 1) {
            ClearTerm();
            printf("\nDo you want to rewatch your game :\n> Yes\n No\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
        else if (position == 0) {
            ClearTerm();
            printf("\nDo you want to rewatch your game :\n Yes\n> No\n\n\n %s : z\t\t%s : x\t\t%s : Enter\n", UP_ARROW, DOWN_ARROW, ENTER_ICON);
        }
    }
}

void ShowKeyAvailable(PlayerInfo *p_playerInfo_player,  int*** matrice_Distance)
{
    int line_count=0;
    printf("\nListe des touches :\n\n");
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][0]) {
        printf("%s : a  (%d kilomètres)", UP_LEFT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][0]);
        printf("\t\t");
        line_count++;
    }
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][1]) {
        printf("%s : z  (%d kilomètres)", UP_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][1]);
        printf("\t\t");
        line_count++;
    }
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][2]) {
        printf("%s : e  (%d kilomètres)", UP_RIGHT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][2]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][7]) {
        printf("%s : q  (%d kilomètres)", LEFT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][7]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][3]) {
        printf("%s : d  (%d kilomètres)", RIGHT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][3]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][5]) {
        printf("%s : x  (%d kilomètres)", DOWN_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][5]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][6]) {
        printf("%s : w  (%d kilomètres)", DOWN_LEFT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][6]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    if (matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][4]) {
        printf("%s : c  (%d kilomètres)", DOWN_RIGHT_ARROW, matrice_Distance[p_playerInfo_player->coordonnees.x][p_playerInfo_player->coordonnees.y][4]);
        printf("\t\t");
        line_count++;
    }
    SkipLine(line_count, &line_count);
    printf("%s : r ", STEP_BACK_ICON);
    line_count++;
    printf("\t\t");
    SkipLine(line_count, &line_count);
    printf("%s : p ", SAVE_ICON);
    printf("\n\n");
}

void DisplayMap(int** matrice_Map, int int_mapSize)
{
    int int_curseur = 0;
    char* constant_caseDisplay = ERROR;
    int bool_isNotEmj = 0;   
    printf(" ");
    for(int i=0; i<int_mapSize+1; i++)
    {
        printf("%s", DOWNBAR);
    }
    printf("\n");
    for(int int_curseurBis = 0; int_curseurBis < int_mapSize; int_curseurBis++)
    {
        printf(" %s", SIDEBAR);
        while ( (int_curseur+1)%(int_mapSize+1) != 0 )
        {
            bool_isNotEmj = 0;
            switch (matrice_Map[int_curseurBis][int_curseur])
            {
                case REP_CHARACTER :
                    constant_caseDisplay = CHARACTERE;
                    break;                
                case REP_END :
                    constant_caseDisplay = END;
                    break;                
                case REP_BONUS1 :
                    constant_caseDisplay = BONUS_COOKIE;
                    break;                
                case REP_BONUS2 :
                    constant_caseDisplay = BONUS_APPLE;
                    break;                
                case REP_OBSTACLE1 :
                    constant_caseDisplay = OBSTACLE_TREE;
                    break;
                case REP_OBSTACLE2 :
                    constant_caseDisplay = OBSTACLE_BEE;
                    break;                
                case REP_VOID :
                    constant_caseDisplay = VOID;
                    break;
                case REP_DEFAULT :
                    constant_caseDisplay = ERROR;
                    break;
                 case REP_UP :
                    constant_caseDisplay = UP_ARROW;
                    bool_isNotEmj = 1;
                    break;
                case REP_DOWN :
                    constant_caseDisplay = DOWN_ARROW;
                    bool_isNotEmj = 1;
                    break;    
                case REP_LEFT :
                    constant_caseDisplay = LEFT_ARROW;
                    bool_isNotEmj = 1;
                    break;                
                case REP_RIGHT :
                    constant_caseDisplay = RIGHT_ARROW;
                    bool_isNotEmj = 1;
                    break;                
                case REP_UPLEFT :
                    constant_caseDisplay = UP_LEFT_ARROW;
                    bool_isNotEmj = 1;
                    break;                
                case REP_UPRIGHT :
                    constant_caseDisplay = UP_RIGHT_ARROW;
                    bool_isNotEmj = 1;
                    break;                
                case REP_DOWNLEFT :
                    constant_caseDisplay = DOWN_LEFT_ARROW;
                    bool_isNotEmj = 1;
                    break;
                case REP_DOWNRIGHT :
                    constant_caseDisplay = DOWN_RIGHT_ARROW;
                    bool_isNotEmj = 1;
                    break;
                case REP_DOT :
                    constant_caseDisplay = DOT;
                    bool_isNotEmj = 1;
                    break;          
                default :
                    constant_caseDisplay = ERROR;
                    break;       
            }
            if(bool_isNotEmj){
                printf(" ");
            } 
            printf("%s", constant_caseDisplay);
            
            int_curseur++;
        }
        printf("%s\n", SIDEBAR);
        int_curseur = 0;
    }
    printf(" ");
    for(int i=0; i<int_mapSize+1; i++)
    {
        printf("%s", UPBAR);
    }
    printf("\n");
}

void DisplayPathInMapArrow(int** matric_Map, int int_mapSize, List* p_list)
{
    int** matric_tmp = AllocMatriceMap(int_mapSize);
    for(int i=0; i<int_mapSize; i++){
        for(int j=0; j<int_mapSize; j++){
            matric_tmp[i][j] = matric_Map[i][j];
        }
    }
    Node* node_current = p_list->firstnode;
    while(node_current != NULL && node_current->next != NULL)
    {
        if(!CoordCompare2(matric_Map, node_current->next->coordonnees, REP_CHARACTER)){
            if(
                node_current->next->coordonnees.x == node_current->coordonnees.x + 1 &&
                node_current->next->coordonnees.y == node_current->coordonnees.y
            ){
                     matric_tmp[node_current->next->coordonnees.x][node_current->next->coordonnees.y]= REP_UP;
            } else if (
                node_current->next->coordonnees.x == node_current->coordonnees.x &&
                node_current->next->coordonnees.y == node_current->coordonnees.y + 1
            ){
                     matric_tmp[node_current->next->coordonnees.x][node_current->next->coordonnees.y]= REP_LEFT;
            } else if (
                node_current->next->coordonnees.x == node_current->coordonnees.x + 1 &&
                node_current->next->coordonnees.y == node_current->coordonnees.y + 1
            ){
                     matric_tmp[node_current->next->coordonnees.x][node_current->next->coordonnees.y]= REP_UPLEFT;
            } else if(
                node_current->next->coordonnees.x == node_current->coordonnees.x - 1 &&
                node_current->next->coordonnees.y == node_current->coordonnees.y
            ){
                     matric_tmp[node_current->next->coordonnees.x][node_current->next->coordonnees.y]= REP_DOWN;
            } else if (
                node_current->next->coordonnees.x == node_current->coordonnees.x &&
                node_current->next->coordonnees.y == node_current->coordonnees.y - 1
            ){
                     matric_tmp[node_current->next->coordonnees.x][node_current->next->coordonnees.y]= REP_RIGHT;
            } else if (
                node_current->next->coordonnees.x == node_current->coordonnees.x - 1 &&
                node_current->next->coordonnees.y == node_current->coordonnees.y - 1
            ){
                     matric_tmp[node_current->next->coordonnees.x][node_current->next->coordonnees.y]= REP_DOWNRIGHT;
            } else if (
                node_current->next->coordonnees.x == node_current->coordonnees.x - 1 &&
                node_current->next->coordonnees.y == node_current->coordonnees.y + 1
            ){
                     matric_tmp[node_current->next->coordonnees.x][node_current->next->coordonnees.y]= REP_DOWNLEFT;
            } else if (
                node_current->next->coordonnees.x == node_current->coordonnees.x + 1 &&
                node_current->next->coordonnees.y == node_current->coordonnees.y - 1
            ){
                     matric_tmp[node_current->next->coordonnees.x][node_current->next->coordonnees.y]= REP_UPRIGHT;
            }
        }
        node_current = node_current->next;
    }    
    DisplayMap(matric_tmp, int_mapSize);
    UnallocMatriceMap(matric_tmp,int_mapSize);
}



void DisplayPathInMap(int** matric_Map, int int_mapSize, List* p_list)
{
    int** matric_tmp = AllocMatriceMap(int_mapSize);
    for(int i=0; i<int_mapSize; i++){
        for(int j=0; j<int_mapSize; j++){
            matric_tmp[i][j] = matric_Map[i][j];
        }
    }
    Node* node_current = p_list->firstnode;
    while(node_current != NULL && node_current->next != NULL)
    {
        if(!CoordCompare2(matric_Map, node_current->next->coordonnees, REP_CHARACTER)){
            matric_tmp[node_current->next->coordonnees.x][node_current->next->coordonnees.y]= REP_DOT;
        }
        node_current = node_current->next;
    }    
    DisplayMap(matric_tmp, int_mapSize);
    UnallocMatriceMap(matric_tmp,int_mapSize);
}

void VictoryMessage(int bool_victory, PlayerInfo *p_playerInfo)
{
    if (bool_victory) 
        printf("Congratulations, you won with %d energy remaining!\nYou traveled %d km.\nYou earned %d energy from the bonus and lost %d energy from obstacles.\n", p_playerInfo->energy, p_playerInfo->distance, p_playerInfo->gain_energy, p_playerInfo->lost_energy);
    else 
        printf("Too bad, you lost shamefully!\nYou traveled %d km.\nYou earned %d energy from the bonus and lost %d energy from obstacles.\n", p_playerInfo->distance, p_playerInfo->gain_energy, p_playerInfo->lost_energy);
}



void DisplayList(List* p_list)
{
    if(p_list == NULL){
        printf("Liste Vide\n");
        return;
    }
    Node* node_current = p_list->firstnode;
    while(node_current != NULL)
    {
        if(node_current->next){
             printf("[%d;%d]->", node_current->coordonnees.x, node_current->coordonnees.y);
        } else {
            printf("[%d;%d]\n", node_current->coordonnees.x, node_current->coordonnees.y);
        }
       
        node_current = node_current->next;
    }
    printf("\n");
}



/////////////////////////////////////////////////////////////////////////////
//Fonctions de DEBUG pour dev, ne serons pas utiliser dans le process final//
////////////////////////////////////////////////////////////////////////////

void DebugDisplayMap(int** matrice_Map, int int_mapSize)
{
    for( int i = 0 ; i<int_mapSize; i++) { 
        printf("%d> ", i);
       for( int j = 0 ; j<int_mapSize; j++){
            printf("%c", matrice_Map[i][j]);
            if(j != int_mapSize - 1) {
                printf(",");
            } else {
                printf("\n");
            }
        }
        if(i != int_mapSize - 1) {
            printf(";");
        } else {
            printf("\n");
        }
    }
    return;
}

void DebugDisplayMatriceDistance(int int_mapSize, int*** matrice_Distance)
{
    for(int p = 0; p < int_mapSize; p++)
    {
        printf("ligne %d :", p);
        for ( int m = 0; m < int_mapSize; m++)
        {
            printf(" %d :[", m);
            for ( int n = 0; n < 8; n++)
            {
                if(n != 7) {
                    printf("%d,", matrice_Distance[p][m][n]);
                } else {
                    printf("%d", matrice_Distance[p][m][n]);
                }
                
            }
            printf("],");
        }
        printf("\n");
    }
}

void DebugInfoPlayer(PlayerInfo s_playerInfo)
{   
    printf("Votre position x : %d\n",s_playerInfo.coordonnees.x);
    printf("Votre position y : %d\n",s_playerInfo.coordonnees.y);
    printf("Votre energie : %d\n",s_playerInfo.energy);
    printf("Votre distance parcourue : %d\n",s_playerInfo.distance);
    printf("Votre energie gagnée : %d\n",s_playerInfo.gain_energy);
    printf("Votre energie perdue : %d\n",s_playerInfo.lost_energy);
    printf("Vos retour en arrière disponible : %d\n",s_playerInfo.backward);
}

void PrintList(List* p_list) //affiche une liste passer en parametre
{
    if(p_list == NULL){
        printf("Liste Vide\n");
        return;
    }
    Node* node_current = p_list->firstnode;
    printf("List: |");
    while(node_current != NULL)
    {
        printf("x=%d, y=%d |", node_current->coordonnees.x, node_current->coordonnees.y);
        node_current = node_current->next;
    }
    printf("\n");
}

void PrintFirstList(List* p_list)
{
    if(p_list == NULL || p_list->firstnode == NULL){
        printf("Liste Vide\n");
        return;
    }
    printf("x=%d, y=%d \n", p_list->firstnode->coordonnees.x, p_list->firstnode->coordonnees.y);
}

/*
int affiche(Node_d *node)
{
    puts("NODE-");
    printf("%d %d   %d ", node->DataD.x,node->DataD.y, node->DataD.distance);
    int int_cpt = 0;
    //while (node->DataD.chemin[int_cpt]!= 100){ printf("{%d;%d}"); int_cpt = int_cpt+2;}
    printf("\n");
    if(node->next != NULL) return(affiche(node->next));
}*/