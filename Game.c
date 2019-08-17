#include "Game.h"
Game* gameCreate(int historySize){
	int i,j;
	if(historySize<=0){
		return NULL;
	}
	Game* game=(Game*) malloc(sizeof(Game));
	if(!game){
		gameDestroy(game);
		exit(0);
		return NULL;
	}
	game->curPlayer=PLAYER_1;
	game->history= arrayListCreate(historySize);
	if(!(game->history)){
		gameDestroy(game);
		exit(0);
		return NULL;
	}
	for(i=0;i<COLUMNS;i++){
		for(j=0;j<ROWS;j++){
			game->gameBoard[j][i]=NULL;
		}
	}
	return game;
}
Game* gameInitalize(Game* game,Settings settings){
	int i;
	if(settings.gameMode==2){
		game->set.userColor=1;
	}
	setSettings(&(game->set),settings.difficulty,settings.gameMode,settings.userColor);
	game->player1=(Player*)creatPlayer(PLAYER_1,game->set.userColor);
	game->player2=(Player*)creatPlayer(PLAYER_2,1-game->set.userColor);
	game->player1=initPlayer(game->player1);
	game->player2=initPlayer(game->player2);
	for(i=0;i<16;i++){
		game->gameBoard[game->player1->pieces[i]->y][game->player1->pieces[i]->x]=game->player1->pieces[i];
		game->gameBoard[game->player2->pieces[i]->y][game->player2->pieces[i]->x]=game->player2->pieces[i];
	}
	return game;
}
Game* gameCopy(Game* game){
	int i;
	Game* copy = gameCreate(game->history->maxSize);
	copy->history= arrayListCopy(game->history);
	copy->player1=copyPlayer(game->player1);
	copy->player2=copyPlayer(game->player2);
	copy->set=game->set;
	copy->curPlayer=game->curPlayer;
	for(i=0;i<copy->player1->nump;i++){
		copy->gameBoard[copy->player1->pieces[i]->y][copy->player1->pieces[i]->x]=copy->player1->pieces[i];
	}
	for(i=0;i<copy->player2->nump;i++){
		copy->gameBoard[copy->player2->pieces[i]->y][copy->player2->pieces[i]->x]=copy->player2->pieces[i];
	}
	for(i=game->player1->nump;i<16;i++){
		game->player2->pieces[i]=NULL;
	}
	for(i=game->player2->nump;i<16;i++){
		game->player2->pieces[i]=NULL;
	}
	return copy;
}
void gameDestroy(Game* game){
	if(!game){
		return;
	}
	destroyPlayer(game->player1);
	destroyPlayer(game->player2);
	arrayListDestroy(game->history);
	free(game);
	return;
}
CHESSMESSAGE gameSetMove(Game* game, Move move){
	if (arrayListIsFull(game->history)){
		if(arrayListRemoveFirst(game->history)==ARRAY_LIST_INVALID_ARGUMENT){
			return INVALID_MOVE;
		}
	}
	gameSetMoveAux(game,&move);
	arrayListAddLast(game->history,move);
	return SUCCESS;
}
int gameSetMoveAux(Game* game,Move* move){
	move->dead=false;
	move->eatenpieces=NULL;

		if(game->gameBoard[move->jt][move->it]!=NULL){
			move->eatenpieces=game->gameBoard[move->jt][move->it];
			move->dead=true;
			move->eatenpieces->alive=false;
		}
	game->gameBoard[move->jt][move->it]=game->gameBoard[move->yf][move->xf];
	game->gameBoard[move->yf][move->xf]=NULL;
	movePiece(game->gameBoard[move->jt][move->it], move->it,move->jt);
	return 1;
}
bool gameIsValidMove(Game* game,Move* move){
	if(!indexIsValid(move->it,move->jt)||!indexIsValid(move->yf,move->xf)){
		return false;
	}
	if(game->gameBoard[move->yf][move->xf]==NULL){
		return false;
	}
	if(game->gameBoard[move->yf][move->xf]->color!=gameGetCurPlayer(game)->color){
		return false;
	}
	if(game->gameBoard[move->jt][move->it]!=NULL){
		if(game->gameBoard[move->yf][move->xf]->color==game->gameBoard[move->jt][move->it]->color){
			return false;
		}
	}
	bool pseudolegal=false;
	bool legal=false;
	pseudolegal=gameFakeMove(game, *move);

	if(pseudolegal==true){//pseudo legal move now needs to check if the player's king isn't threatened
		gameSetMoveAux(game,move);//moves the piece
		if(gameCheck(game)==false){//legal move(the king is not threatened)
			legal=true;
		}
		undoLastMoveAux(game,move);
	}
	return legal;
}
bool gameFakeMove(Game* game, Move move){
	bool fakemove=false;
	switch(game->gameBoard[move.yf][move.xf]->type){
		case('r'):
				fakemove=validMoveRook(game,move);
		break;
		case('b'):
				fakemove=validMoveBishop(game,move);
		break;
		case('n'):
				fakemove=validMoveKnight(game,move);
		break;
		case('q'):
				fakemove=validMoveQueen(game,move);
		break;
		case('k'):
				fakemove=validMoveKing(game,move);
		break;
		case('m'):
				fakemove=validMovePawn(game,move);
		break;
		default: fakemove=false; break;
	}
	return fakemove;
}
CHESSMESSAGE gameUndoPrevMove(Game* game){
	if(!game){

		return INVALID_ARGUMENT;
	}
	if(arrayListIsEmpty(game->history)){
		return NO_HISTORY;
	}
	undoLastMove(game);
	return SUCCESS;
}
void undoLastMove(Game* game){
	Move move = arrayListGetLast(game->history);
	ARRAY_LIST_MESSAGE message=arrayListRemoveLast(game->history);
	if(message==ARRAY_LIST_SUCCESS){
		undoLastMoveAux(game,&move);
		printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",game->gameBoard[move.yf][move.xf]->color?"white":"black",8-move.jt,move.it+CHANGE_FOR_PRINT,8-move.yf,move.xf+CHANGE_FOR_PRINT);
	}
	else if(message==ARRAY_LIST_EMPTY){
		printf("Empty history, move cannot be undone\n");
	}
}
void undoLastMoveAux(Game* game,Move* move){

		if(game->gameBoard[move->jt][move->it]==NULL){
			printGameBoard(game);
			printf("something went wrong - undo last move aux\n");
		}
		game->gameBoard[move->yf][move->xf]=game->gameBoard[move->jt][move->it];
		movePiece(game->gameBoard[move->yf][move->xf], move->xf,move->yf);
		game->gameBoard[move->jt][move->it]=NULL;
		if(move->dead==true){
			move->eatenpieces->alive=true;
			game->gameBoard[move->jt][move->it]=move->eatenpieces;
		}

}

