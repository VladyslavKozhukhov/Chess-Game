
#ifndef VALIDATION_H_
#define VALIDATION_H_
#include "stdbool.h"
#include "Game.h"

bool validMoveRook(Game* game,Move move);
bool validMoveBishop(Game* game,Move move);
bool validMoveKnight(Game* game,Move move);
bool validMoveQueen(Game* game,Move move);
bool validMoveKing(Game* game,Move move);
bool validMovePawn(Game* game,Move move);
bool validMovePawnBlack(Game* game,Move move);
bool validMovePawnWhite(Game* game,Move move);

#endif /* VALIDATION_H_ */
