#include "Game.h"

void SetupGame()
{
    EditTerminal();
    InitRNG();
    SupprFile(CURRENT_GAME_CSV);
}

void BeforeTurn(int** matrice_Map, int*** matrice_Distance, int int_mapSize, PlayerInfo* p_playerInfo, List* p_list)
{
    ClearTerm();
    if(p_list == NULL){
        DisplayMap(matrice_Map, int_mapSize);
    } else {
        DisplayPathInMap(matrice_Map, int_mapSize, p_list);
    }
    printf("Votre energie : %d\n",p_playerInfo->energy);
    ShowKeyAvailable(p_playerInfo, matrice_Distance);
}

void ErrorStepBack(int int_error)
{
    ClearTerm();    //on clear et réaffiche la map, pour eviter l'accumulation de message d'erreur 
    BeforeTurn(GameInfo.matrice_Map, GameInfo.matrice_Distance, GameInfo.int_mapSize, &GameInfo.s_playerInfo, GameInfo.p_listpath);
    if(int_error == 1){
        printf("\nVous n'avez plus de retour en arrière possible.\n");
    } else if(int_error == 2){
        // PrintList(p_list);
        printf("\nVous ne pouvez pas revenir plus en arrière.\n");
    }
    return;
}

int BeforeStepBack(PlayerInfo* p_playerInfo, List* p_list)
{
    if(p_playerInfo->backward <= 0){
        return (1);
    } else if(LengthList(p_list) <= 1){
        return (2);
    } else {
        return (0);
    }
}

void Game()
{
    int key_pressed, int_wanted_x, int_wanted_y, int_error;
    int bool_victory = 0;
    int choice;
    int bool_isanObstacle = 0;
    int bool_alreadybeen = 0;
    RemoveNode(GameInfo.p_listpath);
    AddNode(GameInfo.p_listpath,  GameInfo.s_playerInfo.coordonnees, 0);

    BeforeTurn(GameInfo.matrice_Map, GameInfo.matrice_Distance, GameInfo.int_mapSize, &GameInfo.s_playerInfo, GameInfo.p_listpath);
    while( !bool_victory && GameInfo.s_playerInfo.energy > 0){
        StockCurrentTurn(GameInfo.matrice_Map, GameInfo.matrice_Distance, GameInfo.p_listpath, GameInfo.int_mapSize, &GameInfo.s_playerInfo);
        key_pressed = ListenKeyboard();
        ChangePosition(key_pressed, &int_wanted_x, &int_wanted_y, &GameInfo.s_playerInfo); 
        if(key_pressed == STEP_BACK){
            int_error = BeforeStepBack(&GameInfo.s_playerInfo, GameInfo.p_listpath);
            if(int_error != 0){
                ErrorStepBack(int_error);
            }else{
                StepBack(GameInfo.p_listpath, GameInfo.matrice_Map, &GameInfo.s_playerInfo, GameInfo.matrice_Distance);
                BeforeTurn(GameInfo.matrice_Map, GameInfo.matrice_Distance, GameInfo.int_mapSize, &GameInfo.s_playerInfo, GameInfo.p_listpath);
            }
        } else if(key_pressed == LEAVE){
            choice = MenuSave();
            if (choice == 0) 
                Quit(); //l'utilisateur a choisi de partir sans sauvegarder.
            else if (choice == 1)
                SaveAndQuit();//fonction Fabien sauvegarde; 
            else //choice ==2 l'utilisateur veut revenir jouer sur sa game
                BeforeTurn(GameInfo.matrice_Map, GameInfo.matrice_Distance, GameInfo.int_mapSize, &GameInfo.s_playerInfo, GameInfo.p_listpath);
       } else {
            if(AlreadyBeen(int_wanted_x, int_wanted_y, GameInfo.p_listpath) == 1 && GameInfo.s_playerInfo.distance>0){ //on regarde si le joueur est déjà passé sur la case
                bool_alreadybeen = 1;
            }
            GameInfo.matrice_Map = AfterMovement(GameInfo.matrice_Map, int_wanted_x, int_wanted_y, &GameInfo.s_playerInfo, GameInfo.int_mapSize, &bool_victory, GameInfo.p_listpath, GameInfo.matrice_Distance, &bool_isanObstacle);
            printf("\n"); 
            BeforeTurn(GameInfo.matrice_Map, GameInfo.matrice_Distance, GameInfo.int_mapSize, &GameInfo.s_playerInfo, GameInfo.p_listpath);
            if(bool_isanObstacle == 1){
                printf("\nOh no, it was an obstacle, you lost %d energy\n", LOST_ENERGY);
                bool_isanObstacle=0;
            }
            if(bool_alreadybeen == 1){
                printf("\nBe careful, you've already been there\n");
                bool_alreadybeen = 0;
            }
        }
    }
    StockCurrentTurn(GameInfo.matrice_Map, GameInfo.matrice_Distance, GameInfo.p_listpath, GameInfo.int_mapSize, &GameInfo.s_playerInfo);
    GameInfo.bool_victory=bool_victory;
    return;
}

