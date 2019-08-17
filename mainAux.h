#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "Parser.h"



void NewGame();
/*
 * get game status
 */
int GameStatus(Game* game);
/*
 * player turn
 */
int playerTurn(Game* game);
/*
 * ai turn
 */
int computerTurn(Game* game);
/*
 * quit the game
 */
void quitGame(Game* game);
/*
 * restart game
 */
void restartGame(Game* game);
/*
 * move Game
 */
int moveGame(Move move,Game* game);
/*
 * save game
 */
int saveGame(Game* game,char* filename);
/*
 * load game
 */
Game* loadGame(char* fileName);
/*
 * undogame
 */
int undoGame(Game* game);

#endif /* MAINAUX_H_ */
