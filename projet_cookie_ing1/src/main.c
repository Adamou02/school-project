#include "Game.h"

GameInformation GameInfo;

int main(void)
{  
    SetupGame();
    InitGame();
    Game();
    EndGame();
    FreeGame();
    return 0;
}
