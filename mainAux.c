#include "mainAux.h"

int GameStatus(Game* game){
	CHESSMESSAGE message=checkWinnerOrTie(game);
	switch(message){
		case(CHECKMATE):
  		  	if(gameGetCurPlayer(game)->color)
  		       	printf("Checkmate! black player wins the game\n");
  		     else
  		        printf("Checkmate! white player wins the game\n");

				gameDestroy(game);break;
				case(TIE):
				if(game->set.gameMode==1&&game->curPlayer==PLAYER_1){
					printf("The game ends in a tie\n"); gameDestroy(game);break;
				}
				else{
					printf("The game is tied\n"); gameDestroy(game);break;
				}
				case(CHECK):
						if(game->set.gameMode==1&&game->curPlayer==PLAYER_1){
							printf("Check!\n");break;
						}
						else{
							if( gameGetCurPlayer(game)->color)
							printf("Check: white King is threatened!\n");
							else
							printf("Check: black King is threatened!\n");
							break;
						}
		default:break;
	}
	if(message==CHECKMATE||message==TIE){
		return GAME_OVER;
	}
	return GAMECONTINUE;
}
int computerTurn(Game* game){
	Move aimove;
	setMovePiece(&aimove,0,0,1,1);
	aimove=chooseBestMove(game,game->set.difficulty);
	moveGame(aimove,game);
	switch(game->gameBoard[aimove.jt][aimove.it]->type){
		case('r'):
				printf("Computer: move rook at <%d,%c> to <%d,%c>\n",8-aimove.yf,(char)(aimove.xf+65),8-aimove.jt,(char)(aimove.it+65));
		break;
		case('b'):
				printf("Computer: move bishop at <%d,%c> to <%d,%c>\n",8-aimove.yf,(char)(aimove.xf+65),8-aimove.jt,(char)(aimove.it+65));
		break;
		case('n'):
				printf("Computer: move knight at <%d,%c> to <%d,%c>\n",8-aimove.yf,(char)(aimove.xf+65),8-aimove.jt,(char)(aimove.it+CHANGE_FOR_PRINT));
		break;
		case('q'):
				printf("Computer: move queen at <%d,%c> to <%d,%c>\n",8-aimove.yf,(char)(aimove.xf+65),8-aimove.jt,(char)(aimove.it+65));
		break;
		case('k'):
				printf("Computer: move king at <%d,%c> to <%d,%c>\n",8-aimove.yf,(char)(aimove.xf+65),8-aimove.jt,(char)(aimove.it+65));
		break;
		case('m'):
				printf("Computer: move pawn at <%d,%c> to <%d,%c>\n",8-aimove.yf,(char)(aimove.xf+65),8-aimove.jt,(char)(aimove.it+65));
		break;
		default:break;
	}
	return 1;
}
void quitGame(Game* game){
	gameDestroy(game);
	printf("Exiting...\n");
	exit(0);
}
void restartGame(Game* game){
	gameDestroy(game);
	printf("Restarting...\n");
	NewGame();
}
void NewGame(){
	Game* game;
	int gameover=0;
	bool loaded=false;
	Settings set;
	set.userColor=1;
	set.difficulty=2;
	set.gameMode=ONE_PLAYER_MODE;
	Command cmd;
	printf("Specify game settings or enter 'start' to begin a game with the current settings:\n");
	cmd=gameSetting(&set);
	if(cmd.cmd==QUIT){
		exit(0);
	}
	while(cmd.cmd!=START){
		if(cmd.cmd==LOAD){
			Game* check;
			check=loadGame(cmd.str);
			if(check==NULL){
				printf("Can not load the game");
			}
			else{
				game=check;
				loaded=true;
				printGameBoard(game);
			}
		}
		if(cmd.cmd==QUIT){
			if(loaded==true){//added 11.9
				gameDestroy(game);
			}
			exit(0);
			break;
		}
		cmd=gameSetting(&set);
	}
	if(loaded==false){
		game=gameCreate(HISTORY_SIZE);
		gameInitalize(game,set);
	}
	if(game->set.gameMode==ONE_PLAYER_MODE){
		if(game->set.userColor==BLACK){
			if(loaded==false){
				game->curPlayer=PLAYER_2;
			}
			if(gameGetCurPlayer(game)->color==WHITE){
				game->curPlayer=PLAYER_2;
				Move bestmove;
				setMovePiece(&bestmove,0,0,1,1);
				bestmove=chooseBestMove(game,game->set.difficulty);
				gameSetMoveAux(game,&bestmove);
				changeTurn(game);
				gameover=GameStatus(game);
			}
		}
		while(gameover==GAMECONTINUE){
			playerTurn(game);
			gameover=GameStatus(game);
			if(gameover==GAME_OVER){
				break;
			}
			computerTurn(game);
			gameover=GameStatus(game);
		}
	}
	else{
		while(true){
			playerTurn(game);
			int gameover=GameStatus(game);
			if(gameover==GAME_OVER){
				break;
			}
		}
	}
}
int moveGame(Move move,Game* game){
	gameSetMove(game,move);
	changeTurn(game);
	return 1;
}
int saveGame(Game* game,char* fileName){
	int i,j;
	char line[MAX_LEN];
	FILE* file=fopen(fileName,"w");
	if(file==NULL){
		fclose(file);
		exit(0);
		return 0;
	}
	fprintf(file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<game>\n");
	fprintf(file,"\t<current_turn>%d</current_turn>\n",gameGetCurPlayer(game)->color);
	fprintf(file,"\t<game_mode>%d</game_mode>\n",game->set.gameMode);
	if(game->set.gameMode==1){
		fprintf(file,"\t<difficulty>%d</difficulty>\n",game->set.difficulty);
		fprintf(file,"\t<user_color>%d</user_color>\n",game->set.userColor);
	}
	fprintf(file,"\t<board>\n");
	for(j=0;j<8;j++){
		for(i=0;i<8;i++){
			line[i]=getPiecePrint(game->gameBoard[j][i]);
		}
		line[8]='\0';
		fprintf(file,"\t\t<row_%d>%s</row_%d>\n",8-j,line,8-j);
	}
	fprintf(file,"\t</board>\n</game>");
	fclose(file);
	return 1;
}
Game* loadGame(char* fileName){
	int i,j;
	char line[1024];
	Settings set;
	FILE* file=fopen(fileName,"r");
	if(file==NULL){
		fclose(file);
		exit(0);
		return 0;
	}
	int mode,difficulty,color,currentturn;
	fscanf(file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<game>\n");
	fscanf(file,"\t<current_turn>%d</current_turn>\n",&currentturn);
	fscanf(file,"\t<game_mode>%d</game_mode>\n",&mode);
	if(mode==1){
		fscanf(file,"\t<difficulty>%d</difficulty>\n",&difficulty);
		fscanf(file,"\t<user_color>%d</user_color>\n",&color);
	}
	else{
		difficulty=1;
		color=1;
	}
	fscanf(file,"\t<board>\n");
	set.difficulty=difficulty;
	if(set.difficulty==5){
		printf("Expert level not supported\n");
	}
	set.gameMode=mode;
	set.userColor=color;
	Game* game=gameCreate(HISTORY_SIZE);
	game->set=set;
	if(currentturn==1){
		if(game->set.userColor==WHITE){
			game->curPlayer=PLAYER_1;
		}
		else{
			game->curPlayer=PLAYER_2;
		}
	}
	else{
		if(game->set.userColor==WHITE){
			game->curPlayer=PLAYER_2;
		}
		else{
			game->curPlayer=PLAYER_1;
		}
	}
	game->player1=creatPlayer(PLAYER_1,game->set.userColor);
	game->player2=creatPlayer(PLAYER_2,1-game->set.userColor);
	int tr1,tr2;
	for(j=0;j<8;j++){
		fscanf(file,"\t\t<row_%d>%s</row_%d>\n",&tr1,line,&tr2);
		for(i=0;i<8;i++){
			char ch=line[i];
			if(ch==NONE_PIECE){
				continue;
			}
			else if(ch==toupper(ch)){
				if(game->player1->color==0){
					game->gameBoard[j][i]=addPiecePlayer(game->player1,i,j,tolower(ch));
					if(game->gameBoard[j][i]->type=='k'){
						game->player1->king=game->gameBoard[j][i];
					}
				}
				else{
					game->gameBoard[j][i]=addPiecePlayer(game->player2,i,j,tolower(ch));
					if(game->gameBoard[j][i]->type=='k'){
						game->player2->king=game->gameBoard[j][i];
					}
				}
			}
			else{
				if(game->player1->color==0){
					game->gameBoard[j][i]=addPiecePlayer(game->player2,i,j,ch);
					if(game->gameBoard[j][i]->type=='k'){
						game->player2->king=game->gameBoard[j][i];
					}
				}
				else{
					game->gameBoard[j][i]=addPiecePlayer(game->player1,i,j,ch);
					if(game->gameBoard[j][i]->type=='k'){
						game->player1->king=game->gameBoard[j][i];
					}
				}
			}
		}
	}
	for(i=game->player1->nump;i<16;i++){
		game->player1->pieces[i]=NULL;
	}
	for(i=game->player2->nump;i<16;i++){
		game->player2->pieces[i]=NULL;
	}
	fscanf(file,"\t</board>\n</game>");
	fclose(file);
	return game;
}

int undoGame(Game* game){
	changeTurn(game);
	gameUndoPrevMove(game);
	changeTurn(game);
	CHESSMESSAGE message=gameUndoPrevMove(game);
	if(message==SUCCESS){
		return 1;
	}
	else if(message==NO_HISTORY){
		return 0;
	}
	else{
		return -1;
	}
}

int playerTurn(Game* game){
	Command cmd;
	printGameBoard(game);
	cmd.validArg=0;
	cmd.cmd=INVALID_LINE;
    while (cmd.cmd==INVALID_LINE){
   	if(gameGetCurPlayer(game)->color)
       	printf("white player - enter your move:\n");
     else
        printf("black player - enter your move:\n");
   	cmd=userInput(game);
	}
    return 1;

}
