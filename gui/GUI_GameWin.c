#include "GUI_GameWin.h"

GameWin* gameWinCreate(Game* game){
	GameWin* res=(GameWin*) calloc(sizeof(GameWin), sizeof(char));
	SDL_Surface* loadingSurface=NULL; //Used as temp surface
	if (res==NULL||game==NULL){
		printf("Can not create GameWin struct\n");
		return NULL ;
	}
	res->game=game;
	// Create an application window with the following settings:
	res->window=SDL_CreateWindow("ChessGame:Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1020,740,SDL_WINDOW_OPENGL);

	if (res->window==NULL){
	gameWinDestroy(res);
		return NULL ;
	}
	res->renderer=SDL_CreateRenderer(res->window, -1,SDL_RENDERER_ACCELERATED);
	if (res->renderer==NULL){
		gameWinDestroy(res);
		return NULL ;
	}

	loadingSurface=SDL_LoadBMP("./gui/images/chessboard.bmp");
	if (loadingSurface==NULL){
		gameWinDestroy(res);
		return NULL ;
	}
	res->bgTexture=SDL_CreateTextureFromSurface(res->renderer,loadingSurface);
	if (res->bgTexture==NULL){
		gameWinDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	res->widgets=iniatGameWinWidgets(res->renderer,res->game);
	if (res->widgets==NULL){
		gameWinDestroy(res);
		return NULL ;
	}
	res->numOfWidgets=6+game->player1->nump+game->player2->nump;
	res->first=true;
	res->saved=true;
	res->backmain=false;
	res->moves=NULL;
	return res;
}
Widget** iniatGameWinWidgets(SDL_Renderer* renderer,Game* game){
	int i=0;
	if (renderer == NULL){
		return NULL ;
	}
	Widget** widgets=calloc(6+game->player1->nump+game->player2->nump,sizeof(Widget*));
	if (widgets == NULL){
		return NULL ;
	}
	SDL_Rect resetR ={.x =750,.y=30,.h=70,.w=240 };
	SDL_Rect saveR ={.x =750,.y=110,.h=70,.w=240 };
	SDL_Rect loadR ={.x=750,.y=190,.h=70,.w=240 };
	SDL_Rect undoR ={.x=750,.y=270,.h=70,.w=240 };
	SDL_Rect mainmenuR ={.x=750,.y=470,.h=BUTTON_HEIGTH,.w=BUTTON_WIDTH };
	SDL_Rect quitR ={.x=750,.y=580,.h=BUTTON_HEIGTH,.w=BUTTON_WIDTH };
	widgets[0]=createSB(renderer, &resetR, "./gui/images/buttons/restart.bmp",NULL,true);
	widgets[1]=createSB(renderer, &saveR, "./gui/images/buttons/save.bmp",NULL,true);
	widgets[2]=createSB(renderer, &loadR, "./gui/images/buttons/load.bmp",NULL,true);
	widgets[3]=createSB(renderer, &undoR, "./gui/images/buttons/undo.bmp","./gui/images/buttons/undob.bmp",true);
	widgets[4]=createSB(renderer, &mainmenuR, "./gui/images/buttons/main.bmp",NULL,true);
	widgets[5]=createSB(renderer, &quitR, "./gui/images/buttons/quit.bmp",NULL,true);
	for(i=0;i<game->player1->nump;i++){
		if(game->player1->pieces[i]!=NULL){
			SDL_Rect pieceR ={.x=game->player1->pieces[i]->x*90,.y=game->player1->pieces[i]->y*90,.h=90,.w=90 };
			char path[40],name[15],ending[5];
			strcpy(path,"./gui/images/pieces/");
			strcpy(name,getPieceName(game->player1->pieces[i]));
			strcpy(ending,".bmp");
			strcat(path,name);
			strcat(path,ending);
			widgets[i+6]=createPB(renderer, &pieceR,path,game->player1->pieces[i]->alive);
		}
	}
	for(i=0;i<game->player2->nump;i++){
		if(game->player2->pieces[i]!=NULL){
			SDL_Rect pieceR ={.x=game->player2->pieces[i]->x*90,.y=game->player2->pieces[i]->y*90,.h=90,.w=90 };
			char path[40],name[15],ending[5];
			strcpy(path,"./gui/images/pieces/");
			strcpy(name,getPieceName(game->player2->pieces[i]));
			strcpy(ending,".bmp");
			strcat(path,name);
			strcat(path,ending);
			widgets[i+6+game->player1->nump]=createPB(renderer, &pieceR,path,game->player2->pieces[i]->alive);
		}
	}
	for(i=0;i<6+game->player1->nump+game->player2->nump;i++){
		if(widgets[i]==NULL){

			gameWinWidgetsDestroy(widgets,game);
			break;
		}
	}
	return widgets;
}
void gameWinDraw(GameWin* src,bool update){
	int numwidget,i;
	if(src==NULL){
		return;
	}
	SDL_Rect rec ={.x=0,.y=0,.w=720,.h=720 };
	SDL_SetRenderDrawColor(src->renderer, 40, 40, 40, 40);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &rec);
	if(update==true){
		((SimpleButton*) src->widgets[3]->data)->active=false;
		int historysize=arrayListSize(src->game->history);
		if(historysize!=0){
			if(src->game->set.gameMode==ONE_PLAYER_MODE){
				((SimpleButton*) src->widgets[3]->data)->active=true;
			}
		}
		for(i=0;i<src->game->player1->nump;i++){
			numwidget=i+6;
			if(src->game->player1->pieces[i]!=NULL){

				((PieceButton*)src->widgets[numwidget]->data)->location->x=src->game->player1->pieces[i]->x*90;
				((PieceButton*)src->widgets[numwidget]->data)->location->y=src->game->player1->pieces[i]->y*90;
				if(src->game->player1->pieces[i]->alive==false){
					((PieceButton*)src->widgets[numwidget]->data)->show=false;
				}
				else if(src->game->player1->pieces[i]->alive==true){
					((PieceButton*)src->widgets[numwidget]->data)->show=true;
				}
			}
		}
		for(i=0;i<src->game->player2->nump;i++){
			numwidget=i+6+src->game->player1->nump;
			if(src->game->player2->pieces[i]!=NULL){
				if(src->game->player2->pieces[i]!=NULL){
					((PieceButton*)src->widgets[numwidget]->data)->location->x=src->game->player2->pieces[i]->x*90;
					((PieceButton*)src->widgets[numwidget]->data)->location->y=src->game->player2->pieces[i]->y*90;
					if(src->game->player2->pieces[i]->alive==false){
						((PieceButton*)src->widgets[numwidget]->data)->show=false;
					}
					else if(src->game->player2->pieces[i]->alive==true){
						((PieceButton*)src->widgets[numwidget]->data)->show=true;
					}
				}
			}
		}
	}


	for (i=0; i < src->numOfWidgets; i++){
		(src->widgets[i])->drawWidget(src->widgets[i]);
	}
	SDL_RenderPresent(src->renderer);
	SDL_RenderPresent(src->renderer);
}
void gameWinDestroy(GameWin* src){
	if (!src){
		return;
	}
	gameWinWidgetsDestroy(src->widgets,src->game);
	gameDestroy(src->game);
	if (src->bgTexture!=NULL){
		SDL_DestroyTexture(src->bgTexture);
	}
	if (src->renderer!=NULL){
		SDL_DestroyRenderer(src->renderer);
	}
	if (src->window!=NULL){
		SDL_DestroyWindow(src->window);
	}
	free(src);

}
void gameWinWidgetsDestroy(Widget** widgets,Game* game){
	int i;
	for(i=0;i<6+game->player1->nump+game->player2->nump;i++){
		if(widgets[i]!=NULL){
			destroyWidget(widgets[i]);
		}
	}

	free(widgets);
}
GAME_EVENT gameWinHandleEvent(GameWin* src, SDL_Event* event){
	int x,y,i,j;
	int LegalMove=-1;
	if (event==NULL||src==NULL){
		return GAME_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type){
	case SDL_MOUSEBUTTONUP:
		if (src->widgets[0]->handleEvent(src->widgets[0],event)==1){
			Game* fakegame=src->game;
			Game* newgame=gameCreate(HISTORY_SIZE);
			newgame=gameInitalize(newgame,src->game->set);
			src->game=newgame;
			gameDestroy(fakegame);
			printf("Reset!\n");
			src->saved=false;
			return GAME_EVENT_UPDATE;
		}
		else if (src->widgets[1]->handleEvent(src->widgets[1],event)==1){
			src->saved=true;
			return GAME_EVENT_SAVE;
		}
		else if (src->widgets[2]->handleEvent(src->widgets[2],event)==1){
			src->saved=true;
			return GAME_EVENT_LOAD;
		}
		else if (src->widgets[3]->handleEvent(src->widgets[3],event)==1){
			if(src->game->set.gameMode!=TWO_PLAYERS_MODE){
				undoGame(src->game);
				src->saved=false;
			}
			return GAME_EVENT_UPDATE;
		}
		else if (src->widgets[4]->handleEvent(src->widgets[4],event)==1){
			src->backmain=true;
			return GAME_EVENT_MAIN_MENU;
		}
		else if (src->widgets[5]->handleEvent(src->widgets[5],event)==1){
			printf("Exit from Game window\n");
			return GAME_EVENT_EXIT;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:{

		for(i=0;i<gameGetCurPlayer(src->game)->nump;i++){
			int num=i+6;
			if(src->game->curPlayer==PLAYER_2){
				num+=src->game->player1->nump;
			}
			if (src->widgets[num]->handleEvent(src->widgets[num],event)==1){
				x=event->button.x/90;
				y=event->button.y/90;
				if(src->game->gameBoard[y][x]!=NULL){
					if(src->game->gameBoard[y][x]->player==src->game->curPlayer){
						if(src->game->gameBoard[y][x]->alive==true){
							LegalMove=num;
						}
					}
				}
			}
		}

			if(LegalMove!=-1){
				SDL_Event eventmotion;
				SDL_WaitEvent(&eventmotion);
				while(eventmotion.type==SDL_MOUSEMOTION){
					((PieceButton*)src->widgets[LegalMove]->data)->location->x=eventmotion.motion.x-45;
					((PieceButton*)src->widgets[LegalMove]->data)->location->y=eventmotion.motion.y-45;
					gameWinDraw(src,false);
					SDL_WaitEvent(&eventmotion);
					if(eventmotion.type!=SDL_MOUSEMOTION){
						break;
					}
				}
				i=eventmotion.button.x/90;
				j=eventmotion.button.y/90;
				Move move;
				setMovePiece(&move,x,y,i,j);
				bool validmove=gameIsValidMove(src->game,&move);
				if(validmove==true){
					src->saved=false;
					gameSetMove(src->game,move);
					changeTurn(src->game);
					gameWinDraw(src,true);
					CHESSMESSAGE gameover=checkWinnerOrTie(src->game);
					if(src->game->set.gameMode==TWO_PLAYERS_MODE){
						if(gameover==CHECK){
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","Check!", NULL );
						}
						if(gameover==CHECKMATE){
							src->saved=true;
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","YOU HAVE WON!", NULL );
							return GAME_EVENT_MAIN_MENU;
						}
						if(gameover==TIE){
							src->saved=true;
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","IT'S A TIE!", NULL );
							return GAME_EVENT_MAIN_MENU;
						}
					}
					else if(src->game->set.gameMode==ONE_PLAYER_MODE){
						if(gameover==CHECKMATE){
							src->saved=true;
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","YOU HAVE WON!", NULL );
							return GAME_EVENT_MAIN_MENU;
						}
						if(gameover==TIE){
							src->saved=true;
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","IT'S A TIE!", NULL );
							return GAME_EVENT_MAIN_MENU;
						}
						Move bestmove;
						setMovePiece(&bestmove,0,0,1,1);
						bestmove=chooseBestMove(src->game,src->game->set.difficulty);
						gameSetMove(src->game,bestmove);
						changeTurn(src->game);
						gameover=checkWinnerOrTie(src->game);
						if(gameover==CHECK){
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","Check!", NULL );
						}
						if(gameover==CHECKMATE){
							src->saved=true;
							printf("checkmate\n");
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","YOU HAVE LOST!", NULL );
							return GAME_EVENT_MAIN_MENU;
						}
						if(gameover==TIE){
							src->saved=true;
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","IT'S A TIE!", NULL );
							return GAME_EVENT_MAIN_MENU;
						}
					}
				}
			}

		return GAME_EVENT_UPDATE;
		break;
	}
	case SDL_WINDOWEVENT:
		if (event->window.event==SDL_WINDOWEVENT_CLOSE){
			return GAME_EVENT_EXIT;
		}
		break;
	default:
		return GAME_EVENT_NONE;
	}
	return GAME_EVENT_NONE;
}
void gameWindowHide(GameWin* src){
	SDL_HideWindow(src->window);
}

void gameWindowShow(GameWin* src){
	SDL_ShowWindow(src->window);
}
