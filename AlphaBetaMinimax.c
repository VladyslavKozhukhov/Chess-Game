#include "AlphaBetaMinimax.h"

int gamescore(Game* game,char first){
	int p1sum=0;
	int p2sum=0;
	int i;
	for(i=0;i<game->player1->nump;i++){
		p1sum+=getPieceScore(game->player1->pieces[i]);
	}
	for(i=0;i<game->player2->nump;i++){
		p2sum+=getPieceScore(game->player2->pieces[i]);
	}
	if(first!=PLAYER_2){
		return p1sum-p2sum;
	}
	else{
		return p2sum-p1sum;
	}
}
Move chooseBestMove(Game* game,int depth){
	int alpha=INT_MIN;
	int beta=INT_MAX;
	int i,j;
	bool st=true;
	Player* cur=gameGetCurPlayer(game);
	char first=cur->symbol;
	Move bestmove;
	setMovePiece(&bestmove,1,1,1,2);
	bestmove.dead=false;
	bestmove.eval=alpha;
	for(i=cur->nump-1;i>=0;i--){
		Piece* piece =cur->pieces[i];
		if(piece->alive==true){
			ArrayList* moves=getMvs(game,piece);
			int ammount=arrayListSize(moves);
			for(j=0;j<ammount;j++){
				Move littlemove=arrayListGetAt(moves,j);
				gameSetMoveAux(game,&littlemove);
				changeTurn(game);
				littlemove.eval=alphabeta(game,bestmove.eval,beta,0,first,depth-1);
				changeTurn(game);
				undoLastMoveAux(game,&littlemove);
				if(littlemove.eval>bestmove.eval){
					bestmove=littlemove;
				}
				//if(littlemove.eatenpieces->type=="m"){
				//	int i =rand();
				//	if(i%2)
				//		bestmove=littlemove;


			//	}
			}
			arrayListDestroy(moves);
		}
	}
	return bestmove;
}
int alphabeta(Game* game,int alpha,int beta,int max_player,char first,int depth){
	Player* cur=gameGetCurPlayer(game);
	int move;
	CHESSMESSAGE message;
	message=checkWinnerOrTie(game);
	if(message==CHECKMATE){
		int score=gamescore(game,first);
		cur->king->alive=true;
		return score;
	}
	else if(message==TIE||depth==0){
		return gamescore(game,first);
	}
	else if(max_player==1){
		move=alpha;
		int j;
		int i;
		for( i=0;i<cur->nump;i++){
			Piece* piece =cur->pieces[i];
			if(piece->alive==true){
				ArrayList* moves=getMvs(game,piece);
				int numberofmoves=arrayListSize(moves);
				for(j=0;j<numberofmoves;j++){
					Move childmove=arrayListGetAt(moves,j);
					gameSetMoveAux(game,&childmove);
					changeTurn(game);
					childmove.eval=alphabeta(game,move,beta,0,first,depth-1);
					changeTurn(game);
					undoLastMoveAux(game,&childmove);
					move=max(move,childmove.eval);
					if(beta<=move){
						arrayListDestroy(moves);
						return move;
					}
				}
				arrayListDestroy(moves);
			}
		}
	}
	else{int i;
		int j;
		move=beta;
		for(i=0;i<cur->nump;i++){
			Piece* piece =cur->pieces[i];
			if(piece->alive==true){
				ArrayList* moves=getMvs(game,piece);
				int numberofmoves=arrayListSize(moves);
				for(j=0;j<numberofmoves;j++){
					Move childmove=arrayListGetAt(moves,j);
					gameSetMoveAux(game,&childmove);
					changeTurn(game);
					childmove.eval=alphabeta(game,alpha,move,1,first,depth-1);
					changeTurn(game);
					undoLastMoveAux(game,&childmove);
					move=min(move,childmove.eval);
					if(move<=alpha){
						arrayListDestroy(moves);
						return move;
					}
				}
				arrayListDestroy(moves);
			}
		}
	}
	return move;
}
int max(int x,int y){
	if(x>y){

		return x;
	}
	if(x==y){
		int surp=rand();
		if(surp%2)
			return y;
		else
			return x;
	}
	return y;
}
int min(int x, int y){
	if(x<y){
		return x;
	}
	if(x==y){
			int surp=rand();
			if(surp%2)
				return x;
			else
				return y;
		}
	return y;
}


