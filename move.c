#include "move.h"
int setMovePiece(Move* move,int xf,int yf,int it,int jt){
	move->xf=xf;move->jt=jt;move->it=it;move->yf=yf;
	return 1;
}

bool isEatMove(Move* move){
	return move->dead;
}

int IfEateanMove(Move move){
	if(move.dead==true){
		return 2;
	}
	return 0;
}
