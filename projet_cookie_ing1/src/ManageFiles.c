  #include "ManageFiles.h"

int ExistFile(char str_NameFile[])
{
    FILE* File = fopen(str_NameFile, "r+");  
    if (File == NULL){// Le fichier n'existe pas
        return 0;
    }else{// Le fichier existe  
        fclose(File);
        return 1;
    }
}

void createFile(char str_NameFile[])
{
    FILE* File = fopen(str_NameFile, "w+");  
        fclose(File);
}

int SupprFile(char str_NameFile[])
{
    int int_A = ExistFile(str_NameFile);
    if (int_A == 0){// Le fichier n'existe pas, on ne peut donc pas le supprimer
        return (0);
    }else{// Le fichier existe, on le supprime
        remove(str_NameFile);
        return (1);
    }
}

int IsEmptyFile(char str_NameFile[])
{
    if(ExistFile(str_NameFile)){
        FILE* File = fopen(str_NameFile, "r");
        fseek(File, 0, SEEK_END);
        long lengthFile = ftell(File);
        if(lengthFile == 0){
            fclose(File);
            return 1;
        }else{
            fclose(File);
            return 0;
        }
    }
    return 1;
}

void DeleteLastLine(char str_NameFile[])
{
    FILE* file_CSV = fopen(str_NameFile, "r");
    FILE* file_temp = fopen("Tmp.csv", "w");

    char* line = malloc(100000*sizeof(*line));
    int line_nbr = 0;

    while(fgets(line, 100000*sizeof(*line), file_CSV))
    {
        line_nbr++;
    }
    rewind(file_CSV);

    for(int i=0; i<line_nbr-1; i++)
    {
        fgets(line, 100000*sizeof(*line), file_CSV);
        fprintf(file_temp, "%s", line);
    }

    fclose(file_CSV);
    fclose(file_temp);

    SupprFile(CURRENT_GAME_CSV);

    FILE* new_CSV = fopen(CURRENT_GAME_CSV, "w");
    file_temp = fopen("Tmp.csv", "r");
    
    while(fgets(line, 100000*sizeof(*line), file_temp))
    {
        fprintf(new_CSV, "%s", line);
    }
    
    fclose(new_CSV);
    fclose(file_temp);
    SupprFile("Tmp.csv");
    free(line);
    return;
}

//*******************************************************************
//******FONTIONS DE SAUVEGARDE/RECUPERATION PARTIE*******************
//*******************************************************************

int SavedTurnsCount(int int_mapSize, char str_NameFile[])
{
    FILE* file_CSV = fopen(str_NameFile, "r");
    char* CSV_String = malloc((int_mapSize*int_mapSize*64+11)*sizeof(*CSV_String));
    int turn_count = 0;

    while(fgets(CSV_String, (int_mapSize*int_mapSize*64+11)*sizeof(*CSV_String) ,file_CSV))
    {
        turn_count++;
    }
    free(CSV_String);
    return(turn_count);
}


void GetPlayerInfo(int int_mapSize, PlayerInfo * s_playerInfo_player, int num_turn, char str_NameFile[])
{
    FILE* file_CSV = fopen(str_NameFile, "r");
    char* CSV_String = (char *)malloc(int_mapSize*int_mapSize*64+11);
    
    //Acces au tour souhaité
    for(int i=0; i<num_turn; i++)
    {
        //Recuperation de toutes les donnees
        fgets(CSV_String, int_mapSize*int_mapSize*64+11 ,file_CSV);
    }

    //Separation et implementation des donnees aux variables de jeu
    s_playerInfo_player->coordonnees.x = atoi(strtok(CSV_String, ",;"));
    s_playerInfo_player->coordonnees.y = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->energy = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->distance = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->gain_energy = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->lost_energy = atoi(strtok(NULL, ",;"));
    s_playerInfo_player->backward = atoi(strtok(NULL, ",;"));
    
    fclose(file_CSV);
    free(CSV_String);
    return;
}

