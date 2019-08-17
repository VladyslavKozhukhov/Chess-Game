#include "GUI_Manager.h"

GuiManager* managerCreate(){
	GuiManager* res=(GuiManager*) malloc(sizeof(GuiManager));
	if(res==NULL){
		return NULL ;
	}
	res->mainWin=mainWinCreate();
	if(res->mainWin==NULL){
		free(res);
		return NULL ;
	}
	res->gameWin=NULL;
	res->activeWin=MAIN_WINDOW_ACTIVE;
	return res;
}
void managerDestroy(GuiManager* src){
	if(!src){
		return;
	}
	if(src->activeWin==GAME_WINDOW_ACTIVE){
		gameWinDestroy(src->gameWin);
	}
	mainWinDestroy(src->mainWin);
	free(src);
}
void managerDraw(GuiManager* src){
	if(!src){
		return;
	}
	if(src->activeWin==MAIN_WINDOW_ACTIVE){
		mainWinDraw(src->mainWin);
	}
	else if(src->activeWin==SETTINGS_WINDOW_ACTIVE){
		settingsWinDraw(src->settingsWin);
	}
	else if(src->activeWin==LOAD_WINDOW_ACTIVE){
		loadWinDraw(src->loadWin);
	}

	else {
		gameWinDraw(src->gameWin,true);
	}
}
MANAGER_EVENET handleManagerDueToMainEvent(GuiManager* src,MAIN_EVENT event){
	if(src==NULL){
		return MANAGER_NONE;
	}
	if(event==MAIN_START){
		mainWindowHide(src->mainWin);
		src->settingsWin=settingsWinCreate();
		if(src->settingsWin==NULL){
			printf("Can not create settings window\n");
			return MANAGER_QUIT;
		}
		src->activeWin=SETTINGS_WINDOW_ACTIVE;
		return MANAGER_UPDATE;
	}
	else if(event==MAIN_LOAD){
		mainWindowHide(src->mainWin);
		src->loadWin=loadWinCreate();
		if(src->loadWin==NULL){
			return MANAGER_QUIT;
		}
		src->activeWin=LOAD_WINDOW_ACTIVE;
		return MANAGER_UPDATE;
	}
	else if(event==MAIN_EXIT){
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}
MANAGER_EVENET handleManagerDueToSettingsEvent(GuiManager* src,SETTINGS_EVENT event){
	if(src==NULL){
		return MANAGER_NONE;
	}
	if(event==SETTINGS_EVENT_UPDATE){
		return MANAGER_UPDATE;
	}
	if(event==SETTINGS_EVENT_START){
		Game* game=gameCreate(HISTORY_SIZE);
		src->settingsWin->settings.Xflag=1;
		game=gameInitalize(game,src->settingsWin->settings);
		src->gameWin=gameWinCreate(game);
		src->activeWin=GAME_WINDOW_ACTIVE;
		settingsWinDestroy(src->settingsWin);
		return MANAGER_UPDATE;
	}
	if(event==SETTINGS_EVENT_BACK){
		settingsWinDestroy(src->settingsWin);
		mainWindowShow(src->mainWin);
		src->activeWin=MAIN_WINDOW_ACTIVE;
		return MANAGER_UPDATE;
	}
	if(event==SETTINGS_EVENT_QUIT){
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}
MANAGER_EVENET handleManagerDueToLoadEvent(GuiManager* src,LOAD_EVENT event){
	if(src==NULL){
		return MANAGER_NONE;
	}
	if(event==LOAD_EVENT_UPDATE){
		return MANAGER_UPDATE;
	}
	if(event==LOAD_EVENT_BACK){
		loadWinDestroy(src->loadWin);
		if(src->gameWin!=NULL){
			gameWindowShow(src->gameWin);
			src->activeWin=GAME_WINDOW_ACTIVE;
		}
		else{
			mainWindowShow(src->mainWin);
			src->activeWin=MAIN_WINDOW_ACTIVE;
		}
		return MANAGER_UPDATE;
	}
	if(event==LOAD_EVENT_START){
		if(src->gameWin!=NULL){
			gameWinDestroy(src->gameWin);
		}
		char* path=getFilePath(src->loadWin->slot_num);
		Game* game=loadGame(path);
		//free(path);
		loadWinDestroy(src->loadWin);
		src->gameWin=gameWinCreate(game);
		if(src->gameWin==NULL){
			printf("Couldn't create game window\n");
			return MANAGER_QUIT;
		}
		src->gameWin->saved=true;
		src->activeWin=GAME_WINDOW_ACTIVE;
		return MANAGER_UPDATE;
	}
	else if(event==LOAD_EVENT_QUIT){
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}

MANAGER_EVENET handleManagerDueToGameEvent(GuiManager* src,GAME_EVENT event){

	if(event==GAME_EVENT_NONE||src==NULL){
		return MANAGER_NONE;
	}
	if(event==GAME_EVENT_UPDATE){
		return MANAGER_UPDATE;
	}
	else if(event==GAME_EVENT_RESET){
		return MANAGER_UPDATE;
	}
	else if(event==GAME_EVENT_MAIN_MENU){
		if(src->gameWin->saved==true){
			printf("You have saved or you lose/win\n");
			gameWinDestroy(src->gameWin);
			src->gameWin=NULL;
			src->activeWin=MAIN_WINDOW_ACTIVE;
			mainWindowShow(src->mainWin);
			return MANAGER_UPDATE;
		}
		else{
			const SDL_MessageBoxButtonData buttons[] = { {
								SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" }, { 0, 0, "no" } };
						const SDL_MessageBoxColorScheme colorScheme = { { { 255, 0, 0 },
								{ 0, 255, 0 }, { 255, 255, 0 }, { 0, 0, 255 }, { 255, 0, 255 } } };
							const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION,
										NULL, "Save Game",
											"Do you want to save the game before leaving ?", SDL_arraysize(
															buttons), buttons, &colorScheme };
											int buttonid;
												if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
										SDL_Log("error displaying message box");
												return 0; /* error */
											}
										if(buttonid==1){
											promoteSlots();
											if(saveGame(src->gameWin->game,SLOT0)<0){
												SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR!",	"Unable to save the ame",
																		NULL);

													} else
														SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
													"SUCCESS!", "Game was successfully saved!",
															NULL);

											}

			}
		gameWinDestroy(src->gameWin);
					src->gameWin=NULL;
					src->activeWin=MAIN_WINDOW_ACTIVE;
					mainWindowShow(src->mainWin);
					return MANAGER_UPDATE;
		}

	else if(event==GAME_EVENT_SAVE){
	const SDL_MessageBoxButtonData buttons[] = { {
		SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" }, { 0, 0, "no" }};
	const SDL_MessageBoxColorScheme colorScheme = { { { 255, 0, 0 },
		{ 0, 255, 0 }, { 255, 255, 0 }, { 0, 0, 255 }, { 255, 0, 255 } } };
	const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION,
				NULL, "Save Game",
					"Do you want to save the game ?", SDL_arraysize(
									buttons), buttons, &colorScheme };
					int buttonid;
						if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
							SDL_Log("error displaying message box");
							return 0; /* error */
						}
				if(buttonid==1){
					promoteSlots();
					if(saveGame(src->gameWin->game,SLOT0)<0){
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR!",	"Unable to save the game",
												NULL);
									} else
									SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
								"SUCCESS!", "Game was successfully saved!",
										NULL);
					}

		return MANAGER_UPDATE;
	}
	else if(event==GAME_EVENT_LOAD){
		gameWindowHide(src->gameWin);
		src->loadWin=loadWinCreate();
		if(src->loadWin==NULL){
			printf("Couldn't create load window\n");
			return MANAGER_QUIT;
		}
		src->activeWin=LOAD_WINDOW_ACTIVE;
		return MANAGER_UPDATE;
	}
	else if(event==GAME_EVENT_EXIT){
		if(src->gameWin->saved==true){
			return MANAGER_QUIT;
		}
		else{

			const SDL_MessageBoxButtonData buttons[] = { {
					SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" }, { 0, 0, "no" },
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "back" }, };
			const SDL_MessageBoxColorScheme colorScheme = { { { 255, 0, 0 },
					{ 0, 255, 0 }, { 255, 255, 0 }, { 0, 0, 255 }, { 255, 0, 255 } } };
				const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION,
							NULL, "Save Game",
								"Do you want to save the game before leaving ?", SDL_arraysize(
												buttons), buttons, &colorScheme };
								int buttonid;
									if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
							SDL_Log("error displaying message box");
									return 0; /* error */
								}
							if(buttonid==1){
								promoteSlots();
								if(saveGame(src->gameWin->game,SLOT0)<0){
									SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR!",	"Unable to save the ame",
															NULL);
									return MANAGER_QUIT;
										} else
											SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
										"SUCCESS!", "Game was successfully saved!",
												NULL);
								return MANAGER_NONE;


								}
							if(buttonid==0)
								return MANAGER_QUIT;

							src->activeWin=GAME_WINDOW_ACTIVE;
			return MANAGER_UPDATE;
		}
	}
	return MANAGER_NONE;
}