void changeTurn(Game* game){
	if(game->curPlayer==PLAYER_1){
		game->curPlayer=PLAYER_2;
	}
	else{
		game->curPlayer=PLAYER_1;
	}
}
CHESSMESSAGE printGameBoard(Game* game){
	int i,j;
	if(!game){
		return INVALID_ARGUMENT;
	}
	for(j=0;j<8;j++){
		printf("%d|",8-j);
		for(i=0;i<8;i++){
			printf(" %c",getPiecePrint(game->gameBoard[j][i]));
		}
		printf(" |\n");
	}
	printf("  ");
	for(i=1;i<=(2*8+1);i++){
		printf("-");
	}
	printf("\n   ");
	for(i=1;i<=8;i++){
		printf("%c ",i+64);
	}
	printf("\n");
	return SUCCESS;
}
Player* gameGetCurPlayer(Game* game){
	if(!game){

		return NULL;
	}
	else if(game->curPlayer==PLAYER_1){
		return game->player1;
	}
	return game->player2;
}
CHESSMESSAGE checkWinnerOrTie(Game* game){
	if(gameCheck(game)){
		if(gameCheckmate(game)){
			return CHECKMATE;
		}
		return CHECK;
	}
	if(gameTie(game)){
		return TIE;
	}
	return CONTINUE;//the game continues
}