char* GetMapString(char* MapString, int int_mapSize, int num_turn, char str_NameFile[])
{
    FILE* file_CSV = fopen(str_NameFile, "r");
    char* CSV_String = malloc((int_mapSize*int_mapSize*2048)*sizeof(*CSV_String));
    
    //Acces au tour souhaité
    for(int i=0; i<num_turn; i++)
    {
        //Recuperation de toutes les donnees
        fgets(CSV_String, (int_mapSize*int_mapSize*2048)*sizeof(*CSV_String) ,file_CSV);        
    }

    //Separation et implementation des donnees aux variables de jeu
    strtok(CSV_String, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strcpy(MapString,strtok(NULL, ",;"));
    
    fclose(file_CSV);
    free(CSV_String);
    return(MapString);
}

char* GetDistanceString(char* DistanceString, int int_mapSize, int num_turn, char str_NameFile[])
{
    FILE* file_CSV = fopen(str_NameFile, "r");
    char* CSV_String = (char *)malloc(int_mapSize*int_mapSize*64+11);
    
    //Acces au tour souhaité
    for(int i=0; i<num_turn; i++)
    {
        //Recuperation de toutes les donnees
        fgets(CSV_String, int_mapSize*int_mapSize*64+11 ,file_CSV);        
    }

    //Separation et implementation des donnees aux variables de jeu
    strtok(CSV_String, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strcpy(DistanceString,strtok(NULL, ",;"));
    
    fclose(file_CSV);
    free(CSV_String);
    return(DistanceString);
}

char* GetListString(char* ListString, int int_mapSize, int num_turn)
{
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "r");
    char* CSV_String = malloc((int_mapSize*int_mapSize*64+11)*sizeof(*CSV_String));

    //Acces au tour souhaité
    for(int i=0; i<num_turn; i++)
    {
        //Recuperation de toutes les donnees
        fgets(CSV_String,(int_mapSize*int_mapSize*64+11)*sizeof(*CSV_String) ,Current_Game_CSV);
    }

    //Separation et implementation des donnees aux variables de jeu
    strtok(CSV_String, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strtok(NULL, ",;");
    strcpy(ListString, strtok(NULL, ",;"));
    
    fclose(Current_Game_CSV);
    free(CSV_String);
    return(ListString);
}

char* AllocMapString(int int_mapSize){
    char* MapString = malloc((2*int_mapSize*int_mapSize+1)*sizeof(*MapString));
    return(MapString);
}

char* AllocDistanceString(int int_mapSize){
    char* DistanceString = malloc((16*int_mapSize*int_mapSize+1)*sizeof(*DistanceString));
    return(DistanceString);
}

char* AllocListString(int int_mapSize)
{
    char* ListString = malloc((2*200*int_mapSize)*sizeof(*ListString));
    return(ListString);
}

char* MatriceMapToString(int** matrice_Map, int int_mapSize, char* MapString)
{
    int int_nbchar = 0;
    int int_curseur = 0;
    char Current_Char;
    char c_sep1 = '.';
    char c_sep2 = '*';

    for(int int_curseurBis = 0; int_curseurBis < int_mapSize; int_curseurBis++)
    {
        while ( (int_curseur+1)%(int_mapSize+1) != 0 )
        {
            //Recuperation du char correspondant a chaque case
            Current_Char = matrice_Map[int_curseurBis][int_curseur];
            //Ajout du char au string
            *(MapString + int_nbchar) = Current_Char;
            int_nbchar++;
            
            if(( (int_curseur+2)%(int_mapSize+1) != 0) ){
                //Ajout d'un separateur entre chaque char, sauf a la fin d'une ligne
                *(MapString + int_nbchar) = c_sep1;
                int_nbchar++;
            }
            int_curseur++;
        }
        //Ajout d'un separateur different en fin de ligne
        *(MapString + int_nbchar) = c_sep2;
        int_nbchar++;
        int_curseur = 0;
        
    }
    *(MapString + int_nbchar) = '\0';
    return(MapString);
}

char* MatriceDistanceToString(int*** matrice_Distance, int int_mapSize, char* DistanceString){
    char Current_Str[2];
    int int_nbchar = 0;
    strcpy(DistanceString, "");
    for (int i = 0; i < int_mapSize; i++)
    {
        for (int j = 0; j < int_mapSize; j++)
        {   
            for (int k = 0; k < 8; k++){
                //Recuperation de la distance
                sprintf(Current_Str, "%d", matrice_Distance[i][j][k]);
                //Ajout de la valeur recuperee au string
                *(DistanceString + int_nbchar) = Current_Str[0];
                int_nbchar++;
                if(k != 7){
                    //Ajout d'un separateur entre chaque distance, sauf pour la derniere de chaque case
                    *(DistanceString + int_nbchar) = '.';
                    int_nbchar++;
                }
            }
            if(j != int_mapSize-1){
                //Ajout d'un separateur different entre chaque case, sauf pour la derniere de chaque ligne
                *(DistanceString + int_nbchar) = '*';
                int_nbchar++;
            }
        }
        if(i != int_mapSize-1){
            //Ajout d'un separateur entre chaque ligne, sauf en fin de string
            *(DistanceString + int_nbchar) = '/';
            int_nbchar++;
        }
    }
    *(DistanceString + int_nbchar) = '\0';
    return(DistanceString);
}

char* ListToString(List* p_list, char* ListString)
{
    Node* node_current = p_list->firstnode;
    char Current_Val[3];
    strcpy(ListString, "");
    while(node_current != NULL)
    {
        sprintf(Current_Val, "%d", node_current->coordonnees.x);
        strcat(ListString, Current_Val);
        strcat(ListString, ".");
        sprintf(Current_Val, "%d", node_current->coordonnees.y);
        strcat(ListString, Current_Val);
        strcat(ListString, ".");
        sprintf(Current_Val, "%d", node_current->is_bonus);
        strcat(ListString, Current_Val);
        strcat(ListString, "*");
        node_current = node_current->next;
    }
    return(ListString);
}

int** StringToMatriceMap(char* MapString, int int_mapSize, int** matrice_Map){
    char* current_Char = strtok(MapString, ".*");
    for(int i=0; i<int_mapSize ; i++){
        for(int j=0; j<int_mapSize ; j++){
            //Separation du string et ajout des valeurs recuperees dans la matrice
            matrice_Map[i][j] = (int)current_Char[0];
            current_Char = strtok(NULL, ".*");
        }
    }
    //Reinitialisation du string
    strcpy(MapString, "");
    return (matrice_Map);
}

int*** StringToMatriceDistance(char* DistanceString, int int_mapSize, int*** matrice_Distance){
    char* current_Char = strtok(DistanceString, ".*/");
    for(int i=0; i<int_mapSize ; i++){
        for(int j=0; j<int_mapSize ; j++){
            for(int k=0; k<8 ; k++){
                //Separation du string et ajout des valeurs recuperees dans la matrice
                matrice_Distance[i][j][k] = atoi(current_Char);
                current_Char = strtok(NULL, ".*/");
            }
        }
    }
    //Reinitialisation du string
    strcpy(DistanceString, "");
    return (matrice_Distance);
}

int ListElementsCount(char* ListString)
{
    int count = 0;
    int i = 0;
    while(ListString[i] != '\0')
    {
        if(ListString[i] == '*')
        {
            count++;
        }
        i++;
    }
    return(count);
}

List* StringToList(List* p_list, char* ListString)
{
    int tab_size = ListElementsCount(ListString);
    int ** List_tab = malloc(3*tab_size*sizeof(int));
    int Current_Val = atoi(strtok(ListString, ".*"));
    coordonnees coord;
    int bool = 1;
    
    for(int i = 0; i < tab_size; i++)
    {
        List_tab[i] = malloc(3*sizeof(int));
    }

    //Remplir le tableau avec les éléments de la liste
    for(int j = 0; j < tab_size; j++)
    {
        for(int k = 0; k < 3; k++)
        {
            List_tab[j][k] = Current_Val;
            Current_Val = atoi(strtok(NULL, ".*"));
        }
    }

    //Créer la liste à partir des éléments du tableau
    for(int m = tab_size-1; m >= 0; m--)
    {
        coord.x = List_tab[m][0];
        coord.y = List_tab[m][1];
        if(bool)
        {
            p_list = InitList(coord, List_tab[m][2]);
            bool = 0;
        }
        else
        {
            AddNode(p_list, coord, List_tab[m][2]);
        }
    }

    for(int l = 0; l < tab_size; l++)
    {
        free(List_tab[l]);
    }

    free(List_tab);
    return(p_list);
}

char* SaveMap(int** matrice_Map, int int_mapSize)
{
    char* MapString = AllocMapString(int_mapSize);
    MatriceMapToString(matrice_Map, int_mapSize, MapString);
    return(MapString);
}

int** RestoreMap(int** matrice_Map, int int_mapSize, int num_turn, char str_NameFile[])
{
    char* MapString = AllocMapString(int_mapSize);
    MapString = GetMapString(MapString, int_mapSize, num_turn, str_NameFile);
    StringToMatriceMap(MapString, int_mapSize, matrice_Map);
    free(MapString);
    return(matrice_Map);
}

char* SaveDistance(int*** matrice_Distance, int int_mapSize)
{
    char* DistanceString = AllocDistanceString(int_mapSize);
    MatriceDistanceToString(matrice_Distance, int_mapSize, DistanceString);
    return(DistanceString);
}

int*** RestoreDistance(int*** matrice_Distance, int int_mapSize, int num_turn, char str_NameFile[])
{
    char* DistanceString = AllocDistanceString(int_mapSize);
    DistanceString = GetDistanceString(DistanceString, int_mapSize, num_turn, str_NameFile);
    StringToMatriceDistance(DistanceString, int_mapSize, matrice_Distance);
    free(DistanceString);
    return(matrice_Distance);
}

char* SaveList(List* p_list, int int_mapSize)
{
    char* ListString = AllocListString(int_mapSize);
    ListString = ListToString(p_list, ListString);
    return(ListString);
}

List* RestoreList(int int_mapSize, int num_turn)
{
    char* ListString = AllocListString(int_mapSize);
    ListString = GetListString(ListString, int_mapSize, num_turn);
    List* p_list = StringToList(p_list, ListString);
    free(ListString);
    return(p_list);
}

void StockCurrentTurn(int** matrice_Map, int*** matrice_Distance, List* p_list, int int_mapSize, PlayerInfo * s_playerInfo_player)
{
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "a");
    //Verification de l'ouverture du fichier
    if(Current_Game_CSV == NULL){
        printf("\nErreur de chemin d'accès au fichier\n\n");
    }
    char* MapString = SaveMap(matrice_Map, int_mapSize);
    char* DistanceString = SaveDistance(matrice_Distance, int_mapSize);
    char* ListString = SaveList(p_list, int_mapSize);
    //Ajout de toutes les donnees au fichier
    fprintf(Current_Game_CSV, "%d,%d,%d,%d,%d,%d,%d,%s,%s,%s\n", s_playerInfo_player->coordonnees.x, s_playerInfo_player->coordonnees.y, 
        s_playerInfo_player->energy, s_playerInfo_player->distance, s_playerInfo_player->gain_energy, 
        s_playerInfo_player->lost_energy, s_playerInfo_player->backward, MapString, DistanceString, ListString);
    fclose(Current_Game_CSV);
    free(MapString);
    free(DistanceString);
    free(ListString);
    return;
}

void RestoreTurn(int num_turn, int*** matrice_Map, int**** matrice_Distance, PlayerInfo* p_playerInfo, int int_mapSize, char str_NameFile[])
{
    *matrice_Map = RestoreMap(*matrice_Map, int_mapSize, num_turn, str_NameFile);
    *matrice_Distance = RestoreDistance(*matrice_Distance, int_mapSize, num_turn, str_NameFile);
    GetPlayerInfo(int_mapSize, p_playerInfo, num_turn, str_NameFile);
}

int RestoreMapSize(char str_NameFile[])
{
    FILE* File_CSV = fopen(str_NameFile, "r");
    char* CSV_String = malloc(4*sizeof(*CSV_String));
    int int_mapSize = 0;

    //Verification de l'ouverture du fichier
    if(File_CSV == NULL){
        printf("\nErreur de chemin d'accès au fichier\n\n");
    }

    fgets(CSV_String, 4*sizeof(*CSV_String), File_CSV);
    int_mapSize = atoi(CSV_String);
    free(CSV_String);
    return(int_mapSize);
}

void Save(int int_mapSize)
{
    SupprFile(SAVE_CSV);
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "r");
    FILE* Save_CSV = fopen(SAVE_CSV, "w");
    char current_Char;

    if (Current_Game_CSV == NULL || Save_CSV == NULL)
    {
        printf("\nErreur d'ouverture du fichier\n\n");
    }
    
    fprintf(Save_CSV, "%d\n", int_mapSize);

    current_Char = fgetc(Current_Game_CSV);
    while (current_Char != EOF)
    {
        fputc(current_Char, Save_CSV);
        current_Char = fgetc(Current_Game_CSV);
    }
    fclose(Current_Game_CSV);
    fclose(Save_CSV);
    return;
}

