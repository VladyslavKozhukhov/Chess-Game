#ifndef PIECE_H_
#define PIECE_H_
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#define MAX_LEN 1024
#define NONE_PIECE '_'
#define TIE_SYMBOL '-'
#define GAME_SPAN 4
#define GAME_OVER 1
#define GAMECONTINUE 0
#define COLUMNS 8
#define TWO_PLAYERS_MODE 2
#define ONE_PLAYER_MODE 1
#define PLAYER_1 'V'
#define PLAYER_2 'D'
#define WHITE 1
#define BLACK 0
#define ROWS 8



typedef struct {
	int x,y;
	char player;
	char type;
	int color;
	bool alive;
	bool moved;
}Piece;

Piece* createPiece(int x,int y,char player,char type,int color);

void destroyPiece(Piece* piece);
int setPiece(Piece* piece,int x,int y,char player,char type,int color,bool alive,bool moved,int castle);
Piece* CopyPiece(Piece* piece);
bool isPieceMoved(Piece* piece);
void movePiece(Piece* piece,int i,int j);
char getPiecePrint(Piece* piece);
void printPiece(Piece* piece);
char* getPieceName(Piece* piece);
void printPiece(Piece* piece);
int setPieceType(Piece* piece,char type);
int setPieceColor(Piece* piece,int color);
int getPieceScore(Piece* piece);
bool isPieceAlive(Piece* piece);


#endif /* PIECE_H_ */
