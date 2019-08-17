#ifndef PLAYER_H
#define PLAYER_H
#include "Piece.h"
typedef struct {
	Piece* king;
	Piece* pieces[16];
	int nump;
	int color;
	char symbol;
}Player;





Player* creatPlayer(char symbol,int color);
Player* initPlayer(Player* player);
Player* copyPlayer(Player* player);
void destroyPlayer(Player* player);
int setColorPlayer(Player* player,int color);
int setSymbolPlayer(Player* player,char symbol);
int getColorPlayer(Player* player);
char getUserSymbol(Player* player);
Piece* getPiecePlayer(Player* player,int index);
Piece* getKingPlayer(Player* player);
Piece* addPiecePlayer(Player* player,int x,int y,char type);
void printPlayer(Player* player);

#endif /* USER_H_ */