void SaveToCurrentGame()
{
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "w");
    FILE* Save_CSV = fopen(SAVE_CSV, "r");
    char current_Char;

    if (Current_Game_CSV == NULL || Save_CSV == NULL)
    {
        printf("\nErreur d'ouverture du fichier\n\n");
    }
    
    while (current_Char != '\n'){
        current_Char = fgetc(Save_CSV);
    }
    current_Char = fgetc(Save_CSV);

    while (current_Char != EOF)
    {
        fputc(current_Char, Current_Game_CSV);
        current_Char = fgetc(Save_CSV);
    }

    fclose(Current_Game_CSV);
    fclose(Save_CSV);
    return;
}

void History(int int_mapSize)
{
    FILE* Current_Game_CSV = fopen(CURRENT_GAME_CSV, "r");
    FILE* History_CSV = fopen(HISTORY_CSV, "a");
    char current_Char;

    if (Current_Game_CSV == NULL || History_CSV == NULL)
    {
        printf("\nErreur d'ouverture du fichier\n\n");
    }

    fprintf(History_CSV, "%d\n", int_mapSize);
    fprintf(History_CSV, "%d\n", SavedTurnsCount(int_mapSize, CURRENT_GAME_CSV));

    current_Char = fgetc(Current_Game_CSV);
    while (current_Char != EOF)
    {
        fputc(current_Char, History_CSV);
        current_Char = fgetc(Current_Game_CSV);
    }
    fclose(Current_Game_CSV);
    fclose(History_CSV);
    return;
}

