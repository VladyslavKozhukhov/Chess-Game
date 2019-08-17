/*
 * CON_MoveP.c
 *
 *  Created on: Sep 29, 2017
 *      Author: Vlad
 */
#include"Get_MoveP.h"



ArrayList* getMvBishop(Game* game,Piece* piece){
	int i;
	ArrayList* mv=arrayListCreate(13);
	for(i=0;i<8;i++){
		updateMove(game,mv,piece,piece->x,piece->y,piece->x-i,piece->y-i);
		updateMove(game,mv,piece,piece->x,piece->y,piece->x+i,piece->y-i);
		updateMove(game,mv,piece,piece->x,piece->y,piece->x-i,piece->y+i);
		updateMove(game,mv,piece,piece->x,piece->y,piece->x+i,piece->y+i);

	}
	return mv;
}
ArrayList* getMvKing(Game* game,Piece* piece){
	ArrayList* mv=arrayListCreate(8);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x-1,piece->y+1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x-1,piece->y);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x-1,piece->y-1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x,piece->y-1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x,piece->y+1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x+1,piece->y+1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x+1,piece->y);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x+1,piece->y-1);

	return mv;
}
ArrayList* getMvKnight(Game* game,Piece* piece){
	ArrayList* mv=arrayListCreate(8);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x-2,piece->y-1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x+1,piece->y+2);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x+1,piece->y-2);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x-1,piece->y+2);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x-1,piece->y-2);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x+2,piece->y+1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x+2,piece->y-1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x-2,piece->y+1);

	return mv;
}
ArrayList* getMvQueen(Game* game,Piece* piece){
	int i;
	ArrayList* mv=arrayListCreate(27);
	ArrayList* mvAsRook=getMvRook(game,piece);
	ArrayList* mvAsBishop=getMvBishop(game,piece);
	if(mvAsRook!=NULL){
		for(i=0;i<arrayListSize(mvAsRook);i++){
			arrayListAddLast(mv,arrayListGetAt(mvAsRook,i));
		}
	}
	arrayListDestroy(mvAsRook);
	if(mvAsBishop!=NULL){
		for(i=0;i<arrayListSize(mvAsBishop);i++){
			arrayListAddLast(mv,arrayListGetAt(mvAsBishop,i));
		}
	}
	arrayListDestroy(mvAsBishop);
	return mv;
}

ArrayList* getMvPawn(Game* game,Piece* piece){
	ArrayList* mv=arrayListCreate(4);
	Player* player =gameGetCurPlayer(game);
	if(player->color==WHITE){
		getMvPawnWhite(game,mv,piece);
	}
	else if(player->color==BLACK){
		getMvPawnBlack(game,mv,piece);
	}
	return mv;
}
ArrayList* getMvPawnWhite(Game* game,ArrayList* mv,Piece* piece){
	updateMove(game,mv,piece,piece->x,piece->y,piece->x,piece->y-1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x,piece->y-2);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x+1,piece->y-1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x-1,piece->y-1);

	return mv;
}
ArrayList* getMvPawnBlack(Game* game,ArrayList* mv,Piece* piece){
	updateMove(game,mv,piece,piece->x,piece->y,piece->x-1,piece->y+1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x,piece->y+1);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x,piece->y+2);
	updateMove(game,mv,piece,piece->x,piece->y,piece->x+1,piece->y+1);

	return mv;
}
ArrayList* getMvRook(Game* game,Piece* piece){
	int i;
	ArrayList* mv=arrayListCreate(14);
	for(i=0;i<8;i++){
		if(piece->x!=i){
			updateMove(game,mv,piece,piece->x,piece->y,i,piece->y);
		}
		if(piece->y!=i){
			updateMove(game,mv,piece,piece->x,piece->y,piece->x,i);
		}
	}

	return mv;
}
ArrayList* getMvs(Game* game,Piece* piece){
	switch(piece->type){
		case('r'):
				return getMvRook(game,piece);
		break;
		case('b'):
				return getMvBishop(game,piece);
		break;
		case('n'):
				return getMvKnight(game,piece);
		break;
		case('q'):
				return getMvQueen(game,piece);
		break;
		case('k'):
				return getMvKing(game,piece);
		break;
		case('m'):
				return getMvPawn(game,piece);
		break;
		default: return NULL; break;
	}
}