MANAGER_EVENET managerHandleEvent(GuiManager* src, SDL_Event* event){
	if(src==NULL||event==NULL){
		return MANAGER_NONE;
	}
	if(src->activeWin==MAIN_WINDOW_ACTIVE){
		if(src->mainWin->first==true){
			src->mainWin->first=false;
			managerDraw(src);
		}
		MAIN_EVENT mainEvent=mainWinHandleEvent(src->mainWin, event);
		return handleManagerDueToMainEvent(src, mainEvent);
	}
	else if(src->activeWin==SETTINGS_WINDOW_ACTIVE){
		if(src->settingsWin->first==true){
			src->settingsWin->first=false;
			managerDraw(src);
		}
		SETTINGS_EVENT mainEvent=settingsWinHandleEvent(src->settingsWin, event);
		return handleManagerDueToSettingsEvent(src, mainEvent);
	}
	else if(src->activeWin==LOAD_WINDOW_ACTIVE){
		if(src->loadWin->first==true){
			src->loadWin->first=false;
			managerDraw(src);
		}
		LOAD_EVENT mainEvent=loadWinHandleEvent(src->loadWin, event);
		return handleManagerDueToLoadEvent(src, mainEvent);
	}

	else if(src->activeWin==GAME_WINDOW_ACTIVE){
		if(src->gameWin->first==true){
			src->gameWin->first=false;
			if(src->gameWin->game->set.userColor==BLACK){
				src->gameWin->game->curPlayer=PLAYER_2;
				src->gameWin->saved=false;
				Move bestmove;
				setMovePiece(&bestmove,0,0,1,1);//Initial
				bestmove=chooseBestMove(src->gameWin->game,src->gameWin->game->set.difficulty);
				gameSetMoveAux(src->gameWin->game,&bestmove);
				printf("computer move!\n");
				changeTurn(src->gameWin->game);
			}
			managerDraw(src);
			CHESSMESSAGE gameover=checkWinnerOrTie(src->gameWin->game);

			if(gameover==CHECK){
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","Check!", NULL );
			}
			if(gameover==CHECKMATE){
				src->gameWin->saved=true;
				printf("checkmate\n");
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","YOU HAVE LOST!", NULL );
				return GAME_EVENT_MAIN_MENU;
			}
			if(gameover==TIE){
				src->gameWin->saved=true;
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Chess_Game","IT'S A TIE!", NULL );
				return GAME_EVENT_MAIN_MENU;
			}
		}
		GAME_EVENT gameEvent=gameWinHandleEvent(src->gameWin, event);
		return handleManagerDueToGameEvent(src, gameEvent);
	}
	return MANAGER_NONE;
}
