 #include "GUI_SettingsWin.h"

SettingsWin* settingsWinCreate(){
	SettingsWin* res = NULL;
	res=(SettingsWin*) calloc(sizeof(SettingsWin), sizeof(char));
	if(res==NULL){
		return NULL;
	}


	res->window = SDL_CreateWindow("ChessProg - Settings",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			1000,
			700,
			SDL_WINDOW_OPENGL
			);
	if (res->window==NULL ) {
		settingsWinDestroy(res);
		printf("Can not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,SDL_RENDERER_ACCELERATED);
	if (res->renderer==NULL ) {
		settingsWinDestroy(res);
		printf("Can not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->widgets=createSettingsWinWidgets(res->renderer);
	if (res->widgets==NULL ) {
		settingsWinDestroy(res);
		printf("Could not create widgets: %s\n", SDL_GetError());
		return NULL ;
	}
	res->numOfWidgets=11;
	res->first=true;
	printf("created everything\n");
	res->settings=initSettings();
	return res;
}
Widget** createSettingsWinWidgets(SDL_Renderer* renderer) {
	int i;
	if (renderer == NULL ) {
		return NULL ;
	}
	Widget** widgets = calloc(11,sizeof(Widget*));
	if (widgets == NULL ) {
		return NULL ;
	}
	SDL_Rect OnePlayer = { .x =20, .y = 30, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect TwoPlayers = { .x =20, .y = 140, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect Noob = { .x = 400, .y = 30, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect Easy = { .x = 400, .y = 140, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect Moderate = { .x = 400, .y = 250, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect Hard = { .x = 400, .y = 360, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect BlackC = { .x = 750, .y = 30, .h = 120, .w = 120 };
	SDL_Rect WhiteC = { .x =750, .y = 300, .h = 120, .w = 120 };
	SDL_Rect Next = { .x = 150, .y = 470, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect Start = { .x = 720, .y = 580, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect Back = { .x = 20, .y = 580, .h =BUTTON_HEIGTH, .w = BUTTON_WIDTH };

	widgets[0] = createSB(renderer, &OnePlayer,"./gui/images/buttons/oneplayer.bmp","./gui/images/buttons/oneplayerb.bmp",false);
	widgets[1] = createSB(renderer, &TwoPlayers, "./gui/images/buttons/twoplayers.bmp","./gui/images/buttons/twoplayersb.bmp",false);
	widgets[2] = createSB(renderer, &Next, "./gui/images/buttons/next.bmp",NULL,false);
	widgets[3] = createSB(renderer, &Start, "./gui/images/buttons/start.bmp",NULL,false);
	widgets[4] = createSB(renderer, &Back, "./gui/images/buttons/back.bmp",NULL,false);
	widgets[5] = createSB(renderer, &Noob, "./gui/images/buttons/noob.bmp","./gui/images/buttons/noobb.bmp",false);
	widgets[6] = createSB(renderer, &Easy, "./gui/images/buttons/easy.bmp","./gui/images/buttons/easyb.bmp",false);
	widgets[7] = createSB(renderer, &Moderate, "./gui/images/buttons/moderate.bmp","./gui/images/buttons/moderateb.bmp",false);
	widgets[8] = createSB(renderer, &Hard, "./gui/images/buttons/hard.bmp","./gui/images/buttons/hardb.bmp",false);
	widgets[9] = createSB(renderer, &BlackC, "./gui/images/pieces/BlackKingb.bmp","./gui/images/pieces/BlackKing.bmp",false);
	widgets[10] = createSB(renderer, &WhiteC, "./gui/images/pieces/WhiteKingb.bmp","./gui/images/pieces/WhiteKing.bmp",false);




	for(i=0;i<11;i++){
		if(widgets[i]==NULL){
			printf("widget number %d is broken",i);
			settingsWinWidgetsDestroy(widgets);
			break;
		}
	}
	return widgets;
}
void settingsWinDraw(SettingsWin* src) {
	int i;
	if(src==NULL){
		return;
	}
	SDL_SetRenderDrawColor(src->renderer, 40, 40, 40, 40);
	SDL_RenderClear(src->renderer);

	if(src->settings.Xflag==1)
	{
		for (i=0; i < src->numOfWidgets; i++) {
				((SimpleButton*)src->widgets[i]->data)->show=true;
				src->widgets[i]->canPush=false;
				((SimpleButton*)src->widgets[2]->data)->show=false;
				((SimpleButton*)src->widgets[i]->data)->active=false;
			}
		((SimpleButton*)src->widgets[2]->data)->show=false;

		((SimpleButton*) src->widgets[0]->data)->active=true;
		((SimpleButton*) src->widgets[1]->data)->active=true;
		((SimpleButton*) src->widgets[3]->data)->active=true;
		((SimpleButton*) src->widgets[4]->data)->active=true;
		src->widgets[0]->canPush=true;
		src->widgets[1]->canPush=true;
		src->widgets[3]->canPush=true;
		src->widgets[4]->canPush=true;
		src->settings.Xflag=2;
	}

	for (i=0; i < src->numOfWidgets; i++) {
		(src->widgets[i])->drawWidget(src->widgets[i]);
	}
	SDL_RenderPresent(src->renderer);
}
void settingsWinDestroy(SettingsWin* src) {
	if (!src) {

		return;
	}
	settingsWinWidgetsDestroy(src->widgets);
	if (src->renderer != NULL ) {
		SDL_DestroyRenderer(src->renderer);
	}
	if (src->window != NULL ) {
		SDL_DestroyWindow(src->window);
	}
	free(src);
}
void settingsWinWidgetsDestroy(Widget** widgets){
	int i;
	for(i=0;i<11;i++){
		if(widgets[i]!=NULL){
			destroyWidget(widgets[i]);
		}
	}
	free(widgets);
	printf("free widgets\n");
}
SETTINGS_EVENT settingsWinHandleEvent(SettingsWin* src, SDL_Event* event) {
	if (!event) {
		return SETTINGS_EVENT_INVALID_ARGUMENT;
	}
	int i;

	int index=-1;
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:

				for(i=0;i<11;i++){
			SDL_Point point;
			point.x=event->button.x;
			point.y=event->button.y;
	if (SDL_PointInRect(&point, ((SimpleButton*) src->widgets[i]->data)->location) &&
					 src->widgets[i]->canPush==true) {
					index=i;
					i=11;
		}
				}
		switch(index){
		case 0:
			src->settings.gameMode=ONE_PLAYER_MODE;

			for(i=0;i<11;i++){
				((SimpleButton*) src->widgets[i]->data)->active=false;
				((SimpleButton*)src->widgets[2]->data)->show=false;
				((SimpleButton*) src->widgets[i]->data)->show=true;
				src->widgets[i]->canPush=false;
									}
			((SimpleButton*) src->widgets[0]->data)->active=true;
			src->widgets[3]->canPush=true;
			src->widgets[4]->canPush=true;
			src->widgets[5]->canPush=true;
			src->widgets[6]->canPush=true;
			src->widgets[7]->canPush=true;
			src->widgets[8]->canPush=true;
			((SimpleButton*) src->widgets[3]->data)->active=true;

			((SimpleButton*) src->widgets[4]->data)->active=true;
			((SimpleButton*) src->widgets[5]->data)->active=true;
			((SimpleButton*) src->widgets[6]->data)->active=true;
			((SimpleButton*) src->widgets[7]->data)->active=true;
			((SimpleButton*) src->widgets[8]->data)->active=true;
			src->settings.selectMode=true;
			index=-1;
			return SETTINGS_EVENT_UPDATE;
		break;

		case 1:
						src->settings.gameMode=TWO_PLAYERS_MODE;
						((SimpleButton*) src->widgets[0]->data)->active=false;

						for(i=0;i<11;i++){
						((SimpleButton*) src->widgets[i]->data)->active=false;
						((SimpleButton*) src->widgets[i]->data)->show=true;
						src->widgets[i]->canPush=false;
						}
						((SimpleButton*)src->widgets[2]->data)->show=false;
						((SimpleButton*) src->widgets[1]->data)->active=true;
						((SimpleButton*) src->widgets[3]->data)->active=true;
						((SimpleButton*) src->widgets[0]->data)->active=false;
						src->widgets[0]->canPush=false;
						src->widgets[1]->canPush=false;

						src->widgets[3]->canPush=true;
						((SimpleButton*)src->widgets[4]->data)->active=true;
						src->widgets[4]->canPush=true;
						src->settings.selectMode=true;
						index=-1;

						return SETTINGS_EVENT_UPDATE;
		break;
		case 2:			return SETTINGS_EVENT_NONE;
		break;

		case 3:

						return SETTINGS_EVENT_START;

					break;
		break;
		case 4:
			if(src->settings.selectColor) {
				for(i=9;i<11;i++){
					((SimpleButton*) src->widgets[i]->data)->active=false;
					((SimpleButton*) src->widgets[i]->data)->show=true;
								src->widgets[i]->canPush=false;
													}
							src->widgets[4]->canPush=true;
							src->widgets[5]->canPush=true;
							src->widgets[6]->canPush=true;
							src->widgets[7]->canPush=true;
							src->widgets[8]->canPush=true;
							((SimpleButton*)src->widgets[2]->data)->show=false;
							((SimpleButton*) src->widgets[4]->data)->active=true;
							((SimpleButton*) src->widgets[5]->data)->active=true;
							((SimpleButton*) src->widgets[6]->data)->active=true;
							((SimpleButton*) src->widgets[7]->data)->active=true;
							((SimpleButton*) src->widgets[8]->data)->active=true;
							src->settings.selectColor=false;
							return SETTINGS_EVENT_UPDATE;
			}
						if(src->settings.selectLVL){
							for(i=0;i<11;i++){
												((SimpleButton*) src->widgets[i]->data)->active=false;
											     ((SimpleButton*) src->widgets[i]->data)->show=true;
												src->widgets[i]->canPush=false;
															}
															((SimpleButton*) src->widgets[0]->data)->active=true;
																	((SimpleButton*) src->widgets[1]->data)->active=true;
																	((SimpleButton*) src->widgets[3]->data)->active=true;
												((SimpleButton*) src->widgets[4]->data)->active=true;
												((SimpleButton*)src->widgets[2]->data)->show=false;
																src->widgets[0]->canPush=true;
																src->widgets[1]->canPush=true;
																src->widgets[3]->canPush=true;
																	src->widgets[4]->canPush=true;
																	src->settings.selectLVL=false;
																	return SETTINGS_EVENT_UPDATE;
						}
								if(src->settings.selectMode){
								for(i=0;i<11;i++){
											((SimpleButton*) src->widgets[i]->data)->active=false;
								     ((SimpleButton*) src->widgets[i]->data)->show=true;
												src->widgets[i]->canPush=false;
								}
								((SimpleButton*) src->widgets[0]->data)->active=true;
								((SimpleButton*)src->widgets[2]->data)->show=false;
								((SimpleButton*) src->widgets[1]->data)->active=true;
										((SimpleButton*) src->widgets[3]->data)->active=true;
										((SimpleButton*) src->widgets[4]->data)->active=true;
										src->widgets[0]->canPush=true;
										src->widgets[1]->canPush=true;
										src->widgets[3]->canPush=true;
										src->widgets[4]->canPush=true;
										src->settings.selectMode=false;
										return SETTINGS_EVENT_UPDATE;
								}

							return SETTINGS_EVENT_BACK;



		break;
		case 5:
			src->settings.difficulty=1;

			src->settings.selectLVL=true;
			for(i=6;i<11;i++){
				((SimpleButton*) src->widgets[i]->data)->active=false;											     ((SimpleButton*) src->widgets[i]->data)->show=true;
					src->widgets[i]->canPush=false;
											}
								((SimpleButton*) src->widgets[9]->data)->active=true;
								((SimpleButton*)src->widgets[2]->data)->show=false;
								((SimpleButton*) src->widgets[10]->data)->active=true;
										((SimpleButton*) src->widgets[3]->data)->active=true;
									((SimpleButton*) src->widgets[4]->data)->active=true;
										src->widgets[9]->canPush=true;
									src->widgets[10]->canPush=true;
										src->widgets[3]->canPush=true;
										src->widgets[4]->canPush=true;
										return SETTINGS_EVENT_UPDATE;

		break;
		case 6:
			src->settings.selectLVL=true;
			src->settings.difficulty=2;

			for(i=7;i<11;i++){
							((SimpleButton*) src->widgets[i]->data)->active=false;											     ((SimpleButton*) src->widgets[i]->data)->show=true;
								src->widgets[i]->canPush=false;
														}
											((SimpleButton*) src->widgets[9]->data)->active=true;
											((SimpleButton*)src->widgets[2]->data)->show=false;
											((SimpleButton*) src->widgets[10]->data)->active=true;
													((SimpleButton*) src->widgets[3]->data)->active=true;
												((SimpleButton*) src->widgets[4]->data)->active=true;
													src->widgets[9]->canPush=true;
												src->widgets[10]->canPush=true;
													src->widgets[3]->canPush=true;
													src->widgets[4]->canPush=true;
													((SimpleButton*) src->widgets[5]->data)->active=false;
													src->widgets[5]->canPush=false;

													return SETTINGS_EVENT_UPDATE;

		break;
		case 7:
			src->settings.difficulty=3;

			src->settings.selectLVL=true;

			for(i=5;i<7;i++){
									((SimpleButton*) src->widgets[i]->data)->active=false;
									((SimpleButton*) src->widgets[i]->data)->show=true;
										src->widgets[i]->canPush=false;
																}
									((SimpleButton*) src->widgets[9]->data)->active=true;
									((SimpleButton*)src->widgets[2]->data)->show=false;
									((SimpleButton*) src->widgets[10]->data)->active=true;
													((SimpleButton*) src->widgets[3]->data)->active=true;
											((SimpleButton*) src->widgets[4]->data)->active=true;
												src->widgets[9]->canPush=true;
										src->widgets[10]->canPush=true;
												src->widgets[3]->canPush=true;
													src->widgets[4]->canPush=true;
										((SimpleButton*) src->widgets[8]->data)->active=false;
													src->widgets[8]->canPush=false;
													return SETTINGS_EVENT_UPDATE;

					break;
		case 8:
			src->settings.difficulty=4;

			for(i=5;i<8;i++){
					((SimpleButton*) src->widgets[i]->data)->active=false;
							((SimpleButton*) src->widgets[i]->data)->show=true;
										src->widgets[i]->canPush=false;
			}
							((SimpleButton*) src->widgets[9]->data)->active=true;
												((SimpleButton*) src->widgets[10]->data)->active=true;
												((SimpleButton*)src->widgets[2]->data)->show=false;
												((SimpleButton*) src->widgets[3]->data)->active=true;
										((SimpleButton*) src->widgets[4]->data)->active=true;
												src->widgets[9]->canPush=true;
												src->widgets[10]->canPush=true;
												src->widgets[3]->canPush=true;
													src->widgets[4]->canPush=true;
											((SimpleButton*) src->widgets[9]->data)->active=true;
													return SETTINGS_EVENT_UPDATE;
													src->settings.selectLVL=true;

		break;
		case 9:
			src->settings.selectColor=true;
			src->settings.userColor=0;
			((SimpleButton*)src->widgets[2]->data)->show=false;

			((SimpleButton*) src->widgets[10]->data)->active=false;
			src->widgets[10]->canPush=false;
			src->widgets[9]->canPush=false;
			return SETTINGS_EVENT_UPDATE;
			break;

		case 10:
			src->settings.selectColor=true;
			src->settings.userColor=1;
			((SimpleButton*)src->widgets[2]->data)->show=false;

			((SimpleButton*) src->widgets[10]->data)->active=true;
						((SimpleButton*) src->widgets[9]->data)->active=false;
						src->widgets[10]->canPush=false;
									src->widgets[9]->canPush=false;
						return SETTINGS_EVENT_UPDATE;
						break;
		default:return SETTINGS_EVENT_NONE;
		break;
		break;
	}

	case SDL_WINDOWEVENT:
		if (event->window.event==SDL_WINDOWEVENT_CLOSE) {
				return SETTINGS_EVENT_QUIT;
			}
			break;
		default:
			return SETTINGS_EVENT_NONE;
		}
		return SETTINGS_EVENT_NONE;
}


void settingsWindowHide(SettingsWin* src) {
	SDL_HideWindow(src->window);



}

void settingsWindowShow(SettingsWin* src) {
	SDL_ShowWindow(src->window);



}
