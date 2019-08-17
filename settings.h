#ifndef SETTINGS_H_
#define SETTINGS_H_


#include "Piece.h"
typedef struct Settings
{
    unsigned int gameMode;
    unsigned int difficulty;
  unsigned int userColor;
  int Xflag;//GUI_Settings
  bool selectLVL;
  bool 	selectColor;
  bool	selectMode;


} Settings;

Settings initSettings();
void setSettings(Settings* set,int level,int mode,int color);
void setColour (Settings* set, unsigned int col);
void resetSettings (Settings* set);
void printSettings (Settings* set);
void SetDifficulty(Settings* set, unsigned int dif);
void SetMode (Settings* set, unsigned int mode);
int getGameLevel(Settings* set);
int getGameMode(Settings* set);
int getGameColor(Settings* set);

#endif //CHESS_SETTINGS_H
