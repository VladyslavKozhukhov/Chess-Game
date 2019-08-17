/*
 * move.h
 *
 *  Created on: Sep 28, 2017
 *      Author: Vlad
 */

#ifndef MOVE_H_
#define MOVE_H_
#include "Player.h"
typedef struct move_VK{
	int xf;
	int yf;
	int it;
	int jt;
	Piece* eatenpieces;
	bool dead;
	int eval;
}Move;
int setMovePiece(Move* move,int xf,int yf,int it,int jt);
bool isEatMove(Move* move);
int IfEateanMove(Move move);

#endif /* MOVE_H_ */
