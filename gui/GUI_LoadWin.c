 #include "GUI_LoadWin.h"

LoadWin* loadWinCreate(){
	LoadWin* res = NULL;
	res=(LoadWin*) calloc(sizeof(LoadWin), sizeof(char));
	if (res==NULL){
		return NULL;
	}
	res->window = SDL_CreateWindow("Chess_Game: Load", 	SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 700,600,
					SDL_WINDOW_OPENGL
			);

	if (res->window==NULL ) {
		loadWinDestroy(res);
		printf("Can  not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,SDL_RENDERER_ACCELERATED);
	if (res->renderer==NULL ) {
		loadWinDestroy(res);
		printf("Can not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->widgets= createLoadWinWidgets(res->renderer);
	if (res->widgets==NULL ) {
		loadWinDestroy(res);
		printf("Can not create widgets: %s\n", SDL_GetError());
		return NULL ;
	}
	res->numOfWidgets=7;
	res->first=true;
	res->slot_num=1;
	res->legalload=false;//CheckPath(getFilePath(res->slot_num));
	return res;
}
Widget** createLoadWinWidgets(SDL_Renderer* renderer) {
	if (renderer == NULL ) {
		return NULL ;
	}
	Widget** widgets = calloc(7,sizeof(Widget*));
	if (widgets == NULL ) {
		return NULL ;
	}
	int i;
	SDL_Rect slot1 = { .x =50, .y = 30, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect slot2  = { .x =400, .y = 30, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect slot3 = { .x = 50, .y = 150, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect slot4 = { .x = 400, .y = 150, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect slot5 = { .x = 230, .y = 250, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect back = { .x = 30, .y = 400, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect load = { .x = BUTTON_SHIFT, .y = 690, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };

	widgets[0] = createSB(renderer, &slot1, "./gui/images/buttons/slot1.bmp", "./gui/images/buttons/slot1c.bmp",true);
	widgets[1] = createSB(renderer, &slot2, "./gui/images/buttons/slot2.bmp","./gui/images/buttons/slot2c.bmp",true);
	widgets[2] = createSB(renderer, &slot3, "./gui/images/buttons/slot3.bmp","./gui/images/buttons/slot3c.bmp",true);
	widgets[3] = createSB(renderer, &slot4, "./gui/images/buttons/slot4.bmp","./gui/images/buttons/slot4c.bmp",true);
	widgets[4] = createSB(renderer, &slot5, "./gui/images/buttons/slot5.bmp","./gui/images/buttons/slot5c.bmp",true);
	widgets[5] = createSB(renderer, &back, "./gui/images/buttons/back.bmp",NULL,true);
	widgets[6] = createSB(renderer, &load, "./gui/images/buttons/load.bmp","./gui/images/buttons/loadb.bmp",true);
//Daniel DOnt USE Load Button it will work without!!!
	for(i=0;i<7;i++){
		if(widgets[i]==NULL){
			loadWinWidgetsDestroy(widgets);
			break;
		}
	}
	return widgets;
}
void loadWinDraw(LoadWin* src) {
	int i;
	if(src==NULL){
		return;
	}
	SDL_SetRenderDrawColor(src->renderer, 40, 40, 40, 40);
	SDL_RenderClear(src->renderer);
	for( i=0;i<6;i++){
		src->widgets[i]->canPush=true;
		((SimpleButton*) src->widgets[i]->data)->active=true;

	}

	for (i=0; i < src->numOfWidgets; i++) {
		(src->widgets[i])->drawWidget(src->widgets[i]);
	}
	SDL_RenderPresent(src->renderer);
}
void loadWinDestroy(LoadWin* src) {
	if (!src) {
		return;
	}
	loadWinWidgetsDestroy(src->widgets);

	if (src->renderer != NULL ) {
		SDL_DestroyRenderer(src->renderer);
	}
	if (src->window != NULL ) {
		SDL_DestroyWindow(src->window);
	}
	free(src);
}
bool CheckPath(char* path){
	FILE* file=fopen(path,"r");
	if(file==NULL){
		printf("the file path is illegal\n");
		return false;
	}
	else{
		printf("the file path is legal\n");
		fclose(file);
		return true;
	}
}

void loadWinWidgetsDestroy(Widget** widgets){
	int i;
	for(i=0;i<7;i++){
		if(widgets[i]!=NULL){
			destroyWidget(widgets[i]);
		}
	}
	free(widgets);
}
LOAD_EVENT loadWinHandleEvent(LoadWin* src, SDL_Event* event) {
	if (!event) {
		return LOAD_EVENT_INVALID_ARGUMENT;
	}

	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (src->widgets[0]->handleEvent(src->widgets[0],event)==1) {
			if(CheckPath(SLOT0)){
			src->slot_num=1;
			((SimpleButton*) src->widgets[0]->data)->active=false;
			src->legalload=true;
			return LOAD_EVENT_START;
			}
			const SDL_MessageBoxButtonData buttons[] = { {
						SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "ok" }};
				const SDL_MessageBoxColorScheme colorScheme = { { { 255, 0, 0 },
					{ 0, 255, 0 }, { 255, 255, 0 }, { 0, 0, 255 }, { 255, 0, 255 } } };
				const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION,
							NULL, "EMPTY!",
								"This is empty slot!", SDL_arraysize(
												buttons), buttons, &colorScheme };
								int buttonid;
								SDL_ShowMessageBox(&messageboxdata, &buttonid);
			src->legalload=false;
			return LOAD_EVENT_NONE;
		} else if (src->widgets[1]->handleEvent(src->widgets[1],event)==1){

			if(CheckPath(SLOT1)){
					src->slot_num=2;
					((SimpleButton*) src->widgets[1]->data)->active=false;
					src->legalload=true;
					return LOAD_EVENT_START;
					}
			const SDL_MessageBoxButtonData buttons[] = { {
						SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "ok" }};
				const SDL_MessageBoxColorScheme colorScheme = { { { 255, 0, 0 },
					{ 0, 255, 0 }, { 255, 255, 0 }, { 0, 0, 255 }, { 255, 0, 255 } } };
				const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION,
							NULL, "EMPTY!",
								"This is empty slot!", SDL_arraysize(
												buttons), buttons, &colorScheme };
								int buttonid;
								SDL_ShowMessageBox(&messageboxdata, &buttonid);
					src->legalload=false;
					return LOAD_EVENT_NONE;
		}else if (src->widgets[2]->handleEvent(src->widgets[2],event)==1){
			if(CheckPath(SLOT2)){
				src->slot_num=3;
				((SimpleButton*) src->widgets[2]->data)->active=false;
					src->legalload=true;
					return LOAD_EVENT_START;
					}
			const SDL_MessageBoxButtonData buttons[] = { {
						SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "ok" }};
				const SDL_MessageBoxColorScheme colorScheme = { { { 255, 0, 0 },
					{ 0, 255, 0 }, { 255, 255, 0 }, { 0, 0, 255 }, { 255, 0, 255 } } };
				const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION,
							NULL, "EMPTY!",
								"This is empty slot!", SDL_arraysize(
												buttons), buttons, &colorScheme };
								int buttonid;
								SDL_ShowMessageBox(&messageboxdata, &buttonid);
					src->legalload=false;
					return LOAD_EVENT_NONE;

		}else if (src->widgets[3]->handleEvent(src->widgets[3],event)==1){
			if(CheckPath(SLOT3)){
							src->slot_num=4;
							((SimpleButton*) src->widgets[3]->data)->active=false;
								src->legalload=true;
								return LOAD_EVENT_START;
								}
								src->legalload=false;
			const SDL_MessageBoxButtonData buttons[] = { {
				SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "ok" }};
		const SDL_MessageBoxColorScheme colorScheme = { { { 255, 0, 0 },
			{ 0, 255, 0 }, { 255, 255, 0 }, { 0, 0, 255 }, { 255, 0, 255 } } };
		const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION,
					NULL, "EMPTY!",
					"This is empty slot!", SDL_arraysize(
										buttons), buttons, &colorScheme };
						int buttonid;
						SDL_ShowMessageBox(&messageboxdata, &buttonid);

							return LOAD_EVENT_NONE;
		}else if (src->widgets[4]->handleEvent(src->widgets[4],event)==1){


			if(CheckPath(SLOT4)){
					src->slot_num=5;
							((SimpleButton*) src->widgets[4]->data)->active=false;
								src->legalload=true;
								return LOAD_EVENT_START;
											}
			const SDL_MessageBoxButtonData buttons[] = { {
				SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "ok" }};
		const SDL_MessageBoxColorScheme colorScheme = { { { 255, 0, 0 },
			{ 0, 255, 0 }, { 255, 255, 0 }, { 0, 0, 255 }, { 255, 0, 255 } } };
		const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION,
					NULL, "EMPTY!",
						"This is empty slot!", SDL_arraysize(
										buttons), buttons, &colorScheme };
						int buttonid;
						SDL_ShowMessageBox(&messageboxdata, &buttonid);
											src->legalload=false;
											return LOAD_EVENT_NONE;
			return LOAD_EVENT_UPDATE;
		}else if (src->widgets[5]->handleEvent(src->widgets[5],event)==1){
			return LOAD_EVENT_BACK;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event==SDL_WINDOWEVENT_CLOSE) {
			return LOAD_EVENT_QUIT;
		}
		break;
	default:
		return LOAD_EVENT_NONE;
	}
	return LOAD_EVENT_NONE;
}
char* getFilePath(int slot_num){
	switch(slot_num-1){
	case 0:
		return SLOT0;
	case 1:return SLOT1;
	case 2:return SLOT2;
	case 3:return SLOT3;
	case 4:return SLOT4;
	}
	return NULL;
}

