#ifndef CONSTANT_H
#define CONSTANT_H

    #define INF 9999999

    #define TAILLE_BIG_MAP 40
    #define TAILLE_AVE_MAP 30
    #define TAILLE_LIL_MAP 20

    #define TAUX_DIFF_EZ 1.6
    #define TAUX_DIFF_NORMAL 1.9
    #define TAUX_DIFF_HARD 2.3

    #define TAUX_BONUS 2
    #define TAUX_OBSTACLE 2.3

    #define BASE_ENERGY 2       //
    #define GAIN_ENERGY 5       //  Les constantes d'energie doivent être très inferieur au taille de map
    #define LOST_ENERGY 5       //  
    #define STEP_ENERGY 1       //

    #define REP_CHARACTER 'P'
    #define REP_BONUS1 'b'
    #define REP_BONUS2 'B'
    #define REP_OBSTACLE1 'o'
    #define REP_OBSTACLE2 'O'
    #define REP_VOID '0'
    #define REP_END 'D'
    #define REP_DEFAULT 'X'
    #define REP_UP '1'
    #define REP_DOWN '2'
    #define REP_LEFT '3'
    #define REP_RIGHT '4'
    #define REP_UPLEFT '5'
    #define REP_UPRIGHT '6'
    #define REP_DOWNLEFT '7'
    #define REP_DOWNRIGHT '8'
    #define REP_DOT '.'


    #define BONUS_COOKIE "\U0001f36a"
    #define BONUS_APPLE "\U0001f34e"
    #define CHARACTERE "\U0001f57a"
    #define OBSTACLE_TREE "\U0001f384"
    #define OBSTACLE_BEE "\U0001f41d"
    #define VOID "  "
    #define END "\U0001f3c1"
    #define START "\U0001F43e"
    #define ERROR "\U0001F232"
    #define DOT "."


    #define DOWNBAR "\uff3f"
    #define UPBAR "\uffe3"
    #define SIDEBAR "|"

    #define UP_ARROW "\U00002191"
    #define DOWN_ARROW "\U00002193"
    #define LEFT_ARROW "\U00002190"
    #define RIGHT_ARROW "\U00002192"
    #define UP_LEFT_ARROW "\U00002196"
    #define UP_RIGHT_ARROW "\U00002197"
    #define DOWN_LEFT_ARROW "\U00002199"
    #define DOWN_RIGHT_ARROW "\U00002198"
    #define STEP_BACK_ICON "\U000027f2"
    #define SAVE_ICON "\U0001F6AA"
    #define ENTER_ICON "\U00002386"


    #define UP 122
    #define DOWN 120
    #define LEFT 113
    #define RIGHT 100
    #define UP_LEFT 97
    #define UP_RIGHT 101
    #define DOWN_LEFT 119
    #define DOWN_RIGHT 99
    #define STEP_BACK 114
    #define LEAVE 112
    #define LEAVE_WITHOUT_SAVE 108
    #define ENTER 10

    #define MAJ_UP 90
    #define MAJ_DOWN 88
    #define MAJ_LEFT 81
    #define MAJ_RIGHT 68
    #define MAJ_UP_LEFT 65
    #define MAJ_UP_RIGHT 69
    #define MAJ_DOWN_LEFT 87
    #define MAJ_DOWN_RIGHT 67
    #define MAJ_STEP_BACK 82
    #define MAJ_LEAVE 80
    #define MAJ_LEAVE_WITHOUT_SAVE 76

    #define MAX_DISTANCE 9

    #define CURRENT_GAME_CSV "data/CurrentGame.csv"
    #define HISTORY_CSV "data/History.csv"
    #define SAVE_CSV "data/Save.csv"

    #define SLOW_SPEED 35
    #define NORMAL_SPEED 25
    #define FAST_SPEED 15

#endif