void FreeGame()
{
    FreeList(GameInfo.p_listpath);
    FreeList(GameInfo.p_listBestWay);
    UnallocMatriceMap(GameInfo.matrice_Map, GameInfo.int_mapSize);
    UnallocMatriceDistance(GameInfo.matrice_Distance, GameInfo.int_mapSize);
}


void Quit()
{
    FreeGame();
    exit(EXIT_SUCCESS);
}

void SaveAndQuit()
{
    Save(GameInfo.int_mapSize);
    Quit();
}

void QuitFail(const char* str_errMsg){
    puts(str_errMsg);
    FreeGame();
    exit(EXIT_FAILURE);
}

void NewGame()
{
     //Choix des parametre de la game
    GameInfo.float_diffRate = ChooseDifficulty();
    GameInfo.int_mapSize = ChooseMapSize();

    //Initialisation de la structure Joueur et du stockage du chemin
    GameInfo.s_playerInfo = SetupPlayer(); 
    InitEnergy(&GameInfo.s_playerInfo, GameInfo.int_mapSize);
    GameInfo.p_listpath = InitList(GameInfo.s_playerInfo.coordonnees, 0);

    //Creation des structures contenant les infos de la carte
    GameInfo.matrice_Map = InitMap(GameInfo.int_mapSize, GameInfo.float_diffRate, &GameInfo.s_playerInfo);
    GameInfo.matrice_Distance = InitDistance(GameInfo.int_mapSize);
}

void ReloadSave(int*** matrice_Map, int**** matrice_Distance, PlayerInfo* s_playerInfo, int int_mapSize)
{
    SaveToCurrentGame();
    RestoreTurn(SavedTurnsCount(int_mapSize, CURRENT_GAME_CSV)+1, matrice_Map, matrice_Distance, s_playerInfo, int_mapSize, SAVE_CSV );
}

void ResumeGame()
{
    if(!ExistFile(SAVE_CSV)){ //verif si le fichier est vide ou n'existe pas
        ClearTerm();
        puts("File Save.csv not found or empty, press enter to return to the previous menu");
        ListenKeyboard();
        InitGame();
        return;
    }   
    GameInfo.int_mapSize = RestoreMapSize(SAVE_CSV);
    GameInfo.matrice_Map = AllocMatriceMap(GameInfo.int_mapSize);
    GameInfo.matrice_Distance = AllocMatriceDistance(GameInfo.int_mapSize);
    ReloadSave(
                &GameInfo.matrice_Map,
                &GameInfo.matrice_Distance,
                &GameInfo.s_playerInfo,
                GameInfo.int_mapSize
                );
    GameInfo.p_listpath = RestoreList(GameInfo.int_mapSize, SavedTurnsCount(GameInfo.int_mapSize, CURRENT_GAME_CSV)+1);
    DeleteLastLine(CURRENT_GAME_CSV);
}

