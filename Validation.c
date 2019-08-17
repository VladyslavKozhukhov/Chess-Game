

#include "Validation.h"

bool validMoveRook(Game* game,Move move){
	int n;
	if(move.yf!=move.jt && move.xf!=move.it){
		return false;
	}
	if(move.yf==move.jt && move.xf!=move.it){//left/right
		if(move.xf>move.it){//moves left
			for(n=(move.xf-1);n>=move.it+1;n--){
				if(game->gameBoard[move.yf][n]!=NULL){
					return false;
				}
			}
		}
		else{//moves right
				for(n=move.xf+1;n<=move.it-1;n++){
					if(game->gameBoard[move.yf][n]!=NULL){
						return false;
					}
				}
			}
	}
	else if(move.yf!=move.jt && move.xf==move.it){//up/down
		if(move.yf>move.jt){//moves up
			for(n=(move.yf-1);n>=move.jt+1;n--){
				if(game->gameBoard[n][move.xf]!=NULL){
					return false;
				}
			}
		}
		else{//moves down
				for(n=move.yf+1; n<=move.jt-1; n++){
					if(game->gameBoard[n][move.xf]!=NULL){
						return false;
					}
				}
			}
	}
	return true;
}
bool validMoveBishop(Game* game,Move move){
	int n;
	if(move.yf>move.jt&&move.xf<move.it){//up right
		n=1;
		while(indexIsValid(move.xf+n,move.yf-n)){
			if(move.yf-n==move.jt&&move.xf+n==move.it){
				return true;
			}
			else if(game->gameBoard[move.yf-n][move.xf+n]!=NULL){
				return false;
			}
			n++;
		}
		return false;
	}
	else if(move.yf>move.jt&&move.xf>move.it){//up left
		n=1;
		while(indexIsValid(move.xf-n,move.yf-n)){
			if(move.yf-n==move.jt&&move.xf-n==move.it){
				return true;
			}
			else if(game->gameBoard[move.yf-n][move.xf-n]!=NULL){
				return false;
			}
			n++;
		}
		return false;
	}
	else if(move.yf<move.jt&&move.xf<move.it){//down right
		n=1;
		while(indexIsValid(move.xf+n,move.yf+n)){
			if(move.yf+n==move.jt&&move.xf+n==move.it){
				return true;
			}
			else if(game->gameBoard[move.yf+n][move.xf+n]!=NULL){
				return false;
			}
			n++;
		}
		return false;
	}
	else if(move.yf<move.jt&&move.xf>move.it){//down left
		n=1;
		while(indexIsValid(move.xf-n,move.yf+n)){
			if(move.yf+n==move.jt&&move.xf-n==move.it){
				return true;
			}
			else if(game->gameBoard[move.yf+n][move.xf-n]!=NULL){
				return false;
			}
			n++;
		}
		return false;
	}
	return false;
}
bool validMoveKnight(Game* game,Move move){
	if((move.yf+1==move.jt)&&((move.xf+2==move.it)||(move.xf-2==move.it))){
		return true;
	}
	else if((move.yf+2==move.jt)&&((move.xf+1==move.it)||(move.xf-1==move.it))){
		return true;
	}
	else if((move.yf-1==move.jt)&&((move.xf+2==move.it)||(move.xf-2==move.it))){
		return true;
	}
	else if((move.yf-2==move.jt)&&((move.xf+1==move.it)||(move.xf-1==move.it))){
		return true;
	}
	return false;
}
bool validMoveQueen(Game* game,Move move){
	if(validMoveBishop(game,move)||validMoveRook(game,move)){
		return true;
	}
	return false;
}
bool validMoveKing(Game* game,Move move){
	if((move.yf+1==move.jt)&&((move.xf+1==move.it)||(move.xf-1==move.it)||(move.xf==move.it))){//3 options
		return true;
	}
	else if((move.yf==move.jt)&&((move.xf+1==move.it)||(move.xf-1==move.it))){//2 options
		return true;
	}
	else if((move.yf-1==move.jt)&&((move.xf+1==move.it)||(move.xf-1==move.it)||(move.xf==move.it))){//3 options
		return true;
	}
	return false;
}
bool validMovePawn(Game* game,Move move){
	Player* current =gameGetCurPlayer(game);
	if(current->color==WHITE){
		return validMovePawnWhite(game,move);
	}
	else if(current->color==BLACK){
		return validMovePawnBlack(game,move);
	}
	return false;
}
bool validMovePawnBlack(Game* game,Move move){
	char player=game->gameBoard[move.yf][move.xf]->player;
	if(move.jt==move.yf+1&&move.xf==move.it){//doesn't eat
		if(game->gameBoard[move.jt][move.it]==NULL){
			return true;
		}
		else{
			return false;
		}
	}
	else if(move.yf==1&&move.xf==move.it){//pawn can move 2 steps at its first position
		if(move.jt==move.yf+2){
			if(game->gameBoard[move.jt][move.it]==NULL&&game->gameBoard[move.yf+1][move.xf]==NULL){
				return true;
			}
			else{
				return false;
			}
		}
	}
	else{//eats
		if((move.jt==move.yf+1)&&((move.xf+1==move.it)||(move.xf-1==move.it))){
			if(game->gameBoard[move.jt][move.it]!=NULL){
				if(game->gameBoard[move.jt][move.it]->player!=player){
					return true;
				}
				else{
					return false;
				}
			}
		}
	}
	return false;
}
bool validMovePawnWhite(Game* game,Move move){
	char player=game->gameBoard[move.yf][move.xf]->player;
	if(move.jt==move.yf-1&&move.xf==move.it){//doesn't eat
		if(game->gameBoard[move.jt][move.it]==NULL){
			return true;
		}
		else{
			return false;
		}
	}
	else if(move.yf==8-2&&move.xf==move.it){//pawn can move 2 steps at its first position
		if(move.jt==move.yf-2){
			if(game->gameBoard[move.jt][move.it]==NULL&&game->gameBoard[move.yf-1][move.xf]==NULL){
				return true;
			}
			else{
				return false;
			}
		}
	}
	else{//eats
		if((move.jt==move.yf-1)&&((move.xf+1==move.it)||(move.xf-1==move.it))){
			if(game->gameBoard[move.jt][move.it]!=NULL){
				if(game->gameBoard[move.jt][move.it]->player!=player){
					return true;
				}
				else{
					return false;
				}
			}
		}
	}
	return false;
}