void ReadHistory(int num_game, int*** matrice_Map, int speed)
{
    FILE* History_CSV = fopen(HISTORY_CSV, "r");
    int int_mapSize = RestoreMapSize(HISTORY_CSV); // ajouter un moyen de recuperer la taille de la map du nème historique
    char* CSV_String = malloc(int_mapSize*int_mapSize*2048*sizeof(*CSV_String));
    int sum_turns = 0;
    int turns_nbr = 0;
    fgets(CSV_String, 4*sizeof(*CSV_String), History_CSV);
    fgets(CSV_String, 4*sizeof(*CSV_String), History_CSV);

    for(int i=1; i<num_game; i++)
    {
        sum_turns+=atoi(CSV_String)+2;
        turns_nbr = atoi(CSV_String);

        for(int j=0; j<turns_nbr; j++){
            fgets(CSV_String, (int_mapSize*int_mapSize*2048)*sizeof(*CSV_String), History_CSV);
        }
        fgets(CSV_String, 4*sizeof(*CSV_String), History_CSV);
        int_mapSize = atoi(CSV_String);
        fgets(CSV_String, 4*sizeof(*CSV_String), History_CSV);
    }

    for(int k=3; k<atoi(CSV_String)+3; k++)
    {
        ClearTerm();
        RestoreMap(*matrice_Map, int_mapSize, k + sum_turns, HISTORY_CSV);
        DisplayMap(*matrice_Map, int_mapSize);
        struct timeval tv;//
        switch (speed)
        {
            case 1: //Slow
                tv.tv_sec = 0;
                tv.tv_usec = SLOW_SPEED * 10000; 
                select(0, NULL, NULL, NULL, &tv);//equivalent de sleep
                break;
            case 2: //Normal
                tv.tv_sec = 0;
                tv.tv_usec = NORMAL_SPEED * 10000; 
                select(0, NULL, NULL, NULL, &tv);//equivalent de sleep
                break;
            case 3: //Fast
                tv.tv_sec = 0;
                tv.tv_usec = FAST_SPEED * 10000;
                select(0, NULL, NULL, NULL, &tv);//equivalent de sleep
                break;
            
            default:
                break;
        }
    }
    free(CSV_String);
    return;
}

int CountHistory()
{
    FILE* History_CSV = fopen(HISTORY_CSV, "r");
    int int_mapSize = RestoreMapSize(HISTORY_CSV);
    char* CSV_String = malloc((int_mapSize*int_mapSize*2048)*sizeof(*CSV_String));
    char* String_Value;

    int sum_turns = 0;
    int turns_nbr = 0;
    fgets(CSV_String, 4*sizeof(*CSV_String), History_CSV);
    fgets(CSV_String, 4*sizeof(*CSV_String), History_CSV);

    while(String_Value != NULL)
    {
        sum_turns+=1;
        turns_nbr = atoi(CSV_String);

        for(int j=0; j<turns_nbr; j++){
            fgets(CSV_String, (int_mapSize*int_mapSize*2048)*sizeof(*CSV_String), History_CSV);
        }
        fgets(CSV_String, 4*sizeof(*CSV_String), History_CSV);
        int_mapSize = atoi(CSV_String);
        String_Value = fgets(CSV_String, 4*sizeof(*CSV_String), History_CSV);
    }

    free(CSV_String);
    return(sum_turns);
}

void ClearHistory()
{
    SupprFile(HISTORY_CSV);
}