void EndGame()
{
   ClearTerm();
    //messsage de victoire/defaite et recap de la partie
    VictoryMessage(GameInfo.bool_victory, &GameInfo.s_playerInfo);
    MenuNext();
    printf("The Path you followed: ");
    DisplayList(InvertList(GameInfo.p_listpath));
    DisplayPathInMapArrow(GameInfo.matrice_Map, GameInfo.int_mapSize, InvertList(GameInfo.p_listpath));
    MenuNext();
    //recherche et affichage du meilleur chemin en terme de distance
    RestoreTurn(1 ,&GameInfo.matrice_Map, &GameInfo.matrice_Distance, &GameInfo.s_playerInfo, GameInfo.int_mapSize, CURRENT_GAME_CSV);
    GameInfo.p_listBestWay = AlgoDijkstra(GameInfo.matrice_Map,
                                          GameInfo.matrice_Distance,
                                          &GameInfo.s_playerInfo, 
                                          GameInfo.int_mapSize,
                                          1
                                          );
    if(GameInfo.p_listBestWay != NULL){
        printf("The shortest path: ");
        DisplayList(GameInfo.p_listBestWay);
        printf("Total distance: %d\n", GameInfo.p_listBestWay->firstnode->is_bonus);
        DisplayPathInMapArrow(GameInfo.matrice_Map,GameInfo.int_mapSize,InvertList(GameInfo.p_listBestWay));
    } else {
        puts("Error in Dijkstra Distance"); 
    }

    MenuNext();
    //recherche et affichage du meilleur chemin en terme de Energy
    RestoreTurn(1 ,&GameInfo.matrice_Map, &GameInfo.matrice_Distance, &GameInfo.s_playerInfo, GameInfo.int_mapSize, CURRENT_GAME_CSV);
    GameInfo.p_listBestWayEnergy = AlgoDijkstra(GameInfo.matrice_Map,
                                          GameInfo.matrice_Distance,
                                          &GameInfo.s_playerInfo, 
                                          GameInfo.int_mapSize,
                                          2
                                          );
    if(GameInfo.p_listBestWayEnergy != NULL){
        printf("Less energy intensive path: ");
        DisplayList(GameInfo.p_listBestWayEnergy);
        printf("Total energy left: %d\n", (BASE_ENERGY*GameInfo.int_mapSize)-(GameInfo.p_listBestWayEnergy->firstnode->is_bonus));
        DisplayPathInMapArrow(GameInfo.matrice_Map,GameInfo.int_mapSize,InvertList(GameInfo.p_listBestWayEnergy));
    } else {
         puts("Error in Dijkstra Energy");
    }
    //ajout de la partie dans l'historique
    History(GameInfo.int_mapSize);
    MenuNext();
    //revisualisation de la partie (ajouter un menu pr choisir oui ou non a la place de MenuNext)
    if(MenuReplay()){
         ReadHistory(CountHistory(), &GameInfo.matrice_Map, MenuSpeedHistory());
    }
    SupprFile(CURRENT_GAME_CSV);
}

void ViewGameHistory() 
{
    int choice = MenuGameHistory();
    if(choice != 0){
        GameInfo.int_mapSize = TAILLE_BIG_MAP;
        GameInfo.matrice_Map = AllocMatriceMap(TAILLE_BIG_MAP) ;
        ReadHistory(choice, &GameInfo.matrice_Map, MenuSpeedHistory());
        UnallocMatriceMap(GameInfo.matrice_Map, TAILLE_BIG_MAP);
    }
    
}


void ConfirmClearHistory() 
{
    int choice = MenuConfirmClearHistory();
    if (choice == 1) {
        ClearHistory();
        ClearTerm();
        printf("History Clean successfully, press Enter to return to previous menu\n");
        ListenKeyboard();
    }
}

void ManageHistory()    
{
    if(!ExistFile(HISTORY_CSV)){ //verif si le fichier est vide ou n'existe pas
        ClearTerm();
        puts("File History.csv not found or empty, press enter to return to the previous menu");
        ListenKeyboard();
        InitGame();
        return;
    }
    int choice = MenuHistory();
    switch (choice)
    {
    case 1:
        ViewGameHistory();
        exit(EXIT_SUCCESS);
        break;
    case 2:
        ConfirmClearHistory();
        InitGame();
        break;
    case 3:
        InitGame();
        break;
    default:
        break;
    }      
}

void InitGame()
{
    switch(MenuStartGame()){
        case 1:
            ResumeGame();
            break;
        case 2:
            NewGame();
            break;
        case 3:
            ManageHistory();
            break;
        case 4:
            exit(EXIT_SUCCESS);
            break;
        default:
            exit(EXIT_FAILURE);
            break;
    }
}
