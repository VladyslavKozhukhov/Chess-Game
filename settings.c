#include "settings.h"




Settings initSettings()
{
    Settings set ;
    set.gameMode = 1;
    set.difficulty = 2;
    set.userColor = WHITE;
    setSettings(&set,2,1,1);

    set.selectLVL=false;
    set.selectColor=false;
    set.selectMode=false;
    set.Xflag=1;
    return set;
}


void SetDifficulty(Settings* set, unsigned int dif)
{
	set->difficulty = dif;
}

void SetMode (Settings* set, unsigned int mode)
{
	set->gameMode = mode;
    if (mode ==1)
    {
        printf("Game mode is set to 1 player");
    }
    else{
        printf("Game mode is set to 2 players");
    }

}


void setColour (Settings* set, unsigned int col)
{
	set->userColor = col;
}

void resetSettings (Settings* set)
{
   set->userColor = WHITE;
   set->gameMode = 1;
    set->difficulty = 2;
}

void printSettings (Settings* set)
{
    printf("SETTINGS:\n");
    if (set->gameMode ==1)
    {
        printf("GAME MODE: 1\n");
    }
    else
    {
        printf("GAME MODE: 2\n");
        printf("DIFFICULTY_LVL: %d",set->difficulty);
        if (set->userColor == WHITE)
        {
            printf("USER_CLR: WHITE");
        }
        else
        {
            printf("USER_CLR: BLACK");
        }
    }
}

void setSettings(Settings* set,int lvl,int mode,int color){
	set->difficulty=lvl;
	set->gameMode=mode;
	set->userColor=color;

}


int getGameLevel(Settings* set){
    return set->difficulty;
}
int getGameMode(Settings* set){
    return set->gameMode;
}
int getGameColor(Settings* set){
    return set->userColor;
}

