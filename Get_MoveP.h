

#ifndef GET_MOVEP_H_
#define CON_MOVEP_H_
#include "Game.h"

/*
 * Moves of Pieces
 */
ArrayList* getMvRook(Game* game,Piece* piece);
ArrayList* getMvBishop(Game* game,Piece* piece);
ArrayList* getMvKnight(Game* game,Piece* piece);
ArrayList* getMvQueen(Game* game,Piece* piece);
ArrayList* getMvKing(Game* game,Piece* piece);
ArrayList* getMvPawn(Game* game,Piece* piece);
ArrayList* getMvPawnWhite(Game* game,ArrayList* moves,Piece* piece);
ArrayList* getMvPawnBlack(Game* game,ArrayList* moves,Piece* piece);
ArrayList* getMvs(Game* game,Piece* piece);

#endif /* GET_MOVEP_H_ */
