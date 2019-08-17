#include "Piece.h"
Piece* createPiece(int x,int y,char player,char type,int color){
	Piece* piece=(Piece*)malloc(sizeof(Piece));
	if(!piece){
		destroyPiece(piece);
		exit(0);
	}
	piece->type=type;
	piece->alive= true;
	piece->player=player;
	piece->x=x;
	piece->y=y;
	piece->color=color;
	return piece;
}
Piece* CopyPiece(Piece* piece){
	Piece* copy;
	copy->x=piece->x;
	copy->y=piece->y;
	copy->player=piece->player;
	copy->type=piece->type;
	copy->color=piece->color;
	copy->alive=piece->alive;
	copy->moved=piece->moved;
	return copy;
}
void printPiece(Piece* piece){
	printf("the %s at <%d,%c> is %s.\n",getPieceName(piece),ROWS-piece->y,piece->x+65,
			isPieceAlive(piece)?"alive":"dead");
}
void destroyPiece(Piece* piece){
	free(piece);
}
int setPiece(Piece* piece,int x,int y,char player,char type,int color,bool alive,
		bool moved,int castle){
	piece->type=type;
	piece->alive= alive;
	piece->player=player;
	piece->x=x;
	piece->y=y;
	piece->color=color;
	piece->moved=moved;
    return 1;
}
int getPieceScore(Piece* piece){
	if(piece->alive==true){
		switch(piece->type){
			case('k'): return 100;break;
			case('r'): return 5;break;
			case('q'): return 9;break;
			case('b'): return 3;break;
			case('n'): return 3;break;
			case('m'): return 1;break;
			default: return 0; break;
		}
	}
	return 0;
}
char* getPieceName(Piece* piece){
	 switch(piece->type){
	        case('q'): if(piece->color==BLACK)
	                return "BlackQueen";
	            else
	                return "WhiteQueen";
	        case('k'): if(piece->color==BLACK)
	                return "BlackKing";
	            else
	                return "WhiteKing";
	        case('r'): if(piece->color==BLACK)
	                return "BlackRook";
	            else
	                return "WhiteRook";
	        case('m'): if(piece->color==BLACK)
	                return "BlackPawn";
	            else
	                return "WhitePawn";
	        case('b'): if(piece->color==BLACK)
	                return "BlackBishop";
	            else
	                return "WhiteBishop";
	        case('n'): if(piece->color==BLACK)
	                return "BlackKnight";
	            else
	                return "WhiteKnight";

	        default: NULL; break;
	    }
	    return NULL;
	}

bool isPieceAlive(Piece* piece){
	return piece->alive;
}
void movePiece(Piece* piece,int i,int j){
	piece->x=i;
	piece->y=j;
}
char getPiecePrint(Piece* piece){
	if(piece==NULL){
		return NONE_PIECE;
	}
	if(piece->color==0){
		return (char)toupper(piece->type);
	}
	return piece->type;
}