void updateMove(Game* game,ArrayList* moves,Piece* piece,int x,int y,int i,int j){
	Move move;
	setMovePiece(&move,x,y,i,j);
	insertMoves(game,move,moves);
}
void insertMoves(Game* game,Move move,ArrayList* moves){
	bool legal;
	legal=gameIsValidMove(game,&move);
	if(legal==true){
		arrayListAddLast(moves,move);
	}
}
bool gameCheck(Game* game){
	int i,j;
	Player* player=gameGetCurPlayer(game);
	Piece* kingthreat;
	i=player->king->x;
	j=player->king->y;
	kingthreat=gameThreat(game,i,j);
	if(kingthreat!=NULL){
		return true;
	}
	return false;
}
Piece* gameThreat(Game* game,int i,int j){//i,j the threatened piece
	Piece* threat;
	threat=threatByBishop(game,i,j,'b');
	if(threat!=NULL){
		return threat;
	}
	threat=threatByRook(game,i,j,'r');
	if(threat!=NULL){
		return threat;
	}
	threat=threatByKnight(game,i,j,'n');
	if(threat!=NULL){
		return threat;
	}
	threat=threatByPawn(game,i,j,'m');
	if(threat!=NULL){
		return threat;
	}
	threat=threatByQueen(game,i,j,'q');
	if(threat!=NULL){
		return threat;
	}
	threat=threatByKing(game,i,j,'k');
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatByPawn(Game* game,int i,int j,char type){
	Piece* threat;
	Player* player =gameGetCurPlayer(game);
	if(player->color==WHITE){
		threat=threatByBlackPawn(game,i,j,'m');
		if(threat!=NULL){
			return threat;
		}
	}
	else if(player->color==BLACK){
		threat=threatByWhitePawn(game,i,j,'m');
		if(threat!=NULL){
			return threat;
		}
	}
	return NULL;
}
Piece* threatByWhitePawn(Game* game,int i,int j,char type){
	Piece* threat=findThreatBasic(game,i,j,-1,1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,1,1,type);
	return threat;
}
Piece* threatByBlackPawn(Game* game,int i,int j,char type){
	Piece* threat=findThreatBasic(game,i,j,-1,-1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,1,-1,type);
	return threat;
}
Piece* threatByBishop(Game* game,int i,int j,char type){
	Piece* threat;
	threat=threatDiagToLeftUpBishop(game,i,j,type);
	if(threat!=NULL){
		return threat;
	}
	threat=threatDiagToRightUpBishop(game,i,j,type);
	if(threat!=NULL){
		return threat;
	}
	threat=threatDiagToLeftDownBishop(game,i,j,type);
	if(threat!=NULL){
		return threat;
	}
	threat=threatDiagToRightDownBishop(game,i,j,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatDiagToLeftUpBishop(Game* game,int i,int j,char type){
	Piece* threat=findThreat(game,i,j,-1,-1,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatDiagToRightUpBishop(Game* game,int i,int j,char type){
	Piece* threat=findThreat(game,i,j,1,-1,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatDiagToLeftDownBishop(Game* game,int i,int j,char type){
	Piece* threat=findThreat(game,i,j,-1,1,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatDiagToRightDownBishop(Game* game,int i,int j,char type){
	Piece* threat=findThreat(game,i,j,1,1,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatByKnight(Game* game,int i,int j,char type){
	Piece* threat=findThreatBasic(game,i,j,1,-2,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,2,-1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,1,2,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,-1,2,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,2,1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,-2,1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,-2,-1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,-1,-2,type);
	return threat;
}
Piece* threatByRook(Game* game,int i,int j,char type){
	Piece* threat;
	threat=threatUpRook(game,i,j,type);
	if(threat!=NULL){
		return threat;
	}
	threat=threatDownRook(game,i,j,type);
	if(threat!=NULL){
		return threat;
	}
	threat=threatLeftRook(game,i,j,type);
	if(threat!=NULL){
		return threat;
	}
	threat=threatRightRook(game,i,j,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatUpRook(Game* game,int i,int j,char type){
	Piece* threat=findThreat(game,i,j,0,-1,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatDownRook(Game* game,int i,int j,char type){
	Piece* threat=findThreat(game,i,j,0,1,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatLeftRook(Game* game,int i,int j,char type){
	Piece* threat=findThreat(game,i,j,-1,0,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatRightRook(Game* game,int i,int j,char type){
	Piece* threat=findThreat(game,i,j,1,0,type);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatByQueen(Game* game,int i,int j,char type){
	Piece* threat;
	threat=threatByRook(game,i,j,'q');
	if(threat!=NULL){
		return threat;
	}
	threat=threatByBishop(game,i,j,'q');
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
Piece* threatByKing(Game* game,int i,int j,char type){
	Piece* threat=findThreatBasic(game,i,j,1,1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,1,0,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,1,-1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,0,-1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,-1,-1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,-1,0,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,-1,1,type);
	if(threat!=NULL){
		return threat;
	}
	threat=findThreatBasic(game,i,j,0,1,type);
	return threat;
}
Piece* threatBasic(Game* game,Move move){//x,y threat - i,j target
	if(indexIsValid(move.xf,move.yf)){
		if(game->gameBoard[move.yf][move.xf]!=NULL){//there is a piece in there
			if(game->gameBoard[move.yf][move.xf]->player!=game->curPlayer){//piece of the opponent
				if(game->gameBoard[move.jt][move.it]!=NULL&&game->gameBoard[move.jt][move.it]->type=='k'){//direct threat on the king
					changeTurn(game);
					if(gameFakeMove(game,move)==true){
						changeTurn(game);
						return game->gameBoard[move.yf][move.xf];
					}
					changeTurn(game);
				}
				else{
					changeTurn(game);
					if(gameIsValidMove(game,&move)==true){//valid move
						changeTurn(game);
						return game->gameBoard[move.yf][move.xf];
					}
					changeTurn(game);
				}
			}
		}
	}
	return NULL;
}
Piece* findThreat(Game* game,int i,int j,int sum1,int sum2,char type){//sum1=how much to add to move.x, sum2=how much to add to move.y
	Move move;
	int k;
	Piece* threat;
	setMovePiece(&move,i+sum1,j+sum2,i,j);
	for(k=0;k<8;k++){
		if(indexIsValid(move.xf,move.yf)==true){
			threat=threatBasic(game,move);
			if(threat!=NULL){
				return threat;
			}
		}
		move.xf+=sum1;
		move.yf+=sum2;
	}
	return NULL;
}
Piece* findThreatBasic(Game* game,int i,int j,int sum1,int sum2,char type){//sum1=how much to add to move.x, sum2=how much to add to move.y
	Move move;
	Piece* threat;
	setMovePiece(&move,i+sum1,j+sum2,i,j);
	threat=threatBasic(game,move);
	if(threat!=NULL){
		return threat;
	}
	return NULL;
}
bool gameCheckmate(Game* game){
	Player* current=gameGetCurPlayer(game);
	Piece* kingthreat=gameThreat(game,current->king->x,current->king->y);
	if(kingthreat==NULL){
		return false;
	}
	Piece* kingthreat2;
	Piece* piecethreat;
	bool canblock=false;
	ArrayList* kingmoves=getMvKing(game,current->king);
	int numberofkingsmoves=kingmoves->actualSize;
	arrayListDestroy(kingmoves);
	if(numberofkingsmoves>0){//king can escape the check
		return false;
	}
	//there is at least one threat on the king and he can't move
	game->gameBoard[kingthreat->y][kingthreat->x]=NULL;
	kingthreat2=gameThreat(game,current->king->x,current->king->y);
	game->gameBoard[kingthreat->y][kingthreat->x]=kingthreat;
	if(kingthreat2!=NULL){//more than one threat -->checkmate
		current->king->alive=false;
		return true;
	}
	//only one threat
	changeTurn(game);
	piecethreat=gameThreat(game,kingthreat->x,kingthreat->y);
	if(piecethreat!=NULL){//can eat the threat
		changeTurn(game);
		return false;
	}
	changeTurn(game);
	canblock=gameBlockThreat(game,current->king,kingthreat);
	if(canblock==true){
		return false;
	}
	current->king->alive=false;
	return true;
}
bool gameBlockThreat(Game* game,Piece* king,Piece* kingthreat){
	switch(kingthreat->type){
		case('r'): return gameBlockThreatRook(game,king,kingthreat);break;
		case('b'): return gameBlockThreatBishop(game,king,kingthreat);break;
		case('q'): return gameBlockThreatQueen(game,king,kingthreat);break;
		default: return false; break;//you can't block the knight or the pawn
	}
}
bool gameBlockThreatBishop(Game* game,Piece* king,Piece* kingthreat){
	int i;
	changeTurn(game);
	bool canblock=false;
	if(king->x<kingthreat->x&&king->y>kingthreat->y){//check from up/right
		for(i=1;i<king->y-kingthreat->y;i++){
			if(gameThreat(game,king->x+i,king->y-i)!=NULL){
				canblock=true;
				break;
			}
		}
	}
	else if(king->x>kingthreat->x&&king->y>kingthreat->y){//check from up/left
		for(i=1;i<=king->y-kingthreat->y;i++){
			if(gameThreat(game,king->x-i,king->y-i)!=NULL){
				canblock=true;
				break;
			}
		}
	}
	else if(king->x<kingthreat->x&&king->y<kingthreat->y){//check from down/right
		for(i=1;i<=kingthreat->y-king->y;i++){
			if(gameThreat(game,king->x+i,king->y+i)!=NULL){
				canblock=true;
				break;
			}
		}
	}
	else if(king->x>kingthreat->x&&king->y<kingthreat->y){//check from down/left
		for(i=1;i<=kingthreat->y-king->y;i++){
			if(gameThreat(game,king->x-i,king->y+i)!=NULL){
				canblock=true;
				break;
			}
		}
	}
	changeTurn(game);
	return canblock;
}
bool gameBlockThreatRook(Game* game,Piece* king,Piece* kingthreat){
	int i;
	changeTurn(game);
	bool canblock=false;
	if(king->x==kingthreat->x&&king->y>kingthreat->y){//check from up
		for(i=king->y-1;i>=kingthreat->y;i--){
			if(gameThreat(game,king->x,i)!=NULL){
				canblock=true;
				break;
			}
		}
	}
	else if(king->x==kingthreat->x&&king->y<kingthreat->y){//check from down
		for(i=king->y+1;i<=kingthreat->y;i++){
			if(gameThreat(game,king->x,i)!=NULL){
				canblock=true;
				break;
			}
		}
	}
	else if(king->x>kingthreat->x&&king->y==kingthreat->y){//check from left
		for(i=king->x-1;i>=kingthreat->x;i--){
			if(gameThreat(game,i,king->y)!=NULL){
				canblock=true;
				break;
			}
		}
	}
	else if(king->x<kingthreat->x&&king->y==kingthreat->y){//check from right
		for(i=king->x+1;i<=kingthreat->x;i++){
			if(gameThreat(game,i,king->y)!=NULL){
				canblock=true;
				break;
			}
		}
	}
	changeTurn(game);
	return canblock;
}
bool gameBlockThreatQueen(Game* game,Piece* king,Piece* kingthreat){
	if(gameBlockThreatRook(game,king,kingthreat)||gameBlockThreatBishop(game,king,kingthreat)){
		return true;
	}
	return false;
}
bool gameTie(Game* game){
	int i;
	ArrayList* moves;
	int numberofmoves;
	Player* player=gameGetCurPlayer(game);
	for(i=0;i<player->nump;i++){
		if(player->pieces[i]->alive==true&&player->pieces[i]->type!='k'){
			moves=getMvs(game,player->pieces[i]);
			numberofmoves=arrayListSize(moves);
			arrayListDestroy(moves);
			if(numberofmoves!=0){
				return false;
			}
		}
	}
	return true;
}
bool indexIsValid(int x,int y){
	if(y>=0&&y<=8-1&&x>=0&&x<=8-1){
		return true;
	}
	return false;
}
